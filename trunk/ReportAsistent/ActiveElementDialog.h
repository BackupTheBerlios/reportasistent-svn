#if !defined(AFX_ACTIVEELEMENTDIALOG_H__B6C94842_01BD_40CE_A47F_0949AE4BBB56__INCLUDED_)
#define AFX_ACTIVEELEMENTDIALOG_H__B6C94842_01BD_40CE_A47F_0949AE4BBB56__INCLUDED_

#include "TransformationsDialog.h"	// Added by ClassView
#include "SimpleFilterDialog.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ActiveElementDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CActiveElementDialog dialog

class CActiveElementDialog : public CDialog
{
// Construction
public:
	CActiveElementDialog(MSXML2::IXMLDOMElementPtr & active_element, CWnd* pParent = NULL);   // standard constructor
private:
	BOOL m_bApplyPerformed;


// Dialog Data
	//{{AFX_DATA(CActiveElementDialog)
	enum { IDD = IDD_ACTIVE_ELEMENT_DIALOG };
	CTabCtrl	m_TabControl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CActiveElementDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CSimpleFilterDialog m_SimpleFilterDialog;
	CTransformationsDialog m_TransformationsDialog;

	// Generated message map functions
	//{{AFX_MSG(CActiveElementDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTabControl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSwitchButton();
	afx_msg void OnApplyButton();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACTIVEELEMENTDIALOG_H__B6C94842_01BD_40CE_A47F_0949AE4BBB56__INCLUDED_)
