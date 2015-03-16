// BrowserHistory.cpp : Implementation of DLL Exports.


#include "stdafx.h"
#include "resource.h"
#include "BrowserHistory_i.h"
#include "dllmain.h"

#include <atlstr.h>
#include <atlbase.h>
#include <ShlObj.h>
#include <ATLComTime.h>

using namespace ATL;

extern class CBrowserHistoryModule _AtlModule;

// Used to determine whether the DLL can be unloaded by OLE.
STDAPI DllCanUnloadNow(void)
{
	return _AtlModule.DllCanUnloadNow();
}

// Returns a class factory to create an object of the requested type.
STDAPI DllGetClassObject(_In_ REFCLSID rclsid, _In_ REFIID riid, _Outptr_ LPVOID* ppv)
{
	return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
}

// DllRegisterServer - Adds entries to the system registry.
STDAPI DllRegisterServer(void)
{
	// registers object, typelib and all interfaces in typelib
	HRESULT hr = _AtlModule.DllRegisterServer();
	return hr;
}

// DllUnregisterServer - Removes entries from the system registry.
STDAPI DllUnregisterServer(void)
{
	HRESULT hr = _AtlModule.DllUnregisterServer();
	return hr;
}

// DllInstall - Adds/Removes entries to the system registry per user per machine.
STDAPI DllInstall(BOOL bInstall, _In_opt_  LPCWSTR pszCmdLine)
{
	HRESULT hr = E_FAIL;
	static const wchar_t szUserSwitch[] = L"user";

	if (pszCmdLine != NULL)
	{
		if (_wcsnicmp(pszCmdLine, szUserSwitch, _countof(szUserSwitch)) == 0)
		{
			ATL::AtlSetPerUserRegistration(true);
		}
	}

	if (bInstall)
	{	
		hr = DllRegisterServer();
		if (FAILED(hr))
		{
			DllUnregisterServer();
		}
	}
	else
	{
		hr = DllUnregisterServer();
	}

	return hr;
}

// BrowserHistory.cpp : Implementation of CBrowserHistory

#include "stdafx.h"
#include "BrowserHistory.h"


// CBrowserHistory

STDMETHODIMP CBrowserHistory::SetSite(IUnknown* pUnkSite)
{
    if (pUnkSite != NULL)
    {
        // Cache the pointer to IWebBrowser2.
        HRESULT hr = pUnkSite->QueryInterface(IID_IWebBrowser2, (void **)&m_spWebBrowser);
        if (SUCCEEDED(hr))
        {
            // Register to sink events from DWebBrowserEvents2.
            hr = DispEventAdvise(m_spWebBrowser);
            if (SUCCEEDED(hr))
            {
                m_fAdvised = TRUE;
            }
        }
    }
    else
    {
        // Unregister event sink.
        if (m_fAdvised)
        {
            DispEventUnadvise(m_spWebBrowser);
            m_fAdvised = FALSE;
        }

        // Release cached pointers and other resources here.
        m_spWebBrowser.Release();
    }
    // Return the base class implementation
    return IObjectWithSiteImpl<CBrowserHistory>::SetSite(pUnkSite);
}

void STDMETHODCALLTYPE CBrowserHistory::OnDownloadComplete()
{
    HRESULT hr = S_OK;

    // Get the current document object from browser...
    CComPtr<IDispatch> spDispDoc;
    hr = m_spWebBrowser->get_Document(&spDispDoc);
    if (SUCCEEDED(hr))
    {
        // ...and query for an HTML document.
        CComQIPtr<IHTMLDocument2> spHTMLDoc = spDispDoc;
        if (spHTMLDoc != NULL)
        {
            LogPage(spHTMLDoc);
        }
    }
}

void STDMETHODCALLTYPE CBrowserHistory::OnDocumentComplete(IDispatch *pDisp, VARIANT *pvarURL)
{
    HRESULT hr = S_OK;

    // Get the current document object from browser...
    CComPtr<IDispatch> spDispDoc;
    hr = m_spWebBrowser->get_Document(&spDispDoc);
    if (SUCCEEDED(hr))
    {
        // ...and query for an HTML document.
        CComQIPtr<IHTMLDocument2> spHTMLDoc = spDispDoc;
        if (spHTMLDoc != NULL)
        {
            LogPage(spHTMLDoc);
        }
    }
}

