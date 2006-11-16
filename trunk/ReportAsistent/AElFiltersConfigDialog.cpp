// AElFiltersConfigDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ReportAsistent.h"
#include "AElFiltersConfigDialog.h"
#include "ComplexFilterDialog.h"
#include "CSkeletonDoc.h"
#include "APTransform.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAElFiltersConfigDialog dialog


CAElFiltersConfigDialog::CAElFiltersConfigDialog(MSXML2::IXMLDOMElementPtr & active_element, MSXML2::IXMLDOMElementPtr & cloned_element, CWnd* pParent)
	: CPropertyPage(CAElFiltersConfigDialog::IDD), m_active_element(active_element), m_bSourceIsInit(FALSE)
	, CFilterResultImpl(m_filter_DOM), m_cloned_active_element(cloned_element)
{
	//{{AFX_DATA_INIT(CAElFiltersConfigDialog)
	m_CF_IdEdit = _T("");
	//}}AFX_DATA_INIT
	
	//Iva: Inicialisation of ID edit:
	_variant_t varAtr=m_active_element->getAttribute("id");
	m_OldID=(LPCTSTR) (_bstr_t)  varAtr;
	if (varAtr.vt!=VT_NULL)
		m_CF_IdEdit = m_OldID;


	m_cloned_active_element = m_active_element->cloneNode(VARIANT_TRUE);

//	AfxMessageBox(m_cloned_active_element->xml);
}


void CAElFiltersConfigDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAElFiltersConfigDialog)
	DDX_Text(pDX, IDC_CF_ID_EDIT, m_CF_IdEdit);
	DDV_MaxChars(pDX, m_CF_IdEdit, 50);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_DATA_SOURCE_COMBO, m_SourcesCombo);
	DDV_NonDuplicateID(pDX,IDC_CF_ID_EDIT, m_CF_IdEdit);

	DDX_Control(pDX, IDC_FILTERS_LIST, m_FiltersList);
	DDX_Control(pDX, IDC_RESULT_LIST, m_ResultList);

}


BEGIN_MESSAGE_MAP(CAElFiltersConfigDialog, CDialog)
	//{{AFX_MSG_MAP(CAElFiltersConfigDialog)
	ON_BN_CLICKED(IDC_REMOVE_FILTER_BUTTON, OnRemoveFilterButton)
	ON_BN_CLICKED(IDC_MOVE_UP_BUTTON, OnMoveUpButton)
	ON_BN_CLICKED(IDC_MOVE_DOWN_BUTTON, OnMoveDownButton)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_ADD_FILTER_BUTTON, OnBnClickedAddFilterButton)
	ON_CBN_SELCHANGE(IDC_DATA_SOURCE_COMBO, OnCbnSelchangeDataSourceCombo)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CONFIGURE_FILTER_BUTTON, OnBnClickedConfigureFilterButton)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAElFiltersConfigDialog message handlers




