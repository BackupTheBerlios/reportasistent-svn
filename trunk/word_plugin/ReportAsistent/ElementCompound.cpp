// ElementCompound.cpp : Implementation of CElementCompound
#include "stdafx.h"
#include "ReportAsistent.h"
#include "ElementCompound.h"
#include "ElementText.h"

/////////////////////////////////////////////////////////////////////////////
// CElementCompound


STDMETHODIMP CElementCompound::get_GetNextInsertElement(InsertElement **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (pVal == NULL) return E_POINTER;

	CComPtr <IInsertElement> cp;

	if (test_call_cnt++ == 2)
	{
		cp.CoCreateInstance(CLSID_ElementTable);
		*pVal = (InsertElement *) cp.Detach();
		return S_OK;
	}

	if (test_call_cnt == 5)
	{
		cp.CoCreateInstance(CLSID_ElementGraph);
		*pVal = (InsertElement *) cp.Detach();
		return S_OK;
	}

	cp.CoCreateInstance(CLSID_ElementText);

	*pVal = (InsertElement *) cp.Detach();

	CElementText * ro = (CElementText *) *pVal;

	CString s;
	s.Format("ahoj tak tady je ten textik c%d*", test_call_cnt);
	ro->Init(s);


	return S_OK;
}

STDMETHODIMP CElementCompound::get_continueInserting(BOOL *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (pVal == NULL) return E_POINTER;

	*pVal = test_call_cnt < 7;

	return S_OK;
}
