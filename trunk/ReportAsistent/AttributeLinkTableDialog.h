#if !defined(AFX_ATTRIBUTELINKTABLEDIALOG_H__00DFFA22_E7F7_4DF7_9BC2_43DC491F82F6__INCLUDED_)
#define AFX_ATTRIBUTELINKTABLEDIALOG_H__00DFFA22_E7F7_4DF7_9BC2_43DC491F82F6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AttributeLinkTableDialog.h : header file
//

#include "AttributeLinkDialogBase.h"

/////////////////////////////////////////////////////////////////////////////
// CAttributeLinkTableDialog dialog

class CAttributeLinkTableDialog : public CDialog, CAttributeLinkDialogBase
{
// Construction
public:
	CAttributeLinkTableDialog(IXMLDOMElementPtr & edited_element, CWnd* pParent = NULL, BOOL show_target = TRUE);   // standard constructor
	//show_target - mase zobrazovat combo box s target elementem? - kvuli attr_link_table uvnitr active_element

// Dialog Data
	//{{AFX_DATA(CAttributeLinkTableDialog)
	enum { IDD = IDD_ATTRIBUTE_LINK_TABLE_DIALOG };
	CListCtrl	m_CaptionsList;
	CComboBox	m_TargetCombo;
	CListCtrl	m_AttributesList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAttributeLinkTableDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

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
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bShowTarget;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ATTRIBUTELINKTABLEDIALOG_H__00DFFA22_E7F7_4DF7_9BC2_43DC491F82F6__INCLUDED_)