void CBrowserHistory::LogPage(IHTMLDocument2* pDocument)
{
	HRESULT hr;

	CComBSTR url;
	hr = pDocument->get_URL(& url);
	if(hr == S_OK && url != NULL)
	{
		if((_wcsicmp(L"about:blank", url) == 0) ||
			(_wcsicmp(L"about:tabs", url) == 0))
		{
			return;
		}

		COleDateTime outputDate = COleDateTime::GetCurrentTime();
		CString outputPath;

		// Get the location of LocalAppDataLow
		PWSTR pBuf;
		SHGetKnownFolderPath(FOLDERID_LocalAppDataLow, 0, NULL, &pBuf);
		CString localAppDataLow = pBuf;

		// See if we already have a filename for this URL
		map<CComBSTR, PageInfo>::iterator found = historyMap.find(url);
		if(found != historyMap.end())
		{
			PageInfo entry = found->second;
			COleDateTimeSpan timeSinceWritten = outputDate - entry.lastAccessed;

			// If we wrote to this entry in the last 2 minutes, reuse it.
			if(timeSinceWritten.GetMinutes() < 2)
			{
				outputPath = entry.outputPath;
				entry.lastAccessed = outputDate;
				outputDate = entry.outputDate;
			}
		}
		else
		{
			// Create a filename based on the URL that has filesystem-safe characters
			CString urlFilename;
			CreateUrlFilename(&urlFilename, url);

			// Create a GUID for this file
			GUID guid;
			CoCreateGuid(&guid);
			CString guidString = GuidToCString(guid);

			// Create the actual filename
			outputPath.Format(_T("%s\\BrowserHistory\\%s\\%s_%s.txt"),
				localAppDataLow,
				outputDate.Format(_T("%Y-%m-%d")),
				urlFilename,
				guidString);

			PageInfo newPage;
			newPage.lastAccessed = outputDate;
			newPage.outputDate = outputDate;
			newPage.outputPath = outputPath;
			historyMap[url] = newPage;
		}

		// Ensure the BrowserHistory directory exists
		CString dataPath;
		dataPath.Format(_T("%s\\BrowserHistory"), localAppDataLow);
		if(! DirectoryExists(dataPath))
		{
			CreateDirectory(dataPath, NULL);
		}

		// Ensure that the day-specific directory exists
		dataPath.Format(_T("%s\\BrowserHistory\\%s"),
			localAppDataLow,
			outputDate.Format(_T("%Y-%m-%d")));

		// Create the directory, if it does not exist
		if(! DirectoryExists(dataPath))
		{
			CreateDirectory(dataPath, NULL);
		}

		WritePageToFile(url, pDocument, outputPath);

	}
}

bool CBrowserHistory::DirectoryExists(CString directory)
{
	DWORD dwAttrib = GetFileAttributes(directory);

	return (dwAttrib != INVALID_FILE_ATTRIBUTES && 
			(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

void CBrowserHistory::CreateUrlFilename(CString *urlFilename, CComBSTR originalUrl)
{
	int newSize = originalUrl.Length();
	if(newSize > 100)
	{
		newSize = 100;
	}

	(*urlFilename).Append(originalUrl, newSize);

	// Keep a-z A-Z 0-9. Else, replace with '_'
	for(int currentIndex = 0; currentIndex < newSize; currentIndex++)
	{
		if(
			(((*urlFilename)[currentIndex] >= 'a') && ((*urlFilename)[currentIndex] <= 'z')) ||
			(((*urlFilename)[currentIndex] >= 'A') && ((*urlFilename)[currentIndex] <= 'Z')) ||
			(((*urlFilename)[currentIndex] >= '0') && ((*urlFilename)[currentIndex] <= '9')))
		{
			continue;
		}
		else
		{
			urlFilename->SetAt(currentIndex, '_');
		}
	}
}

CString CBrowserHistory::GuidToCString(GUID guid)
{
    CString str;
    str.Format(_T("%08lx%04x%04x%02x%02x%02x%02x%02x%02x%02x%02x"),
		guid.Data1,
		guid.Data2,
		guid.Data3,
		guid.Data4[0],
		guid.Data4[1],
		guid.Data4[2],
		guid.Data4[3],
		guid.Data4[4],
		guid.Data4[5],
		guid.Data4[6],
		guid.Data4[7]);

    return str;
}

void CBrowserHistory::WritePageToFile(CComBSTR url, IHTMLDocument2* pDocument, CString path)
{
	HRESULT hr;

	IHTMLElement *pBody = NULL;
	hr = pDocument->get_body(&pBody);

	if((hr != S_OK) || (pBody == NULL))
	{
		return;
	}

	CComBSTR documentContent;
	hr = pBody->get_outerText(& documentContent);

	if((hr != S_OK) || (documentContent == NULL))
	{
		return;
	}

	CString outputContent;
	outputContent.Format(_T("Original URL: %s\r\n\r\n%s"),
		url,
		documentContent);

	FILE* outputFile;
	fopen_s(& outputFile, CT2CA(path), "w");
	if(outputFile != NULL)
	{
		fprintf(outputFile, "\xEF\xBB\xBF");
		CT2CA outputString(outputContent, CP_UTF8);
		fprintf(outputFile, "%s", outputString);
		fclose(outputFile);
	}
}