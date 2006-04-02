// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "ReportAsistent.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndDlgBar.Create(this, IDR_MAINFRAME, 
		CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR))
	{
		TRACE0("Failed to create dialogbar\n");
		return -1;		// fail to create
	}

	if (!m_wndReBar.Create(this) ||
		!m_wndReBar.AddBar(&m_wndToolBar) ||
		!m_wndReBar.AddBar(&m_wndDlgBar))
	{
		TRACE0("Failed to create rebar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	//Iva: Dynamicky pridam do menu seznam prvku ke vlozeni do kostry
	CMenu * hMainMenu = AfxGetApp()->GetMainWnd()->GetMenu();
	CMenu * hNewMenu = hMainMenu->GetSubMenu(1/*Edit*/)->GetSubMenu(7/*New*/);
	char Textik [20]="";
	/*	hNewMenu->GetMenuString(0,Textik,19,MF_BYPOSITION);
		AfxMessageBox(Textik,0,0);*/

	CElementManager & OElementManager = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;

	int pom=OElementManager.getFirstActiveElementID();
	int I;
	//Vlozim do menu staticke prvky:
	for(I=0;I<=(OElementManager.getFirstActiveElementID() - OElementManager.getFirstStaticElementID()-1);I++)
	{
		hNewMenu->InsertMenu(	-1, //pridej na konec seznamu
								MF_BYPOSITION,
								ID_MMNEWSTATICFIRST + I,
								OElementManager.getElementName(I+OElementManager.getFirstStaticElementID()) //nazev
								);	

/*		int pom = hNewMenu->EnableMenuItem(ID_MMNEWSTATICFIRST + I,MF_ENABLED|MF_BYCOMMAND);
		if (pom ==MF_ENABLED) pom=-1;
		if (pom ==MF_DISABLED) pom=-2;
		if (pom ==MF_GRAYED) pom=-3;
		hNewMenu->GetMenuString(ID_MMNEWSTATICFIRST + I,Textik,19,MF_BYCOMMAND);
		AfxMessageBox(Textik,0,0);
		hNewMenu->EnableMenuItem(ID_MMNEWSTATICFIRST + I,MF_ENABLED|MF_BYCOMMAND);
*/
	}


	//Vlozim do menu delici caru:
//	hNewMenu->InsertMenu(	-1, //pridej na konec seznamu
//								MF_SEPARATOR,
//								0,
//								""
//							);

	//Vlozim do menu aktivni prvky:
	//for(I=ID_MMACTIVEFIRST;I<=ID_MMNEWACTIVELAST;I++)
	//	hMainMenu->InsertMenu(-1,MF_BYPOSITION,I,/*nazev*/,/*bitmap*/)
	
	//pokud by se zmeny neprovedly, je treba volat: CWnd::DrawMenuBar()
	//:Iva

	// TODO: Remove this if you don't want tool tips
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


