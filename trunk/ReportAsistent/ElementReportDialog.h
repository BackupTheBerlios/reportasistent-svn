#if !defined(AFX_ELEMENTREPORTDIALOG_H__186E37FE_019D_48FA_BF22_8D1E8AB4B95F__INCLUDED_)
#define AFX_ELEMENTREPORTDIALOG_H__186E37FE_019D_48FA_BF22_8D1E8AB4B95F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ElementReportDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CElementReportDialog dialog

class CElementReportDialog : public CDialog
{
// Construction
public:
	CElementReportDialog(MSXML2::IXMLDOMElementPtr & SelXMLElm, CWnd* pParent = NULL);
	MSXML2::IXMLDOMElementPtr m_SelXMLElm;
// Dialog Data
	//{{AFX_DATA(CElementReportDialog)
	enum { IDD = IDD_DIALOG_REPORT };
	CString	m_DialReportIDEditValue;
	CString	m_DialReportTitleEditValue;
	CString	m_DialReportSubtitleEditValue;
	CString	m_DialReportAuthorEditValue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CElementReportDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void DDV_NonDuplicateID(CDataExchange *pDX, int nId, CString csIDEditValue);
	CString m_OldID;

	// Generated message map functions
	//{{AFX_MSG(CElementReportDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ELEMENTREPORTDIALOG_H__186E37FE_019D_48FA_BF22_8D1E8AB4B95F__INCLUDED_)
