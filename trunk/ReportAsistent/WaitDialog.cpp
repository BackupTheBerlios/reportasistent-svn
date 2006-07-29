// WaitDialog.cpp : implementation file
//

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


CWaitDialog::CWaitDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CWaitDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWaitDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CWaitDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWaitDialog)
	DDX_Control(pDX, IDC_WAIT_ANIMATION, m_wait_animation);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWaitDialog, CDialog)
	//{{AFX_MSG_MAP(CWaitDialog)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWaitDialog message handlers

BOOL CWaitDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetTimer(1, 30, NULL);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CWaitDialog::OnTimer(UINT nIDEvent) 
{
	m_wait_animation.RedrawWindow();
	
	CDialog::OnTimer(nIDEvent);
}
