// InsertElement.h : Declaration of the CInsertElement

#ifndef __INSERTELEMENT_H_
#define __INSERTELEMENT_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CInsertElement
class ATL_NO_VTABLE CInsertElement : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CInsertElement, &CLSID_InsertElement>,
	public IDispatchImpl<IInsertElement, &IID_IInsertElement, &LIBID_REPORTASISTENTLib>
{
public:
	CInsertElement()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_INSERTELEMENT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CInsertElement)
	COM_INTERFACE_ENTRY(IInsertElement)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IInsertElement
public:
	STDMETHOD(get_elementType)(/*[out, retval]*/ ElementTypeEnum *pVal);
};

#endif //__INSERTELEMENT_H_
