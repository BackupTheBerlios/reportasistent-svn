// TransformationsDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ReportAsistent.h"
#include "TransformationsDialog.h"
#include "AttributeLinkTableDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransformationsDialog dialog


CTransformationsDialog::CTransformationsDialog(MSXML2::IXMLDOMElementPtr & active_element, CWnd* pParent /*=NULL*/)
	: CDialog(CTransformationsDialog::IDD, pParent), m_active_element(active_element)
{
	//{{AFX_DATA_INIT(CTransformationsDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT


	m_cloned_output_element = m_active_element->selectSingleNode("output")->cloneNode(VARIANT_TRUE);
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
//	ON_BN_CLICKED(IDC_CONFIGURE_ATTR_LINK_TABLE_BUTTON, OnConfigureAttrLinkTableButton)
//	ON_BN_CLICKED(IDC_ADD_ATTR_LINK_TABLE_BUTTON, OnAddAttrLinkTableButton)
	ON_BN_CLICKED(IDC_CONFIGURE_BUTTON, OnConfigureButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransformationsDialog message handlers

#define ATTR_TL_STR		"* attr_link_table *"

BOOL CTransformationsDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	int a;

	
	ASSERT(m_active_element != NULL);

	CElementManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;
	
	ASSERT(m.isElementActive(m.IdentifyElement(m_active_element)));
	


	CAElInfo * info = m.getActiveElementInfo(m.IdentifyElement(m_active_element));

	
	m_SupportedList.AddString(ATTR_TL_STR);
	
	//nacti podporovane transformace
	for (a = 0; a < info->getTranformationsCount(); a++)
	{
		int index = m_SupportedList.AddString(info->getTranformationName(a));
		//m_SupportedList.SetItemData(index, a);
	}


	//nacti transformace vybrane v prvku
	MSXML2::IXMLDOMNodeListPtr selected_transfs = m_active_element->selectNodes("output/transformation/@name");

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
	ASSERT(m_cloned_output_element != NULL);

	m_active_element->replaceChild(
		m_cloned_output_element,
		m_active_element->selectSingleNode("output"));

	m_cloned_output_element = m_active_element->selectSingleNode("output")->cloneNode(VARIANT_TRUE);

	return TRUE;

/*
//	CheckAndRepareAttrLinkTable();


	MSXML2::IXMLDOMNodePtr output_node = m_active_element->selectSingleNode("output");

	//vymaze soucasne transormace
	MSXML2::IXMLDOMSelectionPtr sel = output_node->selectNodes("*");
	sel->removeAll();
	sel.Release();

	//vytvori ukazkovou transformaci
	MSXML2::IXMLDOMElementPtr transf_elem = m_active_element->ownerDocument->createElement("transformation");
	MSXML2::IXMLDOMAttributePtr name_attr_elem = m_active_element->ownerDocument->createAttribute("name");
	MSXML2::IXMLDOMAttributePtr type_attr_elem = m_active_element->ownerDocument->createAttribute("type");
	type_attr_elem->text = "simple";
	transf_elem->setAttributeNode(name_attr_elem);
	transf_elem->setAttributeNode(type_attr_elem);
	name_attr_elem.Release();
	type_attr_elem.Release();

	//ulozi transformace
	for (int a = 0; a< m_SelectedList.GetCount(); a++)
	{
		CString it_text;
		m_SelectedList.GetText(a, it_text);

		transf_elem->setAttribute("name", (LPCTSTR) it_text);

		//jedna se o attr_link_table
		if (it_text == ATTR_TL_STR)
		{
			MSXML2::IXMLDOMElementPtr clone = transf_elem->cloneNode(VARIANT_FALSE);
			clone->setAttribute("type", "attr_link_table");
			output_node->appendChild(clone);
			clone.Release();
		}
		else
		{
			output_node->appendChild(transf_elem->cloneNode(VARIANT_FALSE));
		}

	}


	transf_elem.Release();
	output_node.Release();

	
	return TRUE;
	/****/
}

void CTransformationsDialog::OnAddButton() 
{
	CString selected_text;
	int selected_item = m_SupportedList.GetCurSel();

	if (selected_item == LB_ERR) return;
	


	m_SupportedList.GetText(selected_item, selected_text);
	
	int inserted_item = m_SelectedList.AddString(selected_text);
	
	
	
	//uprava xml

	CElementManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;

	//vytvori ukazkovou transformaci
	MSXML2::IXMLDOMElementPtr transf_elem = m_active_element->ownerDocument->createElement("transformation");
	MSXML2::IXMLDOMAttributePtr name_attr_elem = m_active_element->ownerDocument->createAttribute("name");
	MSXML2::IXMLDOMAttributePtr type_attr_elem = m_active_element->ownerDocument->createAttribute("type");
	name_attr_elem->text = (LPCSTR) selected_text;
	transf_elem->setAttributeNode(name_attr_elem);
	name_attr_elem.Release();
	
	if (IsSelectedTransformationAttrLinkTable(inserted_item))
	{
		type_attr_elem->text = "attr_link_table";
		transf_elem->setAttributeNode(type_attr_elem);

		MSXML2::IXMLDOMElementPtr attr_lt;
		attr_lt = m.CreateEmptyElement(ELID_ATTR_LINK_TABLE);

		transf_elem->appendChild(attr_lt);
		
		//nastav id stejne jako m_active_element
		attr_lt->setAttribute("target", m_active_element->getAttribute("id"));
		attr_lt.Release();
	}
	else	//selected_item neni attr_link_table
	{
		int element_id = m.IdentifyElement(m_active_element);
		CAElInfo * element_info = m.getActiveElementInfo(element_id);

		MSXML2::IXMLDOMNodePtr options_node = 
			element_info->getTranformationOptionsDoc(
				element_info->FindTransformationByName(selected_text));
		
		if (options_node == NULL)
		{
			type_attr_elem->text = "simple";
			transf_elem->setAttributeNode(type_attr_elem);
		}
		else
		{
			type_attr_elem->text = "with_options";
			transf_elem->setAttributeNode(type_attr_elem);
			transf_elem->appendChild(
				options_node->selectSingleNode("/visualization/visualization_values")->cloneNode(VARIANT_TRUE));
		}
	}

	type_attr_elem.Release();

	m_cloned_output_element->appendChild(transf_elem);
	transf_elem.Release();

}

void CTransformationsDialog::OnRemoveButton() 
{
	int selected_index = m_SelectedList.GetCurSel();
	if (selected_index == LB_ERR) return;

	m_SelectedList.DeleteString(selected_index);

	//uprava xml
	CString query_str;
	query_str.Format("transformation[%d]", selected_index);

	m_cloned_output_element->removeChild(
		m_cloned_output_element->selectSingleNode((LPCTSTR) query_str));

}

void CTransformationsDialog::OnMoveUpButton() 
{
	if (m_SelectedList.GetCurSel() == LB_ERR) return;

	int selected_index = m_SelectedList.GetCurSel();
	
	if (selected_index <= 0) return;

	
	//uprava listboxu
	CString selected_text;

	m_SelectedList.GetText(selected_index, selected_text);
		
	m_SelectedList.DeleteString(selected_index);

	m_SelectedList.InsertString(selected_index-1, selected_text);

	m_SelectedList.SelectString(selected_index-2, selected_text);


	
	//uprava xml

	CString query_str1;
	CString query_str2;

	query_str1.Format("transformation[%d]", selected_index);
	query_str2.Format("transformation[%d]", selected_index -1);

	m_cloned_output_element->insertBefore(
		m_cloned_output_element->selectSingleNode((LPCTSTR) query_str1),
		(MSXML2::IXMLDOMNode*) m_cloned_output_element->selectSingleNode((LPCTSTR) query_str2));
}

void CTransformationsDialog::OnMoveDownButton() 
{
	if (m_SelectedList.GetCurSel() == LB_ERR) return;

	int selected_index = m_SelectedList.GetCurSel();
	
	CString selected_text;

	if (selected_index >= m_SelectedList.GetCount()-1) return;

	m_SelectedList.GetText(selected_index, selected_text);
		
	m_SelectedList.DeleteString(selected_index);

	m_SelectedList.InsertString(selected_index+1, selected_text);

	m_SelectedList.SelectString(selected_index, selected_text);
	
	//uprava xml
	CString query_str1;
	CString query_str2;

	query_str1.Format("transformation[%d]", selected_index);
	query_str2.Format("transformation[%d]", selected_index +2);

	if (selected_index == m_SelectedList.GetCount()-2)
	{
		m_cloned_output_element->appendChild(
			m_cloned_output_element->selectSingleNode((LPCTSTR) query_str1));
	}
	else
	{
		m_cloned_output_element->insertBefore(
			m_cloned_output_element->selectSingleNode((LPCTSTR) query_str1),
			(MSXML2::IXMLDOMNode*) m_cloned_output_element->selectSingleNode((LPCTSTR) query_str2));
	}

}

void CTransformationsDialog::ConfigureAttrLinkTable(MSXML2::IXMLDOMNodePtr & attr_link_tbl_node)
{
	CAttributeLinkTableDialog dlg(
		(MSXML2::IXMLDOMElementPtr) attr_link_tbl_node, this, FALSE);

	dlg.DoModal();

}



//void CTransformationsDialog::OnConfigureAttrLinkTableButton() 
/*
void CTransformationsDialog::ConfigureAttrLinkTable() 
{
//	CheckAndRepareAttrLinkTable();

	MSXML2::IXMLDOMElementPtr el_alt = m_active_element->selectSingleNode("attr_link_table");

	CAttributeLinkTableDialog dlg(el_alt, this, FALSE);

	dlg.DoModal();
	
	el_alt.Release();
}
void CTransformationsDialog::OnAddAttrLinkTableButton() 
{
	CheckAndRepareAttrLinkTable();

	if (LB_ERR == m_SelectedList.FindString(-1, ATTR_TL_STR))
	{
		m_SelectedList.AddString(ATTR_TL_STR);	
	}
}
*/

/****
void CTransformationsDialog::CheckAndRepareAttrLinkTable()
{
	
	MSXML2::IXMLDOMElementPtr attr_lt = m_active_element->selectSingleNode("attr_link_table");
	
	if (attr_lt == NULL)
	{
		CElementManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;
		attr_lt = m.CreateEmptyElement(ELID_ATTR_LINK_TABLE);

		m_active_element->appendChild(attr_lt);
	}

	//nastav id stejne jako m_active_element
	attr_lt->setAttribute("target", m_active_element->getAttribute("id"));
	
	attr_lt.Release();
}
/****/

void CTransformationsDialog::OnConfigureButton() 
{
	int cur_sel = m_SelectedList.GetCurSel();

	if (cur_sel == LB_ERR) return;

	if (IsSelectedTransformationAttrLinkTable(cur_sel))
	{
		CString query_str;
		query_str.Format("transformation[%d]/attr_link_table", cur_sel);
		ConfigureAttrLinkTable(m_cloned_output_element->selectSingleNode((LPCTSTR) query_str));
		return;
	}
	
}

BOOL CTransformationsDialog::IsSelectedTransformationWithOptions(int transform_index)
{
	return FALSE;
}

BOOL CTransformationsDialog::IsSelectedTransformationAttrLinkTable(int transform_index)
{
	ASSERT(transform_index >= 0);
	ASSERT(transform_index < m_SelectedList.GetCount());

	return transform_index == m_SelectedList.FindString(transform_index-1, ATTR_TL_STR);
}
