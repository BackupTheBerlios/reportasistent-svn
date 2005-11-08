// MainObject.cpp : Implementation of CMainObject
#include "stdafx.h"
#include "ReportAsistent.h"
#include "MainObject.h"
#include "ElementGraph.h"
#include "ElementText.h"

/////////////////////////////////////////////////////////////////////////////
// CMainObject

STDMETHODIMP CMainObject::get_GetNextInsertElement(InsertElement **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (pVal == NULL) return E_POINTER;

	CComPtr <IInsertElement> cp;

//	cp.CoCreateInstance(CLSID_ElementText);
	cp.CoCreateInstance(CLSID_ElementCompound);

	*pVal = (InsertElement *) cp.Detach();

//	CElementText * ro = (CElementText *) *pVal;

//	ro->Init("ahoj tak tady je ten textik");

	
//ElementGraph pouze docastne
/*	cp.CoCreateInstance(CLSID_ElementGraph);

	*pVal = (InsertElement *) cp.Detach();

	CElementGraph * ro = (CElementGraph *) *pVal;
*/
// primy pristup k tride CElementGraph
//	ro->m_hlaska = "nastvil jsem to z Cmain::get_Return_object";


	return S_OK;
}
