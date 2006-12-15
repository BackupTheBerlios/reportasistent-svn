// EToolBar.cpp : implementation file
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
	CFrameWnd* mWnd = AfxGetMainWnd()->GetTopLevelFrame();
	StatBar = (CStatusBar*)(mWnd->GetMessageBar());

	TBBUTTON tbBut;
	CToolBarCtrl & TBCtrl = this->GetToolBarCtrl();
	int iBut  = TBCtrl.HitTest(&point);	
	if ( 0<=iBut) //Mys je nad nejakym tlacitkem
	{
		TBCtrl.GetButton(iBut,&tbBut);
		int elID = tbBut.dwData; // ve fci CMainFrm.CreateS(A)EToolBar() do teto polozky vkladam Id typu prvku, ktery toto tlacitko vytvari
		CString statusMsg = "Create new ";
		statusMsg += OElementManager.getElementLabel(elID);
		
		if (StatBar)
			StatBar->SetPaneText(0,(LPCTSTR) statusMsg,TRUE);

	}
	else
		if (StatBar)StatBar->SetPaneText(0,"Ready",TRUE);
	

	CToolBar::OnMouseMove(nFlags,point); 
}
