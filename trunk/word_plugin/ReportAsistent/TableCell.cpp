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

STDMETHODIMP CTableCell::get_BackgroundPatternColor(enum WdColor *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (pVal == NULL) return E_POINTER;

	* pVal = (enum WdColor) RGB(156 + rand()%100, 156 + rand()%100, 255);

	return S_OK;
}
