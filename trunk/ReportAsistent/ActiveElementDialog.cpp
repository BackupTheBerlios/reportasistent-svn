// ActiveElementDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ReportAsistent.h"
#include "ActiveElementDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CActiveElementDialog dialog


CActiveElementDialog::CActiveElementDialog(IXMLDOMElementPtr & active_element, CWnd* pParent /*=NULL*/)
	: CDialog(CActiveElementDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CActiveElementDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CActiveElementDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CActiveElementDialog)
	DDX_Control(pDX, IDC_TAB1, m_TabControl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CActiveElementDialog, CDialog)
	//{{AFX_MSG_MAP(CActiveElementDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CActiveElementDialog message handlers
