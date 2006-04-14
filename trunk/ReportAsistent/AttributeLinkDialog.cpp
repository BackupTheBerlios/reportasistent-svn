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
	: CDialog(CAttributeLinkDialog::IDD, pParent), m_edited_element(edited_element)
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
	FillTargets();
	if (CB_ERR == m_TargetCombo.SelectString(-1, (_bstr_t) m_edited_element->getAttribute("target")))
	{
		CString s;
		m_TargetCombo.GetLBText(0, s);
		m_TargetCombo.SelectString(-1, s);
	}

	InitAttributesList();
	FillAttributesList();


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

void CAttributeLinkDialog::FillTargets()
{
	
	IXMLDOMNodeListPtr el_list = m_edited_element->ownerDocument->selectNodes("//active_element/@id");

	for (int a=0; a < el_list->length; a++)
	{
		m_TargetCombo.AddString(el_list->item[a]->text);
	}

	el_list.Release();
}

void CAttributeLinkDialog::InitAttributesList()
{
	CRect r;
	m_AttributesList.GetWindowRect(& r);
	m_AttributesList.InsertColumn(0, "name", LVCFMT_LEFT, r.Width()/2);
	m_AttributesList.InsertColumn(1, "value", LVCFMT_LEFT, r.Width()/2 -10);
}

void CAttributeLinkDialog::FillAttributesList()
{
	m_AttributesList.DeleteAllItems();
	
	CString s;
	m_TargetCombo.GetWindowText(s);

	CString query;
	query.Format("id(\"%s\")/attributes/element_attributes/attribute", (LPCTSTR) s);

	IXMLDOMSelectionPtr sel = m_edited_element->ownerDocument->selectNodes((LPCTSTR) query);

	for (int a=0; a < sel->length; a++)
	{
		IXMLDOMElementPtr el = sel->item[a];

		int item = m_AttributesList.InsertItem(a, (_bstr_t) el->getAttribute("name"));

		m_AttributesList.SetItemText(item, 1, (_bstr_t) el->getAttribute("value"));

		el.Release();

	}

	sel.Release();
}

void CAttributeLinkDialog::OnSelchangeTargetCombo() 
{
	FillAttributesList();	
}

void CAttributeLinkDialog::OnOK() 
{
	CString s;
	
	//target
	m_TargetCombo.GetWindowText(s);
	m_edited_element->setAttribute("target", (LPCTSTR) s);
	s = "";

	
	//attr name
	POSITION pos = m_AttributesList.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nItem = m_AttributesList.GetNextSelectedItem(pos);
		s = m_AttributesList.GetItemText(nItem, 0);
	}
	m_edited_element->setAttribute("attr_name", (LPCTSTR) s);
	
	CDialog::OnOK();
}

void CAttributeLinkDialog::OnRefreshButton() 
{
	
	CString s;
	m_TargetCombo.GetWindowText(s);
	CString query;
	query.Format("id(\"%s\")", (LPCTSTR) s);
	
	IXMLDOMElementPtr el = m_edited_element->ownerDocument->selectSingleNode((LPCTSTR) query);
	CAElTransform tr(el);

	if (! tr.FillElementAttributes(0))
		AfxMessageBox(IDS_REFRESH_EL_ATTRIBUTES_FAILED);
	
	el.Release();


	FillAttributesList();
}
