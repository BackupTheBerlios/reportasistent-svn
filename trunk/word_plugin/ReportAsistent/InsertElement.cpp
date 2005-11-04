// InsertElement.cpp : Implementation of CInsertElement
#include "stdafx.h"
#include "ReportAsistent.h"
#include "InsertElement.h"

/////////////////////////////////////////////////////////////////////////////
// CInsertElement


STDMETHODIMP CInsertElement::get_elementType(ElementTypeEnum *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = elNothing;

	return S_OK;
}
