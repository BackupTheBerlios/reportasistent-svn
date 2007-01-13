// MainFrm.cpp : implementation of the CMainFrame class
//
//
// This file is part of LM Report Asistent. (http://reportasistent.berlios.de, reportasistent-list@lists.berlios.de)
//
// Authors: Jan Dedek, Jan Kodym, Martin Chrz, Iva Bartunkova 
//
// LM Report Asistent is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// LM Report Asistent is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with LM Report Asistent; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
#include "stdafx.h"
#include "ReportAsistent.h"
#include "CSkeletonDoc.h"
#include "APTransform.h"

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
	ON_UPDATE_COMMAND_UI(ID_VIEW_STATICELEMENTSTOOLBAR, OnUpdateViewStaticelementstoolbar)
	ON_COMMAND(ID_VIEW_STATICELEMENTSTOOLBAR, OnViewStaticelementstoolbar)
	ON_COMMAND(ID_VIEW_ACTIVEELEMENTTOOLBAR, OnViewActiveelementtoolbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ACTIVEELEMENTTOOLBAR, OnUpdateViewActiveelementtoolbar)
	ON_COMMAND(ID_WORD_EDITOR_EDIT_ACTIVE_ELEMENT, OnWordEditorEditActiveElement)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
   ON_COMMAND(ID_HELP_FINDER, CFrameWnd::OnHelpFinder)
   ON_COMMAND(ID_HELP, CFrameWnd::OnHelp)
   ON_COMMAND(ID_CONTEXT_HELP, CFrameWnd::OnContextHelp)
   ON_COMMAND(ID_DEFAULT_HELP, CFrameWnd::OnHelpFinder)
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

	//Vytvorim ToolBary aktivnich a statickych prvku:
	CreateSEToolBar();
	CreateAEToolBar();

	//vytvoreni rebaru
	if (!m_wndReBar.Create(this) ||
		!m_wndReBar.AddBar(&m_wndToolBar)|| 
		!m_wndReBar.AddBar(&m_wndSEToolBar)||
		!m_wndReBar.AddBar(&m_wndAEToolBar))
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
	CMenu * hMainMenu = GetMenu();
	CMenu * hNewMenu = hMainMenu->GetSubMenu(1/*Edit*/)->GetSubMenu(5/*New*/);
	char Textik [20]="";

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


	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

/*	//povoleni dockovani toolbaru kdekoliv v hlavnim okne
	EnableDocking(CBRS_ALIGN_ANY);

	//povoleni jednotlivym toolbarum, aby kdekoliv dockovaly
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	m_wndAEToolBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndAEToolBar);

	m_wndSEToolBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndSEToolBar);
*/
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




BOOL CMainFrame::CreateAEToolBar()
{
	CElementManager & OElementManager = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;
	
	CRect rcBorders (0, 0, 0, 0);
	m_wndAEToolBar.CreateEx(this,//AfxGetApp()->GetMainWnd(), 
							TBSTYLE_FLAT, 
							WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP|CBRS_TOOLTIPS|CBRS_FLYBY,// |CBRS_SIZE_DYNAMIC, 
							rcBorders, 
							AFX_IDW_TOOLBAR);

	//ziskam ukazatel na odpovidajici ctrl
	CToolBarCtrl& TBCtrl = m_wndAEToolBar.GetToolBarCtrl();
	
	//nactu obrazky
	mAImageList.Create(16, 16, //rozmery obrazku k nacteni do ImageListu	
						ILC_MASK|ILC_COLOR8,  
						OElementManager.getLastElementId(), //pocatecni pocet obrazku v ImageListu..viz Stdafx.h																	
						OElementManager.getLastElementId());//o kolik obrazku se ImageList muze zvetsit.. ??
	OElementManager.FillImageList(mAImageList);

	//odstranim nepotrebne obrazky
	int nBut=mAImageList.GetImageCount( );
	int I;
	for(I=0;I<OElementManager.getFirstActiveElementID();I++)
		mAImageList.Remove(0);

	nBut=mAImageList.GetImageCount();

	CPoint sizeButton(24,24);
	CPoint sizeBitmap(16,16);
	TBCtrl.SetBitmapSize(sizeBitmap);
	TBCtrl.SetButtonSize(sizeButton);
	TBCtrl.SetImageList(&mAImageList);

	TBBUTTON TBButtons[MAX_ELEMENT_COUNT];

	//Naplnim pole struktur - propojeni s patricnymi ID
	for(I=0; I<nBut;I++)
	{
		TBButtons[I].iBitmap=I;
		TBButtons[I].idCommand=ID_MMNEWACTIVEFIRST + I;
		TBButtons[I].fsState=TBSTATE_ENABLED;
		TBButtons[I].fsStyle=TBSTYLE_BUTTON;
		TBButtons[I].dwData=OElementManager.getFirstActiveElementID()+I;//Id typu prvku, ktery bude timto tlacitkem vytvaren
		TBButtons[I].iString=NULL;
	}

	TBCtrl.AddButtons(nBut, TBButtons );
	
	//Pridani ToolTipu
	m_wndAEToolBar.EnableToolTips(); //funguje to i bez tohoto radku, ale pro jistotu ho tu necham
	
	m_AEToolTips.Create(&m_wndAEToolBar,0);
	CString cstrToolTip;//prislusny text k jednotlivym tlacitkum
	CRect rect;//obdelnik jednotlivych tlacitek vzhledem k levemu hornimu rohu toolbaru

	for (I=0;I<nBut;I++) // propojeni textu do tooltipu a tooltipu k tlacitkum
	{
		cstrToolTip = OElementManager.getElementLabel(I+OElementManager.getFirstActiveElementID());
		m_wndAEToolBar.GetItemRect( I, &rect );
		m_AEToolTips.AddTool(&m_wndAEToolBar, (LPCTSTR)cstrToolTip, &rect, I+1/*zvlastnost teto funkce - indexovani od 1*/);
	}

	TBCtrl.SetToolTips(&m_AEToolTips);//prirazeni jiz propojeneho tooltipu k toolbaru (propojenych tooltipu k memu toolbaru muze byt vic, timto urcim, ktery chci nyni pouzivat

	return TRUE;
}

