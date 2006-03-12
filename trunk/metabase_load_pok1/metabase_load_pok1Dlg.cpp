// metabase_load_pok1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "metabase_load_pok1.h"
#include "metabase_load_pok1Dlg.h"
#include "tiHypothesis_Recordset.h"
#include "SQL_pomocnik.h"


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
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


#ifdef USE_WORD	
	DDX_Control(pDX, IDC_WORD_VIEW, m_WordView);
	DDX_Control(pDX, IDC_TREE1, m_XMLTree1);
#endif
//	dat mezi 	//{{AFX_DATA_MAP(CMetabase_load_pok1Dlg)



void CMetabase_load_pok1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMetabase_load_pok1Dlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMetabase_load_pok1Dlg, CDialog)
	//{{AFX_MSG_MAP(CMetabase_load_pok1Dlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_LOAD_BUTTON, OnLoadButton)
	ON_BN_CLICKED(IDC_XML_BUTTON, OnXmlButton)
	ON_BN_CLICKED(IDC_GENERXML_BUTTON, OnGenerxmlButton)
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
	SetDlgItemText(IDC_XML_PATH_EDIT, "..\\xml\\redukovany.xml");

	
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
		// pripoji konec do textu edit okna
		
		
		GetDlgItemText(IDC_RESULT_EDIT, s);

		SetDlgItemText(IDC_RESULT_EDIT, s + EDIT_NEWLINE "--- OK metabse loaded ---" EDIT_NEWLINE);
	}
}



BOOL CMetabase_load_pok1Dlg::NactiMetabazi2()
{
	CDatabase db;
	CtiHypothesis_Recordset rs(& db);
	SQL_Pomocnik pom;

	CString s;
	CString buf;

	//enumarece
	pom.EnumODBCDrivers(s);
	buf = s;	
	
	buf +=  EDIT_NEWLINE "-------- USER DATASOURCES ------";
	pom.EnumODBCDataSources(s, SQL_FETCH_FIRST_USER);
	buf += s;	

	// tady budou LM metabaze
	buf +=  EDIT_NEWLINE "-------- SYSTEM DATASOURCES ------";
	pom.EnumODBCDataSources(s, SQL_FETCH_FIRST_SYSTEM);
	buf += s;	

	SetDlgItemText(IDC_RESULT_EDIT, buf);


	//otevreni databaze
	pom.FindAccesDatasource(s);

	if (

//nekolik verzi connect stringu
//	db.Open(NULL, FALSE, TRUE, _T("ODBC;DSN=Databáze MS Access"), TRUE)
	db.Open(NULL, FALSE, TRUE, _T("ODBC;DSN=" + s), TRUE)

//	tohle funguje bez open dialogu
//	db.Open(NULL, FALSE, TRUE, _T("ODBC;DSN=" + s + ";DBQ=C:\\skola\\sw projekt\\STULONG.mdb;"), TRUE))

/*

  honza:
  
	Cauves, tak jsem se v tom zase hrabal.
	Totiz pri testovani, AR2NL jsem si uvedomil, ze LM Admin vytvari novy ODBC DataSource.
	Tyto jsou k enumerovani jako SYSTEM datasources (pom.EnumODBCDataSources(s, SQL_FETCH_FIRST_SYSTEM))

	A tak vznikl nasledujici connection string, ktery primo otevira metabazi definovanou v LM Admin.

	
	Nekdo by casem mohl vytvorit podobny dialog, jaky pouzivaji vsechny LM moduly pri jejich spusteni.
	(dialog "LISp-Miner working database" - tipnul jsem ho do resourcu jako 25002 :)


	
		//tvrdy odkaz na datasource generovany z LM-Admin:
		db.Open(NULL, FALSE, TRUE, _T("ODBC;DSN=LM LMEntry.mdb Metabase"), TRUE)
*/
	
	)
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








BOOL Otestuj();

BOOL CMetabase_load_pok1Dlg::NactiMetabazi()
{
	return Otestuj();
}





























void LoadXLMFileToWord(LPCTSTR FilePath);
BOOL LoadXMLDOM(LPCTSTR FilePath, CTreeCtrl * treeCtrl);


void CMetabase_load_pok1Dlg::OnXmlButton() 
{
	CString s;
	GetDlgItemText(IDC_XML_PATH_EDIT, s);

#ifdef USE_WORD

	m_XMLTree1.LoadFromFile(s);
#endif
	
//	LoadXMLDOM(s, (CTreeCtrl *) GetDlgItem(IDC_TREE1));

//	LoadXLMFileToWord(s);
}




/*
namespace Wordik
{
	#import "C:\Program Files\Microsoft Office\Office\MSWORD9.OLB"\
	raw_interfaces_only, raw_native_types, no_namespace, named_guids, exclude("Tasks")

}
*/

void CMetabase_load_pok1Dlg::OnGenerxmlButton() 
{
/*

		LPOLEOBJECT o = m_WordView.GetWordObject();

	
		Wordik::_Document * obj = NULL;
		HRESULT hr = o->QueryInterface(Wordik::IID__Document, (void **) & obj);

		obj->Select();

		Wordik::_Application * app = NULL;
		obj->get_Application(& app);

		Wordik::Selection * sel = NULL;
		app->get_Selection(& sel);

//		sel->EndKey(NULL, NULL, NULL);
		static CString s("Ahoj");
		s += " dalsi";
		BSTR bs = s.AllocSysString();
		sel->TypeText(bs);
		SysFreeString(bs);
		sel->Release();
		app->Release();
		obj->Release();

*/	
	
#ifdef USE_WORD
	m_XMLTree1.GenerSelectedSubtree(m_WordView.GetWordObject());
#endif
}
