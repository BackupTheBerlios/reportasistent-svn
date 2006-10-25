// AElFiltersConfigDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ReportAsistent.h"
#include "AElFiltersConfigDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAElFiltersConfigDialog dialog


CAElFiltersConfigDialog::CAElFiltersConfigDialog(MSXML2::IXMLDOMElementPtr & active_element, CWnd* pParent)
	: CPropertyPage(CAElFiltersConfigDialog::IDD), m_active_element(active_element)
{
	//{{AFX_DATA_INIT(CAElFiltersConfigDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAElFiltersConfigDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAElFiltersConfigDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAElFiltersConfigDialog, CDialog)
	//{{AFX_MSG_MAP(CAElFiltersConfigDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAElFiltersConfigDialog message handlers