BOOL CAElFiltersConfigDialog::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	//nastav typ filtru na complex
	m_cloned_active_element->selectSingleNode("filter/@type")->text = "complex";
	
	CDataSourcesManager & dm = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->DataSourcesManager;
	CElementManager & em = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;

	//nacti zdroje
	for (int a=0; a< dm.getSourcesCount(); a++)
	{
		if (em.isElementSupportedBySource(em.IdentifyElement(m_active_element), a))
		{
			m_SourcesCombo.AddString(dm.getSourcePublicID(a));
		}
	}

	int sel = m_SourcesCombo.SelectString(-1, (_bstr_t) m_active_element->getAttribute("source"));
	if (sel == CB_ERR) m_SourcesCombo.SelectString(-1, dm.getDefaultSource());

	//nacti filtry
	int c = -1;
	c = m_FiltersList.InsertColumn(++c, "Attribute name", 0, 150);
	c = m_FiltersList.InsertColumn(++c, "Filter type", 0, 100);
	m_FiltersList.InsertColumn(++c, "Filter data", 0, 150);

	m_bSourceIsInit = FALSE;

	//UpdateFiltersList(); //az v ctlcolor 


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CAElFiltersConfigDialog::DDV_NonDuplicateID(CDataExchange *pDX, int nId, CString csIDEditValue)
{
	if (0!=pDX->m_bSaveAndValidate) //Iva: if it's end of dialog, not beginning
	{

		if (""==csIDEditValue) //Iva: ID can't be empty string
		{
			SetDlgItemText(nId, m_OldID );
			//dedek: ?CReportAsistentApp::ReportError?
			AfxMessageBox(IDS_INVALID_ELEMENT_ID);
			pDX->Fail();
		}

		CSkeletonDoc * Doc = ((CReportAsistentApp *) AfxGetApp())->FirstDocumentInFirstTemplate();
		if (m_OldID!=csIDEditValue)  //Iva: if "==", then ID is in tree, but it's OK
		{
			if (Doc->IsIDInTree(csIDEditValue))
			{
				SetDlgItemText(nId, m_OldID ); //Iva: return old value to edit box
				AfxMessageBox(IDS_DUPLICATE_ELEMENT_ID);
				//dedek: ?CReportAsistentApp::ReportError(IDS_DUPLICATE_ELEMENT_ID);?
				pDX->Fail();
			}
			else
			{
				//Iva: I try to set ID to new value
				try
				{
					m_active_element->setAttribute("id", (LPCTSTR)csIDEditValue); 
				}
				catch(_com_error &e)
				{
					SetDlgItemText(nId, m_OldID ); //Iva: return old value to edit box
					m_active_element->setAttribute("id", (LPCTSTR)m_OldID);
					//AfxMessageBox(e.Description());
					CReportAsistentApp::ReportError(IDS_INVALID_ELEMENT_ID,e.Description() );
					pDX->Fail();
				}
				m_active_element->setAttribute("id", (LPCTSTR)m_OldID); 

			}

		}

	}

}

void CAElFiltersConfigDialog::OnRemoveFilterButton() 
{
	int nItem = GetCurSelFiltersList();
	if (nItem == -1) return;
	
	CString q;
	q.Format("filter/attribute_filter[%d]", nItem);

	m_cloned_active_element->selectSingleNode("filter")->removeChild(
		m_cloned_active_element->selectSingleNode((LPCTSTR) q));

	UpdateFiltersList();
	UpdateResult();
	SetModified();
}

void CAElFiltersConfigDialog::OnMoveUpButton() 
{
	int nItem = GetCurSelFiltersList();
	if (nItem <= 0) return;
	
	MSXML2::IXMLDOMNodePtr filter = m_cloned_active_element->selectSingleNode("filter");
	
	filter->insertBefore(
		filter->removeChild(filter->childNodes->item[nItem]),
		(MSXML2::IXMLDOMNode *) filter->childNodes->item[nItem-1]);

	UpdateFiltersList();
	UpdateResult();
	SetModified();
}

void CAElFiltersConfigDialog::OnMoveDownButton() 
{
	int nItem = GetCurSelFiltersList();
	if (nItem == -1) return;
	if (nItem >= m_FiltersList.GetItemCount()-1) return;
	
	MSXML2::IXMLDOMNodePtr filter = m_cloned_active_element->selectSingleNode("filter");
	
	if (nItem == m_FiltersList.GetItemCount()-2)
	{
		//preposledni
		filter->appendChild(
			filter->removeChild(filter->childNodes->item[nItem]));
	}
	else
	{

	filter->insertBefore(
		filter->removeChild(filter->childNodes->item[nItem]),
		(MSXML2::IXMLDOMNode *) filter->childNodes->item[nItem+2]);
	}

	UpdateFiltersList();
	UpdateResult();
	SetModified();
}

void CAElFiltersConfigDialog::OnBnClickedConfigureFilterButton()
{
	int nItem = GetCurSelFiltersList();
	if (nItem == -1) return;

	CString q;
	q.Format("filter/attribute_filter[%d]", nItem);

	
	CComplexFilterDialog dlg(m_cloned_active_element, m_filter_DOM, m_cloned_active_element->selectSingleNode((LPCTSTR) q));
	if (IDOK == dlg.DoModal())
	{
		UpdateFiltersList();
		UpdateResult();
		SetModified();
	}
}

void CAElFiltersConfigDialog::OnBnClickedAddFilterButton()
{
	CComplexFilterDialog dlg(m_cloned_active_element, m_filter_DOM);
	dlg.DoModal();

	UpdateFiltersList();
	UpdateResult();
	SetModified();
}

