// ElementTable.cpp : Implementation of CElementTable
#include "stdafx.h"
#include "ReportAsistent.h"
#include "ElementTable.h"
#include "TableCell.h"
#include "ElementText.h"

/////////////////////////////////////////////////////////////////////////////
// CElementTable


STDMETHODIMP CElementTable::get_Cells_dx(long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (pVal == NULL) return E_POINTER;

	*pVal = 5;

	return S_OK;
}

STDMETHODIMP CElementTable::get_Cells_dy(long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (pVal == NULL) return E_POINTER;

	*pVal = 7;

	return S_OK;
}

STDMETHODIMP CElementTable::get_Cells(long x, long y, TableCell **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (pVal == NULL) return E_POINTER;

	long dx=0, dy=0;

	get_Cells_dx(& dx);
	get_Cells_dy(& dy);

	if (
		(x < 0) ||
		(y < 0) ||
		(x >= dx) ||
		(y >= dy))
	{
		*pVal = NULL;
		return S_OK;
	}

	CComPtr <ITableCell> pt_tc;

//	cp.CoCreateInstance(CLSID_ElementText);
	pt_tc.CoCreateInstance(CLSID_TableCell);

	*pVal = (TableCell *) pt_tc.Detach();

	CString s;
	s.Format("%d:%d", x, y);

	((CTableCell *) *pVal)->Init((InsertElement *) CElementText::Create(s));


	return S_OK;
}
