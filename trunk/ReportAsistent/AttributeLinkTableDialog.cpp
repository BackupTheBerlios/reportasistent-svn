// AttributeLinkTableDialog.cpp : implementation file
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
#include "AttributeLinkTableDialog.h"
#include "CSkeletonDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAttributeLinkTableDialog dialog


CAttributeLinkTableDialog::CAttributeLinkTableDialog(MSXML2::IXMLDOMElementPtr & edited_element, CWnd* pParent, BOOL show_target)
	: CDialog(CAttributeLinkTableDialog::IDD, pParent), CAttributeLinkDialogBase(edited_element),
	m_bShowTarget(show_target)
{
	ASSERT(edited_element != NULL);
	
	//{{AFX_DATA_INIT(CAttributeLinkTableDialog)
	m_AttrLinkTable_IdEdit = _T("");
	//}}AFX_DATA_INIT

	//Iva: Initialisation of variables of the dialog		
	//Id
	_variant_t varAtr=m_SelXMLElm->getAttribute("id");
	m_OldID=(LPCTSTR) (_bstr_t)  varAtr;
	if (varAtr.vt!=VT_NULL)
		m_AttrLinkTable_IdEdit = m_OldID;
}


void CAttributeLinkTableDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAttributeLinkTableDialog)
	DDX_Control(pDX, IDC_STYLE_COMBO, m_StyleCombo);
	DDX_Control(pDX, IDC_CAPTIONS_LIST, m_CaptionsList);
	DDX_Control(pDX, IDC_TARGET_COMBO, m_TargetCombo);
	DDX_Control(pDX, IDC_ATTRIBUTES_LIST, m_AttributesList);
	DDX_Text(pDX, IDC_ATTRLINKTABLE_ID_EDIT, m_AttrLinkTable_IdEdit);
	DDV_MaxChars(pDX, m_AttrLinkTable_IdEdit, 50);
	//}}AFX_DATA_MAP
	DDV_NonDuplicateID(pDX,IDC_ATTRLINKTABLE_ID_EDIT, m_AttrLinkTable_IdEdit);
}


BEGIN_MESSAGE_MAP(CAttributeLinkTableDialog, CDialog)
	//{{AFX_MSG_MAP(CAttributeLinkTableDialog)
	ON_CBN_SELCHANGE(IDC_TARGET_COMBO, OnSelchangeTargetCombo)
	ON_BN_CLICKED(IDC_REFRESH_BUTTON, OnRefreshButton)
	ON_BN_CLICKED(IDC_ADD_BUTTON, OnAddButton)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_CAPTIONS_LIST, OnEndlabeleditCaptionsList)
	ON_BN_CLICKED(IDC_REMOVE_BUTTON, OnRemoveButton)
	ON_BN_CLICKED(IDC_EDIT_CAPTION_BUTTON, OnEditCaptionButton)
	ON_BN_CLICKED(IDC_MOVE_UP_BUTTON, OnMoveUpButton)
	ON_BN_CLICKED(IDC_MOVE_DOWN_BUTTON2, OnMoveDownButton)
	ON_NOTIFY(NM_DBLCLK, IDC_ATTRIBUTES_LIST, OnDblclkAttributesList)
	//}}AFX_MSG_MAP
	ON_NOTIFY(LVN_DELETEITEM, IDC_ATTRIBUTES_LIST, OnLvnDeleteitemAttributesList)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAttributeLinkTableDialog message handlers

#define CAPTLIST_CL_CAPTION		0
#define CAPTLIST_CL_VALUE		1
#define CAPTLIST_CL_NAME		2

