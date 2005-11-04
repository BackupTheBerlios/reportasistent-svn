// MainObject.h : Declaration of the CMainObject

#ifndef __MAINOBJECT_H_
#define __MAINOBJECT_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMainObject
class ATL_NO_VTABLE CMainObject : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMainObject, &CLSID_MainObject>,
	public IDispatchImpl<IMainObject, &IID_IMainObject, &LIBID_REPORTASISTENTLib>
{
public:
	CMainObject()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_MAINOBJECT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMainObject)
	COM_INTERFACE_ENTRY(IMainObject)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IMainObject
public:
	STDMETHOD(get_GetNextInsertElement)(/*[out, retval]*/ InsertElement* *pVal);
};

#endif //__MAINOBJECT_H_
