#if !defined(AFX_TRANSFORMATIONSDIALOG_H__BE8C8E40_78CC_4E3F_9047_DD5A7E3900BB__INCLUDED_)
#define AFX_TRANSFORMATIONSDIALOG_H__BE8C8E40_78CC_4E3F_9047_DD5A7E3900BB__INCLUDED_

#include "SimpleFilterDialog.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TransformationsDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTransformationsDialog dialog

class CTransformationsDialog : public CDialog
{
// Construction
public:
	BOOL SaveAll();
	CTransformationsDialog(MSXML2::IXMLDOMElementPtr & active_element, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTransformationsDialog)
	enum { IDD = IDD_TRANSFORMATIONS_DIALOG };
	CListBox	m_SupportedList;
	CListBox	m_SelectedList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransformationsDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void CheckAndRepareAttrLinkTable();

	// Generated message map functions
	//{{AFX_MSG(CTransformationsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnAddButton();
	afx_msg void OnRemoveButton();
	afx_msg void OnMoveUpButton();
	afx_msg void OnMoveDownButton();
	afx_msg void ConfigureAttrLinkTable();
	afx_msg void OnAddAttrLinkTableButton();
	afx_msg void OnConfigureButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	MSXML2::IXMLDOMElementPtr & m_active_element;
	MSXML2::IXMLDOMElementPtr m_cloned_element;
	//zmeny se provadeji v klonu, pokud uzivatel zmacken OK, puvodni element (m_active_element) se nahradi klonem
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSFORMATIONSDIALOG_H__BE8C8E40_78CC_4E3F_9047_DD5A7E3900BB__INCLUDED_)
