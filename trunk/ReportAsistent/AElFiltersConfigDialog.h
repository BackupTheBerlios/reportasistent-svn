#include "afxwin.h"
#include "afxcmn.h"
#if !defined(AFX_AELFILTERSCONFIGDIALOG_H__BB057B90_DBD8_44C4_9138_DB1659AA5D98__INCLUDED_)
#define AFX_AELFILTERSCONFIGDIALOG_H__BB057B90_DBD8_44C4_9138_DB1659AA5D98__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AElFiltersConfigDialog.h : header file
//

#include "complexfilterdialog.h"

/////////////////////////////////////////////////////////////////////////////
// CAElFiltersConfigDialog dialog

class CAElFiltersConfigDialog : public CPropertyPage, CFilterResultImpl, CAElDataShare
{
// Construction
public:
	CAElFiltersConfigDialog(CAElDataShare & data_share, CWnd* pParent = NULL);	// nestandard constructor :-)

// Dialog Data
	//{{AFX_DATA(CAElFiltersConfigDialog)
	enum { IDD = IDD_FILTER_AND_CONFIG_DIALOG };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAElFiltersConfigDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL


private:
	int GetCurSelFiltersList();

	CListCtrl m_FiltersList;

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CAElFiltersConfigDialog)
	afx_msg void OnRemoveFilterButton();
	afx_msg void OnMoveUpButton();
	afx_msg void OnMoveDownButton();
	afx_msg void OnBnClickedAddFilterButton();
	afx_msg void OnBnClickedConfigureFilterButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnInitDialog();
	virtual BOOL OnApply();
	virtual void OnOK();

	void UpdateFiltersList(void);
	void UpdateResult(void);

public:
	MSXML2::IXMLDOMElementPtr & getActiveElement(void);
	MSXML2::IXMLDOMElementPtr & getClonedActiveElement(void);
public:
	virtual BOOL OnSetActive();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AELFILTERSCONFIGDIALOG_H__BB057B90_DBD8_44C4_9138_DB1659AA5D98__INCLUDED_)
