/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Nov 04 16:27:20 2005
 */
/* Compiler settings for D:\LM\WORD_PLUGIN\ReportAsistent\ReportAsistent.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __ReportAsistent_h__
#define __ReportAsistent_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IInsertElement_FWD_DEFINED__
#define __IInsertElement_FWD_DEFINED__
typedef interface IInsertElement IInsertElement;
#endif 	/* __IInsertElement_FWD_DEFINED__ */


#ifndef __InsertElement_FWD_DEFINED__
#define __InsertElement_FWD_DEFINED__

#ifdef __cplusplus
typedef class InsertElement InsertElement;
#else
typedef struct InsertElement InsertElement;
#endif /* __cplusplus */

#endif 	/* __InsertElement_FWD_DEFINED__ */


#ifndef __IMainObject_FWD_DEFINED__
#define __IMainObject_FWD_DEFINED__
typedef interface IMainObject IMainObject;
#endif 	/* __IMainObject_FWD_DEFINED__ */


#ifndef __IElementGraph_FWD_DEFINED__
#define __IElementGraph_FWD_DEFINED__
typedef interface IElementGraph IElementGraph;
#endif 	/* __IElementGraph_FWD_DEFINED__ */


#ifndef __MainObject_FWD_DEFINED__
#define __MainObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class MainObject MainObject;
#else
typedef struct MainObject MainObject;
#endif /* __cplusplus */

#endif 	/* __MainObject_FWD_DEFINED__ */


#ifndef __ElementGraph_FWD_DEFINED__
#define __ElementGraph_FWD_DEFINED__

#ifdef __cplusplus
typedef class ElementGraph ElementGraph;
#else
typedef struct ElementGraph ElementGraph;
#endif /* __cplusplus */

#endif 	/* __ElementGraph_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __REPORTASISTENTLib_LIBRARY_DEFINED__
#define __REPORTASISTENTLib_LIBRARY_DEFINED__

/* library REPORTASISTENTLib */
/* [helpstring][version][uuid] */ 

typedef /* [public][public] */ 
enum __MIDL___MIDL_itf_ReportAsistent_0000_0001
    {	elTable	= 0,
	elGraph	= elTable + 1,
	elText	= elGraph + 1,
	elParagraph	= elText + 1,
	elNothing	= elParagraph + 1
    }	ElementTypeEnum;


EXTERN_C const IID LIBID_REPORTASISTENTLib;

#ifndef __IInsertElement_INTERFACE_DEFINED__
#define __IInsertElement_INTERFACE_DEFINED__

/* interface IInsertElement */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IInsertElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F5EBE35B-1ABC-4F40-81AE-0D5D692BFDCC")
    IInsertElement : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_elementType( 
            /* [retval][out] */ ElementTypeEnum __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInsertElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IInsertElement __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IInsertElement __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IInsertElement __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IInsertElement __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IInsertElement __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IInsertElement __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IInsertElement __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_elementType )( 
            IInsertElement __RPC_FAR * This,
            /* [retval][out] */ ElementTypeEnum __RPC_FAR *pVal);
        
        END_INTERFACE
    } IInsertElementVtbl;

    interface IInsertElement
    {
        CONST_VTBL struct IInsertElementVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInsertElement_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInsertElement_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInsertElement_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInsertElement_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInsertElement_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInsertElement_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInsertElement_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInsertElement_get_elementType(This,pVal)	\
    (This)->lpVtbl -> get_elementType(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInsertElement_get_elementType_Proxy( 
    IInsertElement __RPC_FAR * This,
    /* [retval][out] */ ElementTypeEnum __RPC_FAR *pVal);


void __RPC_STUB IInsertElement_get_elementType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInsertElement_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_InsertElement;

#ifdef __cplusplus

class DECLSPEC_UUID("399FF362-6189-48A0-90A3-DC4AE0AF0E41")
InsertElement;
#endif

#ifndef __IMainObject_INTERFACE_DEFINED__
#define __IMainObject_INTERFACE_DEFINED__

/* interface IMainObject */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMainObject;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("528746CB-465B-4DC2-9758-54EF90E93253")
    IMainObject : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_GetNextInsertElement( 
            /* [retval][out] */ InsertElement	__RPC_FAR *__RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMainObjectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMainObject __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMainObject __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMainObject __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IMainObject __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IMainObject __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IMainObject __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IMainObject __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GetNextInsertElement )( 
            IMainObject __RPC_FAR * This,
            /* [retval][out] */ InsertElement	__RPC_FAR *__RPC_FAR *pVal);
        
        END_INTERFACE
    } IMainObjectVtbl;

    interface IMainObject
    {
        CONST_VTBL struct IMainObjectVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMainObject_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMainObject_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMainObject_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMainObject_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMainObject_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMainObject_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMainObject_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMainObject_get_GetNextInsertElement(This,pVal)	\
    (This)->lpVtbl -> get_GetNextInsertElement(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMainObject_get_GetNextInsertElement_Proxy( 
    IMainObject __RPC_FAR * This,
    /* [retval][out] */ InsertElement	__RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IMainObject_get_GetNextInsertElement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMainObject_INTERFACE_DEFINED__ */


#ifndef __IElementGraph_INTERFACE_DEFINED__
#define __IElementGraph_INTERFACE_DEFINED__

/* interface IElementGraph */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IElementGraph;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F6EE1307-8A05-4191-B301-BBA75309C5F9")
    IElementGraph : public IInsertElement
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IElementGraphVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IElementGraph __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IElementGraph __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IElementGraph __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IElementGraph __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IElementGraph __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IElementGraph __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IElementGraph __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_elementType )( 
            IElementGraph __RPC_FAR * This,
            /* [retval][out] */ ElementTypeEnum __RPC_FAR *pVal);
        
        END_INTERFACE
    } IElementGraphVtbl;

    interface IElementGraph
    {
        CONST_VTBL struct IElementGraphVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IElementGraph_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IElementGraph_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IElementGraph_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IElementGraph_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IElementGraph_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IElementGraph_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IElementGraph_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IElementGraph_get_elementType(This,pVal)	\
    (This)->lpVtbl -> get_elementType(This,pVal)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IElementGraph_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_MainObject;

#ifdef __cplusplus

class DECLSPEC_UUID("6775171E-053A-4C35-842D-EED56C4B3531")
MainObject;
#endif

EXTERN_C const CLSID CLSID_ElementGraph;

#ifdef __cplusplus

class DECLSPEC_UUID("286AE5CF-B993-4B21-A82D-E1A376176EE1")
ElementGraph;
#endif
#endif /* __REPORTASISTENTLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
