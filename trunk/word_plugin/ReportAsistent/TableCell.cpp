// TableCell.cpp : Implementation of CTableCell
#include "stdafx.h"
#include "ReportAsistent.h"
#include "TableCell.h"

/////////////////////////////////////////////////////////////////////////////
// CTableCell


STDMETHODIMP CTableCell::get_Content(InsertElement **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (pVal == NULL) return E_POINTER;

	*pVal = m_Content;

	return S_OK;
}

void CTableCell::Init(InsertElement *iContent)
{
	m_Content = iContent;
}
