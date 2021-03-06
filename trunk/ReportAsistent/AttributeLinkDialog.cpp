// AttributeLinkDialog.cpp : implementation file
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
#include "AttributeLinkDialog.h"
#include "APTransform.h"
#include "CSkeletonDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CAttributeLinkDialog dialog


CAttributeLinkDialog::CAttributeLinkDialog(MSXML2::IXMLDOMElementPtr & edited_element, CWnd* pParent /*=NULL*/)
	: CDialog(CAttributeLinkDialog::IDD, pParent), CAttributeLinkDialogBase(edited_element)
{
	//{{AFX_DATA_INIT(CAttributeLinkDialog)
	m_AttrLink_IdEdit = _T("");
	//}}AFX_DATA_INIT

	//Iva: Initialization of variables of the dialog		
	//Id
	_variant_t varAtr=m_SelXMLElm->getAttribute("id");
	m_OldID=(LPCTSTR) (_bstr_t)  varAtr;
	if (varAtr.vt!=VT_NULL)
		m_AttrLink_IdEdit = m_OldID;

}


void CAttributeLinkDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAttributeLinkDialog)
	DDX_Control(pDX, IDC_STYLES_COMBO, m_StylesCombo);
	DDX_Control(pDX, IDC_ATTRIBUTES_LIST, m_AttributesList);
	DDX_Control(pDX, IDC_TARGET_COMBO, m_TargetCombo);
	DDX_Text(pDX, IDC_ATTRLINK_ID_EDIT, m_AttrLink_IdEdit);
	//}}AFX_DATA_MAP
	DDV_NonDuplicateID(pDX,IDC_ATTRLINK_ID_EDIT, m_AttrLink_IdEdit);
}


BEGIN_MESSAGE_MAP(CAttributeLinkDialog, CDialog)
	//{{AFX_MSG_MAP(CAttributeLinkDialog)
	ON_CBN_SELCHANGE(IDC_TARGET_COMBO, OnSelchangeTargetCombo)
	ON_BN_CLICKED(IDC_REFRESH_BUTTON, OnRefreshButton)
	ON_BN_CLICKED(IDC_STYLES_REFRESH_BUTTON, OnStylesRefreshButton)
	//}}AFX_MSG_MAP
	ON_NOTIFY(LVN_DELETEITEM, IDC_ATTRIBUTES_LIST, OnLvnDeleteitemAttributesList)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAttributeLinkDialog message handlers

BOOL CAttributeLinkDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitBaseDialog(m_AttributesList, m_TargetCombo);

	
	
	FillStylesCombo();


	//vyber style v comboboxu
	_variant_t style = m_SelXMLElm->getAttribute("style");
	if (style.vt != VT_NULL)
	{
		m_StylesCombo.SelectString(-1, (_bstr_t) style);
	}

	CString attr_n = (LPCTSTR) (_bstr_t) m_SelXMLElm->getAttribute("attr_name");

	SelectItemByNameString(attr_n);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CAttributeLinkDialog::OnSelchangeTargetCombo() 
{
	OnRefreshButton();
}

void CAttributeLinkDialog::OnOK() 
{
	CString s;
	
	//Id - saved after the close of the dialog in class CSkeletonDoc

	//target
	
	SaveTarget(m_TargetCombo);
	
	//attr name
	POSITION pos = m_AttributesList.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nItem = m_AttributesList.GetNextSelectedItem(pos);
		s = * (CString*) m_AttributesList.GetItemData(nItem);
	}
	m_SelXMLElm->setAttribute("attr_name", (LPCTSTR) s);

	
	
	//style
	
	//vymaz attribut style z tagu
	if (m_SelXMLElm->attributes->getNamedItem("style") != NULL)
	{
		m_SelXMLElm->attributes->removeNamedItem("style");
	}

	CString style_str;
	m_StylesCombo.GetWindowText(style_str);

	if (style_str.GetLength() != 0)
	{
		MSXML2::IXMLDOMAttributePtr s_atr = m_SelXMLElm->ownerDocument->createAttribute("style");
		s_atr->text = (LPCTSTR) style_str;
		m_SelXMLElm->setAttributeNode(s_atr);
		s_atr.Release();
	}
	
	CDialog::OnOK();
}

void CAttributeLinkDialog::OnRefreshButton() 
{
	
	CString s;
	m_TargetCombo.GetWindowText(s);

	POSITION pos = m_AttributesList.GetFirstSelectedItemPosition();

	 
	if (pos != NULL)
	{
		int nItem = m_AttributesList.GetNextSelectedItem(pos);
		CString name_str = * ((CString *) m_AttributesList.GetItemData(nItem));
		OnRefresh(m_AttributesList, s);
		SelectItemByNameString(name_str);
	}
	else
	{
		OnRefresh(m_AttributesList, s);
	}
}

void CAttributeLinkDialog::OnStylesRefreshButton() 
{
	CWordManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->WordManager;
	m.LoadWordStylesAndTempates();

	FillStylesCombo();	
}

void CAttributeLinkDialog::FillStylesCombo()
{
	CWordManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->WordManager;

	CStringTable & st = m.getWordCharacterStyles();

	CString sel;
	m_StylesCombo.GetWindowText(sel);
	
	//vymaze cele combo
	m_StylesCombo.ResetContent();

	//styl - neuveden
	m_StylesCombo.AddString("");

	for (int a=0; a < st.getCount(); a++)
	{
		m_StylesCombo.AddString(st.getItem(a));
	}

	if (CB_ERR == m_StylesCombo.SelectString(-1, sel))
	{
		CString s;
		m_StylesCombo.GetLBText(0, s);
		m_StylesCombo.SelectString(-1, s);
	}


}

void CAttributeLinkDialog::OnLvnDeleteitemAttributesList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	delete (CString *) pNMLV->lParam;

	*pResult = 0;
}

void CAttributeLinkDialog::DDV_NonDuplicateID(CDataExchange *pDX, int nId, CString csIDEditValue)
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




void CAttributeLinkDialog::SelectItemByNameString(LPCTSTR item_caption)
{
	for (int a=0; a < m_AttributesList.GetItemCount(); a++)
	{
		CString * data = (CString *) m_AttributesList.GetItemData(a);

		if (* data == item_caption)
		{
			m_AttributesList.SetItemState(a, LVIS_SELECTED, LVIS_SELECTED);
		}

	}

}

void CAttributeLinkDialog::SelectItemByString(LPCTSTR item_caption)
{
	//najdi vybranou polozku

	LVFINDINFO info;
	ZeroMemory(& info, sizeof info);

	info.flags = LVFI_STRING;
	info.psz = item_caption;
	int item = m_AttributesList.FindItem(& info);

	//vyber vybranou
	m_AttributesList.SetItemState(item, LVIS_SELECTED, LVIS_SELECTED);
}