BOOL CMainFrame::CreateSEToolBar()
{
	CElementManager & OElementManager = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;
	
	CRect rcBorders (0, 0, 0, 0);
//ToolBar vytvorim
	m_wndSEToolBar.CreateEx(this, //AfxGetApp()->GetMainWnd(), 
							TBSTYLE_FLAT|TBSTYLE_TOOLTIPS, 
							WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP|CBRS_TOOLTIPS|CBRS_FLYBY,// |CBRS_SIZE_DYNAMIC, 
							rcBorders, 
							AFX_IDW_TOOLBAR);

	
	//ziskam ukazatel na odpovidajici ctrl
	CToolBarCtrl& TBCtrl = m_wndSEToolBar.GetToolBarCtrl();
	
	//nactu obrazky
	mSImageList.Create(16, 16, //rozmery obrazku k nacteni do ImageListu	
						ILC_MASK|ILC_COLOR8, 
						OElementManager.getFirstActiveElementID(), //pocatecni pocet obrazku v ImageListu..viz Stdafx.h																	
						OElementManager.getFirstActiveElementID());//o kolik obrazku se ImageList muze zvetsit.. ??
	BOOL Res = OElementManager.FillImageList(mSImageList);

	IMAGEINFO ImgInfo;
	Res = mSImageList.GetImageInfo( 0, &ImgInfo ) ;
	
	//odstranim nepotrebne obrazky
	int nBut=mSImageList.GetImageCount( );
	int I;
	for(I=OElementManager.getFirstActiveElementID();I<=OElementManager.getLastElementId();I++)
	{
		mSImageList.Remove(OElementManager.getFirstActiveElementID());
		nBut=mSImageList.GetImageCount( );
	}

	mSImageList.Remove(0);//odstranim obrazek prvku Unknown
	mSImageList.Remove(0);//odstranim obrazek prvku Report

	nBut=mSImageList.GetImageCount( );

	CPoint sizeButton(24,24);
	CPoint sizeBitmap(16,16);
	TBCtrl.SetBitmapSize(sizeBitmap);
	TBCtrl.SetButtonSize(sizeButton);
	TBCtrl.SetImageList(&mSImageList);

	TBBUTTON TBButtons[MAX_ELEMENT_COUNT];

	for(I=0; 
		I<=(OElementManager.getFirstActiveElementID() - OElementManager.getFirstStaticElementID()-1);I++)
	{
		TBButtons[I].iBitmap=I;
		TBButtons[I].idCommand=ID_MMNEWSTATICFIRST + I;
		TBButtons[I].fsState=TBSTATE_ENABLED;
		TBButtons[I].fsStyle=TBSTYLE_BUTTON;
		TBButtons[I].dwData=I+2/*prvky unknown a report*/; //Id typu prvku, ktery bude timto tlacitkem vytvaren
		TBButtons[I].iString=NULL;
	}

	TBCtrl.AddButtons(nBut, TBButtons ); //az tento prikaz skutecne prida tlacitka na toolbar


//Pridani ToolTipu
	m_wndSEToolBar.EnableToolTips(); //funguje to i bez tohoto radku, ale pro jistotu ho tu necham
	
	m_SEToolTips.Create(&m_wndAEToolBar,0);
	CString cstrToolTip; //prislusny text k jednotlivym tlacitkum
	CRect rect; //obdelnik jednotlivych tlacitek vzhledem k levemu hornimu rohu toolbaru
	
	for (I=0;I<nBut;I++)// propojeni textu do tooltipu a tooltipu k tlacitkum
	{
		cstrToolTip = OElementManager.getElementLabel(I+OElementManager.ElementIdFromName("text"));
		m_wndSEToolBar.GetItemRect( I, &rect );
		//prirazeni jiz propojeneho tooltipu k toolbaru (propojenych tooltipu k memu toolbaru muze byt vic, timto urcim, ktery chci nyni pouzivat
		m_SEToolTips.AddTool(&m_wndSEToolBar, (LPCTSTR)cstrToolTip, &rect, I+1/*zvlastnost teto funkce - indexovani od 1*/);
	}

	TBCtrl.SetToolTips(&m_SEToolTips);	//prirazeni jiz propojeneho tooltipu k toolbaru (propojenych tooltipu k memu toolbaru muze byt vic, timto urcim, ktery chci nyni pouzivat

	return TRUE;
}



