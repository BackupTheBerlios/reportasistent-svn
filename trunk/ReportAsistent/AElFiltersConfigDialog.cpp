// AElFiltersConfigDialog.cpp : implementation file
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


CAElFiltersConfigDialog::CAElFiltersConfigDialog(CAElDataShare & data_share, CWnd* pParent)
	: CPropertyPage(CAElFiltersConfigDialog::IDD)
	, CAElDataShare(data_share)
	, CFilterResultImpl(data_share.m_filter_DOM)

{

	m_cloned_active_element = m_active_element->cloneNode(VARIANT_TRUE);

	if (m_cloned_active_element->selectSingleNode("filter[@type=\"complex\"]") != NULL) return;

	MSXML2::IXMLDOMElementPtr new_filter = 
		m_cloned_active_element->selectSingleNode("filter")->cloneNode(VARIANT_FALSE);
	
	new_filter->setAttribute("type", "complex");

	m_cloned_active_element->insertBefore(new_filter, 
		(MSXML2::IXMLDOMNode *) m_cloned_active_element->selectSingleNode("filter"));

}


void CAElFiltersConfigDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAElFiltersConfigDialog)
	//}}AFX_DATA_MAP

	DDX_Control(pDX, IDC_FILTERS_LIST, m_FiltersList);
	DDX_Control(pDX, IDC_RESULT_LIST, m_ResultList);
}


BEGIN_MESSAGE_MAP(CAElFiltersConfigDialog, CDialog)
	//{{AFX_MSG_MAP(CAElFiltersConfigDialog)
	ON_BN_CLICKED(IDC_REMOVE_FILTER_BUTTON, OnRemoveFilterButton)
	ON_BN_CLICKED(IDC_MOVE_UP_BUTTON, OnMoveUpButton)
	ON_BN_CLICKED(IDC_MOVE_DOWN_BUTTON, OnMoveDownButton)
	ON_NOTIFY(NM_DBLCLK, IDC_FILTERS_LIST, OnDblclkFiltersList)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_ADD_FILTER_BUTTON, OnBnClickedAddFilterButton)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CONFIGURE_FILTER_BUTTON, OnBnClickedConfigureFilterButton)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAElFiltersConfigDialog message handlers




BOOL CAElFiltersConfigDialog::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_FiltersList.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	//nacti filtry
	int c = -1;
	c = m_FiltersList.InsertColumn(++c, "Attribute name", 0, 150);
	c = m_FiltersList.InsertColumn(++c, "Filter type", 0, 100);
	m_FiltersList.InsertColumn(++c, "Filter data", 0, 150);


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
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
		//predposledni
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
	ConfigureFilter();
}

void CAElFiltersConfigDialog::OnBnClickedAddFilterButton()
{
	AddFilter();
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
	ApplyChanges();

	return TRUE; //zavola se SetModified(FALSE);
}

void CAElFiltersConfigDialog::UpdateFiltersList(void)
{
	m_FiltersList.DeleteAllItems();

	if(m_filter_DOM == NULL) return;

	MSXML2::IXMLDOMNodeListPtr attr_filters =
		m_cloned_active_element->selectNodes("filter[@type=\"complex\"]/attribute_filter");

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


int CAElFiltersConfigDialog::GetCurSelFiltersList()
{
	POSITION pos = m_FiltersList.GetFirstSelectedItemPosition();
	if (pos == NULL) return -1;

	return m_FiltersList.GetNextSelectedItem(pos);
}

void CAElFiltersConfigDialog::UpdateResult(void)
{
	if (m_filter_DOM == NULL) return;
	
	//zaloha dat
	MSXML2::IXMLDOMElementPtr values_clone = m_filter_DOM->selectSingleNode("/dialog_data/values")->cloneNode(VARIANT_TRUE);
	


	CAElTransform tr(m_cloned_active_element);
	tr.ApplyAllAttributeFilters(m_filter_DOM);

	CFilterResultImpl::UpdateResult(m_filter_DOM);
	


	//obnova dat
	m_filter_DOM->selectSingleNode("/dialog_data")->replaceChild(values_clone,
		m_filter_DOM->selectSingleNode("/dialog_data/values"));
}

BOOL CAElFiltersConfigDialog::OnSetActive()
{
	UpdateFiltersList();

	InitResultView();
	UpdateResult();
	
	return CPropertyPage::OnSetActive();
}

void CAElFiltersConfigDialog::OnDblclkFiltersList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	ConfigureFilter();
	
	*pResult = 0;
}

void CAElFiltersConfigDialog::AddFilter()
{
	CComplexFilterDialog dlg(m_cloned_active_element, m_filter_DOM);
	dlg.DoModal();

	UpdateFiltersList();
	UpdateResult();
	SetModified();
}

void CAElFiltersConfigDialog::ConfigureFilter()
{
	int nItem = GetCurSelFiltersList();
	if (nItem == -1) return;

	CString q;
	q.Format("filter[@type=\"complex\"]/attribute_filter[%d]", nItem);

	
	CComplexFilterDialog dlg(m_cloned_active_element, m_filter_DOM, m_cloned_active_element->selectSingleNode((LPCTSTR) q));
	if (IDOK == dlg.DoModal())
	{
		UpdateFiltersList();
		UpdateResult();
		SetModified();
	}
}
