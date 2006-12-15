// ReportAsistent.cpp : Defines the class behaviors for the application.
//
/*
This file is part of LM Report Asistent.

Authors: Jan Dedek, Jan Kodym, Martin Chrz, Iva Bartunkova

LM Report Asistent is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

Foobar is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Foobar; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include "stdafx.h"
#include "afxpriv.h"

#include "ReportAsistent.h"

#include "MainFrm.h"
#include "CSkeletonDoc.h"
#include "SkeletonView.h"
#include "SourcesDialog.h"
#include "OptionsDialog.h"
#include "StartDialog.h"

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
	ON_COMMAND(ID_FILE_OPTIONS, OnFileOptions)
	ON_COMMAND(ID_OPEN_WORD_EDITOR, OnOpenWordEditor)
	ON_COMMAND(ID_HLP_TOPICS, OnHlpTopics)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)


END_MESSAGE_MAP()


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


/////////////////////////////////////////////////////////////////////////////
// CReportAsistentApp construction

CReportAsistentApp::CReportAsistentApp()
: m_bIdInItemName(0)
, m_iTreeItemHeight(0)
, m_iTreeItemIndent(0)
, m_bTreeHasLines(0)
, m_bTreeHasButtons(0)
, m_bWordPluginMode(FALSE)
, m_iTreeItemNameLength(0)
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

	return AfxMessageBox(sOutputText, MB_OK | MB_HELP,666666);
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

	//dedek
//	CoInitialize(NULL);
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
//  AfxMessageBox("2");

	CStartDialog s_dlg;
	s_dlg.Create(IDD_START_DIALOG);
	s_dlg.ShowWindow(SW_SHOW);
	s_dlg.UpdateWindow();

	//Iva: initialization of RichEditCtrl
	AfxInitRichEdit();

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("LISp-Miner"));

	//dedek
	m_pGeneralManager = new CGeneralManager();
	m_pGeneralManager->ElementManager.Init(m_pGeneralManager->DirectoriesManager);

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	//Iva: read from windows registry
	 m_bIdInItemName = GetProfileInt("Settings", "bIdInItemName", 1);
	 m_iTreeItemHeight = GetProfileInt("Settings", "TreeItemHeight",20);
	 m_iTreeItemIndent= GetProfileInt("Settings", "TreeItemIndent",25);
	 m_bTreeHasLines = GetProfileInt("Settings","bTreeHasLines",1);
	 m_bTreeHasButtons = GetProfileInt("Settings","bTreeHasButtons",1);
	 m_bMarkOrphans = GetProfileInt("Settings","bMarkOrphans",0);
	 m_iTreeItemNameLength = GetProfileInt("Settings","TreeItemNameLength",30);
	 m_iTextEditSize = GetProfileInt("Settings","TextEditSize",165);

	 //CString Pom;
	 //Pom.Format("%d",m_iTreeItemNameLength);
	 //AfxMessageBox(Pom);

	 m_pGeneralManager->WordManager.setWordTemplate(
		 GetProfileString("Settings", "WordTemplate", 
			m_pGeneralManager->DirectoriesManager.getWordTemplateDirectory() + "\\ReportAsistent.dot"));


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

//  AfxMessageBox("3");
	
//	Sleep(5000);
	s_dlg.ShowWindow(SW_HIDE);

  // The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

//  AfxMessageBox("4");
	

	return TRUE;
}



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

int CReportAsistentApp::ExitInstance() 
{
	//Iva: Save information to registry
	/*int iIdInItemName = m_bIdInItemName;
	int iTreeHasLines = m_bTreeHasLines
	int iTreeHasLines = m_bTreeHasLines;*/
	 WriteProfileInt("Settings", "bIdInItemName", m_bIdInItemName);
	 WriteProfileInt("Settings", "TreeItemHeight",m_iTreeItemHeight);
	 WriteProfileInt("Settings", "TreeItemIndent",m_iTreeItemIndent );
	 WriteProfileInt("Settings","bTreeHasLines", m_bTreeHasLines);
	 WriteProfileInt("Settings","bTreeHasButtons",m_bTreeHasLines);
	 WriteProfileInt("Settings","bMarkOrphans",m_bMarkOrphans);
	 WriteProfileInt("Settings","TreeItemNameLength",m_iTreeItemNameLength);
	 WriteProfileInt("Settings","TextEditSize",m_iTextEditSize);

	 WriteProfileString("Settings", "WordTemplate", m_pGeneralManager->WordManager.getWordTemplate());

	//Dedek:
	delete m_pGeneralManager;

	
	return CWinApp::ExitInstance();
}


