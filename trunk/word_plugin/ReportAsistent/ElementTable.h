// ElementTable.h : Declaration of the CElementTable

#ifndef __ELEMENTTABLE_H_
#define __ELEMENTTABLE_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CElementTable
class ATL_NO_VTABLE CElementTable : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CElementTable, &CLSID_ElementTable>,
	public IDispatchImpl<IElementTable, &IID_IElementTable, &LIBID_REPORTASISTENTLib>,
	public IDispatchImpl<IInsertElement, &IID_IInsertElement, &LIBID_REPORTASISTENTLib>
{
public:
	CElementTable()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ELEMENTTABLE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CElementTable)
	COM_INTERFACE_ENTRY(IElementTable)
//DEL 	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY2(IInsertElement, IElementTable)
//	COM_INTERFACE_ENTRY(IInsertElement)
END_COM_MAP()

// IElementTable
public:
// IInsertElement
	STDMETHOD(get_elementType)(ElementTypeEnum * pVal)
	{
		if (pVal == NULL) return E_POINTER;

		*pVal = elTable;
			
		return S_OK;
	}
};

#endif //__ELEMENTTABLE_H_