BOOL CAttributeLinkTableDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	if (! m_bShowTarget) m_TargetCombo.EnableWindow(FALSE);
	
	InitBaseDialog(m_AttributesList, m_TargetCombo);


	//dedek: inicializuj CaptionsList
	CRect r;
	m_CaptionsList.GetWindowRect(& r);
	m_CaptionsList.InsertColumn(CAPTLIST_CL_CAPTION, "caption", LVCFMT_LEFT, r.Width()/3 -3);
	m_CaptionsList.InsertColumn(CAPTLIST_CL_VALUE, "value", LVCFMT_LEFT, r.Width()/3 -3);
	m_CaptionsList.InsertColumn(CAPTLIST_CL_NAME, "name", LVCFMT_LEFT, r.Width()/3 -3);


	//napln CaptionsList hodnotami
	m_CaptionsList.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	MSXML2::IXMLDOMNodeListPtr links = m_SelXMLElm->selectNodes("link");

	CString target_id;
	m_TargetCombo.GetWindowText(target_id);

	int a;
	for (a=0; a < links->length; a++)
	{
		MSXML2::IXMLDOMElementPtr link = links->item[a];

		//caption
		int item = m_CaptionsList.InsertItem(a, (_bstr_t) link->getAttribute("caption"));
		
		//attr_name
		CString attr_name = (LPCTSTR) (_bstr_t) link->getAttribute("attr_name");
		m_CaptionsList.SetItemText(item, CAPTLIST_CL_NAME, attr_name);

		//value
		CString query_str;
		query_str.Format("id(\"%s\")/attributes/element_attributes/attribute[@name=\"%s\"]/@value", target_id, attr_name);

		MSXML2::IXMLDOMNodePtr value_attr = m_SelXMLElm->ownerDocument->selectSingleNode((LPCTSTR) query_str);

		if (value_attr != NULL)
		{
			m_CaptionsList.SetItemText(item, CAPTLIST_CL_VALUE, value_attr->text);
			value_attr.Release();
		}

		
		link.Release();
	}


	//napln style combo

	CElementManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;
	int item = CB_ERR;
	for (a=0; a < m.getAttrLinkTableStylesCount(); a++)
	{
		item = m_StyleCombo.AddString(m.getAttrLinkTableStyleName(a));
	}

	//vyber style
	int sel = m_StyleCombo.SelectString(-1, (_bstr_t) m_SelXMLElm->getAttribute("style"));
	//vyber se nezdaril => kdyz exituje nejaky styl vyber prvni
	if ((sel == CB_ERR) && (item != CB_ERR))
	{
		m_StyleCombo.SelectString(-1, m.getAttrLinkTableStyleName(0));
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAttributeLinkTableDialog::OnSelchangeTargetCombo() 
{
	CString target_id;
	m_TargetCombo.GetWindowText(target_id);
	FillAttributesList(m_AttributesList, target_id);

	m_CaptionsList.DeleteAllItems();
}

void CAttributeLinkTableDialog::OnRefreshButton() 
{
	CString target_id;
	m_TargetCombo.GetWindowText(target_id);

	OnRefresh(m_AttributesList, target_id);


	//refresh pro captions list

	for (int a=0; a < m_CaptionsList.GetItemCount(); a++)
	{
		CString attr_name = m_CaptionsList.GetItemText(a, CAPTLIST_CL_NAME);
		
		CString query_str;
		query_str.Format("id(\"%s\")/attributes/element_attributes/attribute[@name=\"%s\"]/@value", target_id, attr_name);


		MSXML2::IXMLDOMNodePtr attr_value = m_SelXMLElm->ownerDocument->selectSingleNode((LPCTSTR) query_str);

		if (attr_value != NULL)
		{
			m_CaptionsList.SetItemText(a, CAPTLIST_CL_VALUE, attr_value->text);

			attr_value.Release();

		}

	}
		
}

void CAttributeLinkTableDialog::OnAddButton() 
{
	int selected_item;
	//najdi vybranou polozku v attribues listu
	POSITION pos = m_AttributesList.GetFirstSelectedItemPosition();
	while (pos != NULL) 
	{
		selected_item = m_AttributesList.GetNextSelectedItem(pos);
		if (!AddAttribute(selected_item)) return;
	}
	

}

void CAttributeLinkTableDialog::OnEndlabeleditCaptionsList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;

	*pResult = FALSE;

	if (pDispInfo->item.pszText != NULL)
	{		
		*pResult = TRUE;	
	}
}

