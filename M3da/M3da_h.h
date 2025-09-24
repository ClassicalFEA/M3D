

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0628 */
/* at Tue Jan 19 04:14:07 2038
 */
/* Compiler settings for M3da.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0628 
    protocol : all , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */


#ifndef __M3da_h_h__
#define __M3da_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef DECLSPEC_XFGVIRT
#if defined(_CONTROL_FLOW_GUARD_XFG)
#define DECLSPEC_XFGVIRT(base, func) __declspec(xfg_virtual(base, func))
#else
#define DECLSPEC_XFGVIRT(base, func)
#endif
#endif

/* Forward Declarations */ 

#ifndef __IM3da_FWD_DEFINED__
#define __IM3da_FWD_DEFINED__
typedef interface IM3da IM3da;

#endif 	/* __IM3da_FWD_DEFINED__ */


#ifndef __CM3daDoc_FWD_DEFINED__
#define __CM3daDoc_FWD_DEFINED__

#ifdef __cplusplus
typedef class CM3daDoc CM3daDoc;
#else
typedef struct CM3daDoc CM3daDoc;
#endif /* __cplusplus */

#endif 	/* __CM3daDoc_FWD_DEFINED__ */


#ifndef __IDBase_FWD_DEFINED__
#define __IDBase_FWD_DEFINED__
typedef interface IDBase IDBase;

#endif 	/* __IDBase_FWD_DEFINED__ */


#ifndef __DBase_FWD_DEFINED__
#define __DBase_FWD_DEFINED__

#ifdef __cplusplus
typedef class DBase DBase;
#else
typedef struct DBase DBase;
#endif /* __cplusplus */

#endif 	/* __DBase_FWD_DEFINED__ */


#ifndef __IObject_FWD_DEFINED__
#define __IObject_FWD_DEFINED__
typedef interface IObject IObject;

#endif 	/* __IObject_FWD_DEFINED__ */


#ifndef __G_Object_FWD_DEFINED__
#define __G_Object_FWD_DEFINED__

#ifdef __cplusplus
typedef class G_Object G_Object;
#else
typedef struct G_Object G_Object;
#endif /* __cplusplus */

#endif 	/* __G_Object_FWD_DEFINED__ */


#ifndef __IME_Object_FWD_DEFINED__
#define __IME_Object_FWD_DEFINED__
typedef interface IME_Object IME_Object;

#endif 	/* __IME_Object_FWD_DEFINED__ */


#ifndef __ME_Object_FWD_DEFINED__
#define __ME_Object_FWD_DEFINED__

#ifdef __cplusplus
typedef class ME_Object ME_Object;
#else
typedef struct ME_Object ME_Object;
#endif /* __cplusplus */

#endif 	/* __ME_Object_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __M3da_LIBRARY_DEFINED__
#define __M3da_LIBRARY_DEFINED__

/* library M3da */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_M3da;

#ifndef __IM3da_DISPINTERFACE_DEFINED__
#define __IM3da_DISPINTERFACE_DEFINED__

/* dispinterface IM3da */
/* [uuid] */ 


EXTERN_C const IID DIID_IM3da;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("D0A70CB8-1A81-462F-9171-84EFAB11DD21")
    IM3da : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IM3daVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IM3da * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IM3da * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IM3da * This);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfoCount)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IM3da * This,
            /* [out] */ UINT *pctinfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfo)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IM3da * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetIDsOfNames)
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IM3da * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        DECLSPEC_XFGVIRT(IDispatch, Invoke)
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IM3da * This,
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
    } IM3daVtbl;

    interface IM3da
    {
        CONST_VTBL struct IM3daVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IM3da_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IM3da_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IM3da_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IM3da_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IM3da_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IM3da_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IM3da_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IM3da_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CM3daDoc;

#ifdef __cplusplus

class DECLSPEC_UUID("A7226713-7CA7-4243-8B24-4C7AA36D1FA3")
CM3daDoc;
#endif

#ifndef __IDBase_DISPINTERFACE_DEFINED__
#define __IDBase_DISPINTERFACE_DEFINED__

/* dispinterface IDBase */
/* [uuid] */ 


EXTERN_C const IID DIID_IDBase;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("45542F2E-3541-4330-9BE0-A4B59B3D392C")
    IDBase : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDBaseVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDBase * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDBase * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDBase * This);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfoCount)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDBase * This,
            /* [out] */ UINT *pctinfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfo)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDBase * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetIDsOfNames)
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDBase * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        DECLSPEC_XFGVIRT(IDispatch, Invoke)
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDBase * This,
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
    } IDBaseVtbl;

    interface IDBase
    {
        CONST_VTBL struct IDBaseVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDBase_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDBase_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDBase_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDBase_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IDBase_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IDBase_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IDBase_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDBase_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_DBase;

#ifdef __cplusplus

class DECLSPEC_UUID("D619E744-24BA-46CF-9DF3-4E44AEBA447B")
DBase;
#endif

#ifndef __IObject_DISPINTERFACE_DEFINED__
#define __IObject_DISPINTERFACE_DEFINED__

/* dispinterface IObject */
/* [uuid] */ 


EXTERN_C const IID DIID_IObject;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("2EC99D19-8632-44E0-A22E-294CFB4F5D61")
    IObject : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IObjectVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IObject * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IObject * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IObject * This);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfoCount)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IObject * This,
            /* [out] */ UINT *pctinfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfo)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IObject * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetIDsOfNames)
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IObject * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        DECLSPEC_XFGVIRT(IDispatch, Invoke)
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IObject * This,
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
    } IObjectVtbl;

    interface IObject
    {
        CONST_VTBL struct IObjectVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IObject_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IObject_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IObject_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IObject_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IObject_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IObject_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IObject_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IObject_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_G_Object;

#ifdef __cplusplus

class DECLSPEC_UUID("50FB7579-3C0F-4B23-BF30-F9C88B31C307")
G_Object;
#endif

#ifndef __IME_Object_DISPINTERFACE_DEFINED__
#define __IME_Object_DISPINTERFACE_DEFINED__

/* dispinterface IME_Object */
/* [uuid] */ 


EXTERN_C const IID DIID_IME_Object;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("190D2974-17B6-4295-A4C5-08FA06FC6CD9")
    IME_Object : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IME_ObjectVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IME_Object * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IME_Object * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IME_Object * This);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfoCount)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IME_Object * This,
            /* [out] */ UINT *pctinfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfo)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IME_Object * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetIDsOfNames)
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IME_Object * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        DECLSPEC_XFGVIRT(IDispatch, Invoke)
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IME_Object * This,
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
    } IME_ObjectVtbl;

    interface IME_Object
    {
        CONST_VTBL struct IME_ObjectVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IME_Object_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IME_Object_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IME_Object_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IME_Object_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IME_Object_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IME_Object_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IME_Object_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IME_Object_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_ME_Object;

#ifdef __cplusplus

class DECLSPEC_UUID("7C1C0A34-5974-452F-96E7-DB7F46412B29")
ME_Object;
#endif
#endif /* __M3da_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


