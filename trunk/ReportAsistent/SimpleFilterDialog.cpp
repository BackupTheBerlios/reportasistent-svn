// SimpleFilterDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ReportAsistent.h"
#include "SimpleFilterDialog.h"
#include "SkeletonManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSimpleFilterDialog dialog


CSimpleFilterDialog::CSimpleFilterDialog(IXMLDOMElementPtr & active_element, CWnd* pParent)
	: CDialog(CSimpleFilterDialog::IDD, pParent), m_active_element(active_element)
{
	//{{AFX_DATA_INIT(CSimpleFilterDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT




	//necte tranformaci, ktera pripravi data pro vytvoreni dialogu
	m_filter_transform.CreateInstance(_T("Msxml2.DOMDocument"));
	m_filter_transform->async = VARIANT_FALSE; // default - true,
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!111
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!111
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!111
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!111
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!111
	//predelat pres directory manager,ruzne pro ruzne typy prvku
	m_filter_transform->load(_T("../XML/4ft_hyp2filterdlg.xsl"));
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!111
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!111
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!111
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!111	


//	filter_transform.Release();

}


void CSimpleFilterDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSimpleFilterDialog)
	DDX_Control(pDX, IDC_DATA_SOURCE_COMBO, m_SourcesCombo);
	DDX_Control(pDX, IDC_FILTER_LIST, m_FilterList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSimpleFilterDialog, CDialog)
	//{{AFX_MSG_MAP(CSimpleFilterDialog)
	ON_NOTIFY(LVN_DELETEITEM, IDC_FILTER_LIST, OnDeleteitemFilterList)
	ON_CBN_SELCHANGE(IDC_DATA_SOURCE_COMBO, OnSelchangeDataSourceCombo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimpleFilterDialog message handlers

BOOL CSimpleFilterDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CDataSourcesManager & dm = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->DataSourcesManager;
	CElementManager & em = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;

	for (int a=0; a< dm.getSourcesCount(); a++)
	{
		if (em.ElementSupportedBySource(em.IdentifyElement(m_active_element), a))
		{
			m_SourcesCombo.AddString(dm.getSourcePublicID(a));
		}
	}



	int sel = m_SourcesCombo.SelectString(-1, (_bstr_t) m_active_element->getAttribute("source"));
	if (sel == CB_ERR) m_SourcesCombo.SelectString(-1, dm.getSourcePublicID(0));

	OnSelchangeDataSourceCombo();
	  

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSimpleFilterDialog::OnOK() 
{
	POSITION pos = m_FilterList.GetFirstSelectedItemPosition(); 

	if (pos == NULL)
	{
		AfxMessageBox(IDS_SIMPLE_FILTER_EMPTY_SELECTION);
		return;
	}

	CString source;
	m_SourcesCombo.GetWindowText(source);
	m_active_element->setAttribute("source", (LPCTSTR) source);
	
	//okopiruje vzorovy element selection
	IXMLDOMNodePtr select_node = m_active_element->selectSingleNode("filter[@type='simple']/selection")->cloneNode(VARIANT_FALSE);
	
	//vymaze vsechny selection
	IXMLDOMNodeListPtr list = m_active_element->selectNodes("filter[@type='simple']/selection");
	IXMLDOMSelection * sel;
	list.QueryInterface(__uuidof(IXMLDOMSelection), &sel);
	sel->removeAll();
	sel->Release();

	IXMLDOMNodePtr filter = m_active_element->selectSingleNode("filter[@type='simple']");
	
	while (pos)
	{
		int nItem = m_FilterList.GetNextSelectedItem(pos);

		IXMLDOMElementPtr el = select_node->cloneNode(VARIANT_FALSE);

		el->setAttribute("id", (LPCTSTR) * (CString *) m_FilterList.GetItemData(nItem));
		filter->appendChild(el);
	}

	select_node.Release();
	

	CDialog::OnOK();
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
	
	//nacte data z plugin output
	IXMLDOMDocumentPtr filter_doc;
	filter_doc.CreateInstance(_T("Msxml2.DOMDocument"));
	filter_doc->async = VARIANT_FALSE; // default - true,	

	_bstr_t s_out = 
		CSkeletonManager::GetPluginOutput(sId, (_bstr_t) m_active_element->getAttribute("type"));

	if (NULL == (BSTR) s_out) 
	{
		filter_doc.Release();
		return FALSE;	
	}

	filter_doc->loadXML(s_out);
	if (filter_doc->parseError->errorCode != S_OK)
	{
		AfxMessageBox(filter_doc->parseError->reason);
		filter_doc.Release();
		return FALSE;	
	}

	//transformuje data z plugin output a vysledek nacte do m_filter_dom	
	filter_doc->loadXML(
		filter_doc->transformNode(m_filter_transform));
	
	
	//pridat AddRef ?
	if (filter_doc->documentElement != NULL)
	{
		m_filter_DOM = filter_doc->documentElement;
		filter_doc.Release();
		return TRUE;
	}

	filter_doc.Release();
	return FALSE;	
}

CSimpleFilterDialog::~CSimpleFilterDialog()
{
	if (m_filter_DOM != NULL) m_filter_DOM.Release();
	if (m_filter_transform != NULL) m_filter_transform.Release();
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
	
	
	IXMLDOMNodeListPtr attr_list = m_filter_DOM->selectNodes("/dialog_data/attributes/attribute");

	
	//vyrobime sloupce
	for (a=0; a<attr_list->length; a++)
	{
		IXMLDOMElementPtr attr = attr_list->item[a];

		m_FilterList.InsertColumn(a, (_bstr_t) attr->getAttribute("name"), LVCFMT_LEFT, 75);

	}

	//naplnime list hodnotama
	IXMLDOMNodeListPtr value_list = m_filter_DOM->selectNodes("/dialog_data/values/value");

	int item = 0;

	for (b=0; b<value_list->length; b++)
	{
		IXMLDOMElementPtr value = value_list->item[b];


		//pro kazdy sloupec ulozime hodnotu
		for (a=0; a<attr_list->length; a++)
		{
			IXMLDOMElementPtr attr = attr_list->item[a];

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
		patern += id;
		patern += "']";

		IXMLDOMNodePtr select = m_active_element->selectSingleNode((LPCTSTR) patern);

		if (select != NULL)
			m_FilterList.SetItemState(item, LVIS_SELECTED, LVIS_SELECTED);

	}

}

void CSimpleFilterDialog::OnSelchangeDataSourceCombo() 
{	
	CString text;
	m_SourcesCombo.GetWindowText(text);

	if (LoadSource(text))
	{
		UpDateDialog();
	}
	else
	{
		AfxMessageBox(IDS_SIMPLE_FILTER_FAILED_SOURCE_LOAD);
	}

}
