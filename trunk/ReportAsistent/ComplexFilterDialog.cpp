// ComplexFilterDialog.cpp : implementation file
//
//
// This file is part of LM Report Asistent. (http://reportasistent.berlios.de, reportasistent-list@lists.berlios.de)
//
// Authors: Jan Dedek, Jan Kodym, Martin Chrz, Iva Bartunkova 
//
// LM Report Asistent is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// LM Report Asistent is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with LM Report Asistent; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
#include "stdafx.h"
#include "ReportAsistent.h"
#include "ComplexFilterDialog.h"
#include "APTransform.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CComplexFilterDialog property page

//IMPLEMENT_DYNCREATE(CComplexFilterDialog, CPropertyPage)

CComplexFilterDialog::CComplexFilterDialog(
		MSXML2::IXMLDOMElementPtr & active_element,
		MSXML2::IXMLDOMElementPtr & filter_DOM,
		MSXML2::IXMLDOMElementPtr currnet_attribute_filter,
		CWnd* pParent)
: CDialog(CComplexFilterDialog::IDD, pParent)
, CFilterResultImpl(filter_DOM)
, m_active_element(active_element)
, m_currnet_attribute_filter(currnet_attribute_filter)
, m_bSourceIsInit(FALSE)
, m_nTopNValues(5) //default hodnota
{
	//dedek: v tomhle kostruktoru se dialog inicilaizuje z currnet_attribute_filter elementu

	//InitDialogFromXML(); vola se v init dialog
}


CComplexFilterDialog::CComplexFilterDialog(
		MSXML2::IXMLDOMElementPtr & active_element,
		MSXML2::IXMLDOMElementPtr & filter_DOM,
		CWnd* pParent)	// nestandard constructor :-)
: CDialog(CComplexFilterDialog::IDD, pParent)
, CFilterResultImpl(filter_DOM)
, m_active_element(active_element)
, m_bSourceIsInit(FALSE)
, m_nTopNValues(5) //default hodnota
, m_nFilterTypeRadioGroup(1)
, m_bNumericSort(FALSE)
, m_nSortDirectionRadioGroup(0)
, m_nSlectedAttrIndex(-1)
{
	//{{AFX_DATA_INIT(CComplexFilterDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	//dedek: v tomhle kostruktoru se dialog nastavi na vychozi hodnoty a vytvori se prazdny currnet_attribute_filter element

	AppendFilter();
	
	
	//InitDialogFromXML();
}

CComplexFilterDialog::~CComplexFilterDialog()
{
}

void CComplexFilterDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CComplexFilterDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_ATTRIBUTES_LIST, m_AttributesList);
	DDX_Control(pDX, IDC_VALUES_LIST, m_ValuesList);
	DDX_Control(pDX, IDC_TRESHOLD_EDIT, m_TresholdEdeit);

	DDX_Radio(pDX, IDC_TRESHOLD_RADIO, m_nFilterTypeRadioGroup);
	DDX_Radio(pDX, IDC_ASCENDING_RADIO, m_nSortDirectionRadioGroup);

	DDX_LBIndex(pDX, IDC_ATTRIBUTES_LIST, m_nSlectedAttrIndex);
	DDX_Text(pDX, IDC_TRESHOLD_EDIT, m_sTresholdOrFixedValue);
	DDX_Text(pDX, IDC_TOPN_EDIT, m_nTopNValues);
	DDV_MinMaxUInt(pDX, m_nTopNValues, 1, 100);
	DDX_Control(pDX, IDC_TOPN_SPIN, m_TopNSpin);

	DDX_Check(pDX, IDC_NUMERIC_SORT_CHECK, m_bNumericSort);
	DDX_Control(pDX, IDC_RESULT_LIST, m_ResultList);
}


BEGIN_MESSAGE_MAP(CComplexFilterDialog, CDialog)
	//{{AFX_MSG_MAP(CComplexFilterDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
