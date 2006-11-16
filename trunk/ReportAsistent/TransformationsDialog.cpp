// TransformationsDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ReportAsistent.h"
#include "TransformationsDialog.h"
#include "PropertyEditor.h"
#include "AttributeLinkTableDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransformationsDialog dialog


CTransformationsDialog::CTransformationsDialog(MSXML2::IXMLDOMElementPtr & active_element, MSXML2::IXMLDOMElementPtr & cloned_element, CWnd* pParent /*=NULL*/)
: CPropertyPage(CTransformationsDialog::IDD/*, pParent*/), m_active_element(active_element), m_cloned_active_element(cloned_element)
{
	//{{AFX_DATA_INIT(CTransformationsDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT


//	srand( (unsigned)time( NULL ) );

	if (m_cloned_active_element == NULL)
		m_cloned_active_element = m_active_element->cloneNode(VARIANT_TRUE);


	
	//dedek: neklonuje se, predelano, klonuje se uz ve fitrovacim dialogu (CAElFiltersConfigDialog)
	m_cloned_output_element = m_cloned_active_element->selectSingleNode("output");//->cloneNode(VARIANT_TRUE);
}


void CTransformationsDialog::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTransformationsDialog)
	DDX_Control(pDX, IDC_CONFIGURE_BUTTON, m_ConfigureButton);
	DDX_Control(pDX, IDC_SUPPORTED_TRANSF_LIST, m_SupportedList);
	DDX_Control(pDX, IDC_SELECTED_TRANSFS_LIST, m_SelectedList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTransformationsDialog, CPropertyPage)
	//{{AFX_MSG_MAP(CTransformationsDialog)
	ON_BN_CLICKED(IDC_ADD_BUTTON, OnAddButton)
	ON_BN_CLICKED(IDC_REMOVE_BUTTON, OnRemoveButton)
	ON_BN_CLICKED(IDC_MOVE_UP_BUTTON, OnMoveUpButton)
	ON_BN_CLICKED(IDC_MOVE_DOWN_BUTTON, OnMoveDownButton)
	ON_BN_CLICKED(IDC_CONFIGURE_BUTTON, OnConfigureButton)
	ON_LBN_DBLCLK(IDC_SUPPORTED_TRANSF_LIST, OnDblclkSupportedTransfList)
	ON_LBN_DBLCLK(IDC_SELECTED_TRANSFS_LIST, OnDblclkSelectedTransfsList)
	ON_LBN_SELCHANGE(IDC_SELECTED_TRANSFS_LIST, OnSelchangeSelectedTransfsList)
	ON_LBN_SELCANCEL(IDC_SELECTED_TRANSFS_LIST, OnSelcancelSelectedTransfsList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransformationsDialog message handlers

#define ATTR_TL_STR		"* attr_link_table *"

BOOL CTransformationsDialog::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	int a;

	
	ASSERT(m_active_element != NULL);
	ASSERT(m_cloned_active_element != NULL);

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
	MSXML2::IXMLDOMNodeListPtr selected_transfs = m_cloned_active_element->selectNodes("output/transformation/@name");

	for (a = 0; a < selected_transfs->length; a++)
	{
		m_SelectedList.AddString(selected_transfs->item[a]->text);
	}

	//When no item is selected in m_SelectedList, configuration button is disabled:
	m_ConfigureButton.EnableWindow(false);




		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTransformationsDialog::OnOK() 
{
  OnApply();
}


BOOL CTransformationsDialog::SaveAll()
{
	ASSERT(m_active_element != NULL);
	ASSERT(m_cloned_output_element != NULL);

//	AfxMessageBox(m_cloned_output_element->xml);
/*

	m_active_element->replaceChild(
		m_cloned_output_element,
		m_active_element->selectSingleNode("output"));

	m_cloned_output_element = m_active_element->selectSingleNode("output")->cloneNode(VARIANT_TRUE);
*/

//	m_active_element

/*
	AfxMessageBox(m_cloned_output_element->xml);
	AfxMessageBox(m_cloned_active_element->xml);
	AfxMessageBox(m_active_element->parentNode->xml);
*/

	m_active_element->parentNode->replaceChild(m_cloned_active_element, m_active_element);

	m_active_element = m_cloned_active_element;
	m_cloned_active_element = m_active_element->cloneNode(VARIANT_TRUE);

//	AfxMessageBox(m_active_element->parentNode->xml);

	SetModified(FALSE);

	return TRUE;
}

void CTransformationsDialog::OnAddButton() 
{
	CElementManager & OElementManager = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;		
	CAElInfo * info = OElementManager.getActiveElementInfo(OElementManager.IdentifyElement(m_active_element));
	if ( MAX_TRANSFORMATION_COUNT < info->getTranformationsCount() )  
	{
		//Error  
		return;
	}
	
	int nSel = m_SupportedList.GetSelCount();
	int SelItems[ MAX_TRANSFORMATION_COUNT ];
	

	int nRes = m_SupportedList.GetSelItems( MAX_TRANSFORMATION_COUNT, SelItems );
	if (nRes == LB_ERR) return;
	int I;

	for (I=0;I<nSel;I++)
	{
		 
		if (!AddTransformation(SelItems[I])) return;
	}
}

void CTransformationsDialog::OnRemoveButton() 
{
	CElementManager & OElementManager = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;		
	CAElInfo * info = OElementManager.getActiveElementInfo(OElementManager.IdentifyElement(m_active_element));
	if ( MAX_TRANSFORMATION_COUNT < info->getTranformationsCount() )  
	{
		//Error  
		return;
	}
	
	int nSel = m_SelectedList.GetSelCount();
	int SelItems[ MAX_CHOSEN_TRANSFORMATION_COUNT ];
	

	int nRes = m_SelectedList.GetSelItems( MAX_CHOSEN_TRANSFORMATION_COUNT, SelItems );
	if (nRes == LB_ERR) return;
	int I;

	for (I=nSel-1;I>=0;I--)
	{
		 
		RemoveTransf(SelItems[I]);
	}
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

	m_SelectedList.SetSel(selected_index-1, true);



	
	//uprava xml

	CString query_str1;
	CString query_str2;

	query_str1.Format("transformation[%d]", selected_index);
	query_str2.Format("transformation[%d]", selected_index -1);

	m_cloned_output_element->insertBefore(
		m_cloned_output_element->selectSingleNode((LPCTSTR) query_str1),
		(MSXML2::IXMLDOMNode*) m_cloned_output_element->selectSingleNode((LPCTSTR) query_str2));

  SetModified();
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

	m_SelectedList.SetSel(selected_index+1, true);	
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

  SetModified();
}

void CTransformationsDialog::ConfigureAttrLinkTable(MSXML2::IXMLDOMNodePtr & attr_link_tbl_node)
{
	CAttributeLinkTableDialog dlg(
		(MSXML2::IXMLDOMElementPtr) attr_link_tbl_node, this, FALSE);

	if (dlg.DoModal() == IDOK)
  {
    SetModified();
  }

}

void CTransformationsDialog::OnConfigureButton() 
{
	CElementManager & OElementManager = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;		
	CAElInfo * info = OElementManager.getActiveElementInfo(OElementManager.IdentifyElement(m_active_element));
	if ( MAX_TRANSFORMATION_COUNT < info->getTranformationsCount() )  
	{
		//Error  
		return;
	}
	
	int nSel = m_SelectedList.GetSelCount();
	int SelItems[ MAX_TRANSFORMATION_COUNT ];
	

	int nRes = m_SelectedList.GetSelItems( MAX_TRANSFORMATION_COUNT, SelItems );
	if (nRes == LB_ERR || nRes < 1) return;

	SelTransformConfigure(SelItems[0]);
}

BOOL CTransformationsDialog::IsSelectedTransformationWithOptions(int transform_index)
{
 	ASSERT(transform_index >= 0);
	ASSERT(transform_index < m_SelectedList.GetCount());

  CString query_str;
  query_str.Format("transformation[%d]/@type", transform_index);
  
  
  return 
    m_cloned_output_element->selectSingleNode((LPCTSTR) query_str)->text == _bstr_t("with_options");
}

BOOL CTransformationsDialog::IsSelectedTransformationAttrLinkTable(int transform_index)
{
	ASSERT(transform_index >= 0);
	ASSERT(transform_index < m_SelectedList.GetCount());

	return transform_index == m_SelectedList.FindString(transform_index-1, ATTR_TL_STR);
}


CString CTransformationsDialog::FindOptionEnumItemLabelFromValue(
							MSXML2::IXMLDOMNodePtr & options_node,
							LPCTSTR variable_name,
							LPCTSTR otion_value)
{
	
    CString value_label_query_str;
	value_label_query_str.Format(
		"/visualization/visualization_options/enum_option[@variable_name=\"%s\"]/enum_item[@value = \"%s\"]/@label",
		variable_name, otion_value);

	_bstr_t ret;
	try
	{
		ret = options_node->selectSingleNode((LPCTSTR) value_label_query_str)->text;
	}
	catch (_com_error &)
	{
		CString msg;
		msg.Format("Label for value \"%s\" of enum variable \"%s\" is missing.", otion_value, variable_name);
		throw msg;
	}
	
	return  (LPCTSTR) ret;
}

CString CTransformationsDialog::FindOptionEnumItemValueFromLabel(
							MSXML2::IXMLDOMNodePtr & options_node,
							LPCTSTR variable_name,
							LPCTSTR otion_label)
{
	
    CString label_query_str;
	label_query_str.Format(
		"/visualization/visualization_options/enum_option[@variable_name=\"%s\"]/enum_item[@label = \"%s\"]/@value",
		variable_name, otion_label);

	return (LPCTSTR) options_node->selectSingleNode((LPCTSTR) label_query_str)->text;
}

CProperty * CTransformationsDialog::CreateDoubleProperty(
					MSXML2::IXMLDOMElementPtr & option_element,
					LPCTSTR current_value)
{
	double min = -1.7E+308;
	double max = 1.7E+308;

	try 
	{
		min = option_element->getAttribute("min_value");
	}
	catch (...)
	{
		min = -1.7E+308;
	}

	try 
	{
		max = option_element->getAttribute("max_value");
	}
	catch (...)
	{
		max = 1.7E+308;
	}


	return new CDoubleProperty(
		(_bstr_t) option_element->getAttribute("title"), //label
		(_variant_t) current_value, min, max);	//default value
}

CProperty * CTransformationsDialog::CreateIntProperty(
					MSXML2::IXMLDOMElementPtr & option_element,
					LPCTSTR current_value)
{
	int min = 0x80000000;
	int max = 0x7FFFFFFF;


	try 
	{
		min = (long) option_element->getAttribute("min_value");
	}
	catch (...)
	{
		min = 0x80000000;
	}

	try 
	{
		max = (long) option_element->getAttribute("max_value");
	}
	catch (...)
	{
		max = 0x7FFFFFFF;
	}


	return new CIntProperty(
		(_bstr_t) option_element->getAttribute("title"),  //label
		(long) (_variant_t) current_value, min, max);  //default value
}


CProperty * CTransformationsDialog::CreateEnumProperty(
					MSXML2::IXMLDOMElementPtr & option_element,
					LPCTSTR current_value)
{
    CString variable_name = 
		(LPCTSTR) (_bstr_t) option_element->getAttribute("variable_name");

	CEnumProperty * ep = new CEnumProperty(
		(_bstr_t) option_element->getAttribute("title"),  //label
        FindOptionEnumItemLabelFromValue(option_element->selectSingleNode("/"), variable_name, current_value));  //default value

      //napln combo hodnotami
      MSXML2::IXMLDOMNodeListPtr enum_nodes = 
		  option_element->selectNodes("enum_item/@label");
      
	  for (int b=0; b < enum_nodes->length; b++)
      {
        ep->AddCombostr(enum_nodes->item[b]->text);
      }
      enum_nodes.Release();

	return ep;
}


void CTransformationsDialog::AddOptionToPropetryEditor(
			MSXML2::IXMLDOMElementPtr & option_element,
			MSXML2::IXMLDOMElementPtr & transformation_element,
			CPropertyEditor & property_editor)
{
    CString option_type = (LPCTSTR) option_element->nodeName;
    CString variable_name = (LPCTSTR) (_bstr_t) option_element->getAttribute("variable_name");
    CString value_query_str; //dotaz na default value
    value_query_str.Format("visualization_values/variable[@name=\"%s\"]/@value", (LPCTSTR) variable_name);
	
	CString value;
	try
	{
		value = (LPCTSTR) transformation_element->selectSingleNode((LPCTSTR) value_query_str)->text;
	}
	catch (_com_error &)
	{
		CString err_msg;
		err_msg.Format("Value of variable \"%s\" is missing.", variable_name);
		throw err_msg;
	}

        
    if (option_type == "enum_option")
    {
		//enum

		property_editor.AddProperty(
		  CreateEnumProperty(option_element, value));

    }
    else if (option_type == "string_option")
    {
      //string
      
      property_editor.AddProperty(new CStringProperty(
        (_bstr_t) option_element->getAttribute("title"),  //label
        value));  //default value
    }
    else if (option_type == "color_option")
    {
      //color
      
      property_editor.AddProperty(new CColorProperty(
        (_bstr_t) option_element->getAttribute("title"),  //label
        value));  //default value
    }
    else if (option_type == "number_option")
    {
      if ((_bstr_t) option_element->getAttribute("num_type") == _bstr_t("float"))
      {
        //float

		  property_editor.AddProperty(
			  CreateDoubleProperty(option_element, value));
      }
      else if ((_bstr_t) option_element->getAttribute("num_type") == _bstr_t("integer"))
      {
        //integer
		  
  		  property_editor.AddProperty(
			  CreateIntProperty(option_element, value));
  
      }
    }
}

void CTransformationsDialog::ConfigureTransformation(int transform_index)
{
	ASSERT(transform_index >= 0);
	ASSERT(transform_index < m_SelectedList.GetCount());

	CElementManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;

	//element info
	int element_id = m.IdentifyElement(m_active_element);
	CAElInfo * element_info = m.getActiveElementInfo(element_id);


	//tranformation
	CString query_str;
	query_str.Format("transformation[%d]", transform_index);
	MSXML2::IXMLDOMElementPtr transformation_element = m_cloned_output_element->selectSingleNode((LPCTSTR) query_str);

	//options definition
	MSXML2::IXMLDOMNodePtr options_node = 
		element_info->getTranformationOptionsDoc(
			element_info->FindTransformationByName((_bstr_t) transformation_element->getAttribute("name")));

	//single options
	MSXML2::IXMLDOMNodeListPtr option_nodes = options_node->selectNodes("/visualization/visualization_options/*");



	
	//napln property editor

	//label
	CString label;
	label.Format("%s (%s) properties", 
	(LPCTSTR) options_node->selectSingleNode("/visualization/visualization_options/@visualization_label")->text,
	(LPCTSTR) (_bstr_t) m_active_element->getAttribute("id"));

	CPropertyEditor property_editor(label, this);


	//pridej jednotlive properties
	for (int a=0; a < option_nodes->length; a++)
	{
		MSXML2::IXMLDOMElementPtr option_element = option_nodes->item[a];

		AddOptionToPropetryEditor(option_element, transformation_element, property_editor);
		
		option_element.Release();
	}


	//vytvor modalni dialog
	if (IDOK == property_editor.DoModal())
	{
		
		
		//uloz hodnoty z property editoru
		for (int a=0; a < option_nodes->length; a++)
		{
		    MSXML2::IXMLDOMElementPtr option_element = option_nodes->item[a];
			CString variable_name = (LPCTSTR) (_bstr_t) option_element->getAttribute("variable_name");
			
			CString value_query_str;
		    value_query_str.Format("visualization_values/variable[@name=\"%s\"]/@value", (LPCTSTR) variable_name);
			
			//nastav hodnotu parametru value
			if (option_element->nodeName == _bstr_t("enum_option"))
			{
				transformation_element->selectSingleNode((LPCTSTR) value_query_str)->text = 
					(LPCTSTR) FindOptionEnumItemValueFromLabel(
						options_node, variable_name, property_editor.GetValueOfProperty(a)->GetValue());
			}
			else
			{
				transformation_element->selectSingleNode((LPCTSTR) value_query_str)->text = 
					property_editor.GetValueOfProperty(a)->GetValue();
			}
			option_element.Release();
		}
	}

	option_nodes.Release();
}

BOOL CTransformationsDialog::OnApply()
{
  return SaveAll();
}



void CTransformationsDialog::OnDblclkSupportedTransfList() 
{
	int nSel = m_SupportedList.GetSelCount();
	if (nSel > 1) return;
	int SelItems[2];

	int nRes = m_SupportedList.GetSelItems( 1, SelItems );
	if (nRes == LB_ERR) return;
	 
	AddTransformation(SelItems[0]);

	return;
}

BOOL CTransformationsDialog::AddTransformation(int selected_item)
{
	//Iva: check, whether the number of selected transformations is not too high	
	CString Pom;
	if (m_SelectedList.GetCount() >= MAX_CHOSEN_TRANSFORMATION_COUNT)
	{
		Pom.Format("%d", MAX_CHOSEN_TRANSFORMATION_COUNT);
		CReportAsistentApp::ReportError(IDS_TOO_MANY_SELECTED_ITEMS, Pom);
		return false;
	}


	CString selected_text;

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

/*
		CString new_id;
		CString old_id = (LPCTSTR) (_bstr_t) attr_lt->getAttribute("id");
		new_id.Format("%s_trsnsform%d", (LPCTSTR) old_id, rand());
		attr_lt->setAttribute("id", (LPCTSTR) new_id);
*/

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
			try
			{
				transf_elem->appendChild(
					options_node->selectSingleNode("/visualization/visualization_values")->cloneNode(VARIANT_TRUE));
			}
			catch (_com_error &)
			{
				CReportAsistentApp::ReportError(IDS_TR_OPTIONS_ERROR, (LPCTSTR) selected_text,
					"Tag visualization_values is missing");

				m_SelectedList.DeleteString(inserted_item);
				return false;
			}
		}
	}

	type_attr_elem.Release();

	m_cloned_output_element->appendChild(transf_elem);
	transf_elem.Release();

  SetModified();
  return true;
}

