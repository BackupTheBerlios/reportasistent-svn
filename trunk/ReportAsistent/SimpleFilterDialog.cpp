// SimpleFilterDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ReportAsistent.h"
#include "SimpleFilterDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSimpleFilterDialog dialog


CSimpleFilterDialog::CSimpleFilterDialog(IXMLDOMElementPtr & active_element, BSTR plugin_output, CWnd* pParent)
	: CDialog(CSimpleFilterDialog::IDD, pParent), m_active_element(active_element)
{
	//{{AFX_DATA_INIT(CSimpleFilterDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT




	//necte tranformaci, ktera pripravi data pro vytvoreni dialogu
	IXMLDOMDocumentPtr filter_transform;
	filter_transform.CreateInstance(_T("Msxml2.DOMDocument"));
	filter_transform->async = VARIANT_FALSE; // default - true,
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!111
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!111
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!111
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!111
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!111
	//predelat pres directory manager,ruzne pro ruzne typy prvku
	filter_transform->load(_T("../XML/4ft_hyp2filterdlg.xsl"));
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!111
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!111
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!111
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!111	
	
	
	//nacte data z plugin output
	IXMLDOMDocumentPtr filter_doc;
	filter_doc.CreateInstance(_T("Msxml2.DOMDocument"));
	filter_doc->async = VARIANT_FALSE; // default - true,	
	filter_doc->loadXML(plugin_output);

	//transformuje data z plugin output a vysledek nacte do m_filter_dom	
	filter_doc->loadXML(
		filter_doc->transformNode(filter_transform));
	
	
	//pridat AddRef ?
	m_filter_DOM = filter_doc->documentElement;

	filter_transform.Release();
	filter_doc.Release();

}


void CSimpleFilterDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSimpleFilterDialog)
	DDX_Control(pDX, IDC_FILTER_LIST, m_FilterList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSimpleFilterDialog, CDialog)
	//{{AFX_MSG_MAP(CSimpleFilterDialog)
	ON_NOTIFY(LVN_DELETEITEM, IDC_FILTER_LIST, OnDeleteitemFilterList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimpleFilterDialog message handlers

BOOL CSimpleFilterDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	int a,b;

	IXMLDOMNodeListPtr attr_list = m_filter_DOM->selectNodes("/dialog_data/attributes/attribute");

	
	//vyrobime sloupce
	for (a=0; a<attr_list->length; a++)
	{
		IXMLDOMElementPtr attr = attr_list->item[a];

		m_FilterList.InsertColumn(a, (_bstr_t) attr->getAttribute("name"), LVCFMT_LEFT, 75);

	}

	//naplnime list hodnotama
	IXMLDOMNodeListPtr value_list = m_filter_DOM->selectNodes("/dialog_data/values/value");

	for (b=0; b<value_list->length; b++)
	{
		IXMLDOMElementPtr value = value_list->item[b];


		//pro kazdy sloupec ulozime hodnotu
		for (a=0; a<attr_list->length; a++)
		{
			IXMLDOMElementPtr attr = attr_list->item[a];

			if (a == 0)
			{
				m_FilterList.InsertItem(b, (_bstr_t) value->getAttribute(
					(_bstr_t) attr->getAttribute("name")));

			}
			else
			{	
				m_FilterList.SetItemText(b, a, (_bstr_t) value->getAttribute(
					(_bstr_t) attr->getAttribute("name")));
			}

		}

		_bstr_t id = value->getAttribute("id");
		m_FilterList.SetItemData(b, (DWORD) new CString((BSTR) id));

		//selsected polozky

		CString patern = "filter[@type='simple']/selection[@id='";
		patern += id;
		patern += "']";

		IXMLDOMNodePtr select = m_active_element->selectSingleNode((LPCTSTR) patern);

		if (select != NULL)
			m_FilterList.SetItemState(b, LVIS_SELECTED, LVIS_SELECTED);

	}
	
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
	
	//honza nutno po sobe uklidit - thle jsem tam nasypal v init dialog
	delete (CString *) pNMListView->lParam;

	*pResult = 0;
}
