// ElementText.cpp : Implementation of CElementText
#include "stdafx.h"
#include "ReportAsistent.h"
#include "ElementText.h"

/////////////////////////////////////////////////////////////////////////////
// CElementText


STDMETHODIMP CElementText::get_Text(BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (pVal == NULL) return E_POINTER;

	*pVal = m_text.AllocSysString();

	return S_OK;
}

void CElementText::Init(LPCTSTR s)
{
	m_text = s;
}

IElementText * CElementText::Create(LPCTSTR s)
{
	CComPtr <IElementText> cp;

	cp.CoCreateInstance(CLSID_ElementText);
	((CElementText *) cp.p)->Init(s);

	return cp.Detach();
}
