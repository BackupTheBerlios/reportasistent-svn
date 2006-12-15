// SimpleFilterDialog.cpp : implementation file
//
/*
This file is part of LM Report Asistent.

Authors: Jan Dedek, Jan Kodym, Martin Chrz, Iva Bartunkova

LM Report Asistent is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

Foobar is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Foobar; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
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

	SetDisabledCheck();
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
	ON_BN_CLICKED(IDC_SIMPLE_FILTER_DISABLED_CHECK, OnSimpleFilterDisabledCheck)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimpleFilterDialog message handlers

BOOL CSimpleFilterDialog::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	 
//	CheckSimpleFilterDisabled();


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

BOOL CSimpleFilterDialog::OnApply()
{
	ApplyChanges();
	return TRUE;
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
	UpdateSimpleView();
	SetDisabledCheck();
	UpdateData(FALSE);
	CheckSimpleFilterDisabled();
	
	if (! m_bSimpleFilterDisabled) UpdateSelection();

	return CPropertyPage::OnSetActive();
}

void CSimpleFilterDialog::CheckSimpleFilterDisabled()
{
	UpdateData();

	if (m_bSimpleFilterDisabled)
	{
		m_ResultList.EnableWindow(FALSE);

		//vycisti simple fiter tag

		MSXML2::IXMLDOMNodePtr simple_filter = m_cloned_active_element->selectSingleNode("filter[@type=\"simple\"]");
		while (simple_filter->firstChild != NULL)
		{
			simple_filter->removeChild(simple_filter->firstChild);
		}

		//zrusi vybrane polozky		
		UpdateSimpleView();
	}
	else
	{
		m_ResultList.EnableWindow(TRUE);
	}
}


void CSimpleFilterDialog::OnSimpleFilterDisabledCheck()
{
	CheckSimpleFilterDisabled();
	SetModified();
}

void CSimpleFilterDialog::SetDisabledCheck(void)
{
	m_bSimpleFilterDisabled = 
		m_cloned_active_element->
			selectNodes("filter[@type=\"simple\"]/selection")->length == 0;

	m_bSimpleFilterDisabled = 
		(m_bSimpleFilterDisabled || (m_filter_DOM == NULL));

	//AfxMessageBox(m_cloned_active_element->selectSingleNode("filter[@type=\"simple\"]")->xml);

}



BOOL CSimpleFilterDialog::OnKillActive()
{
	SaveSelection();

	return CPropertyPage::OnKillActive();
}

void CSimpleFilterDialog::SaveSelection(void)
{
	POSITION pos = m_ResultList.GetFirstSelectedItemPosition(); 

	
	//okopiruje vzorovy element selection
	MSXML2::IXMLDOMElementPtr selection_elem = m_active_element->ownerDocument->createElement("selection");
	MSXML2::IXMLDOMAttributePtr id_attr = m_active_element->ownerDocument->createAttribute("id");
	selection_elem->setAttributeNode(id_attr);
	id_attr.Release();
	
	//vymaze vsechny selection
	MSXML2::IXMLDOMNodeListPtr list = m_cloned_active_element->selectNodes("filter[@type='simple']/selection");
	MSXML2::IXMLDOMSelection * sel;
	list.QueryInterface(__uuidof(MSXML2::IXMLDOMSelection), &sel);
	sel->removeAll();
	sel->Release();

	MSXML2::IXMLDOMNodePtr filter = m_cloned_active_element->selectSingleNode("filter[@type='simple']");
	
	while (pos)
	{
		int nItem = m_ResultList.GetNextSelectedItem(pos);

		selection_elem->setAttribute("id", (LPCTSTR) m_ResultList.GetItemText(nItem, 0));
		filter->appendChild(selection_elem->cloneNode(VARIANT_FALSE));
	}

	selection_elem.Release();

}


void CSimpleFilterDialog::UpdateSimpleView(void)
{
	if (m_filter_DOM == NULL) return;

	//zaloha dat
	MSXML2::IXMLDOMElementPtr values_clone = m_filter_DOM->selectSingleNode("/dialog_data/values")->cloneNode(VARIANT_TRUE);
	
	CAElTransform at(m_cloned_active_element);
	at.ApplyAllAttributeFilters(m_filter_DOM);

	UpdateResult(m_filter_DOM);


	//obnova dat
	m_filter_DOM->selectSingleNode("/dialog_data")->replaceChild(values_clone,
		m_filter_DOM->selectSingleNode("/dialog_data/values"));
}

//DEL void CSimpleFilterDialog::OnItemclickFilterList(NMHDR* pNMHDR, LRESULT* pResult) 
//DEL {
//DEL 	NMLISTVIEW *pLV = (NMLISTVIEW *) pNMHDR;
//DEL 	AfxMessageBox("Pozor");
//DEL 
//DEL 	m_ResultList.SortItems((PFNLVCOMPARE)SortFunc, pLV->iItem);
//DEL 	
//DEL 	*pResult = 0;
//DEL }


//DEL int CALLBACK CSimpleFilterDialog::SortFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
//DEL {
//DEL  
//DEL  	int nRetVal=0;
//DEL 
//DEL 	if (!(lParam1 && lParam2)) return 1;
//DEL 
//DEL  	CString pData1 = ((LVITEM*)lParam1)->pszText;
//DEL  	CString pData2 = ((LVITEM*)lParam2)->pszText;
//DEL  
//DEL 	AfxMessageBox(pData1);
//DEL  /*
//DEL  	switch(lParamSort)
//DEL  	{
//DEL  	case 0:	// Last Name
//DEL  		nRetVal = strcmp(pData1->pszLastName,
//DEL                                   pData2->pszLastName);
//DEL  		break;
//DEL  
//DEL  	case 1:	// First Name
//DEL  		nRetVal = strcmp(pData1->pszFirstName,
//DEL                                   pData2->pszFirstName);
//DEL  		break;
//DEL  
//DEL  	case 2: // Term
//DEL  		nRetVal = strcmp(pData1->pszTerm, pData2->pszTerm);
//DEL  		break;
//DEL  
//DEL  	default:
//DEL  		break;
//DEL  	}*/
//DEL 
//DEL  	return nRetVal;
//DEL }


