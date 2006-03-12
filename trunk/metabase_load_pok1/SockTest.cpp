
#include "stdafx.h"
#include "SockInterface.h"
#include "tiHypothesis_Recordset.h"
#include "SQL_pomocnik.h"




BOOL Perform(hSource_t hSource, const char* AP, BSTR* result)
{
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
}


hSource_t NewSource(PersistID_t * pPID)
{
	CDatabase * db;
	SQL_Pomocnik pom;

	CString s;

	 * pPID = NULL;

	if (! pom.FindAccesDatasource(s)) return NULL;

	db = new CDatabase();
	if (!db->Open(NULL, FALSE, TRUE, _T("ODBC;DSN=" + s), TRUE))
	{
		delete db;
		return NULL;
	}

	* pPID = db->GetConnect().AllocSysString();
	return db;
}

hSource_t OpenSource(PersistID_t PID)
{
	CString connn_str = PID;

	CDatabase * db;
	
	db = new CDatabase();


	if (!db->Open(NULL, FALSE, TRUE, connn_str, TRUE))
	{
		delete db;
		return NULL;
	}
	
	return db;
}

BOOL CloseSource(hSource_t hSource)
{
	if (hSource == NULL) return FALSE;
	
	CDatabase * db = (CDatabase *) hSource;

	db->Close();

	delete db;

	return TRUE;
}



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