void CAttributeLinkTableDialog::OnRemoveButton() 
{
	int selected_item[MAX_CHOSEN_ATTRIBUTES_COUNT];
	int I=0;
	POSITION pos = m_CaptionsList.GetFirstSelectedItemPosition();
	while (pos != NULL ) 
	{
		selected_item[I] = m_CaptionsList.GetNextSelectedItem(pos);
		I++;
	}
	while (I>=0)
	{
		RemoveAttribute(selected_item[I]);
		I--;
	}
	
}

void CAttributeLinkTableDialog::OnEditCaptionButton() 
{
	POSITION pos = m_CaptionsList.GetFirstSelectedItemPosition();
	if (pos == NULL) return;
	int nItem = m_CaptionsList.GetNextSelectedItem(pos);

	//edituj caption
	m_CaptionsList.SetFocus();
	m_CaptionsList.EditLabel(nItem);		
}

void CAttributeLinkTableDialog::OnMoveUpButton() 
{
	POSITION pos = m_CaptionsList.GetFirstSelectedItemPosition();
	if (pos == NULL) return;
	int nItem = m_CaptionsList.GetNextSelectedItem(pos);

	if (nItem <= 0) return;


	CString name = m_CaptionsList.GetItemText(nItem, CAPTLIST_CL_NAME);
	CString value = m_CaptionsList.GetItemText(nItem, CAPTLIST_CL_VALUE);
	CString caption = m_CaptionsList.GetItemText(nItem, CAPTLIST_CL_CAPTION);

		
	m_CaptionsList.DeleteItem(nItem);

	nItem = m_CaptionsList.InsertItem(--nItem, caption);
	m_CaptionsList.SetItemText(nItem, CAPTLIST_CL_NAME, name);
	m_CaptionsList.SetItemText(nItem, CAPTLIST_CL_VALUE, value);

	m_CaptionsList.SetItemState(nItem, LVIS_SELECTED, LVIS_SELECTED);
}

void CAttributeLinkTableDialog::OnMoveDownButton() 
{
	POSITION pos = m_CaptionsList.GetFirstSelectedItemPosition();
	if (pos == NULL) return;
	int nItem = m_CaptionsList.GetNextSelectedItem(pos);

	if (nItem >= m_CaptionsList.GetItemCount()) return;


	CString name = m_CaptionsList.GetItemText(nItem, CAPTLIST_CL_NAME);
	CString value = m_CaptionsList.GetItemText(nItem, CAPTLIST_CL_VALUE);
	CString caption = m_CaptionsList.GetItemText(nItem, CAPTLIST_CL_CAPTION);

		
	m_CaptionsList.DeleteItem(nItem);

	nItem = m_CaptionsList.InsertItem(++nItem, caption);
	m_CaptionsList.SetItemText(nItem, CAPTLIST_CL_NAME, name);
	m_CaptionsList.SetItemText(nItem, CAPTLIST_CL_VALUE, value);

	m_CaptionsList.SetItemState(nItem, LVIS_SELECTED, LVIS_SELECTED);
	
}

void CAttributeLinkTableDialog::OnOK() 
{

	SaveTarget(m_TargetCombo);

	//smaz vsecky link elementy
	MSXML2::IXMLDOMSelectionPtr sel = m_SelXMLElm->selectNodes("link");
	sel->removeAll();
	sel.Release();

	//vytvor vzorovy element
	MSXML2::IXMLDOMElementPtr link_elenet = m_SelXMLElm->ownerDocument->createElement("link");
	link_elenet->setAttributeNode(m_SelXMLElm->ownerDocument->createAttribute("attr_name"));
	link_elenet->setAttributeNode(m_SelXMLElm->ownerDocument->createAttribute("caption"));

	//pridej elementy podle listu
	for (int a=0; a < m_CaptionsList.GetItemCount(); a++)
	{
		link_elenet->setAttribute("attr_name", (LPCTSTR) m_CaptionsList.GetItemText(a, CAPTLIST_CL_NAME));
		link_elenet->setAttribute("caption", (LPCTSTR) m_CaptionsList.GetItemText(a, CAPTLIST_CL_CAPTION));

		m_SelXMLElm->appendChild(link_elenet->cloneNode(VARIANT_FALSE));
	}

	link_elenet.Release();

	//uloz style
	CString style_str;
	m_StyleCombo.GetWindowText(style_str);
	m_SelXMLElm->setAttribute("style", (LPCTSTR) style_str);
	
	CDialog::OnOK();
}

