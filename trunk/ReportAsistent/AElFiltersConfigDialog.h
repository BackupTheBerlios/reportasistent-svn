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

class CAElFiltersConfigDialog : public CPropertyPage, CFilterResultImpl
{
// Construction
public:
//	CAElFiltersConfigDialog(CWnd* pParent = NULL);   // standard constructor
	CAElFiltersConfigDialog(MSXML2::IXMLDOMElementPtr & active_element, MSXML2::IXMLDOMElementPtr & cloned_element, CWnd* pParent = NULL);	// nestandard constructor :-)

// Dialog Data
	//{{AFX_DATA(CAElFiltersConfigDialog)
	enum { IDD = IDD_FILTER_AND_CONFIG_DIALOG };
	CString	m_CF_IdEdit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAElFiltersConfigDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL


private:
	int GetCurSelFiltersList();
	BOOL LoadSource(public_source_id_t sId);
	MSXML2::IXMLDOMElementPtr & m_active_element;
	MSXML2::IXMLDOMElementPtr & m_cloned_active_element;
   	MSXML2::IXMLDOMElementPtr m_filter_DOM;	//plugin output

	BOOL m_bSourceIsInit;


// Implementation
protected:
	void DDV_NonDuplicateID(CDataExchange *pDX, int nId, CString csIDEditValue);
	// Generated message map functions
	//{{AFX_MSG(CAElFiltersConfigDialog)
	afx_msg void OnRemoveFilterButton();
	afx_msg void OnMoveUpButton();
	afx_msg void OnMoveDownButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_SourcesCombo;
protected:
	CString m_OldID;
//	virtual void PreInitDialog();
public:
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnBnClickedAddFilterButton();
public:
	MSXML2::IXMLDOMElementPtr & getActiveElement(void);
public:
	MSXML2::IXMLDOMElementPtr & getClonedActiveElement(void);
public:
	virtual BOOL OnApply();
public:
	virtual void OnOK();
	CListCtrl m_FiltersList;
	void UpdateFiltersList(void);
public:
	afx_msg void OnCbnSelchangeDataSourceCombo();
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
public:
	afx_msg void OnBnClickedConfigureFilterButton();
protected:
	void UpdateResult(void);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AELFILTERSCONFIGDIALOG_H__BB057B90_DBD8_44C4_9138_DB1659AA5D98__INCLUDED_)
