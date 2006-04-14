// AttributeLinkTableDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ReportAsistent.h"
#include "AttributeLinkTableDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAttributeLinkTableDialog dialog


CAttributeLinkTableDialog::CAttributeLinkTableDialog(IXMLDOMElementPtr & edited_element, CWnd* pParent /*=NULL*/)
	: CDialog(CAttributeLinkTableDialog::IDD, pParent), CAttributeLinkDialogBase(edited_element)
{
	//{{AFX_DATA_INIT(CAttributeLinkTableDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAttributeLinkTableDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAttributeLinkTableDialog)
	DDX_Control(pDX, IDC_TARGET_COMBO, m_TargetCombo);
	DDX_Control(pDX, IDC_ATTRIBUTES_LIST, m_AttributesList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAttributeLinkTableDialog, CDialog)
	//{{AFX_MSG_MAP(CAttributeLinkTableDialog)
	ON_CBN_SELCHANGE(IDC_TARGET_COMBO, OnSelchangeTargetCombo)
	ON_BN_CLICKED(IDC_REFRESH_BUTTON, OnRefreshButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAttributeLinkTableDialog message handlers

BOOL CAttributeLinkTableDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitBaseDialog(m_AttributesList, m_TargetCombo);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAttributeLinkTableDialog::OnSelchangeTargetCombo() 
{
	CString target_id;
	m_TargetCombo.GetWindowText(target_id);
	FillAttributesList(m_AttributesList, target_id);	
}

void CAttributeLinkTableDialog::OnRefreshButton() 
{
	CString s;
	m_TargetCombo.GetWindowText(s);

	OnRefresh(m_AttributesList, s);	
}
