// WaitDialog.cpp : implementation file
//
/*
This file is part of LM Report Asistent.

Authors: Jan Dedek, Jan Kodym, Martin Chrz, Iva Bartunkova

LM Report Asistent is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

LM Report Asistent is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with LM Report Asistent; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/



#include "stdafx.h"
#include "ReportAsistent.h"
#include "WaitDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWaitDialog dialog


CWaitDialog::CWaitDialog(LPCTSTR strDlgText, BOOL bShowKillButtons, CWnd* pParent /*=NULL*/)
	: CDialog(CWaitDialog::IDD, pParent), m_bEndDialog(FALSE), m_strDlgText(strDlgText),
	m_bShowKillButtons(bShowKillButtons)
{
	//{{AFX_DATA_INIT(CWaitDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_pThreadPramas = new SThreadPramas;
}


void CWaitDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWaitDialog)
	DDX_Control(pDX, IDC_REASON_TEXT, m_ReasonText);
	DDX_Control(pDX, IDC_WAIT_ANIMATION, m_wait_animation);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWaitDialog, CDialog)
	//{{AFX_MSG_MAP(CWaitDialog)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_EXIT_BUTTON, OnExitButton)
	ON_BN_CLICKED(IDC_KILL_THREAD_BUTTON, OnKillThreadButton)
	ON_BN_CLICKED(IDC_RESUME_APP_BUTTON, OnResumeAppButton)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWaitDialog message handlers

BOOL CWaitDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	if (! m_bShowKillButtons)
	{
		GetDlgItem(IDC_KILL_THREAD_BUTTON)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RESUME_APP_BUTTON)->ShowWindow(SW_HIDE);
	}

	m_ReasonText.SetWindowText(m_strDlgText);
	
	m_nTimer = SetTimer(1, 30, NULL);

	m_pThreadPramas->hWaitDlg = m_hWnd;
	m_pWorkerThread->ResumeThread();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CWaitDialog::OnTimer(UINT nIDEvent) 
{
	if (m_bEndDialog) EndDialog(IDOK);

	m_wait_animation.RedrawWindow();
	
	CDialog::OnTimer(nIDEvent);
}

void CWaitDialog::OnExitButton() 
{
	m_pThreadPramas = NULL;
	m_bEndDialog = TRUE;
	//EndDialog(IDOK);	
}

void CWaitDialog::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	//dedek: cancel disabled
	//CDialog::OnCancel();
}



/************************************************************************************/
//DoThreadFunctions
void CWaitDialog::DoThreadFunction(WaitUserThreadFunction5 f, LPARAM Param1, LPARAM Param2, LPARAM Param3, LPARAM Param4, LPARAM Param5)
{
	m_pThreadPramas->nParams = 5;
	m_pThreadPramas->params[0] = Param1;
	m_pThreadPramas->params[1] = Param2;
	m_pThreadPramas->params[2] = Param3;
	m_pThreadPramas->params[3] = Param4;
	m_pThreadPramas->params[4] = Param5;
	DoThreadFunctionImpl(f);
}

void CWaitDialog::DoThreadFunction(WaitUserThreadFunction4 f, LPARAM Param1, LPARAM Param2, LPARAM Param3, LPARAM Param4)
{
	m_pThreadPramas->nParams = 4;
	m_pThreadPramas->params[0] = Param1;
	m_pThreadPramas->params[1] = Param2;
	m_pThreadPramas->params[2] = Param3;
	m_pThreadPramas->params[3] = Param4;
	DoThreadFunctionImpl(f);
}

void CWaitDialog::DoThreadFunction(WaitUserThreadFunction3 f, LPARAM Param1, LPARAM Param2, LPARAM Param3)
{
	m_pThreadPramas->nParams = 3;
	m_pThreadPramas->params[0] = Param1;
	m_pThreadPramas->params[1] = Param2;
	m_pThreadPramas->params[2] = Param3;
	DoThreadFunctionImpl(f);
}

void CWaitDialog::DoThreadFunction(WaitUserThreadFunction2 f, LPARAM Param1, LPARAM Param2)
{
	m_pThreadPramas->nParams = 2;
	m_pThreadPramas->params[0] = Param1;
	m_pThreadPramas->params[1] = Param2;
	DoThreadFunctionImpl(f);
}

void CWaitDialog::DoThreadFunction(WaitUserThreadFunction1 f, LPARAM Param1)
{
	m_pThreadPramas->nParams = 1;
	m_pThreadPramas->params[0] = Param1;
	DoThreadFunctionImpl(f);
}

void CWaitDialog::DoThreadFunction(WaitUserThreadFunction0 f)
{
	m_pThreadPramas->nParams = 0;
	DoThreadFunctionImpl(f);
}
//DoThreadFunctions end
/************************************************************************************/ 


void CWaitDialog::DoThreadFunctionImpl(void *f)
{
	m_pThreadPramas->pUserFunction = f;
	m_pWorkerThread = AfxBeginThread(
		ThreadControllingFunction, m_pThreadPramas, 
		THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);

	DoModal();
}

UINT CWaitDialog::ThreadControllingFunction(LPVOID pParam)
{
	SThreadPramas * p =  (SThreadPramas *) pParam;

	switch (p->nParams)
	{
	case 5:
		((WaitUserThreadFunction5) p->pUserFunction)(p->params[0], p->params[1], p->params[2], p->params[3], p->params[4]);
		break;
	case 4:
		((WaitUserThreadFunction4) p->pUserFunction)(p->params[0], p->params[1], p->params[2], p->params[3]);
		break;
	case 3:
		((WaitUserThreadFunction3) p->pUserFunction)(p->params[0], p->params[1], p->params[2]);
		break;
	case 2:
		((WaitUserThreadFunction2) p->pUserFunction)(p->params[0], p->params[1]);
		break;
	case 1:
		((WaitUserThreadFunction1) p->pUserFunction)(p->params[0]);
		break;
	case 0:
		((WaitUserThreadFunction0) p->pUserFunction)();
		break;
	}

	if (IsWindow(p->hWaitDlg))
		::SendMessage(p->hWaitDlg, WM_COMMAND, IDC_EXIT_BUTTON, 0);

	delete	p;

	return 0;
}

void CWaitDialog::OnKillThreadButton() 
{
	if (IDYES != AfxMessageBox(IDS_CONFIRM_THRAD_KILL, MB_ICONWARNING | MB_YESNO))
		return;
	
	TerminateThread(m_pWorkerThread->m_hThread, 0);
	
	if (m_pThreadPramas != NULL)
	{
		delete m_pThreadPramas;
		m_pThreadPramas = NULL;
	}
	
	EndDialog(IDOK);	
}

void CWaitDialog::OnResumeAppButton() 
{
	if (IDYES != AfxMessageBox(IDS_CONFIRM_APP_RESUME, MB_ICONWARNING | MB_YESNO))
		return;

	EndDialog(IDOK);	
}

void CWaitDialog::OnDestroy() 
{
	KillTimer(m_nTimer);

	if (m_pThreadPramas != NULL)
		m_pThreadPramas->hWaitDlg = NULL;	
	
	CDialog::OnDestroy();
}

//DEL void CWaitDialog::OnStnClickedReasonText()
//DEL {
//DEL 	// TODO: Add your control notification handler code here
//DEL }
