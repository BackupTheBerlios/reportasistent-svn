// ReportAsistent.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ReportAsistent.h"

#include "MainFrm.h"
#include "CSkeletonDoc.h"
#include "SkeletonView.h"
#include "SourcesDialog.h"
#include "PropertyEditor.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReportAsistentApp

BEGIN_MESSAGE_MAP(CReportAsistentApp, CWinApp)
	//{{AFX_MSG_MAP(CReportAsistentApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_MMSOURCES, OnMmsources)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportAsistentApp construction

CReportAsistentApp::CReportAsistentApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CReportAsistentApp object

CReportAsistentApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CReportAsistentApp initialization

#define FIRST_ERR_STR_ID (IDS_INSERT_NEW_ELEMENT_WRONG_LOCATION-1)

int CReportAsistentApp::ReportError(UINT nResourceErrorStringID, ...)
{
	CString sFormatStr;
	sFormatStr.LoadString(nResourceErrorStringID);

	va_list params;
	va_start(params, nResourceErrorStringID);

	CString sMessgeText;
	sMessgeText.FormatV(sFormatStr, params);
	
	va_end(params);
	
	CString sOutputText;
	sOutputText.Format("Program error: ERR%03d\n\n%s", nResourceErrorStringID-FIRST_ERR_STR_ID, (LPCTSTR) sMessgeText);

	return AfxMessageBox(sOutputText);
}


BOOL CReportAsistentApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
#if _MFC_VER < 0x0700
	Enable3dControls();			// Call this when using MFC in a shared DLL
#endif
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

		//pridal honza
	CoInitialize(NULL);

		//pridal honza
	m_pGeneralManager = new CGeneralManager();



	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("LISp-Miner"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)


	//dedek
	//zapis do windows registry
	AfxGetApp()->WriteProfileString("Settings", "ApplicationRoot", 
		m_pGeneralManager->DirectoriesManager.getApplicationRoot());


	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CSkeletonDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CSkeletonView));
	AddDocTemplate(pDocTemplate);

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CReportAsistentApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CReportAsistentApp message handlers

//Iva
//DEL void CReportAsistentApp::OnMMNewText() 
//DEL {
//DEL 	//Pridam do TreeCtrl Novou Item a do XML stromu taky.
//DEL 	
//DEL }

int CReportAsistentApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class

	//pridal honza
	delete m_pGeneralManager;

	
	return CWinApp::ExitInstance();
}


//honza: vrati prvni dokument v prvni DocTemlate - proste nas dokument :)
CSkeletonDoc * CReportAsistentApp::FirstDocumentInFirstTemplate()
{
	POSITION pos = GetFirstDocTemplatePosition();
	CDocTemplate * t = GetNextDocTemplate(pos);

	pos = t->GetFirstDocPosition();
	return (CSkeletonDoc *) t->GetNextDoc(pos);

}

//honza
void CReportAsistentApp::OnMmsources() 
{
	CSourcesDialog dlg(AfxGetMainWnd());

	dlg.DoModal();
	
}
