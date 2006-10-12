#include "afxwin.h"
#if !defined(AFX_COMPLEXFILTERDIALOG_H__2CD50BAE_2DA0_4301_AEB9_05756F4ED841__INCLUDED_)
#define AFX_COMPLEXFILTERDIALOG_H__2CD50BAE_2DA0_4301_AEB9_05756F4ED841__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ComplexFilterDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CComplexFilterDialog dialog

class CComplexFilterDialog : public CPropertyPage
{
//	DECLARE_DYNCREATE(CComplexFilterDialog)

// Construction
public:
	CComplexFilterDialog(MSXML2::IXMLDOMElementPtr & active_element, CWnd* pParent = NULL);	// nestandard constructor :-)
	~CComplexFilterDialog();

// Dialog Data
	//{{AFX_DATA(CComplexFilterDialog)
	enum { IDD = IDD_COMPLEX_FILTER_DIALOG };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CComplexFilterDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CComplexFilterDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
private:
	BOOL m_bSourceIsInit;
	CComboBox m_SourcesCombo;
	MSXML2::IXMLDOMElementPtr & m_active_element;

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSelchangeDataSourceCombo();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMPLEXFILTERDIALOG_H__2CD50BAE_2DA0_4301_AEB9_05756F4ED841__INCLUDED_)
