// SimpleFilterDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ReportAsistent.h"
#include "SimpleFilterDialog.h"
#include "APTransform.h"
//#include "SkeletonManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSimpleFilterDialog dialog


CSimpleFilterDialog::CSimpleFilterDialog(MSXML2::IXMLDOMElementPtr & active_element, CWnd* pParent)
: CPropertyPage(CSimpleFilterDialog::IDD), m_active_element(active_element)
, m_bSourceIsInit(FALSE)
{
	//{{AFX_DATA_INIT(CSimpleFilterDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT




	//necte tranformaci, ktera pripravi data pro vytvoreni dialogu
//	m_filter_transform.CreateInstance(_T("Msxml2.DOMDocument"));
//	m_filter_transform->async = VARIANT_FALSE; // default - true,
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!111
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!111
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!111
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!111
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!111
	//predelat pres directory manager,ruzne pro ruzne typy prvku
//	m_filter_transform->load(_T("../XML/4ft_hyp2filterdlg.xsl"));
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!111
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!111
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!111
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!111	


//	filter_transform.Release();
}

CSimpleFilterDialog::~CSimpleFilterDialog()
{
	if (m_filter_DOM != NULL) m_filter_DOM.Release();
//	if (m_filter_transform != NULL) m_filter_transform.Release();

	//ladici:
//	CAElTransform tr(m_active_element);
//	tr.FillElementAttributes(0);
}


void CSimpleFilterDialog::DoDataExchange(CDataExchange* pDX)
{
  CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSimpleFilterDialog)
	DDX_Control(pDX, IDC_DATA_SOURCE_COMBO, m_SourcesCombo);
	DDX_Control(pDX, IDC_FILTER_LIST, m_FilterList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSimpleFilterDialog, CPropertyPage)
	//{{AFX_MSG_MAP(CSimpleFilterDialog)
	ON_NOTIFY(LVN_DELETEITEM, IDC_FILTER_LIST, OnDeleteitemFilterList)
	ON_CBN_SELCHANGE(IDC_DATA_SOURCE_COMBO, OnSelchangeDataSourceCombo)
	//}}AFX_MSG_MAP
//  ON_WM_ENTERIDLE()
//ON_WM_ACTIVATE()
ON_WM_CTLCOLOR()
//ON_NOTIFY(LVN_ODSTATECHANGED, IDC_FILTER_LIST, &CSimpleFilterDialog::OnLvnOdstatechangedFilterList)
ON_NOTIFY(NM_CLICK, IDC_FILTER_LIST, OnNMClickFilterList)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimpleFilterDialog message handlers

BOOL CSimpleFilterDialog::OnInitDialog() 
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


	//ve VS2005 nefungovalo, preneseno do OnCtlColor
	//OnSelchangeDataSourceCombo();
	m_bSourceIsInit = FALSE;
	  

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSimpleFilterDialog::OnDeleteitemFilterList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	//honza: nutno po sobe uklidit - tohle jsem tam nasypal v init dialog
	delete (CString *) pNMListView->lParam;

	*pResult = 0;
}

BOOL CSimpleFilterDialog::LoadSource(public_source_id_t sId)
{
	
	//inicializace
	MSXML2::IXMLDOMDocumentPtr filter_doc;
	MSXML2::IXMLDOMDocumentPtr filter_doc2;
	filter_doc2.CreateInstance(_T("Msxml2.DOMDocument"));
	filter_doc2->async = VARIANT_FALSE; // default - true,

	CGeneralManager * m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager;

	CAElInfo * element_info = m->ElementManager.getActiveElementInfo(
								m->ElementManager.IdentifyElement(m_active_element));



	//nacte data z plugin output

	if (! m->DataSourcesManager.GetPluginOutput(sId, (_bstr_t) element_info->getElementName(), & filter_doc)) 
	{
		filter_doc.Release();
		CReportAsistentApp::ReportError(IDS_SIMPLE_FILTER_FAILED_SOURCE_LOAD, "Plugin output is empty.");
		return FALSE;	
	}


#ifdef _DEBUG	
	//dadici - kdykoliv smazat nebo zakomentovat
	CDirectoriesManager & dm = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->DirectoriesManager;
	filter_doc->save((LPCTSTR) (dm.getXMLFilesDirectory() + "/plug_out_example.xml"));
#endif


	//ulozi element atributy
	CAElTransform tr(m_active_element, (MSXML2::IXMLDOMNodePtr) filter_doc);
	tr.FillElementAttributes(0);

	
	//transformuje data z plugin output a vysledek nacte do m_filter_dom	
	filter_doc2->loadXML(
		filter_doc->transformNode(element_info->getSimpleFilterTransformation()));

	
#ifdef _DEBUG	
	//dadici - kdykoliv smazat nebo zakomentovat
	filter_doc->save((LPCTSTR) (dm.getXMLFilesDirectory() + "/simple_filter_example.xml"));
#endif

	
	//pridat AddRef ?
	if (filter_doc2->documentElement != NULL)
	{
		m_filter_DOM = filter_doc2->documentElement;
		filter_doc2.Release();
		filter_doc.Release();
		return TRUE;
	}

	filter_doc.Release();
	CReportAsistentApp::ReportError(IDS_SIMPLE_FILTER_FAILED_SOURCE_LOAD, "Plugin output - document element is empty.");
	return FALSE;	
}