MSXML2::IXMLDOMElementPtr & CAElFiltersConfigDialog::getActiveElement(void)
{
	return m_active_element;
}

MSXML2::IXMLDOMElementPtr & CAElFiltersConfigDialog::getClonedActiveElement(void)
{
	return m_cloned_active_element;
}

BOOL CAElFiltersConfigDialog::OnApply()
{
	m_active_element->parentNode->replaceChild(m_cloned_active_element, m_active_element);

	m_active_element = m_cloned_active_element;
	m_cloned_active_element = m_active_element->cloneNode(VARIANT_TRUE);

/*
	AfxMessageBox(m_active_element->xml);
	
	CAElTransform tr(m_active_element);
	tr.TransformCmplexFilterToSimple();

	AfxMessageBox(m_active_element->xml);
*/
	return TRUE; //zavola se SetModified(FALSE);
}

void CAElFiltersConfigDialog::OnOK()
{
	OnApply();

	CPropertyPage::OnOK();
}

void CAElFiltersConfigDialog::UpdateFiltersList(void)
{
	ASSERT(m_filter_DOM != NULL);

	m_FiltersList.DeleteAllItems();

	MSXML2::IXMLDOMNodeListPtr attr_filters =
		m_cloned_active_element->selectNodes("filter/attribute_filter");

	for (int a = 0; a < attr_filters->length; a++)
	{
		CString q;
		q.Format("/dialog_data/attributes/attribute[@name=\"%s\"]/@label", (LPCTSTR) attr_filters->item[a]->selectSingleNode("@attr_name")->text);
		
		
		CString attr_label = "(n/a)";

		try 
		{
			attr_label = (LPCTSTR) m_filter_DOM->selectSingleNode((LPCTSTR) q)->text;
		}
		catch (...) {}
		
		int i = m_FiltersList.InsertItem(a, attr_label);

		m_FiltersList.SetItemText(i, 1, attr_filters->item[a]->selectSingleNode("@filter_type")->text);
		m_FiltersList.SetItemText(i, 2, attr_filters->item[a]->selectSingleNode("@filter_data")->text);
	}
}

void CAElFiltersConfigDialog::OnCbnSelchangeDataSourceCombo()
{
	CString text;
	m_SourcesCombo.GetWindowText(text);

	m_cloned_active_element->setAttribute("source", (_bstr_t) text);

	if (text.GetLength() == 0) return;

	if (LoadSource(text))
	{
//		UpDateDialog();
		InitResultView();
		UpdateFiltersList();
		UpdateResult();
	}
	else
	{
//		ClearAttributesList();
	}

	
	// TODO: Add your control notification handler code here
}

HBRUSH CAElFiltersConfigDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

	//dedek: tohle se tady vola kvuli inicializaci filtru - kdyz se to delalo uz v init_dialog tak to padalo!!
	if (! m_bSourceIsInit)
	{
		m_bSourceIsInit = TRUE;
		OnCbnSelchangeDataSourceCombo();
//		SetModified(FALSE);
		Invalidate(FALSE);
	}

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}



BOOL CAElFiltersConfigDialog::LoadSource(public_source_id_t sId)
{
	CAElTransform tr(m_active_element);

	return tr.LoadFilterDOM(sId, m_filter_DOM);
/*
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
*/		
}


int CAElFiltersConfigDialog::GetCurSelFiltersList()
{
	POSITION pos = m_FiltersList.GetFirstSelectedItemPosition();
	if (pos == NULL) return -1;

	return m_FiltersList.GetNextSelectedItem(pos);
}

void CAElFiltersConfigDialog::UpdateResult(void)
{
		//zaloha dat
	MSXML2::IXMLDOMElementPtr values_clone = m_filter_DOM->selectSingleNode("/dialog_data/values")->cloneNode(VARIANT_TRUE);
	
	CAElTransform tr(m_cloned_active_element);
	tr.ApplyAllAttributeFilters(m_filter_DOM);

//	AfxMessageBox(m_filter_DOM->xml);

	CFilterResultImpl::UpdateResult(m_filter_DOM);
	
	//obnova dat
	m_filter_DOM->selectSingleNode("/dialog_data")->replaceChild(values_clone,
		m_filter_DOM->selectSingleNode("/dialog_data/values"));
}
