// BrowserHistory.h : Declaration of the CBrowserHistory

#pragma once
#include "resource.h"       // main symbols
#include "BrowserHistory_i.h"
#include "PageInfo.h"
#include <ShlGuid.h>
#include <ExDispid.h>
#include <MsHTML.h>
#include <map>

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;
using namespace std;

// CBrowserHistory

class ATL_NO_VTABLE CBrowserHistory :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CBrowserHistory, &CLSID_BrowserHistory>,
	public IObjectWithSiteImpl<CBrowserHistory>,
	public IDispatchImpl<IBrowserHistory, &IID_IBrowserHistory, &LIBID_BrowserHistoryLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IDispEventImpl<1, CBrowserHistory, &DIID_DWebBrowserEvents2, &LIBID_SHDocVw, 1, 1>
{
public:
	CBrowserHistory()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_BROWSERHISTORY1)

DECLARE_NOT_AGGREGATABLE(CBrowserHistory)

BEGIN_COM_MAP(CBrowserHistory)
	COM_INTERFACE_ENTRY(IBrowserHistory)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IObjectWithSite)
END_COM_MAP()

BEGIN_SINK_MAP(CBrowserHistory)
	SINK_ENTRY_EX(1, DIID_DWebBrowserEvents2, DISPID_DOWNLOADCOMPLETE, OnDownloadComplete)
	SINK_ENTRY_EX(1, DIID_DWebBrowserEvents2, DISPID_DOCUMENTCOMPLETE, OnDocumentComplete)
END_SINK_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:

	STDMETHOD(SetSite)(IUnknown *pUnkSite);
	void STDMETHODCALLTYPE OnDownloadComplete();
	void STDMETHODCALLTYPE OnDocumentComplete(IDispatch *pDisp, VARIANT *pvarURL);

private:

	void LogPage(IHTMLDocument2 *pDocument);
	bool DirectoryExists(CString directory);
	void CreateUrlFilename(CString *urlFilename, CComBSTR originalUrl);
	CString GuidToCString(GUID pGuid);
	void WritePageToFile(CComBSTR url, IHTMLDocument2* pDocument, CString path);

	CComPtr<IWebBrowser2> m_spWebBrowser;
	BOOL m_fAdvised;
	map<CComBSTR, PageInfo> historyMap;

};

OBJECT_ENTRY_AUTO(__uuidof(BrowserHistory), CBrowserHistory)