void CSimpleFilterDialog::UpDateDialog()
{
	int a,b;

	m_FilterList.DeleteAllItems();

	
	// Delete all of the columns.
	int nColumnCount = m_FilterList.GetHeaderCtrl()->GetItemCount();
	for (int i=0;i < nColumnCount;i++)
	{
		m_FilterList.DeleteColumn(0);
	}
	
	
	MSXML2::IXMLDOMNodeListPtr attr_list = m_filter_DOM->selectNodes("/dialog_data/attributes/attribute");

	
	//vyrobime sloupce
	for (a=0; a<attr_list->length; a++)
	{
		MSXML2::IXMLDOMElementPtr attr = attr_list->item[a];

		m_FilterList.InsertColumn(a, (_bstr_t) attr->getAttribute("name"), LVCFMT_LEFT, 75);

	}

	//naplnime list hodnotama
	MSXML2::IXMLDOMNodeListPtr value_list = m_filter_DOM->selectNodes("/dialog_data/values/value");

	int item = 0;

	for (b=0; b<value_list->length; b++)
	{
		MSXML2::IXMLDOMElementPtr value = value_list->item[b];


		//pro kazdy sloupec ulozime hodnotu
		for (a=0; a<attr_list->length; a++)
		{
			MSXML2::IXMLDOMElementPtr attr = attr_list->item[a];

			if (a == 0)
			{
				item = m_FilterList.InsertItem(b, (_bstr_t) value->getAttribute(
					(_bstr_t) attr->getAttribute("name")));

			}
			else
			{	
				m_FilterList.SetItemText(item, a, (_bstr_t) value->getAttribute(
					(_bstr_t) attr->getAttribute("name")));
			}

		}

		_bstr_t id = value->getAttribute("id");
		m_FilterList.SetItemData(item, (DWORD) new CString((BSTR) id));

		//selsected polozky

		CString patern = "filter[@type='simple']/selection[@id='";
		patern += (LPCTSTR) id;
		patern += "']";

		MSXML2::IXMLDOMNodePtr select = m_active_element->selectSingleNode((LPCTSTR) patern);

		if (select != NULL)
			m_FilterList.SetItemState(item, LVIS_SELECTED, LVIS_SELECTED);

	}

}

void CSimpleFilterDialog::OnSelchangeDataSourceCombo() 
{	
	CString text;
	m_SourcesCombo.GetWindowText(text);

	if (text.GetLength() == 0) return;

	if (LoadSource(text))
	{
		UpDateDialog();
	}

  SetModified();
/*
	else
	{
		AfxMessageBox(IDS_SIMPLE_FILTER_FAILED_SOURCE_LOAD);
		presunuto do LoadSource
	}
*/
}


BOOL CSimpleFilterDialog::SaveAll()
{
	POSITION pos = m_FilterList.GetFirstSelectedItemPosition(); 

//dedek:	umoznime i prazdny fiter
/*		
	if (pos == NULL)
	{
		AfxMessageBox(IDS_SIMPLE_FILTER_EMPTY_SELECTION);
		return FALSE;
	}
*/
	CString source;
	m_SourcesCombo.GetWindowText(source);
	m_active_element->setAttribute("source", (LPCTSTR) source);
	
	//okopiruje vzorovy element selection
	MSXML2::IXMLDOMElementPtr selection_elem = m_active_element->ownerDocument->createElement("selection");
	MSXML2::IXMLDOMAttributePtr id_attr = m_active_element->ownerDocument->createAttribute("id");
	selection_elem->setAttributeNode(id_attr);
	id_attr.Release();
	
	//vymaze vsechny selection
	MSXML2::IXMLDOMNodeListPtr list = m_active_element->selectNodes("filter[@type='simple']/selection");
	MSXML2::IXMLDOMSelection * sel;
	list.QueryInterface(__uuidof(MSXML2::IXMLDOMSelection), &sel);
	sel->removeAll();
	sel->Release();

	MSXML2::IXMLDOMNodePtr filter = m_active_element->selectSingleNode("filter[@type='simple']");
	
	while (pos)
	{
		int nItem = m_FilterList.GetNextSelectedItem(pos);

		selection_elem->setAttribute("id", (LPCTSTR) * (CString *) m_FilterList.GetItemData(nItem));
		filter->appendChild(selection_elem->cloneNode(VARIANT_FALSE));
	}

	selection_elem.Release();

	return TRUE;
}




HBRUSH CSimpleFilterDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
  HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

  //dedek: tohle se tady vola kvuli inicializaci filtru - kdyz se to delalo uz v init_dialog tak to padalo!!
  if (! m_bSourceIsInit)
  {
    m_bSourceIsInit = TRUE;
    OnSelchangeDataSourceCombo();
    SetModified(FALSE);
    Invalidate(FALSE);
  }

  // TODO:  Change any attributes of the DC here

  // TODO:  Return a different brush if the default is not desired
  return hbr;
}


BOOL CSimpleFilterDialog::OnApply()
{
  if (SaveAll())
  {
    SetModified(FALSE);
    return TRUE;
  }

  return FALSE;
}


void CSimpleFilterDialog::OnOK()
{
  OnApply();

  CPropertyPage::OnOK();
}



void CSimpleFilterDialog::OnNMClickFilterList(NMHDR *pNMHDR, LRESULT *pResult)
{
  SetModified();

  // TODO: Add your control notification handler code here
  *pResult = 0;
}