//	ON_WM_CTLCOLOR()
//	ON_CBN_SELCHANGE(IDC_DATA_SOURCE_COMBO, OnSelchangeDataSourceCombo)
	ON_LBN_SELCHANGE(IDC_ATTRIBUTES_LIST, OnLbnSelchangeAttributesList)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_ASCENDING_RADIO, OnBnClickedAscendingRadio)
	ON_BN_CLICKED(IDC_DESCENDING_RADIO, OnBnClickedDescendingRadio)
	ON_BN_CLICKED(IDC_NUMERIC_SORT_CHECK, OnBnClickedNumericSortCheck)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_LBN_SELCHANGE(IDC_VALUES_LIST, OnLbnSelchangeValuesList)
	ON_BN_CLICKED(IDC_REFRESH_RESULTS_BUTTON, OnBnClickedRefreshResultsButton)
	ON_BN_CLICKED(IDC_TRESHOLD_RADIO, OnBnClickedFilterTypeRadio)
	ON_BN_CLICKED(IDC_FIXED_VAL_RADIO, OnBnClickedFilterTypeRadio)
	ON_BN_CLICKED(IDC_TOP_N_VAL_RADIO, OnBnClickedFilterTypeRadio)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComplexFilterDialog message handlers

BOOL CComplexFilterDialog::OnInitDialog()
{
	CDialog::OnInitDialog();



	m_TopNSpin.SetRange(1, 100);
//	m_TopNSpin.SetPos(5);
	m_TopNSpin.SetBase(1);
	m_TopNSpin.SetBuddy(GetDlgItem(IDC_TOPN_EDIT));

	
/*	
	CDataSourcesManager & dm = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->DataSourcesManager;
	CElementManager & em = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;
	
	for (int a=0; a< dm.getSourcesCount(); a++)
	{
		if (em.isElementSupportedBySource(em.IdentifyElement(m_active_element), a))
		{
			m_SourcesCombo.AddString(dm.getSourcePublicID(a));
		}
	}

	int sel = m_SourcesCombo.SelectString(-1, (_bstr_t) m_active_element->getAttribute("source"));
	if (sel == CB_ERR) m_SourcesCombo.SelectString(-1, dm.getDefaultSource());
*/	
	InitResultView();
	
	UpDateDialog();
	//InitDialogFromXML(); - vola se v update dialog


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

/*
HBRUSH CComplexFilterDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here

	//dedek: tohle se tady vola kvuli inicializaci filtru - kdyz se to delalo uz v init_dialog tak to padalo!!
	if (! m_bSourceIsInit)
	{
		m_bSourceIsInit = TRUE;
		OnSelchangeDataSourceCombo();
//		SetModified(FALSE);
		Invalidate(FALSE);
	}

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}

void CComplexFilterDialog::OnSelchangeDataSourceCombo()
{
	CString text;
	m_SourcesCombo.GetWindowText(text);

	if (text.GetLength() == 0) return;

	if (LoadSource(text))
	{
		UpDateDialog();
	}
	else
	{
		ClearAttributesList();
	}


//    SetModified();
}

BOOL CComplexFilterDialog::LoadSource(public_source_id_t sId)
{
	CGeneralManager * m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager;

    CAElInfo * element_info = m->ElementManager.getActiveElementInfo(
								m->ElementManager.IdentifyElement(m_active_element));

   	
    MSXML2::IXMLDOMDocumentPtr plugout_doc;

	//nacte data z plugin output
	if (! m->DataSourcesManager.GetPluginOutput(sId, element_info->getElementName(), & plugout_doc))
	{
		CReportAsistentApp::ReportError(IDS_SIMPLE_FILTER_FAILED_SOURCE_LOAD, "Plugin output is empty.");
		return FALSE;	
	}

#ifdef _DEBUG	
    plugout_doc->save((LPCTSTR) (m->DirectoriesManager.getXMLFilesDirectory() + "/plug_out_example.xml"));
#endif

	
    //ulozi element atributy
	CAElTransform tr(m_active_element, (MSXML2::IXMLDOMNodePtr) plugout_doc);
	tr.FillElementAttributes(0);


    //transformace plugout na filter dom
    MSXML2::IXMLDOMDocumentPtr filter_doc;
    filter_doc.CreateInstance(_T("Msxml2.DOMDocument"));
	filter_doc->async = VARIANT_FALSE; // default - true,
	filter_doc->loadXML(
		plugout_doc->transformNode(element_info->getComplexFilterTransformation()));

    plugout_doc.Release();

    if (filter_doc->documentElement != NULL)
	{
    	//ok data nactena

#ifdef _DEBUG	
    	filter_doc->save((LPCTSTR) (m->DirectoriesManager.getXMLFilesDirectory() + "/complex_filter_example.xml"));
#endif
        m_filter_DOM = filter_doc->documentElement;
		filter_doc.Release();
		return TRUE;
	}

    //problem, zdroj neprosel    
   	CReportAsistentApp::ReportError(IDS_SIMPLE_FILTER_FAILED_SOURCE_LOAD, "Plugin output - document element is empty.");
    return FALSE;
}
*/

void CComplexFilterDialog::UpDateDialog()
{
	//fill attributes list

	ClearAttributesList();
	
//	MSXML2::IXMLDOMNodeListPtr attributes = m_filter_DOM->selectNodes("/dialog_data/attributes/attribute");

	for (int a = 0; a < getAttributesCount(); a++)
	{
		m_AttributesList.AddString(getAttributeLabel(a));
/*

		m_AttributesList.SetItemDataPtr(i, 
			new CString((LPCTSTR) attributes->item[a]->selectSingleNode("@name")->text));
*/
	}

//dedek:	pride pridat: m_AttributesList.SelectString


//	attributes.Release();

	InitDialogFromXML();
}

void CComplexFilterDialog::OnLbnSelchangeAttributesList()
{

	int cur_sel = m_AttributesList.GetCurSel();
	if (cur_sel == LB_ERR) return;

	CString query_str, cur_str = getAttributeName(cur_sel);
	query_str.Format("/dialog_data/attributes/attribute[@name=\"%s\"]", (LPCTSTR) cur_str);
	MSXML2::IXMLDOMElementPtr attr_elem = m_result_filter_DOM->selectSingleNode((LPCTSTR) query_str);
	SetSortButtons(attr_elem);
	attr_elem.Release();


	FillValuesList( cur_str);
	OnBnClickedRefreshResultsButton();
}

void CComplexFilterDialog::OnDestroy()
{
	ClearAttributesList();
	
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
}

void CComplexFilterDialog::ClearAttributesList(void)
{
/*	for (int a = 0; a < m_AttributesList.GetCount(); a++)
	{
		delete (CString *) m_AttributesList.GetItemDataPtr(a);
	}
*/
	m_AttributesList.ResetContent();
}

void CComplexFilterDialog::OnBnClickedAscendingRadio()
{
	FillValuesList();

	OnBnClickedRefreshResultsButton();
}

void CComplexFilterDialog::OnBnClickedDescendingRadio()
{
	FillValuesList();

	OnBnClickedRefreshResultsButton();
}

void CComplexFilterDialog::SetSortButtons(MSXML2::IXMLDOMElementPtr & attr_elem)
{
	BOOL num_sort = FALSE;
	BOOL asc_sort = TRUE;

	if (attr_elem != NULL)
	{
		try 
		{
			if (((LPCTSTR) (_bstr_t) (attr_elem->getAttribute("numeric_sort"))) == CString("true"))
				num_sort = TRUE;
		}
		catch (...) {}

		try 
		{
			if (((LPCTSTR) (_bstr_t) (attr_elem->getAttribute("default_sort_direction"))) == CString("descending"))
				asc_sort = FALSE;
		}
		catch (...) {}
	}

	if (num_sort)
		CheckDlgButton(IDC_NUMERIC_SORT_CHECK, BST_CHECKED);
	else
		CheckDlgButton(IDC_NUMERIC_SORT_CHECK, BST_UNCHECKED);

	if (asc_sort)
		CheckRadioButton(IDC_ASCENDING_RADIO, IDC_DESCENDING_RADIO, IDC_ASCENDING_RADIO);
	else
		CheckRadioButton(IDC_ASCENDING_RADIO, IDC_DESCENDING_RADIO, IDC_DESCENDING_RADIO);

}

void CComplexFilterDialog::FillValuesList(LPCTSTR cur_attr_str)
{
	m_ValuesList.ResetContent();

	CString s;
	
	if (cur_attr_str == NULL)
	{
		int cur_sel = m_AttributesList.GetCurSel();
		if (cur_sel == LB_ERR) return;
		cur_attr_str = s = getAttributeName(cur_sel);
	}

	CString query_str;
	query_str = "/dialog_data/values/value/@";
	query_str += cur_attr_str;

	MSXML2::IXMLDOMNodeListPtr values = m_result_filter_DOM->selectNodes((LPCTSTR) query_str);

	CStringTableImpl str_table;

	int a;
	for (a = 0; a < values->length; a++)
	{
		CString value = (LPCTSTR) values->item[a]->text;
		if (-1 == str_table.FindString(value))
		{			
			str_table.Add(value);
		}
	}

	if (IsDlgButtonChecked(IDC_NUMERIC_SORT_CHECK))
	{
		if (IDC_DESCENDING_RADIO == GetCheckedRadioButton(IDC_ASCENDING_RADIO, IDC_DESCENDING_RADIO))
			str_table.SortNumeric(FALSE);
		else
			str_table.SortNumeric(TRUE);
	}
	else
	{
		if (IDC_DESCENDING_RADIO == GetCheckedRadioButton(IDC_ASCENDING_RADIO, IDC_DESCENDING_RADIO))
			str_table.Sort(FALSE);
		else
			str_table.Sort(TRUE);
	}


	for (a = 0; a < str_table.getCount(); a++)
	{
		m_ValuesList.AddString(str_table.getItem(a));
	}



}

void CComplexFilterDialog::OnBnClickedNumericSortCheck()
{
	FillValuesList();

	OnBnClickedRefreshResultsButton();
}


void CComplexFilterDialog::OnBnClickedOk()
{
	if (! UpdateData(TRUE)) return;

	int sel = m_AttributesList.GetCurSel();
	CString s = "";

	if (sel == LB_ERR)
	{
		AfxMessageBox(IDS_COMPLEX_FILTER_SELECT_ATTR);
		if (m_AttributesList.GetCount() > 0) m_AttributesList.GetText(0, s);
		m_AttributesList.SelectString(-1, s);
		m_AttributesList.SetFocus();
		return;
	}

	m_currnet_attribute_filter->parentNode->replaceChild(
		CreateAttrFilterElement(),
		m_currnet_attribute_filter);



	EndDialog(IDOK);
	
	// TODO: Add your control notification handler code here
	//OnOK();
}

void CComplexFilterDialog::OnLbnSelchangeValuesList()
{
	int sel = m_ValuesList.GetCurSel();

	if (sel == LB_ERR) return;

	CString s;
	m_ValuesList.GetText(sel, s);
	m_TresholdEdeit.SetWindowText(s);

	OnBnClickedRefreshResultsButton();
}

void CComplexFilterDialog::InitDialogFromXML(void)
{
	
	//attr_name
	CString query;
	query.Format("/dialog_data/attributes/attribute[@name=\"%s\"]/@label", 
		(LPCTSTR) (_bstr_t) m_currnet_attribute_filter->getAttribute("attr_name"));

	//ladici
//	query.Format("/dialog_data/attributes/attribute[@name=\"%s\"]/@label", "a");

	try
	{
		m_nSlectedAttrIndex =
			m_AttributesList.FindString(-1,	
				m_result_filter_DOM->selectSingleNode((LPCTSTR) query)->text);
	}
	catch (...)
	{
		m_nSlectedAttrIndex = 0;
	}

	//numeric_sort
	if ((_bstr_t) m_currnet_attribute_filter->getAttribute("numeric_sort") == (_bstr_t) "true")
		m_bNumericSort = TRUE;
	else
		m_bNumericSort = FALSE;

	//sort_direction
	if ((_bstr_t) m_currnet_attribute_filter->getAttribute("sort_direction") == (_bstr_t) "descending")
		m_nSortDirectionRadioGroup = IDC_DESCENDING_RADIO - IDC_DESCENDING_RADIO;
	else
		m_nSortDirectionRadioGroup = IDC_ASCENDING_RADIO - IDC_DESCENDING_RADIO;

	
	//filter_type & filter_data
	if ((_bstr_t) m_currnet_attribute_filter->getAttribute("filter_type") == (_bstr_t) "treshold")
	{
		m_nFilterTypeRadioGroup = IDC_TRESHOLD_RADIO - IDC_TRESHOLD_RADIO;
		m_sTresholdOrFixedValue = (LPCTSTR) (_bstr_t) m_currnet_attribute_filter->getAttribute("filter_data");

	}
	else
	if ((_bstr_t) m_currnet_attribute_filter->getAttribute("filter_type") == (_bstr_t) "fixed")
	{
		m_nFilterTypeRadioGroup = IDC_FIXED_VAL_RADIO - IDC_TRESHOLD_RADIO;
		m_sTresholdOrFixedValue = (LPCTSTR) (_bstr_t) m_currnet_attribute_filter->getAttribute("filter_data");
	}
	else
	if ((_bstr_t) m_currnet_attribute_filter->getAttribute("filter_type") == (_bstr_t) "top-n")
	{
		m_nFilterTypeRadioGroup = IDC_TOP_N_VAL_RADIO - IDC_TRESHOLD_RADIO;
		m_nTopNValues = (long) m_currnet_attribute_filter->getAttribute("filter_data");
	}

	UpdateData(FALSE);
	OnLbnSelchangeAttributesList();
}

MSXML2::IXMLDOMElementPtr CComplexFilterDialog::CreateAttrFilterElement()
{
	MSXML2::IXMLDOMDocumentPtr doc = m_active_element->ownerDocument;

/*	
	//filter element
	MSXML2::IXMLDOMElementPtr filter_element = doc->createElement("filter");
	MSXML2::IXMLDOMAttributePtr type_attr = doc->createAttribute("type");
	type_attr->value = "complex";
	filter_element->setAttributeNode(type_attr);
	type_attr.Release();
*/
	//attribute_filter element
	MSXML2::IXMLDOMElementPtr attr_filter_element = doc->createElement("attribute_filter");
	
	//attr_name
	MSXML2::IXMLDOMAttributePtr attr_name_attr = doc->createAttribute("attr_name");
/*	m_AttributesList.GetText(sel, s);
	attr_name_attr->value = (LPCTSTR) s;
*/
	if (m_nSlectedAttrIndex >= 0) 
		attr_name_attr->value = (LPCTSTR) getAttributeName(m_nSlectedAttrIndex);
	else
		attr_name_attr->value = "";

	attr_filter_element->setAttributeNode(attr_name_attr);

	//numeric_sort
	MSXML2::IXMLDOMAttributePtr numeric_sort_attr = doc->createAttribute("numeric_sort");
	if (m_bNumericSort)
		numeric_sort_attr->value = "true";
	else
		numeric_sort_attr->value = "false";
	attr_filter_element->setAttributeNode(numeric_sort_attr);
	
	//sort_direction
	MSXML2::IXMLDOMAttributePtr sort_direction_attr = doc->createAttribute("sort_direction");
	if (m_nSortDirectionRadioGroup + IDC_ASCENDING_RADIO == IDC_DESCENDING_RADIO)
		sort_direction_attr->value = "descending";
	else
		sort_direction_attr->value = "ascending";
	attr_filter_element->setAttributeNode(sort_direction_attr);
	
	
	//filter_type & filter_data
	MSXML2::IXMLDOMAttributePtr filter_type_attr = doc->createAttribute("filter_type");
	MSXML2::IXMLDOMAttributePtr filter_data_attr = doc->createAttribute("filter_data");
//	m_TresholdEdeit.GetWindowText(s);
	switch (m_nFilterTypeRadioGroup + IDC_TRESHOLD_RADIO)
	{
	case IDC_TRESHOLD_RADIO:
		filter_type_attr->value = "treshold";
//		filter_data_attr->value = (LPCTSTR) s;
		filter_data_attr->value = (LPCTSTR) m_sTresholdOrFixedValue;		
		break;
	case IDC_FIXED_VAL_RADIO:
		filter_type_attr->value = "fixed";
//		filter_data_attr->value = (LPCTSTR) s;
		filter_data_attr->value = (LPCTSTR) m_sTresholdOrFixedValue;		
		break;
	case IDC_TOP_N_VAL_RADIO:
		filter_type_attr->value = "top-n";
		filter_data_attr->value = (long) m_nTopNValues;
		break;
	}
	attr_filter_element->setAttributeNode(filter_type_attr);
	attr_filter_element->setAttributeNode(filter_data_attr);

	/*	filter_element->appendChild(attr_filter_element);

	
	//pracovni
	m_active_element->replaceChild(
		filter_element,
		m_active_element->selectSingleNode("filter"));

*/

	
	return attr_filter_element;
}

void CComplexFilterDialog::AppendFilter(void)
{
	m_currnet_attribute_filter = CreateAttrFilterElement();
	m_active_element->selectSingleNode("filter[@type=\"complex\"]")->appendChild(m_currnet_attribute_filter);	
}

void CComplexFilterDialog::OnBnClickedRefreshResultsButton()
{
	if (m_result_filter_DOM == NULL) return;

	//zaloha dat
	MSXML2::IXMLDOMElementPtr values_clone = m_result_filter_DOM->selectSingleNode("/dialog_data/values")->cloneNode(VARIANT_TRUE);
	
	if (! UpdateData(TRUE)) return;
	CAElTransform::ApplySingleAttributeFilter(m_result_filter_DOM, CreateAttrFilterElement());

//	AfxMessageBox(m_filter_DOM->xml);

	UpdateResult(m_result_filter_DOM);
	
	//obnova dat
	m_result_filter_DOM->selectSingleNode("/dialog_data")->replaceChild(values_clone,
		m_result_filter_DOM->selectSingleNode("/dialog_data/values"));
		
}



//******************************************************************************


int CFilterResultImpl::getAttributesCount()
{
	if (m_result_filter_DOM == NULL) return 0;

	MSXML2::IXMLDOMNodeListPtr attributes = m_result_filter_DOM->selectNodes("/dialog_data/attributes/attribute");
	
	if (attributes != NULL)	return attributes->length;
	
	return 0;
}

CString CFilterResultImpl::getAttributeName(int index)
{
	ASSERT (index >= 0);
	ASSERT (index < getAttributesCount());

	CString q;
	q.Format("/dialog_data/attributes/attribute[%d]/@name", index);
	MSXML2::IXMLDOMNodePtr name = m_result_filter_DOM->selectSingleNode((LPCTSTR) q);

	if (name != NULL) return CString((LPCTSTR) name->text);

	return "";
}

CString CFilterResultImpl::getAttributeLabel(int index)
{
	CString q;
	q.Format("/dialog_data/attributes/attribute[%d]/@label", index);
	MSXML2::IXMLDOMNodePtr label = m_result_filter_DOM->selectSingleNode((LPCTSTR) q);

	if (label != NULL) return CString((LPCTSTR) label->text);

	return "";
}


void CFilterResultImpl::InitResultView()
{
	m_ResultList.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	// Delete all of the columns.
	int nColumnCount = m_ResultList.GetHeaderCtrl()->GetItemCount();
	for (int i = 0; i < nColumnCount;i++)
	{
	   m_ResultList.DeleteColumn(0);
	}

	for (int a = 0; a < getAttributesCount(); a++)
	{
		m_ResultList.InsertColumn(a, getAttributeLabel(a), 0, 50);
	}


}

void CFilterResultImpl::UpdateResult(MSXML2::IXMLDOMElementPtr & filter_dom)
{	
	SetCursor(LoadCursor(NULL, IDC_WAIT));

	m_ResultList.DeleteAllItems();

	if (filter_dom == NULL) return;

	MSXML2::IXMLDOMNodeListPtr values_list = filter_dom->selectNodes("/dialog_data/values/value");
			
	m_ResultList.SetItemCount(values_list->length);
	for (int i = 0; i < values_list->length; i++)
	{
		//spoleham se na stejne poradi atributu v m_ResultList jako v m_AttributesList

		int it = m_ResultList.InsertItem(i, "");
		for (int a = 0; a < getAttributesCount(); a++)
		{
			CString q;
			q.Format("@%s", (LPCTSTR) getAttributeName(a));
			
			MSXML2::IXMLDOMNodePtr value_attr = values_list->item[i]->selectSingleNode((LPCTSTR) q);
			if (value_attr != NULL)
				m_ResultList.SetItemText(it, a, value_attr->text);
			else
				m_ResultList.SetItemText(it, a, "?");
		}

	}
}

CAElDataShare::CAElDataShare(
		MSXML2::IXMLDOMElementPtr & active_element,
		MSXML2::IXMLDOMElementPtr & cloned_active_element,
   		MSXML2::IXMLDOMElementPtr & filter_DOM,
		BOOL & bApplyButtonUsed)
	: m_active_element(active_element)
	, m_cloned_active_element(cloned_active_element)
	, m_filter_DOM(filter_DOM)
	, m_bApplyButtonUsed(bApplyButtonUsed)
{
}

CAElDataShare::CAElDataShare(CAElDataShare & data_share)
	: m_active_element(data_share.m_active_element)
	, m_cloned_active_element(data_share.m_cloned_active_element)
	, m_filter_DOM(data_share.m_filter_DOM)
	, m_bApplyButtonUsed(data_share.m_bApplyButtonUsed)
{
}


void CAElDataShare::ApplyChanges()
{
	ASSERT(m_active_element != NULL);
	ASSERT(m_cloned_active_element != NULL);
	
	
	//dedek: kvuli mnoha aply funkcim po sobe - padalo
	ASSERT(m_active_element->parentNode != NULL);

//	if(m_active_element->parentNode == NULL) return;

	m_active_element->parentNode->replaceChild(m_cloned_active_element, m_active_element);

	m_active_element = m_cloned_active_element;
	m_cloned_active_element = m_active_element->cloneNode(VARIANT_TRUE);

	ASSERT(m_active_element->parentNode != NULL);
	m_bApplyButtonUsed = TRUE;
}

void CComplexFilterDialog::OnBnClickedFilterTypeRadio()
{
	OnBnClickedRefreshResultsButton();
}
