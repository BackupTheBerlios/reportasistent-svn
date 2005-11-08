// TableCell.h : Declaration of the CTableCell

#ifndef __TABLECELL_H_
#define __TABLECELL_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTableCell
class ATL_NO_VTABLE CTableCell : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTableCell, &CLSID_TableCell>,
	public IDispatchImpl<ITableCell, &IID_ITableCell, &LIBID_REPORTASISTENTLib>
{
public:
	CTableCell()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_TABLECELL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTableCell)
	COM_INTERFACE_ENTRY(ITableCell)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// ITableCell
public:
};

#endif //__TABLECELL_H_
