// TransformationsDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ReportAsistent.h"
#include "TransformationsDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransformationsDialog dialog


CTransformationsDialog::CTransformationsDialog(IXMLDOMElementPtr & active_element, CWnd* pParent /*=NULL*/)
	: CDialog(CTransformationsDialog::IDD, pParent), m_active_element(active_element)
{
	//{{AFX_DATA_INIT(CTransformationsDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTransformationsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTransformationsDialog)
	DDX_Control(pDX, IDC_SUPPORTED_TRANSF_LIST, m_SupportedList);
	DDX_Control(pDX, IDC_SELECTED_TRANSFS_LIST, m_SelectedList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTransformationsDialog, CDialog)
	//{{AFX_MSG_MAP(CTransformationsDialog)
	ON_BN_CLICKED(IDC_ADD_BUTTON, OnAddButton)
	ON_BN_CLICKED(IDC_REMOVE_BUTTON, OnRemoveButton)
	ON_BN_CLICKED(IDC_MOVE_UP_BUTTON, OnMoveUpButton)
	ON_BN_CLICKED(IDC_MOVE_DOWN_BUTTON, OnMoveDownButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransformationsDialog message handlers

BOOL CTransformationsDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	int a;

	
	ASSERT(m_active_element != NULL);

	CElementManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;
	
	ASSERT(m.isElementActive(m.IdentifyElement(m_active_element)));
	


	CAElInfo * info = m.getActiveElementInfo(m.IdentifyElement(m_active_element));

	
	//nacti podporovane transformace
	for (a = 0; a < info->getTranformationsCount(); a++)
	{
		int index = m_SupportedList.AddString(info->getTranformationName(a));
		//m_SupportedList.SetItemData(index, a);
	}


	//nacti transformace vybrane v prvku
	IXMLDOMNodeListPtr selected_transfs = m_active_element->selectNodes("output/transformation/@name");

	for (a = 0; a < selected_transfs->length; a++)
	{
		m_SelectedList.AddString(selected_transfs->item[a]->text);
	}


		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTransformationsDialog::OnOK() 
{
	GetParent()->SendMessage(WM_COMMAND, IDC_SWITCH_BUTTON | (BN_CLICKED << 16), (LPARAM) m_hWnd);
	
//	CDialog::OnOK();
}

void CTransformationsDialog::OnCancel() 
{
	GetParent()->SendMessage(WM_COMMAND, IDC_SWITCH_BUTTON | (BN_CLICKED << 16), (LPARAM) m_hWnd);

	//CDialog::OnCancel();
}

BOOL CTransformationsDialog::SaveAll()
{
	ASSERT(m_active_element != NULL);

	IXMLDOMNodePtr output_node = m_active_element->selectSingleNode("output");

	//vymaze soucasne transormace
	IXMLDOMSelectionPtr sel = output_node->selectNodes("*");
	sel->removeAll();
	sel.Release();

	//vytvori ukazkovou transformaci
	IXMLDOMElementPtr transf_elem = m_active_element->ownerDocument->createElement("transformation");
	IXMLDOMAttributePtr name_attr_elem = m_active_element->ownerDocument->createAttribute("name");
	transf_elem->setAttributeNode(name_attr_elem);
	name_attr_elem.Release();

	//ulozi transformace
	for (int a = 0; a< m_SelectedList.GetCount(); a++)
	{
		CString it_text;
		m_SelectedList.GetText(a, it_text);

		transf_elem->setAttribute("name", (LPCTSTR) it_text);

		output_node->appendChild(transf_elem->cloneNode(VARIANT_FALSE));
	}


	transf_elem.Release();
	output_node.Release();

	
	return TRUE;
}

void CTransformationsDialog::OnAddButton() 
{
	if (m_SupportedList.GetCurSel() == LB_ERR) return;
	

	CString selected_text;

	m_SupportedList.GetText(m_SupportedList.GetCurSel(), selected_text);
	
	m_SelectedList.AddString(selected_text);
	
}

void CTransformationsDialog::OnRemoveButton() 
{
	if (m_SelectedList.GetCurSel() == LB_ERR) return;

	m_SelectedList.DeleteString(m_SelectedList.GetCurSel());

}

void CTransformationsDialog::OnMoveUpButton() 
{
	if (m_SelectedList.GetCurSel() == LB_ERR) return;

	int selected_index = m_SelectedList.GetCurSel();
	
	CString selected_text;

	if (selected_index <= 0) return;

	m_SelectedList.GetText(selected_index, selected_text);
		
	m_SelectedList.DeleteString(selected_index);

	m_SelectedList.InsertString(--selected_index, selected_text);

	m_SelectedList.SelectString(--selected_index, selected_text);
}

void CTransformationsDialog::OnMoveDownButton() 
{
	if (m_SelectedList.GetCurSel() == LB_ERR) return;

	int selected_index = m_SelectedList.GetCurSel();
	
	CString selected_text;

	if (selected_index >= m_SelectedList.GetCount()-1) return;

	m_SelectedList.GetText(selected_index, selected_text);
		
	m_SelectedList.DeleteString(selected_index);

	m_SelectedList.InsertString(++selected_index, selected_text);

	m_SelectedList.SelectString(--selected_index, selected_text);
	
}
