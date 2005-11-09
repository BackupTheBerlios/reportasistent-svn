// ElementGraph.cpp : Implementation of CElementGraph
#include "stdafx.h"
#include "ReportAsistent.h"
#include "ElementGraph.h"

/////////////////////////////////////////////////////////////////////////////
// CElementGraph


STDMETHODIMP CElementGraph::get_Cells(long x, long y, VARIANT *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (pVal == NULL) return E_POINTER;


	long dx=0, dy=0;

	get_Cells_dx(& dx);
	get_Cells_dy(& dy);



	
	// vrati prazdnou hodnotu
	if (
		((x==0) && (y==0)) ||
		(x >= dx) ||
		(y >= dy) ||
		(x < 0) ||
		(y < 0))
	{
		CComVariant prazdna;
		prazdna.Detach(pVal);

		return S_OK;
	}

	if (y == 0) // prvni radek je popis sloupce
	{
		CString s;
		s.Format("sl. %d", x);
		CComVariant v(s);
		v.Detach(pVal);

		return S_OK;
	}

	if (x == 0) // prvni sloupec je nazev grafu (legenda)
	{
		CString s;
		s.Format("graf c. %d", y);
		CComVariant v(s);
		v.Detach(pVal);

		return S_OK;
	}
		
	// uz zbyly jen hodnoty
	CComVariant v(x + y*3);
	v.Detach(pVal);

	return S_OK;
}

STDMETHODIMP CElementGraph::get_Cells_dx(long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (pVal == NULL) return E_POINTER;

	* pVal = 10;

	return S_OK;
}

STDMETHODIMP CElementGraph::get_Cells_dy(long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (pVal == NULL) return E_POINTER;

	* pVal = 2;

	return S_OK;
}

STDMETHODIMP CElementGraph::get_graphType(enum XlChartType *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (pVal == NULL) return E_POINTER;

	RGB(0,0,0);

	* pVal =  xlPie;

	return S_OK;
}
