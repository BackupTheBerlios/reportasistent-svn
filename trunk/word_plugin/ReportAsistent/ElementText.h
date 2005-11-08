// ElementText.h : Declaration of the CElementText

#ifndef __ELEMENTTEXT_H_
#define __ELEMENTTEXT_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CElementText
class ATL_NO_VTABLE CElementText : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CElementText, &CLSID_ElementText>,
	public IDispatchImpl<IElementText, &IID_IElementText, &LIBID_REPORTASISTENTLib>,
	public IDispatchImpl<IInsertElement, &IID_IInsertElement, &LIBID_REPORTASISTENTLib>
{
public:
	CElementText()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ELEMENTTEXT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CElementText)
	COM_INTERFACE_ENTRY(IElementText)
//DEL 	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY2(IInsertElement, IElementText)
//	COM_INTERFACE_ENTRY(IInsertElement)
END_COM_MAP()

// IElementText
public:
// IInsertElement
	STDMETHOD(get_elementType)(ElementTypeEnum * pVal)
	{
		if (pVal == NULL) return E_POINTER;

		*pVal = elText;
			
		return S_OK;
	}
};

#endif //__ELEMENTTEXT_H_
