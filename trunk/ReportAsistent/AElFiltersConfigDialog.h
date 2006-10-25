#if !defined(AFX_AELFILTERSCONFIGDIALOG_H__BB057B90_DBD8_44C4_9138_DB1659AA5D98__INCLUDED_)
#define AFX_AELFILTERSCONFIGDIALOG_H__BB057B90_DBD8_44C4_9138_DB1659AA5D98__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AElFiltersConfigDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAElFiltersConfigDialog dialog

class CAElFiltersConfigDialog : public CPropertyPage
{
// Construction
public:
//	CAElFiltersConfigDialog(CWnd* pParent = NULL);   // standard constructor
	CAElFiltersConfigDialog(MSXML2::IXMLDOMElementPtr & active_element, CWnd* pParent = NULL);	// nestandard constructor :-)

// Dialog Data
	//{{AFX_DATA(CAElFiltersConfigDialog)
	enum { IDD = IDD_FILTER_AND_CONFIG_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAElFiltersConfigDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL


private:
	MSXML2::IXMLDOMElementPtr & m_active_element;

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAElFiltersConfigDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AELFILTERSCONFIGDIALOG_H__BB057B90_DBD8_44C4_9138_DB1659AA5D98__INCLUDED_)
