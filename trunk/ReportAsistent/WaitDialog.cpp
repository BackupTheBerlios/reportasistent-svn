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


CWaitDialog::CWaitDialog(LPCTSTR strDlgText, CWnd* pParent /*=NULL*/)
	: CDialog(CWaitDialog::IDD, pParent), m_bEndDialog(FALSE), m_strDlgText(strDlgText)
{
	//{{AFX_DATA_INIT(CWaitDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
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
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWaitDialog message handlers

BOOL CWaitDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_ReasonText.SetWindowText(m_strDlgText);
	
	SetTimer(1, 30, NULL);
	
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
	m_bEndDialog = TRUE;
	//EndDialog(IDOK);	
}

void CWaitDialog::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	//dedek: cancel disabled
	//CDialog::OnCancel();
}

void CWaitDialog::DoThreadFunction(WaitUserThreadFunction5 f, LPARAM Param1, LPARAM Param2, LPARAM Param3, LPARAM Param4, LPARAM Param5)
{
	DoThreadFunctionImpl(f, 4,  Param1,  Param2,  Param3,  Param4,  Param5);
}

void CWaitDialog::DoThreadFunction(WaitUserThreadFunction4 f, LPARAM Param1, LPARAM Param2, LPARAM Param3, LPARAM Param4)
{
	DoThreadFunctionImpl(f, 3,  Param1,  Param2,  Param3,  Param4, 0);
}

void CWaitDialog::DoThreadFunction(WaitUserThreadFunction3 f, LPARAM Param1, LPARAM Param2, LPARAM Param3)
{
	DoThreadFunctionImpl(f, 3,  Param1,  Param2,  Param3, 0, 0);
}

void CWaitDialog::DoThreadFunction(WaitUserThreadFunction2 f, LPARAM Param1, LPARAM Param2)
{
	DoThreadFunctionImpl(f, 2,  Param1,  Param2, 0, 0, 0);
}

void CWaitDialog::DoThreadFunction(WaitUserThreadFunction1 f, LPARAM Param1)
{
	DoThreadFunctionImpl(f, 1,  Param1, 0, 0, 0, 0);
}

void CWaitDialog::DoThreadFunction(WaitUserThreadFunction0 f)
{
	DoThreadFunctionImpl(f, 0, 0, 0, 0, 0, 0);
}


void CWaitDialog::DoThreadFunctionImpl(void *f, int nParams, LPARAM Param1, LPARAM Param2, LPARAM Param3, LPARAM Param4, LPARAM Param5)
{

}
