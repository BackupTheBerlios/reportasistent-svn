#if !defined(AFX_ATTRIBUTELINKDIALOG_H__E0B2D1C0_954C_4149_8001_FDFD0B7D3922__INCLUDED_)
#define AFX_ATTRIBUTELINKDIALOG_H__E0B2D1C0_954C_4149_8001_FDFD0B7D3922__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AttributeLinkDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAttributeLinkDialog dialog

class CAttributeLinkDialog : public CDialog
{
// Construction
private:
	IXMLDOMElementPtr & m_edited_element;

public:
	CAttributeLinkDialog(IXMLDOMElementPtr & edited_element, CWnd* pParent = NULL);   // standard constructor



// Dialog Data
	//{{AFX_DATA(CAttributeLinkDialog)
	enum { IDD = IDD_ATTRIBUTE_LINK_DIALOG };
	CListCtrl	m_AttributesList;
	CComboBox	m_TargetCombo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAttributeLinkDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void FillAttributesList();
	void InitAttributesList();
	void FillTargets();

	// Generated message map functions
	//{{AFX_MSG(CAttributeLinkDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTargetCombo();
	virtual void OnOK();
	afx_msg void OnRefreshButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ATTRIBUTELINKDIALOG_H__E0B2D1C0_954C_4149_8001_FDFD0B7D3922__INCLUDED_)
