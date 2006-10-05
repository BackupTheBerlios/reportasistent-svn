// ComplexFilterDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ReportAsistent.h"
#include "ComplexFilterDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CComplexFilterDialog property page

IMPLEMENT_DYNCREATE(CComplexFilterDialog, CPropertyPage)

CComplexFilterDialog::CComplexFilterDialog() : CPropertyPage(CComplexFilterDialog::IDD)
{
	//{{AFX_DATA_INIT(CComplexFilterDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CComplexFilterDialog::~CComplexFilterDialog()
{
}

void CComplexFilterDialog::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CComplexFilterDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CComplexFilterDialog, CPropertyPage)
	//{{AFX_MSG_MAP(CComplexFilterDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComplexFilterDialog message handlers