void CMainFrame::OnUpdateViewStaticelementstoolbar(CCmdUI* pCmdUI)
{	
	pCmdUI->SetCheck((m_wndSEToolBar.GetStyle() & WS_VISIBLE) != 0);
	return;
}

void CMainFrame::OnViewStaticelementstoolbar() 
{
	m_wndSEToolBar.ShowWindow((m_wndSEToolBar.GetStyle() & WS_VISIBLE) == 0);
	RecalcLayout();
	return ;		
}

void CMainFrame::OnViewActiveelementtoolbar() 
{
	m_wndAEToolBar.ShowWindow((m_wndAEToolBar.GetStyle() & WS_VISIBLE) == 0);
	RecalcLayout();
	return ;
}

void CMainFrame::OnUpdateViewActiveelementtoolbar(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck((m_wndAEToolBar.GetStyle() & WS_VISIBLE) != 0);
	return;
	
}

void CMainFrame::WinHelp(DWORD dwData, UINT nCmd) 
{
	if (nCmd == HELP_CONTEXT)
	{
		CString Pom;
		Pom.Format("HELP_CONTEXT , %d", dwData) ;
#ifdef _DEBUG
		AfxMessageBox( (LPCTSTR)Pom);
#endif
		//Translating table:
		//Menu Sec File
		if (dwData >=123136 && dwData <=123169) dwData = 123136;
		if (dwData ==98307 || dwData ==98323 || dwData ==98324) dwData = 123136;
		if (dwData >=123201 && dwData <=123201) dwData = 123136;
		//Menu Sec Edit
		if (dwData >=123170 && dwData <=123173) dwData = 123170;
		if (dwData ==98318) dwData = 123170;
		//Menu Sec View
		if (dwData >=124928 && dwData <=124929) dwData = 124928;
		if (dwData ==98328 ||dwData ==98326) dwData = 124928;
		//Menu Sec Data source
		if (dwData ==98334 ||dwData ==98336) dwData = 98334;
		if (dwData ==98308) dwData = 98334;
		//Menu Sec Help
		if (dwData ==98329 ||dwData ==133200) dwData = 98329;

		//Static Element ID
		if (dwData >=104537 && dwData <=104542) dwData = 104537;
		//Active Element ID
		if (dwData >=104546 && dwData <=104570) dwData = 104546;
		if (dwData >= 666666) dwData=666666;
	} 


	CFrameWnd::WinHelp(dwData, nCmd);
}

void CMainFrame::OnWordEditorEditActiveElement() 
{
	CWordManager & wm = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->WordManager;
	
	wm.WordEditorInsertActiveElement();
}

void CMainFrame::OnClose() 
{
	CWordManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->WordManager;

	if (m.isWordEditorActive())
	{
		m.OpenWordEditor();
	}
	else
	{
		CFrameWnd::OnClose();
	}
}
