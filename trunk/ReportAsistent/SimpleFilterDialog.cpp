// SimpleFilterDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ReportAsistent.h"
#include "SimpleFilterDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSimpleFilterDialog dialog


CSimpleFilterDialog::CSimpleFilterDialog(IXMLDOMElementPtr & active_element, BSTR plugin_output, CWnd* pParent)
	: CDialog(CSimpleFilterDialog::IDD, pParent), m_active_element(active_element)
{
	//{{AFX_DATA_INIT(CSimpleFilterDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSimpleFilterDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSimpleFilterDialog)
	DDX_Control(pDX, IDC_FILTER_LIST, m_FilterList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSimpleFilterDialog, CDialog)
	//{{AFX_MSG_MAP(CSimpleFilterDialog)
	ON_NOTIFY(LVN_DELETEITEM, IDC_FILTER_LIST, OnDeleteitemFilterList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimpleFilterDialog message handlers

BOOL CSimpleFilterDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSimpleFilterDialog::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CSimpleFilterDialog::OnDeleteitemFilterList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}
