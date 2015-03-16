

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0595 */
/* at Wed Nov 26 12:50:53 2014
 */
/* Compiler settings for BrowserHistory.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0595 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __BrowserHistory_i_h__
#define __BrowserHistory_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IBrowserHistory_FWD_DEFINED__
#define __IBrowserHistory_FWD_DEFINED__
typedef interface IBrowserHistory IBrowserHistory;

#endif 	/* __IBrowserHistory_FWD_DEFINED__ */


#ifndef __BrowserHistory_FWD_DEFINED__
#define __BrowserHistory_FWD_DEFINED__

#ifdef __cplusplus
typedef class BrowserHistory BrowserHistory;
#else
typedef struct BrowserHistory BrowserHistory;
#endif /* __cplusplus */

#endif 	/* __BrowserHistory_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IBrowserHistory_INTERFACE_DEFINED__
#define __IBrowserHistory_INTERFACE_DEFINED__

/* interface IBrowserHistory */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IBrowserHistory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("064CF2A7-4DD0-40EB-A9D4-851DD6F17606")
    IBrowserHistory : public IDispatch
    {
    public:
    };
    
    
#else 	/* C style interface */

    typedef struct IBrowserHistoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBrowserHistory * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBrowserHistory * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBrowserHistory * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IBrowserHistory * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IBrowserHistory * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IBrowserHistory * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IBrowserHistory * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } IBrowserHistoryVtbl;

    interface IBrowserHistory
    {
        CONST_VTBL struct IBrowserHistoryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBrowserHistory_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IBrowserHistory_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IBrowserHistory_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IBrowserHistory_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IBrowserHistory_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IBrowserHistory_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IBrowserHistory_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IBrowserHistory_INTERFACE_DEFINED__ */



#ifndef __BrowserHistoryLib_LIBRARY_DEFINED__
#define __BrowserHistoryLib_LIBRARY_DEFINED__

/* library BrowserHistoryLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_BrowserHistoryLib;

EXTERN_C const CLSID CLSID_BrowserHistory;

#ifdef __cplusplus

class DECLSPEC_UUID("C3FEAD02-C2A9-4BFE-B545-B5A78E3E41FF")
BrowserHistory;
#endif
#endif /* __BrowserHistoryLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


