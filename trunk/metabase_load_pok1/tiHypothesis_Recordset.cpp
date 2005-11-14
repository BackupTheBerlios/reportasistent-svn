// tiHypothesis_Recordset.cpp : implementation file
//

#include "stdafx.h"
#include "metabase_load_pok1.h"
#include "tiHypothesis_Recordset.h"
#include "metabase_load_pok1Dlg.h"

extern CMetabase_load_pok1App theApp;


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CtiHypothesis_Recordset

IMPLEMENT_DYNAMIC(CtiHypothesis_Recordset, CRecordset)

CtiHypothesis_Recordset::CtiHypothesis_Recordset(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CtiHypothesis_Recordset)
	m_HypothesisID = 0;
	m_TaskID = 0;
	m_FreqA = 0;
	m_FreqB = 0;
	m_FreqC = 0;
	m_FreqD = 0;
	m_Weight = 0.0;
	m_Ord = 0;
	m_nFields = 8;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CtiHypothesis_Recordset::GetDefaultConnect()
{
	SQLHANDLE h;
	SQLRETURN r;

	
	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, & h);
	//dulezite nastavuje verzi na ODBC3, jinak to nefunguje, verzi nutno vzdy nastavit
	SQLSetEnvAttr(h, SQL_ATTR_ODBC_VERSION, (SQLPOINTER) SQL_OV_ODBC3, NULL);
	
	SQLCHAR		desc[1000];
	SQLCHAR		attr[1000];
	SQLSMALLINT desc_len = sizeof desc;
	SQLSMALLINT attr_len = sizeof attr;

	SQLINTEGER nerr;

	CString nas_driver;
	CString nas_source;

	CEdit * e = (CEdit *) theApp.m_pMainWnd->GetDlgItem(IDC_RESULT_EDIT);


	
//--------------------------------------------------------
//drivers
	r = SQLDrivers(h, SQL_FETCH_FIRST, desc, sizeof desc, & desc_len, attr, sizeof attr, & attr_len);

// vhodne pro odchytavani chyb
//	SQLGetDiagRec(SQL_HANDLE_ENV, h, 1, desc, & nerr, attr, sizeof attr, & attr_len);


	while ((r != SQL_NO_DATA) && (r != SQL_ERROR) && (r != SQL_INVALID_HANDLE))
	{

		CString s;
		e->GetWindowText(s);

		s += EDIT_NEWLINE;
		s += "-------------- dalsi driver -----------" EDIT_NEWLINE;
		s += desc;
		s += EDIT_NEWLINE;

		SQLCHAR * pc;
		
		for (pc = attr; (*pc != 0) && (pc - attr <= sizeof attr); pc = (SQLCHAR *) strchr((LPCTSTR) pc, 0)+1)
		{
			if (strstr((LPCTSTR) pc, "FileExtns="))
			{
				if (strstr((LPCTSTR) pc, ".mdb")) nas_driver = desc;
			}
			
			s += pc;
			s += EDIT_NEWLINE;
		}
		
		e->SetWindowText(s);


		r = SQLDrivers(h, SQL_FETCH_NEXT, desc, sizeof desc, & desc_len, attr, sizeof attr, & attr_len);
	}

//--------------------------------------------------------
//datasources
	r = SQLDataSources(h, SQL_FETCH_FIRST, desc, sizeof desc, & desc_len, attr, sizeof attr, & attr_len);
	
	while ((r != SQL_NO_DATA) && (r != SQL_ERROR) && (r != SQL_INVALID_HANDLE))
	{

		if (0 == strcmp((LPCTSTR) attr, nas_driver)) nas_source = desc;

		CString s;
		e->GetWindowText(s);

		s += EDIT_NEWLINE;
		s += "-------------- dalsi datasource -----------" EDIT_NEWLINE;
		s += desc;
		s += EDIT_NEWLINE;
		s += attr;
		s += EDIT_NEWLINE;

		e->SetWindowText(s);

		r = SQLDataSources(h, SQL_FETCH_NEXT, desc, sizeof desc, & desc_len, attr, sizeof attr, & attr_len);
	}



	SQLFreeHandle(SQL_HANDLE_ENV, h);


//	return _T("ODBC;DSN=Databáze MS Access");
	return _T(CString("ODBC;DSN=") + nas_source);
}

CString CtiHypothesis_Recordset::GetDefaultSQL()
{
	return _T("[tiHypothesis]");
}

void CtiHypothesis_Recordset::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CtiHypothesis_Recordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[HypothesisID]"), m_HypothesisID);
	RFX_Long(pFX, _T("[TaskID]"), m_TaskID);
	RFX_Long(pFX, _T("[FreqA]"), m_FreqA);
	RFX_Long(pFX, _T("[FreqB]"), m_FreqB);
	RFX_Long(pFX, _T("[FreqC]"), m_FreqC);
	RFX_Long(pFX, _T("[FreqD]"), m_FreqD);
	RFX_Double(pFX, _T("[Weight]"), m_Weight);
	RFX_Long(pFX, _T("[Ord]"), m_Ord);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CtiHypothesis_Recordset diagnostics

#ifdef _DEBUG
void CtiHypothesis_Recordset::AssertValid() const
{
	CRecordset::AssertValid();
}

void CtiHypothesis_Recordset::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
