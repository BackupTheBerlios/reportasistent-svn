// ComplexFilterDialog.cpp : implementation file
//

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

CComplexFilterDialog::CComplexFilterDialog(MSXML2::IXMLDOMElementPtr & active_element, CWnd* pParent)	// nestandard constructor :-)
: CPropertyPage(CComplexFilterDialog::IDD), m_active_element(active_element), m_bSourceIsInit(FALSE)
{
	//{{AFX_DATA_INIT(CComplexFilterDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CComplexFilterDialog::~CComplexFilterDialog()
{
}

void CComplexFilterDialog::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CComplexFilterDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_DATA_SOURCE_COMBO, m_SourcesCombo);
	DDX_Control(pDX, IDC_ATTRIBUTES_LIST, m_AttributesList);
	DDX_Control(pDX, IDC_VALUES_LIST, m_ValuesList);
}


BEGIN_MESSAGE_MAP(CComplexFilterDialog, CPropertyPage)
	//{{AFX_MSG_MAP(CComplexFilterDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_WM_CTLCOLOR()
	ON_CBN_SELCHANGE(IDC_DATA_SOURCE_COMBO, OnSelchangeDataSourceCombo)
	ON_LBN_SELCHANGE(IDC_ATTRIBUTES_LIST, OnLbnSelchangeAttributesList)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_ASCENDING_RADIO, OnBnClickedAscendingRadio)
	ON_BN_CLICKED(IDC_DESCENDING_RADIO, OnBnClickedDescendingRadio)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComplexFilterDialog message handlers

BOOL CComplexFilterDialog::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	
	
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



	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CComplexFilterDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here

	//dedek: tohle se tady vola kvuli inicializaci filtru - kdyz se to delalo uz v init_dialog tak to padalo!!
	if (! m_bSourceIsInit)
	{
		m_bSourceIsInit = TRUE;
		OnSelchangeDataSourceCombo();
		SetModified(FALSE);
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

    SetModified();
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


void CComplexFilterDialog::UpDateDialog()
{
	//fill attributes list

	ClearAttributesList();
	
	MSXML2::IXMLDOMNodeListPtr attributes = m_filter_DOM->selectNodes("/dialog_data/attributes/attribute");

	for (int a = 0; a < attributes->length; a++)
	{
		int i = m_AttributesList.AddString(attributes->item[a]->selectSingleNode("@label")->text);

		m_AttributesList.SetItemDataPtr(i, 
			new CString((LPCTSTR) attributes->item[a]->selectSingleNode("@name")->text));

	}

	attributes.Release();
}

void CComplexFilterDialog::OnLbnSelchangeAttributesList()
{

	int cur_sel = m_AttributesList.GetCurSel();
	if (cur_sel == LB_ERR) return;

	CString * cur_str =	(CString *) m_AttributesList.GetItemDataPtr(cur_sel);

	CString query_str;
	query_str.Format("/dialog_data/attributes/attribute[@name=\"%s\"]", (LPCTSTR) * cur_str);
	MSXML2::IXMLDOMElementPtr attr_elem = m_filter_DOM->selectSingleNode((LPCTSTR) query_str);
	SetSortButtons(attr_elem);
	attr_elem.Release();


	FillValuesList(* cur_str);

}

void CComplexFilterDialog::OnDestroy()
{
	ClearAttributesList();
	
	CPropertyPage::OnDestroy();

	// TODO: Add your message handler code here
}

void CComplexFilterDialog::ClearAttributesList(void)
{
	for (int a = 0; a < m_AttributesList.GetCount(); a++)
	{
		delete (CString *) m_AttributesList.GetItemDataPtr(a);
	}

	m_AttributesList.ResetContent();
}

void CComplexFilterDialog::OnBnClickedAscendingRadio()
{
	FillValuesList();
}

void CComplexFilterDialog::OnBnClickedDescendingRadio()
{
	FillValuesList();
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
	
	if (cur_attr_str == NULL)
	{
		int cur_sel = m_AttributesList.GetCurSel();
		if (cur_sel == LB_ERR) return;
		cur_attr_str = * (CString *) m_AttributesList.GetItemDataPtr(cur_sel);
	}

		CString query_str;
	query_str = "/dialog_data/values/value/@";
	query_str += cur_attr_str;

	MSXML2::IXMLDOMNodeListPtr values = m_filter_DOM->selectNodes((LPCTSTR) query_str);

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

	if (IDC_DESCENDING_RADIO == GetCheckedRadioButton(IDC_ASCENDING_RADIO, IDC_DESCENDING_RADIO))
		str_table.Sort(FALSE);
	else
		str_table.Sort(TRUE);


	for (a = 0; a < str_table.getCount(); a++)
	{
		m_ValuesList.AddString(str_table.getItem(a));
	}



}
