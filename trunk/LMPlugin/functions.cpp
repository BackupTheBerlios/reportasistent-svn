// implementace funkci pro vyrizeni pozadavku na AP v zasuvce pro LM
// functions.h
#include "functions.h"


// --- AP Kategorie

CString fLMCategory(void* hSource)
{
	// prozatimni zkusebni - TODO
	return CString("<seznam><kategorie name=\"prvni kategorie\"/><kategorie name=\"druha kategorie\"/></seznam>");
}








//dedek: docasne
/*****/
//Deda: potreba pro MSXML - potreba pro muj testovci vystup jinak (az bude lesi vystup) mozno smazat
#include <afxdb.h>

#import <msxml3.dll>
using namespace MSXML2;
//vlozi namespace MSXML2;


//dedek: testovaci vystup neni to moc usetreny tak bacha :)
BOOL dedek_performLM(void * hSource, const char* AP, BSTR* result)
{
	CDatabase * db = (CDatabase *) hSource;

	CString ft = AP;

	if (ft != "hyp_4ft") return FALSE;

	IXMLDOMDocumentPtr dom;
	dom.CreateInstance(_T("Msxml2.DOMDocument"));
	dom->async = VARIANT_FALSE; // default - true,
	
	dom->load((LPCTSTR) _T("../XML/4ft_hyp.xml"));

	IXMLDOMElementPtr el_hyp = dom->selectSingleNode("/active_list/hyp_4ft");

	el_hyp->setAttribute("db_name", (LPCTSTR) db->GetDatabaseName());

	* result = dom->xml;

	return TRUE;
}

/****/



// --- AP 4ft-hypoteza

CString fLM4fthyp(void* hSource)
{
	// prozatimni zkusebni - TODO
	//return CString("<seznam><4fthyp name=\"prvni 4fthyp\"/><4fthyp name=\"druha 4fthyp\"/></seznam>");

	BSTR result;
	dedek_performLM( hSource, "hyp_4ft", &result );

	return (CString) result;
}



