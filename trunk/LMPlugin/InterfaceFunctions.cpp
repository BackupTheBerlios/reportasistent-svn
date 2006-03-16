#include <afx.h>
#include <afxdb.h>
#include "SockInterface.h"
//#include "tiHypothesis_Recordset.h"
#include "SQL_pomocnik.h"
#include "InterfaceFunctions.h"
#include "LMPlugin.h"



// ---------- performLM 

/* dalsi testovaci verze nize
BOOL performLM(hSource_t hSource, const char* APName, BSTR* Result)
{
	/*

  //Dedovo pomocna zkusebni verze

	CDatabase * db = (CDatabase *) hSource;

	* result = NULL;

	CtiHypothesis_Recordset rs(db);

	if (rs.Open())
	{

		CString buf;
		CString line;

		// postupne tiskne nactene radky
		while (!rs.IsEOF())
		{
			line.Format("ID: %5d Ord: %5d\tA: %5d\tB: %5d\tC: %5d\tD: %5d\tWeight: %f" EDIT_NEWLINE, 
				rs.m_HypothesisID,
				rs.m_Ord,
				rs.m_FreqA,
				rs.m_FreqB,
				rs.m_FreqC,
				rs.m_FreqD,
				rs.m_Weight);

			buf += line;
			rs.MoveNext();
		}

		rs.Close();
		
		* result = buf.AllocSysString();
		return TRUE;
	}


	return FALSE;
	
	
	*/
	
	/*
	
	CString CStrResult; // mezivysledek CString
	pFn_t pFn = LMSock.getFnAddress(APName);	// ukazatel na funkci, ktera vyridi pozadavek
	if (pFn == NULL) // chyba - neexistuje funkce vyrizujici tento AP
		return FALSE;
	CStrResult = pFn(hSource);
	*Result =  CStrResult.AllocSysString();
	return TRUE;
}
*/

//Deda: potreba pro MSXML - potreba pro muj testovci vystup jinak (az bude lesi vystup) mozno smazat
#import <msxml3.dll>
using namespace MSXML2;
//vlozi namespace MSXML2;


//dedek: testovaci vystup neni to moc usetreny tak bacha :)
BOOL performLM(hSource_t hSource, const char* AP, BSTR* result)
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




// ---------- getAPListLM

BSTR getAPListLM()
{
	CString CStrResult = LMSock.getAPList();
	BSTR Result = CStrResult.AllocSysString();
	return Result;
}


///// funkce rozhrani pro praci se zdroji

// ---------- fNewSourceLM

hSource_t fNewSourceLM(PersistID_t * pPerzistID)
{
	CDatabase * db;
	SQL_Pomocnik pom;

	CString s;

	 * pPerzistID = NULL;

	if (! pom.FindAccesDatasource(s)) return NULL;

	db = new CDatabase();
	if (!db->Open(NULL, FALSE, TRUE, _T("ODBC;DSN=" + s), TRUE))
	{
		delete db;
		return NULL;
	}

	* pPerzistID = db->GetConnect().AllocSysString();
	return db;
}


// ---------- fOpenSourceLM

hSource_t fOpenSourceLM(PersistID_t PerzistID)
{
	CString connn_str = PerzistID;

	CDatabase * db;
	
	db = new CDatabase();


	if (!db->Open(NULL, FALSE, TRUE, connn_str, TRUE))
	{
		delete db;
		return NULL;
	}
	
	return db;
}


// ---------- fCloseSourceLM

BOOL fCloseSourceLM(hSource_t hSource)
{
	if (hSource == NULL) return FALSE;
	
	CDatabase * db = (CDatabase *) hSource;

	db->Close();

	delete db;

	return TRUE;
}

/*

CSockInterface i =
{
	Perform, //	 hPerform;
	NULL, //	 hGetAPList;
	NewSource,
	OpenSource,
	CloseSource	 
};


BOOL Otestuj()
{
	hSource_t h;
	PersistID_t pid;
	BSTR result = NULL;



	h = i.hNewSource(& pid);	
	if (h == NULL) return FALSE;

	
	//BOOL Perform(hSource_t hSource, const char* AP, BSTR* result)
	if (i.hPerform(h, NULL, & result))
	{
		CString r = result;
		SysFreeString(result);
		AfxMessageBox(r, 0, 0);
	}

	
	if (! i.hCloseSource(h)) return FALSE;

	

	h = i.hOpenSource(pid);
	if (h == NULL) return FALSE;


	if (i.hPerform(h, NULL, & result))
	{
		CString r = result;
		SysFreeString(result);
		AfxMessageBox(r, 0, 0);
	}

	
	if (! i.hCloseSource(h)) return FALSE;


	SysFreeString(pid);

	
	return TRUE;
}



*/
