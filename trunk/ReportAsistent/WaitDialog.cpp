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
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWaitDialog, CDialog)
	//{{AFX_MSG_MAP(CWaitDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWaitDialog message handlers
