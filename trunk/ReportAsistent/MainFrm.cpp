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

	//vytvoreni toolbaru	
	if (!m_wndToolBar.CreateEx(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

/*	//vytvoreni dialogbaru
	if (!m_wndDlgBar.Create(this, IDR_MAINFRAME, 
		CBRS_ALIGN_BOTTOM, AFX_IDW_DIALOGBAR))
	{
		TRACE0("Failed to create dialogbar\n");
		return -1;		// fail to create
	}
*/

	//CPoint point( 50, 50 );	
	//this->FloatControlBar(&m_wndDlgBar, point,CBRS_ALIGN_TOP );



	//vytvoreni rebaru
	if (!m_wndReBar.Create(this) ||
		!m_wndReBar.AddBar(&m_wndToolBar)/* ||
		!m_wndReBar.AddBar(&m_wndDlgBar)*/)
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
	CMenu * hMainMenu = /*AfxGetApp()->GetMainWnd()->*/GetMenu();
	CMenu * hNewMenu = hMainMenu->GetSubMenu(1/*Edit*/)->GetSubMenu(7/*New*/);
	char Textik [20]="";
	/*	hNewMenu->GetMenuString(0,Textik,19,MF_BYPOSITION);
		AfxMessageBox(Textik,0,0);*/

	CElementManager & OElementManager = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;

	int I;
	//Vlozim do menu staticke prvky:
	 
	for(I=1; //Vkladam az od druheho prvku, prvni - "text" uz je pridan v resourcich 
		I<=(OElementManager.getFirstActiveElementID() - OElementManager.getFirstStaticElementID()-1);I++)
	{
		hNewMenu->InsertMenu(	-1, //pridej na konec seznamu
								MF_BYPOSITION,
								ID_MMNEWSTATICFIRST + I,
								OElementManager.getElementName(I+OElementManager.getFirstStaticElementID()) //nazev
								);	
	}


	//Vlozim do menu delici caru:
	hNewMenu->InsertMenu(	-1, //pridej na konec seznamu
								MF_SEPARATOR,
								0,
								""
							);

	//Vlozim do menu aktivni prvky:
	for(I=0;I<=(OElementManager.getLastElementId() - OElementManager.getFirstActiveElementID());I++)
	{
		hNewMenu->InsertMenu(	-1, //pridej na konec seznamu
								MF_BYPOSITION,
								ID_MMNEWACTIVEFIRST + I,
								OElementManager.getElementLabel/*kody: predtim bylo Name*/(I+OElementManager.getFirstActiveElementID()) //nazev
								);	
	}
	//pokud by se zmeny neprovedly, je treba volat: CWnd::DrawMenuBar()


//Vytvorim ToolBar aktivnich prvku:

	CRect rcBorders (0, 1, 1, 5);
	m_wndAEToolBar.CreateEx(this,//AfxGetApp()->GetMainWnd(), 
							TBSTYLE_FLAT, 
							WS_CHILD | WS_VISIBLE | CBRS_ALIGN_BOTTOM|CBRS_TOOLTIPS|CBRS_FLYBY , 
							rcBorders, 
							AFX_IDW_TOOLBAR);


/*							( AfxGetApp()->GetMainWnd(),			//CWnd* pParentWnd, 
							WS_CHILD | WS_VISIBLE | CBRS_BOTTOM |CBRS_SIZE_DYNAMIC,	//dwStyle
							AFX_IDW_TOOLBAR );					//nID
*/
	CToolBarCtrl& TBCtrl = m_wndAEToolBar.GetToolBarCtrl();
	
	//nactu obrazky
	mImageList.Create(16, 16, //rozmery obrazku k nacteni do ImageListu	
						ILC_MASK, 
						NUM_PICTURES_TREECTRL, //pocatecni pocet obrazku v ImageListu..viz Stdafx.h
						MAX_ELEMENT_COUNT);//o kolik obrazku se ImageList muze zvetsit.. ??
	OElementManager.FillImageList(mImageList);
	mImageList.Remove(0);//odstranim obrazek prvku Unknown
	mImageList.Remove(0);//odstranim obrazek prvku Report

	int nBut=mImageList.GetImageCount( );
	CPoint size(20,24);
	TBCtrl.SetButtonSize(size);
	TBCtrl.SetImageList(&mImageList);

	TBBUTTON TBButtons[MAX_ELEMENT_COUNT];

	
	
	//staticke
	for(I=0; 
		I<=(OElementManager.getFirstActiveElementID() - OElementManager.getFirstStaticElementID()-1);I++)
	{
		TBButtons[I].iBitmap=I;
		TBButtons[I].idCommand=ID_MMNEWSTATICFIRST + I;
		TBButtons[I].fsState=TBSTATE_ENABLED;
		TBButtons[I].fsStyle=TBSTYLE_BUTTON;
		TBButtons[I].dwData=NULL;
	}
	//separator
	UINT J=I;
/*	TBButtons[J].iBitmap=J;
	TBButtons[J].idCommand=0;
	TBButtons[J].fsState=TBSTATE_ENABLED;
	TBButtons[J].fsStyle=TBSTYLE_SEP;
	TBButtons[J].dwData=NULL;
	J++;*/
	//aktivni
	for(I=0;I<=(OElementManager.getLastElementId() - OElementManager.getFirstActiveElementID());I++)
	{
		TBButtons[J+I].iBitmap=J+I;
		TBButtons[J+I].idCommand=ID_MMNEWACTIVEFIRST + I;
		TBButtons[J+I].fsState=TBSTATE_ENABLED;
		TBButtons[J+I].fsStyle=TBSTYLE_BUTTON;
		TBButtons[J+I].dwData=NULL;
	}
		
	TBCtrl.AddButtons(nBut/*+1*/, TBButtons );

//Pridani ToolTipu k AE Tool Baru
	m_AEToolTips.Create(&m_wndAEToolBar,0);
	CString cstrToolTip;
	int Id;
	CRect rect;

	for (Id=OElementManager.ElementIdFromName("text") ; Id <=OElementManager.getLastElementId() ; Id++)
	{
		cstrToolTip = OElementManager.getElementName(Id);
		m_AEToolTips.AddTool(this, (LPCTSTR)cstrToolTip, NULL, 0);
	}

	//m_AEToolTips.Activate(TRUE);
	TBCtrl.SetToolTips(&m_AEToolTips);
	CToolTipCtrl * pom = TBCtrl.GetToolTips();

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


