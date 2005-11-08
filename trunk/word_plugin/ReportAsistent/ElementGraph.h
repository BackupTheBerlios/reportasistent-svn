// ElementGraph.h : Declaration of the CElementGraph

#ifndef __ELEMENTGRAPH_H_
#define __ELEMENTGRAPH_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CElementGraph
class ATL_NO_VTABLE CElementGraph : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CElementGraph, &CLSID_ElementGraph>,
	public IDispatchImpl<IElementGraph, &IID_IElementGraph, &LIBID_REPORTASISTENTLib>,
	public IDispatchImpl<IInsertElement, &IID_IInsertElement, &LIBID_REPORTASISTENTLib>
{
public:
	CElementGraph()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ELEMENTGRAPH)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CElementGraph)
	COM_INTERFACE_ENTRY(IElementGraph)
//DEL 	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY2(IInsertElement, IElementGraph)
//	COM_INTERFACE_ENTRY(IInsertElement) zakomentoval honza a vymenil IDipatch za IInsertElement v radku nad
END_COM_MAP()

// IElementGraph
public:
	STDMETHOD(get_graphType)(/*[out, retval]*/ enum XlChartType *pVal);
	STDMETHOD(get_Cells_dy)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_Cells_dx)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_Cells)(long x, long y, /*[out, retval]*/ VARIANT *pVal);
// IInsertElement
	STDMETHOD(get_elementType)(ElementTypeEnum * pVal)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState())
		if (pVal == NULL) return E_POINTER;

		*pVal = elGraph;

		return S_OK;
	}
};

#endif //__ELEMENTGRAPH_H_
