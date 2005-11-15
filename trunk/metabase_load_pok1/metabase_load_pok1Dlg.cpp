// metabase_load_pok1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "metabase_load_pok1.h"
#include "metabase_load_pok1Dlg.h"
#include "tiHypothesis_Recordset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMetabase_load_pok1Dlg dialog

CMetabase_load_pok1Dlg::CMetabase_load_pok1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMetabase_load_pok1Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMetabase_load_pok1Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMetabase_load_pok1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMetabase_load_pok1Dlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMetabase_load_pok1Dlg, CDialog)
	//{{AFX_MSG_MAP(CMetabase_load_pok1Dlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_LOAD_BUTTON, OnLoadButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMetabase_load_pok1Dlg message handlers

BOOL CMetabase_load_pok1Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMetabase_load_pok1Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMetabase_load_pok1Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMetabase_load_pok1Dlg::OnLoadButton() 
{
	CString s;

	if (NactiMetabazi())
	{
		// pripoji konce do textu edit okna
		
		
		GetDlgItemText(IDC_RESULT_EDIT, s);

		SetDlgItemText(IDC_RESULT_EDIT, s + EDIT_NEWLINE "--- OK metabse loaded ---" EDIT_NEWLINE);
	}
}



class SQL_Pomocnik
{
protected:
	SQLHANDLE h;

	BOOL handle_ok()
	{
		return h != SQL_NULL_HANDLE;
	}

public:
	
	SQL_Pomocnik()
	{
		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, & h))
		{
			h = SQL_NULL_HANDLE;
		}
		else
		{
			SQLSetEnvAttr(h, SQL_ATTR_ODBC_VERSION, (SQLPOINTER) SQL_OV_ODBC3, NULL);
		}
	}


	BOOL EnumODBCDrivers(CString & ret)
	{
		SQLRETURN r;
		ret.Empty();

		if (! handle_ok()) return FALSE;
	
		SQLCHAR		desc[1000];
		SQLCHAR		attr[1000];
		SQLSMALLINT desc_len = sizeof desc;
		SQLSMALLINT attr_len = sizeof attr;

		r = SQLDrivers(h, SQL_FETCH_FIRST, desc, sizeof desc, & desc_len, attr, sizeof attr, & attr_len);

//		vhodne pro odchytavani chyb
//		SQLGetDiagRec(SQL_HANDLE_ENV, h, 1, desc, & nerr, attr, sizeof attr, & attr_len);


		while ((r != SQL_NO_DATA) && (r != SQL_ERROR) && (r != SQL_INVALID_HANDLE))
		{

			ret += EDIT_NEWLINE;
			ret += "-------------- dalsi driver -----------" EDIT_NEWLINE;
			ret += desc;
			ret += EDIT_NEWLINE;

			SQLCHAR * pc;
		
			for (pc = attr; (*pc != 0) && (pc - attr <= sizeof attr); pc = (SQLCHAR *) strchr((LPCTSTR) pc, 0)+1)
			{
				ret += pc;
				ret += EDIT_NEWLINE;
			}
		
			r = SQLDrivers(h, SQL_FETCH_NEXT, desc, sizeof desc, & desc_len, attr, sizeof attr, & attr_len);
		}

		
		return TRUE;
	}

	BOOL EnumODBCDataSources(CString & ret)
	{
		SQLRETURN r;
		ret.Empty();

		if (! handle_ok()) return FALSE;

		SQLCHAR		desc[1000];
		SQLCHAR		attr[1000];
		SQLSMALLINT desc_len = sizeof desc;
		SQLSMALLINT attr_len = sizeof attr;

		r = SQLDataSources(h, SQL_FETCH_FIRST, desc, sizeof desc, & desc_len, attr, sizeof attr, & attr_len);

		while ((r != SQL_NO_DATA) && (r != SQL_ERROR) && (r != SQL_INVALID_HANDLE))
		{

			ret += EDIT_NEWLINE;
			ret += "-------------- dalsi datasource -----------" EDIT_NEWLINE;
			ret += desc;
			ret += EDIT_NEWLINE;
			ret += attr;
			ret += EDIT_NEWLINE;
		
			r = SQLDataSources(h, SQL_FETCH_NEXT, desc, sizeof desc, & desc_len, attr, sizeof attr, & attr_len);
		}

		return TRUE;
	}

	BOOL FindAccesDatasource(CString & ret)
	{
		SQLRETURN r;
		ret.Empty();

		if (! handle_ok()) return FALSE;

		SQLCHAR		desc[1000];
		SQLCHAR		attr[1000];
		SQLSMALLINT desc_len = sizeof desc;
		SQLSMALLINT attr_len = sizeof attr;

		r = SQLDataSources(h, SQL_FETCH_FIRST, desc, sizeof desc, & desc_len, attr, sizeof attr, & attr_len);

		while ((r != SQL_NO_DATA) && (r != SQL_ERROR) && (r != SQL_INVALID_HANDLE))
		{
			//ten string "Microsoft Access Driver (*.mdb)" by se mel ulozit jinam (header nebo resources)..
			//mozna pridat konfigurovatelnost
			if (0 == strcmp((LPCTSTR) attr, "Microsoft Access Driver (*.mdb)"))
			{
				ret = desc;
				return TRUE;
			}

			r = SQLDataSources(h, SQL_FETCH_NEXT, desc, sizeof desc, & desc_len, attr, sizeof attr, & attr_len);
		}

		
		return FALSE;
	}

		
	~SQL_Pomocnik()
	{
		if (handle_ok())
			SQLFreeHandle(SQL_HANDLE_ENV, h);
	}

};

BOOL CMetabase_load_pok1Dlg::NactiMetabazi()
{
	CDatabase db;
	CtiHypothesis_Recordset rs(& db);
	SQL_Pomocnik pom;

	CString s;
	CString buf;

	//enumarece
	pom.EnumODBCDrivers(s);
	buf = s;	
	pom.EnumODBCDataSources(s);
	buf += s;	
	SetDlgItemText(IDC_RESULT_EDIT, buf);


	//otevreni databaze
	pom.FindAccesDatasource(s);

	if (

//nekolik verzi connect stringu
//	db.Open(NULL, FALSE, TRUE, _T("ODBC;DSN=Databáze MS Access"), TRUE)
//	db.Open(NULL, FALSE, TRUE, _T("ODBC;DSN=" + s), TRUE))

//	tohle funguje bez open dialogu
	db.Open(NULL, FALSE, TRUE, _T("ODBC;DSN=" + s + ";DBQ=C:\\skola\\sw projekt\\STULONG.mdb;"), TRUE))
	{
		if (rs.Open())
		{

			buf = EDIT_NEWLINE "--- query start ---" EDIT_NEWLINE;
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
		}

		db.Close();
		
		//nastavi text edit okna
		CString et;
		GetDlgItemText(IDC_RESULT_EDIT, et);
		SetDlgItemText(IDC_RESULT_EDIT, et + buf);

		return TRUE;
	}

	return FALSE;

}
