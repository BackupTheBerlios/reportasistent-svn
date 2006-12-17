#if !defined(AFX_ATTRIBUTELINKTABLEDIALOG_H__00DFFA22_E7F7_4DF7_9BC2_43DC491F82F6__INCLUDED_)
#define AFX_ATTRIBUTELINKTABLEDIALOG_H__00DFFA22_E7F7_4DF7_9BC2_43DC491F82F6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AttributeLinkTableDialog.h : header file
//
/*
This file is part of LM Report Asistent.

Authors: Jan Dedek, Jan Kodym, Martin Chrz, Iva Bartunkova

LM Report Asistent is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

LM Report Asistent is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with LM Report Asistent; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include "AttributeLinkDialogBase.h"
#if!defined MAX_CHOSEN_ATTRIBUTES_COUNT
#define MAX_CHOSEN_ATTRIBUTES_COUNT 50
#endif

/////////////////////////////////////////////////////////////////////////////
// CAttributeLinkTableDialog dialog

/**
 * class CAttributeLinkTableDialog:
 *
 * @author 
 */
class CAttributeLinkTableDialog : public CDialog, CAttributeLinkDialogBase
{
// Construction
public:
	CAttributeLinkTableDialog(MSXML2::IXMLDOMElementPtr & edited_element, CWnd* pParent = NULL, BOOL show_target = TRUE);   // standard constructor
	//show_target - mase zobrazovat combo box s target elementem? - kvuli attr_link_table uvnitr active_element

// Dialog Data
	//{{AFX_DATA(CAttributeLinkTableDialog)
	enum { IDD = IDD_ATTRIBUTE_LINK_TABLE_DIALOG };
	CComboBox	m_StyleCombo;
	CListCtrl	m_CaptionsList;
	CComboBox	m_TargetCombo;
	CListCtrl	m_AttributesList;
	CString	m_AttrLinkTable_IdEdit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAttributeLinkTableDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void RemoveAttribute(int selected_item);
	BOOL AddAttribute(int selected_item);
	void DDV_NonDuplicateID(CDataExchange *pDX, int nId, CString csIDEditValue);
	CString m_OldID;

	// Generated message map functions
	//{{AFX_MSG(CAttributeLinkTableDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTargetCombo();
	afx_msg void OnRefreshButton();
	afx_msg void OnAddButton();
	afx_msg void OnEndlabeleditCaptionsList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRemoveButton();
	afx_msg void OnEditCaptionButton();
	afx_msg void OnMoveUpButton();
	afx_msg void OnMoveDownButton();
	virtual void OnOK();
	afx_msg void OnDblclkAttributesList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bShowTarget;
	afx_msg void OnLvnDeleteitemAttributesList(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnLvnItemchangedAttributesList(NMHDR *pNMHDR, LRESULT *pResult);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ATTRIBUTELINKTABLEDIALOG_H__00DFFA22_E7F7_4DF7_9BC2_43DC491F82F6__INCLUDED_)