//honza: vrati prvni dokument v prvni DocTemlate - proste nas dokument :)
CSkeletonDoc * CReportAsistentApp::FirstDocumentInFirstTemplate()
{
	POSITION pos = GetFirstDocTemplatePosition();

	if (pos == NULL) return NULL;

	CDocTemplate * t = GetNextDocTemplate(pos);

	pos = t->GetFirstDocPosition();
	return (CSkeletonDoc *) t->GetNextDoc(pos);

}

//dedek
void CReportAsistentApp::OnMmsources() 
{
	CSourcesDialog dlg(AfxGetMainWnd());

	dlg.DoModal();
	
}

//dedek
void CReportAsistentApp::OnFileOptions() 
{
	COptionsDialog dlg(AfxGetMainWnd());

	if (IDOK == dlg.DoModal())
	{
		FirstDocumentInFirstTemplate()->SetModifiedFlag();
		FirstDocumentInFirstTemplate()->UpdateAllViews(NULL,0);
	}
	
}

//dedek otevre word v RA edit modu
void CReportAsistentApp::OnOpenWordEditor() 
{
	m_bWordPluginMode = TRUE;
	m_pGeneralManager->WordManager.OpenWordEditor();
}

//Iva: If Help Topics in the menu is chosen, this is the handler
void CReportAsistentApp::OnHlpTopics() 
{
	//WinHelp((unsigned long)"What", HELP_KEY);//Displays Help Topics dialog box, according to "key word"
	WinHelp(IDH_CONTENTS, HELP_CONTEXT);//Displays Help Topics dialog box, according to "mapped ID"
	
}





int CReportAsistentApp::DoMessageBox(LPCTSTR lpszPrompt, UINT nType, UINT nIDPrompt)
{
// disable windows for modal dialog
	EnableModeless(FALSE);
	HWND hWndTop;
	HWND hWnd = CWnd::GetSafeOwner_(NULL, &hWndTop);

	// set help context if possible
	DWORD* pdwContext = NULL;
	HWND hWnd2 = AfxGetMainWnd()->GetSafeHwnd();
	if (hWnd2 != NULL)
	{
		// use app-level context or frame level context
		LRESULT lResult = ::SendMessage(hWnd2, WM_HELPPROMPTADDR, 0, 0); // Use "MainWnd" HWND
		if (lResult != 0)
			pdwContext = (DWORD*)lResult;
	}
	// for backward compatibility use app context if possible
	if (pdwContext == NULL && this != NULL)
		pdwContext = &m_dwPromptContext;

	DWORD dwOldPromptContext = 0;
	if (pdwContext != NULL)
	{
		// save old prompt context for restoration later
		dwOldPromptContext = *pdwContext;
		if (nIDPrompt != 0)
			*pdwContext = HID_BASE_PROMPT+nIDPrompt;
	}

	// determine icon based on type specified
	if ((nType & MB_ICONMASK) == 0)
	{
		switch (nType & MB_TYPEMASK)
		{
		case MB_OK:
		case MB_OKCANCEL:
			nType |= MB_ICONEXCLAMATION;
			break;

		case MB_YESNO:
		case MB_YESNOCANCEL:
			nType |= MB_ICONEXCLAMATION;
			break;

		case MB_ABORTRETRYIGNORE:
		case MB_RETRYCANCEL:
			// No default icon for these types, since they are rarely used.
			// The caller should specify the icon.
			break;
		}
	}

#ifdef _DEBUG
	if ((nType & MB_ICONMASK) == 0)
		TRACE0("Warning: no icon specified for message box.\n");
#endif

	TCHAR szAppName[_MAX_PATH];
	LPCTSTR pszAppName;
	if (this != NULL)
		pszAppName = m_pszAppName;
	else
	{
		pszAppName = szAppName;
		GetModuleFileName(NULL, szAppName, _MAX_PATH);
	}

	int nResult =
		::MessageBox(hWnd, lpszPrompt, pszAppName, nType);

	// restore prompt context if possible
	if (pdwContext != NULL)
		*pdwContext = dwOldPromptContext;

	// re-enable windows
	if (hWndTop != NULL)
		::EnableWindow(hWndTop, TRUE);
	EnableModeless(TRUE);

	return nResult;
}