void CTransformationsDialog::OnDblclkSelectedTransfsList() 
{
	int nSel = m_SelectedList.GetSelCount();
	if (nSel > 1) return;
	int SelItems[2];

	int nRes = m_SelectedList.GetSelItems( 1, SelItems );
	if (nRes == LB_ERR) return;
	 
	SelTransformConfigure(SelItems[0]);
	return;
	
}

void CTransformationsDialog::SelTransformConfigure(int cur_sel)
{

	if (cur_sel == LB_ERR) return;

	if (IsSelectedTransformationAttrLinkTable(cur_sel))
	{
		CString query_str;
		query_str.Format("transformation[%d]/attr_link_table", cur_sel);
		ConfigureAttrLinkTable(m_cloned_output_element->selectSingleNode((LPCTSTR) query_str));
		return;
	}
	else if (IsSelectedTransformationWithOptions(cur_sel))
	{
		try
		{
			ConfigureTransformation(cur_sel);
		}
		catch (CString & msg)
		{
			CString tr_name;
			m_SelectedList.GetText(cur_sel, tr_name);

			CReportAsistentApp::ReportError(IDS_TR_OPTIONS_ERROR,
				(LPCTSTR) tr_name, (LPCTSTR) msg);
				
			return;
		}

	}
}

void CTransformationsDialog::RemoveTransf(int selected_item)
{
	m_SelectedList.DeleteString(selected_item);
	if (m_SelectedList.GetCount() == 0)
			m_ConfigureButton.EnableWindow(false);
	else 
		if (selected_item==0) m_SelectedList.SetSel(0,true);
		else m_SelectedList.SetSel(selected_item-1,true);

	//uprava xml
	CString query_str;
	query_str.Format("transformation[%d]", selected_item);

	m_cloned_output_element->removeChild(
		m_cloned_output_element->selectSingleNode((LPCTSTR) query_str));

   SetModified();
}

//DEL void CTransformationsDialog::OnMmdelete() 
//DEL {
//DEL 	AfxMessageBox("Stisknuto Delete");
//DEL 	
//DEL }

//DEL void CTransformationsDialog::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
//DEL {
//DEL 	if (nChar == 83) AfxMessageBox("Stisknuto Delete");
//DEL 
//DEL 	AfxMessageBox("Stisknuto neco");
//DEL 	CPropertyPage::OnKeyDown(nChar, nRepCnt, nFlags);
//DEL }

void CTransformationsDialog::OnSelchangeSelectedTransfsList() 
{
	//AfxMessageBox("SelChange");
	m_ConfigureButton.EnableWindow(true);

	// TODO: Add your control notification handler code here
	
}

void CTransformationsDialog::OnSelcancelSelectedTransfsList() 
{
	//AfxMessageBox("SelCancel");
	m_ConfigureButton.EnableWindow(false);
	
}
