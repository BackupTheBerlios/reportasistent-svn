#if !defined(AFX_ATTRIBUTELINKDIALOG_H__E0B2D1C0_954C_4149_8001_FDFD0B7D3922__INCLUDED_)
#define AFX_ATTRIBUTELINKDIALOG_H__E0B2D1C0_954C_4149_8001_FDFD0B7D3922__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AttributeLinkDialog.h : header file
//

#include "AttributeLinkDialogBase.h"
#include "ListSort.h"	// Added by ClassView

/////////////////////////////////////////////////////////////////////////////
// CAttributeLinkDialog dialog

class CAttributeLinkDialog : public CDialog, CAttributeLinkDialogBase
{
// Construction

public:
	CAttributeLinkDialog(MSXML2::IXMLDOMElementPtr & edited_element, CWnd* pParent = NULL);   // standard constructor



// Dialog Data
	//{{AFX_DATA(CAttributeLinkDialog)
	enum { IDD = IDD_ATTRIBUTE_LINK_DIALOG };
	CComboBox	m_StylesCombo;
	CListCtrl	m_AttributesList;
	CComboBox	m_TargetCombo;
	CString	m_AttrLink_IdEdit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAttributeLinkDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//CListSort m_ListSort_AttrList(m_AttributesList,2);
	void DDV_NonDuplicateID(CDataExchange *pDX, int nId, CString csIDEditValue);
	CString m_OldID;
	void FillStylesCombo();

	// Generated message map functions
	//{{AFX_MSG(CAttributeLinkDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTargetCombo();
	virtual void OnOK();
	afx_msg void OnRefreshButton();
	afx_msg void OnStylesRefreshButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLvnDeleteitemAttributesList(NMHDR *pNMHDR, LRESULT *pResult);
	void SelectItemByNameString(LPCTSTR item_caption);
	void SelectItemByString(LPCTSTR item_caption);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ATTRIBUTELINKDIALOG_H__E0B2D1C0_954C_4149_8001_FDFD0B7D3922__INCLUDED_)
