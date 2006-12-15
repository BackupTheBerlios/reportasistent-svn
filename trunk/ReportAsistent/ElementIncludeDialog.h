#if !defined(AFX_ELEMENTINCLUDEDIALOG_H__37077C14_C7B6_4A14_8B7B_7F877CA2C478__INCLUDED_)
#define AFX_ELEMENTINCLUDEDIALOG_H__37077C14_C7B6_4A14_8B7B_7F877CA2C478__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ElementIncludeDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CElementIncludeDialog dialog

/**
 * class CElementIncludeDialog:
 *
 * @author 
 */
class CElementIncludeDialog : public CDialog
{
// Construction
public:
	MSXML2::IXMLDOMElementPtr m_SelXMLElm;
	CElementIncludeDialog(MSXML2::IXMLDOMElementPtr & SelXMLElm,CWnd* pParent = NULL);   // standard constructor
	void DDV_NonDuplicateID(CDataExchange *pDX, int nId, CString csIDEditValue);

// Dialog Data
	//{{AFX_DATA(CElementIncludeDialog)
	enum { IDD = IDD_INCLUDE_DIALOG };
	CString	m_Include_IdEdit;
	CString	m_IncludeFileName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CElementIncludeDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	void static DDV_ValidFileName(CDataExchange *pDX, int nIdc, CString csFileName, CString csOldFileName);
protected:
	CString m_OldFileName;
	void DDV_ValidFileName(CDataExchange *pDX, int nIdc, CString csFileName);
	CString m_OldID;

	// Generated message map functions
	//{{AFX_MSG(CElementIncludeDialog)
	afx_msg void OnBrowse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ELEMENTINCLUDEDIALOG_H__37077C14_C7B6_4A14_8B7B_7F877CA2C478__INCLUDED_)
