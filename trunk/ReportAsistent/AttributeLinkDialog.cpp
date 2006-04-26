// AttributeLinkDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ReportAsistent.h"
#include "AttributeLinkDialog.h"
#include "APTransform.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CAttributeLinkDialog dialog


CAttributeLinkDialog::CAttributeLinkDialog(IXMLDOMElementPtr & edited_element, CWnd* pParent /*=NULL*/)
	: CDialog(CAttributeLinkDialog::IDD, pParent), CAttributeLinkDialogBase(edited_element)
{
	//{{AFX_DATA_INIT(CAttributeLinkDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAttributeLinkDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAttributeLinkDialog)
	DDX_Control(pDX, IDC_ATTRIBUTES_LIST, m_AttributesList);
	DDX_Control(pDX, IDC_TARGET_COMBO, m_TargetCombo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAttributeLinkDialog, CDialog)
	//{{AFX_MSG_MAP(CAttributeLinkDialog)
	ON_CBN_SELCHANGE(IDC_TARGET_COMBO, OnSelchangeTargetCombo)
	ON_BN_CLICKED(IDC_REFRESH_BUTTON, OnRefreshButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAttributeLinkDialog message handlers

BOOL CAttributeLinkDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitBaseDialog(m_AttributesList, m_TargetCombo);

	
	
	//najdi vybranou polozku
	LVFINDINFO info;
	ZeroMemory(& info, sizeof info);

	CString attr_n = (LPCTSTR) (_bstr_t) m_edited_element->getAttribute("attr_name");

	info.flags = LVFI_STRING;
	info.psz = attr_n;
	int item = m_AttributesList.FindItem(& info);

	//vyber vybranou
	m_AttributesList.SetItemState(item, LVIS_SELECTED, LVIS_SELECTED);

	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CAttributeLinkDialog::OnSelchangeTargetCombo() 
{
	CString target_id;
	m_TargetCombo.GetWindowText(target_id);
	FillAttributesList(m_AttributesList, target_id);
}

void CAttributeLinkDialog::OnOK() 
{
	CString s;
	
	
	SaveTarget(m_TargetCombo);
	
	//attr name
	POSITION pos = m_AttributesList.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nItem = m_AttributesList.GetNextSelectedItem(pos);
		s = m_AttributesList.GetItemText(nItem, ATTRLIST_CL_NAME);
	}
	m_edited_element->setAttribute("attr_name", (LPCTSTR) s);
	
	CDialog::OnOK();
}

void CAttributeLinkDialog::OnRefreshButton() 
{
	
	CString s;
	m_TargetCombo.GetWindowText(s);

	OnRefresh(m_AttributesList, s);
}
