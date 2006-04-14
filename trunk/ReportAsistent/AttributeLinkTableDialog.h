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
	CAttributeLinkTableDialog(IXMLDOMElementPtr & edited_element, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAttributeLinkTableDialog)
	enum { IDD = IDD_ATTRIBUTE_LINK_TABLE_DIALOG };
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
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ATTRIBUTELINKTABLEDIALOG_H__00DFFA22_E7F7_4DF7_9BC2_43DC491F82F6__INCLUDED_)
