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


//DEL CString CtiHypothesis_Recordset::GetDefaultConnect()
//DEL {
//DEL 	SQLHANDLE h;
//DEL 	SQLRETURN r;
//DEL 
//DEL 	
//DEL 	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, & h);
//DEL 	//dulezite nastavuje verzi na ODBC3, jinak to nefunguje, verzi nutno vzdy nastavit
//DEL 	SQLSetEnvAttr(h, SQL_ATTR_ODBC_VERSION, (SQLPOINTER) SQL_OV_ODBC3, NULL);
//DEL 	
//DEL 	SQLCHAR		desc[1000];
//DEL 	SQLCHAR		attr[1000];
//DEL 	SQLSMALLINT desc_len = sizeof desc;
//DEL 	SQLSMALLINT attr_len = sizeof attr;
//DEL 
//DEL 	SQLINTEGER nerr;
//DEL 
//DEL 	CString nas_driver;
//DEL 	CString nas_source;
//DEL 
//DEL 	CEdit * e = (CEdit *) theApp.m_pMainWnd->GetDlgItem(IDC_RESULT_EDIT);
//DEL 
//DEL 
//DEL 	
//DEL //--------------------------------------------------------
//DEL //drivers
//DEL 	r = SQLDrivers(h, SQL_FETCH_FIRST, desc, sizeof desc, & desc_len, attr, sizeof attr, & attr_len);
//DEL 
//DEL // vhodne pro odchytavani chyb
//DEL //	SQLGetDiagRec(SQL_HANDLE_ENV, h, 1, desc, & nerr, attr, sizeof attr, & attr_len);
//DEL 
//DEL 
//DEL 	while ((r != SQL_NO_DATA) && (r != SQL_ERROR) && (r != SQL_INVALID_HANDLE))
//DEL 	{
//DEL 
//DEL 		CString s;
//DEL 		e->GetWindowText(s);
//DEL 
//DEL 		s += EDIT_NEWLINE;
//DEL 		s += "-------------- dalsi driver -----------" EDIT_NEWLINE;
//DEL 		s += desc;
//DEL 		s += EDIT_NEWLINE;
//DEL 
//DEL 		SQLCHAR * pc;
//DEL 		
//DEL 		for (pc = attr; (*pc != 0) && (pc - attr <= sizeof attr); pc = (SQLCHAR *) strchr((LPCTSTR) pc, 0)+1)
//DEL 		{
//DEL 			if (strstr((LPCTSTR) pc, "FileExtns="))
//DEL 			{
//DEL 				if (strstr((LPCTSTR) pc, ".mdb"))
//DEL 				{
//DEL 					if (0 != strcmp("Microsoft Access Driver (*.mdb)", nas_driver))
//DEL 						nas_driver = desc;
//DEL 				}
//DEL 			}
//DEL 			
//DEL 			s += pc;
//DEL 			s += EDIT_NEWLINE;
//DEL 		}
//DEL 		
//DEL 		e->SetWindowText(s);
//DEL 
//DEL 
//DEL 		r = SQLDrivers(h, SQL_FETCH_NEXT, desc, sizeof desc, & desc_len, attr, sizeof attr, & attr_len);
//DEL 	}
//DEL 
//DEL //--------------------------------------------------------
//DEL //datasources
//DEL 	r = SQLDataSources(h, SQL_FETCH_FIRST, desc, sizeof desc, & desc_len, attr, sizeof attr, & attr_len);
//DEL 	
//DEL 	while ((r != SQL_NO_DATA) && (r != SQL_ERROR) && (r != SQL_INVALID_HANDLE))
//DEL 	{
//DEL 
//DEL 		if (0 == strcmp((LPCTSTR) attr, nas_driver)) nas_source = desc;
//DEL 
//DEL 		CString s;
//DEL 		e->GetWindowText(s);
//DEL 
//DEL 		s += EDIT_NEWLINE;
//DEL 		s += "-------------- dalsi datasource -----------" EDIT_NEWLINE;
//DEL 		s += desc;
//DEL 		s += EDIT_NEWLINE;
//DEL 		s += attr;
//DEL 		s += EDIT_NEWLINE;
//DEL 
//DEL 		e->SetWindowText(s);
//DEL 
//DEL 		r = SQLDataSources(h, SQL_FETCH_NEXT, desc, sizeof desc, & desc_len, attr, sizeof attr, & attr_len);
//DEL 	}
//DEL 
//DEL 
//DEL 
//DEL 	SQLFreeHandle(SQL_HANDLE_ENV, h);
//DEL 
//DEL 
//DEL //	return _T("ODBC;DSN=Databáze MS Access");
//DEL 	return _T(CString("ODBC;DSN=") + nas_source + ";DBQ=D:\\lm\\LMEmpty.mdb;");
//DEL //	return _T(CString("ODBC;DATABASE=D:\\LMEmpty.mdb"));
//DEL }

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
