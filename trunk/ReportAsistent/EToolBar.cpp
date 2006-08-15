// EToolBar.cpp : implementation file
//

#include "stdafx.h"
#include "ReportAsistent.h"
#include "EToolBar.h"
#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEToolBar

CEToolBar::CEToolBar()
{
}

CEToolBar::~CEToolBar()
{
}


BEGIN_MESSAGE_MAP(CEToolBar, CToolBar)
	//{{AFX_MSG_MAP(CEToolBar)
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEToolBar message handlers

void CEToolBar::OnMouseMove(UINT nFlags, CPoint point) 
{
	CElementManager & OElementManager = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;

	CStatusBar * StatBar;
	TBBUTTON tbBut;
	CToolBarCtrl & TBCtrl = this->GetToolBarCtrl();
	int iBut  = TBCtrl.HitTest(&point);	
	TBCtrl.GetButton(iBut,&tbBut);
	int elID = tbBut.dwData; // ve fci CMainFrm.CreateS(A)EToolBar() do teto polozky vkladam Id typu prvku, ktery toto tlacitko vytvari
	CString statusMsg = "Create new ";
	statusMsg += OElementManager.getElementLabel(elID);
	if ( 0<=iBut) //Mys je nad nejakym tlacitkem
	{

		CFrameWnd* mWnd = AfxGetMainWnd()->GetTopLevelFrame();

		StatBar = (CStatusBar*)(mWnd->GetMessageBar());
		if (StatBar)
			StatBar->SetPaneText(0,(LPCTSTR) statusMsg,TRUE);

	}
	

	CToolBar::OnMouseMove(nFlags,point); 
}
