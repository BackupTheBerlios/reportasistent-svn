#ifndef WINVER
#define WINVER 0x0400
#endif

#include <afx.h>
#include <afxdb.h>
#include <Shlwapi.h>

#include "SockInterface.h"
//#include "tiHypothesis_Recordset.h"
#include "SQL_pomocnik.h"
#include "InterfaceFunctions.h"
#include "LMPlugin.h"



// ---------- performLM 

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

  /****** dedek test2 *****

  CString s = "<active_list><category id=\"cat1\" db_name=\"d:\\lmra\\ReportAsistent\\LMMetabase\\LMEmpty2\" matrix_name=\"Entry\" attr_name=\"BMI\" ctgr_name=\"podvaha\" ctgr_type=\"Interval\" ctgr_freq=\"N/A\" bool_type=\"No boolean\" def_length=\"1\"><ctgr_def definition=\"&lt;15;20)\"/></category></active_list>";

  *Result = s.AllocSysString();
  return TRUE;

  /****/
	
	CString CStrResult; // mezivysledek CString
	pFn_t pFn = LMSock.getFnAddress(APName);	// ukazatel na funkci, ktera vyridi pozadavek
	if (pFn == NULL) // chyba - neexistuje funkce vyrizujici tento AP
		return FALSE;
	CStrResult = pFn(hSource);
	*Result =  CStrResult.AllocSysString();
	return TRUE;
}
/****/

/*

*/


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
	 * pPerzistID = NULL;

	CDatabase * db;
	SQL_Pomocnik pom;

	CString s;


	if (! pom.FindAccesDatasource(s)) return NULL;


	//dedek: potreba pokud si chceme udrzet aktualni adresar
	char buf[1001];
	GetCurrentDirectory(1000, buf);


	db = new CDatabase();
	if (!db->Open(NULL, FALSE, TRUE, _T("ODBC;DSN=" + s), TRUE))
	{
		//dedek
		SetCurrentDirectory(buf);
		
		delete db;
		return NULL;
	}

	//dedek
	SetCurrentDirectory(buf);

	CString new_pid =  db->GetDatabaseName();

	new_pid += ".mdb";

	
	* pPerzistID = new_pid.AllocSysString();
	return db;
}


// ---------- fOpenSourceLM

hSource_t fOpenSourceLM(PersistID_t PerzistID)
{
	SQL_Pomocnik pom;
	CString s;
	if (! pom.FindAccesDatasource(s)) return NULL;

	CString file_path = PerzistID;

	if (PathIsRelative(file_path))
	{
		TCHAR module_path[MAX_PATH];
		GetModuleFileName(NULL, module_path, MAX_PATH);
		PathFindFileName(module_path)[-1] = 0;
		PathFindFileName(module_path)[0] = 0;
		file_path = module_path;
		file_path += PerzistID;		
	}


	//	db.Open(NULL, FALSE, TRUE, _T("ODBC;DSN=" + s + ";DBQ=C:\\skola\\sw projekt\\STULONG.mdb;"), TRUE))
	CString connn_str;
	connn_str = "ODBC;DSN=";
	connn_str += s;
	connn_str += ";DBQ=";
	connn_str += file_path; //obsahuje cestu k souboru
	connn_str += ";";

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