void CAttributeLinkTableDialog::OnLvnDeleteitemAttributesList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	delete (CString *) pNMLV->lParam;

	*pResult = 0;
}

void CAttributeLinkTableDialog::DDV_NonDuplicateID(CDataExchange *pDX, int nId, CString csIDEditValue)
{
	if (0!=pDX->m_bSaveAndValidate) //Iva: if it's end of dialog, not beginning
	{

		if (""==csIDEditValue) //Iva: ID can't be empty string
		{
			SetDlgItemText(nId, m_OldID );
			CReportAsistentApp::ReportError(IDS_INVALID_ELEMENT_ID);
			pDX->Fail();
		}

		CSkeletonDoc * Doc = ((CReportAsistentApp *) AfxGetApp())->FirstDocumentInFirstTemplate();
		if (m_OldID!=csIDEditValue)  //Iva: if "==", then ID is in tree, but it's OK
		{
			if (Doc->IsIDInTree(csIDEditValue))
			{
				SetDlgItemText(nId, m_OldID ); //Iva: return old value to edit box
				CReportAsistentApp::ReportError(IDS_DUPLICATE_ELEMENT_ID);
				pDX->Fail();
			}
			else
			{
				//Iva: I try to set ID to new value
				try
				{
					m_SelXMLElm->setAttribute("id", (LPCTSTR)csIDEditValue); 
				}
				catch(_com_error &e)
				{
					SetDlgItemText(nId, m_OldID ); //Iva: return old value to edit box
					m_SelXMLElm->setAttribute("id", (LPCTSTR)m_OldID);
					CReportAsistentApp::ReportError(IDS_INVALID_ELEMENT_ID,e.Description() );
					pDX->Fail();
				}
				m_SelXMLElm->setAttribute("id", (LPCTSTR)m_OldID); 

			}
		}
	}
}

BOOL CAttributeLinkTableDialog::AddAttribute(int selected_item)
{

	CString Pom;
	if (m_CaptionsList.GetItemCount() >= MAX_CHOSEN_ATTRIBUTES_COUNT)
	{
		Pom.Format("%d", MAX_CHOSEN_ATTRIBUTES_COUNT);
		CReportAsistentApp::ReportError(IDS_TOO_MANY_SELECTED_ITEMS, Pom);
		return FALSE;
	}

	CString label = m_AttributesList.GetItemText(selected_item, ATTRLIST_CL_NAME);
	CString value = m_AttributesList.GetItemText(selected_item, ATTRLIST_CL_VALUE);
	CString name = * (CString*) m_AttributesList.GetItemData(selected_item);


	//vloz polozku na konec captions listu
	int item = m_CaptionsList.InsertItem(m_CaptionsList.GetItemCount(), label);
	m_CaptionsList.SetItemText(item, CAPTLIST_CL_NAME, name);
	m_CaptionsList.SetItemText(item, CAPTLIST_CL_VALUE, value);

	//edituj caption
	m_CaptionsList.SetFocus();
	m_CaptionsList.EditLabel(item);	

	return TRUE;
}

void CAttributeLinkTableDialog::RemoveAttribute(int selected_item)
{
	m_CaptionsList.DeleteItem(selected_item);
}



void CAttributeLinkTableDialog::OnDblclkAttributesList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	POSITION pos = m_AttributesList.GetFirstSelectedItemPosition();
	if (pos != NULL) 
	{
		int selected_item = m_AttributesList.GetNextSelectedItem(pos);
		AddAttribute(selected_item);
	}
		
	*pResult = 0;
}
