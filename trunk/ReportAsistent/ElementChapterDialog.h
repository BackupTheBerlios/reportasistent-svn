#if !defined(AFX_ELEMENTCHAPTERDIALOG_H__DFC68060_75E1_44D8_84D6_F29E5A7FED10__INCLUDED_)
#define AFX_ELEMENTCHAPTERDIALOG_H__DFC68060_75E1_44D8_84D6_F29E5A7FED10__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ElementChapterDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CElementChapterDialog dialog

class CElementChapterDialog : public CDialog
{
// Construction
public:
	MSXML2::IXMLDOMElementPtr m_SelXMLElm;
	CElementChapterDialog(MSXML2::IXMLDOMElementPtr & SelXMLElm, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CElementChapterDialog)
	enum { IDD = IDD_DIALOG_CHAPTER };
	CString	m_DialChapterIDEditValue;
	CString	m_DialChapterTitleEditValue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CElementChapterDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void DDV_NonDuplicateID(CDataExchange* pDX,int nId, CString csIDEditValue);
	CString m_OldID;
	

	// Generated message map functions
	//{{AFX_MSG(CElementChapterDialog)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ELEMENTCHAPTERDIALOG_H__DFC68060_75E1_44D8_84D6_F29E5A7FED10__INCLUDED_)
