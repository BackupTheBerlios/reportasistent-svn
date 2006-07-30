// AttributeLinkDialogBase.cpp: implementation of the CAttributeLinkDialogBase class.
//
//////////////////////////////////////////////////////////////////////

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
	:m_edited_element(edited_element)
{
	ASSERT(edited_element != NULL);
}

void CAttributeLinkDialogBase::InitBaseDialog(CListCtrl & AttributesList, CComboBox & TargetCombo)
{
	ASSERT(m_edited_element != NULL);

	FillTargets(TargetCombo);
	if (CB_ERR == TargetCombo.SelectString(-1, (_bstr_t) m_edited_element->getAttribute("target")))
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

}


void CAttributeLinkDialogBase::FillTargets(CComboBox & TargetCombo)
{

	MSXML2::IXMLDOMNodeListPtr el_list = m_edited_element->ownerDocument->selectNodes("//active_element/@id");
//	MSXML2::IXMLDOMNodeListPtr el_list = m_edited_element->selectNodes("//active_element/@id");

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
	
	MSXML2::IXMLDOMElementPtr el = m_edited_element->ownerDocument->selectSingleNode((LPCTSTR) query);

	
	if (el == NULL) return;



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
		// kody
	for (int i=0; i<AttributesList.GetItemCount(); i++)
	{
		if (AttributesList.GetItemData(i) != NULL)
			delete (CString*) AttributesList.GetItemData(i);
	}
		//  /kody
	AttributesList.DeleteAllItems();
	
	CString query;
	query.Format("id(\"%s\")/attributes/element_attributes/attribute", target_id);

	MSXML2::IXMLDOMSelectionPtr sel = (MSXML2::IXMLDOMSelectionPtr) m_edited_element->ownerDocument->selectNodes((LPCTSTR) query);

	for (int a=0; a < sel->length; a++)
	{
		MSXML2::IXMLDOMElementPtr el = sel->item[a];

		// kody - pokus

		
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
		*pName = (CString) (BSTR) (_bstr_t) el->getAttribute("name");

		// /kody - smaz

		//int item = AttributesList.InsertItem(a, (_bstr_t) el->getAttribute("name"));
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
	m_edited_element->setAttribute("target", (LPCTSTR) s);
}
