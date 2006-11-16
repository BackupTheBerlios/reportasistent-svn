// SimpleFilterDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ReportAsistent.h"
#include "SimpleFilterDialog.h"
#include "APTransform.h"
#include "CSkeletonDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSimpleFilterDialog dialog


CSimpleFilterDialog::CSimpleFilterDialog(CAElDataShare & data_share, CWnd* pParent)
: CPropertyPage(CSimpleFilterDialog::IDD)
, CAElDataShare(data_share)
, CFilterResultImpl(data_share.m_filter_DOM)
, m_bSimpleFilterDisabled(TRUE)
{

	if (m_cloned_active_element->selectSingleNode("filter[@type=\"simple\"]") == NULL)
	{
		MSXML2::IXMLDOMElementPtr new_filter = 
			m_cloned_active_element->selectSingleNode("filter")->cloneNode(VARIANT_FALSE);
	
		new_filter->setAttribute("type", "simple");
		
		m_cloned_active_element->insertBefore(new_filter, 
			(MSXML2::IXMLDOMNode *) m_cloned_active_element->selectSingleNode("filter"));
	}

	m_bSimpleFilterDisabled = 
		m_cloned_active_element->
			selectNodes("filter[@type=\"simple\"]/selection")->length == 0;
}

CSimpleFilterDialog::~CSimpleFilterDialog()
{
}


void CSimpleFilterDialog::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	
	//{{AFX_DATA_MAP(CSimpleFilterDialog)
	DDX_Control(pDX, IDC_FILTER_LIST, m_ResultList);
	DDX_Check(pDX, IDC_SIMPLE_FILTER_DISABLED_CHECK, m_bSimpleFilterDisabled);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSimpleFilterDialog, CPropertyPage)
	//{{AFX_MSG_MAP(CSimpleFilterDialog)
	ON_NOTIFY(LVN_DELETEITEM, IDC_FILTER_LIST, OnDeleteitemFilterList)
	ON_NOTIFY(NM_CLICK, IDC_FILTER_LIST, OnNMClickFilterList)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_SIMPLE_FILTER_DISABLED_CHECK, &CSimpleFilterDialog::OnSimpleFilterDisabledCheck)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimpleFilterDialog message handlers

BOOL CSimpleFilterDialog::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	 
	OnSimpleFilterDisabledCheck();


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


void CSimpleFilterDialog::UpdateSelection()
{
	MSXML2::IXMLDOMNodeListPtr sel_ids = m_cloned_active_element->
		selectNodes("filter[@type='simple']/selection/@id");

	LVFINDINFO fi;
	ZeroMemory(& fi, sizeof fi);
	fi.flags = LVFI_STRING;

	for (int a = 0; a < sel_ids->length; a++)
	{
		CString s = (LPCTSTR) sel_ids->item[a]->text;
		fi.psz = s;
	
		int item = m_ResultList.FindItem(& fi);
		if (item != -1)
			m_ResultList.SetItemState(item, LVIS_SELECTED, LVIS_SELECTED);
	}
}




BOOL CSimpleFilterDialog::SaveAll()
{
/*
	POSITION pos = m_FilterList.GetFirstSelectedItemPosition(); 

//dedek:	umoznime i prazdny fiter
/*		
	if (pos == NULL)
	{
		AfxMessageBox(IDS_SIMPLE_FILTER_EMPTY_SELECTION);
		return FALSE;
	}

	
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
*/
	return TRUE;
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


BOOL CSimpleFilterDialog::OnSetActive()
{
	InitResultView();
	UpdateResult(m_filter_DOM);
	UpdateSelection();

	return CPropertyPage::OnSetActive();
}

void CSimpleFilterDialog::OnSimpleFilterDisabledCheck()
{
	UpdateData();

	if (m_bSimpleFilterDisabled)
	{
		m_ResultList.EnableWindow(FALSE);
	}
	else
	{
		m_ResultList.EnableWindow(TRUE);
	}
}
