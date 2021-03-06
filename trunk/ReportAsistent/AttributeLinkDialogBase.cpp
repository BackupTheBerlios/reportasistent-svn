// AttributeLinkDialogBase.cpp: implementation of the CAttributeLinkDialogBase class.
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
#include "AttributeLinkDialogBase.h"
#include "APTransform.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CAttributeLinkDialogBase::CAttributeLinkDialogBase(MSXML2::IXMLDOMElementPtr & edited_element)
	:m_SelXMLElm(edited_element)
{
	ASSERT(edited_element != NULL);
}

void CAttributeLinkDialogBase::InitBaseDialog(CListCtrl & AttributesList, CComboBox & TargetCombo)
{
	ASSERT(m_SelXMLElm != NULL);
	
	AttributesList.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	FillTargets(TargetCombo);
	if (CB_ERR == TargetCombo.SelectString(-1, (_bstr_t) m_SelXMLElm->getAttribute("target")))
	{
		if (TargetCombo.GetCount() > 0)
		{		
			CString s;
			TargetCombo.GetLBText(0, s);
			TargetCombo.SelectString(-1, s);
		}
	}

	InitAttributesList(AttributesList);

	CString target_id;
	TargetCombo.GetWindowText(target_id);
	FillAttributesList(AttributesList, target_id);

	OnRefresh(AttributesList, target_id);
}


void CAttributeLinkDialogBase::FillTargets(CComboBox & TargetCombo)
{

	MSXML2::IXMLDOMNodeListPtr el_list = m_SelXMLElm->ownerDocument->selectNodes("//active_element/@id");

	for (int a=0; a < el_list->length; a++)
	{
		TargetCombo.AddString(el_list->item[a]->text);
	}

	el_list.Release();
}

void CAttributeLinkDialogBase::InitAttributesList(CListCtrl & AttributesList)
{
	CRect r;
	AttributesList.GetWindowRect(& r);
	AttributesList.InsertColumn(ATTRLIST_CL_NAME, "name", LVCFMT_LEFT, r.Width()/2);
	AttributesList.InsertColumn(ATTRLIST_CL_VALUE, "value", LVCFMT_LEFT, r.Width()/2 -20);
}

void CAttributeLinkDialogBase::OnRefresh(CListCtrl & AttributesList, LPCTSTR target_id)
{
	CString query;
	query.Format("id(\"%s\")", target_id);
	
	MSXML2::IXMLDOMElementPtr el = m_SelXMLElm->ownerDocument->selectSingleNode((LPCTSTR) query);

	
	if (el == NULL)
	{
		return;
	}


	CAElTransform tr(el);

	if (! tr.FillElementAttributes(0))
	{
		CReportAsistentApp::ReportError(IDS_REFRESH_EL_ATTRIBUTES_FAILED);
	}
	
	el.Release();

	FillAttributesList(AttributesList, target_id);
}

void CAttributeLinkDialogBase::FillAttributesList(CListCtrl & AttributesList, LPCTSTR target_id)
{
	// smazani puvodniho obsahu
	AttributesList.DeleteAllItems();
	
	CString query;
	query.Format("id(\"%s\")/attributes/element_attributes/attribute", target_id);

	MSXML2::IXMLDOMSelectionPtr sel = (MSXML2::IXMLDOMSelectionPtr) m_SelXMLElm->ownerDocument->selectNodes((LPCTSTR) query);

	for (int a=0; a < sel->length; a++)
	{
		MSXML2::IXMLDOMElementPtr el = sel->item[a];

		 _bstr_t Label;  // pokud je v XML definovan atribut "label", bude mit jeho hodnotu. jinak bude hodnota atributu "name"

		
		try 
		{ 
			Label = (_bstr_t) el->getAttribute("label");
		}
		catch(...) 
		{
			Label = (_bstr_t) el->getAttribute("name");
		}
		
		// atribut "name" uchovan do ItemData polozky
		CString* pName = new CString();
		*pName =  (LPCTSTR) (_bstr_t) el->getAttribute("name");

		int item = AttributesList.InsertItem(a, Label);  

		AttributesList.SetItemText(item, ATTRLIST_CL_VALUE, (_bstr_t) el->getAttribute("value"));

		AttributesList.SetItemData(item, (DWORD) pName);

		el.Release();
	}
	sel.Release();
}



void CAttributeLinkDialogBase::SaveTarget(CComboBox &target_combo)
{
	CString s;
	
	target_combo.GetWindowText(s);
	m_SelXMLElm->setAttribute("target", (LPCTSTR) s);
}
