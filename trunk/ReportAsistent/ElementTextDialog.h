#if !defined(AFX_ELEMENTTEXT_H__B88D04F6_2B23_49A9_B41A_2D577189CEE7__INCLUDED_)
#define AFX_ELEMENTTEXT_H__B88D04F6_2B23_49A9_B41A_2D577189CEE7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ElementTextDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CElementTextDialog dialog

class CElementTextDialog : public CDialog
{
// Construction
public:
	MSXML2::IXMLDOMElementPtr m_SelXMLElm;
	CElementTextDialog(MSXML2::IXMLDOMElementPtr & SelXMLElm,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CElementTextDialog)
	enum { IDD = IDD_DIALOGTEXT };
	CString	m_DialTextEditValue;
	CString	m_DialTextIDEditValue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CElementTextDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void DDV_NonDuplicateID(CDataExchange *pDX, int nId, CString csIDEditValue);
	CString m_OldID;

	// Generated message map functions
	//{{AFX_MSG(CElementTextDialog)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ELEMENTTEXT_H__B88D04F6_2B23_49A9_B41A_2D577189CEE7__INCLUDED_)
