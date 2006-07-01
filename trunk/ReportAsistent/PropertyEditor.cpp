// PropertyEditor.cpp : implementation file
//

#include "stdafx.h"
#include "ReportAsistent.h"
#include "PropertyEditor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropertyEditor dialog


CPropertyEditor::CPropertyEditor(CWnd* pParent /*=NULL*/)
	: CDialog(CPropertyEditor::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPropertyEditor)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPropertyEditor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropertyEditor)
	DDX_Control(pDX, IDC_ERROR_TEXT, m_err_text);
	DDX_Control(pDX, IDC_STATIC1, m_static_border);
	DDX_Control(pDX, IDC_SCROLLBAR1, m_scrollbar);
	DDX_Control(pDX, IDOK, m_ok_button);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropertyEditor, CDialog)
	//{{AFX_MSG_MAP(CPropertyEditor)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropertyEditor message handlers
