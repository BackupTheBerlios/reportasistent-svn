// MainObject.cpp : Implementation of CMainObject
#include "stdafx.h"
#include "ReportAsistent.h"
#include "MainObject.h"
#include "ElementGraph.h"

/////////////////////////////////////////////////////////////////////////////
// CMainObject

STDMETHODIMP CMainObject::get_GetNextInsertElement(InsertElement **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	CComPtr <IInsertElement> cp;

//ElementGraph pouze docastne
	cp.CoCreateInstance(CLSID_ElementGraph);

	*pVal = (InsertElement *) cp.Detach();

	CElementGraph * ro = (CElementGraph *) *pVal;

// primy pristup k tride CElementGraph
//	ro->m_hlaska = "nastvil jsem to z Cmain::get_Return_object";


	return S_OK;
}
