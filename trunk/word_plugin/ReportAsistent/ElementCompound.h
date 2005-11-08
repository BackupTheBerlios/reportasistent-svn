// ElementCompound.h : Declaration of the CElementCompound

#ifndef __ELEMENTCOMPOUND_H_
#define __ELEMENTCOMPOUND_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CElementCompound
class ATL_NO_VTABLE CElementCompound : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CElementCompound, &CLSID_ElementCompound>,
	public IDispatchImpl<IElementCompound, &IID_IElementCompound, &LIBID_REPORTASISTENTLib>,
	public IDispatchImpl<IInsertElement, &IID_IInsertElement, &LIBID_REPORTASISTENTLib>
{
public:
	CElementCompound()
		: test_call_cnt(0)
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ELEMENTCOMPOUND)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CElementCompound)
	COM_INTERFACE_ENTRY(IElementCompound)
//DEL 	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY2(IInsertElement, IElementCompound)
//	COM_INTERFACE_ENTRY(IInsertElement)
END_COM_MAP()

// IElementCompound
public:
	STDMETHOD(get_continueInserting)(/*[out, retval]*/ BOOL *pVal);
	STDMETHOD(get_GetNextInsertElement)(/*[out, retval]*/ InsertElement * *pVal);
// IInsertElement
	STDMETHOD(get_elementType)(ElementTypeEnum * pVal)
	{
		if (pVal == NULL) return E_POINTER;

		*pVal = elCompound;
			
		return S_OK;
	}
private:
	int test_call_cnt;
};

#endif //__ELEMENTCOMPOUND_H_
