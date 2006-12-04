// StartDialog.cpp : implementation file
//

#include "stdafx.h"
#include "reportasistent.h"
#include "StartDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStartDialog dialog


CStartDialog::CStartDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CStartDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStartDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CStartDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStartDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStartDialog, CDialog)
	//{{AFX_MSG_MAP(CStartDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStartDialog message handlers
