#if !defined(AFX_ELEMENTTEXT_H__B88D04F6_2B23_49A9_B41A_2D577189CEE7__INCLUDED_)
#define AFX_ELEMENTTEXT_H__B88D04F6_2B23_49A9_B41A_2D577189CEE7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ElementText.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CElementText dialog

class CElementText : public CDialog
{
// Construction
public:
	CElementText(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CElementText)
	enum { IDD = IDD_DIALOGTEXT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CElementText)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CElementText)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ELEMENTTEXT_H__B88D04F6_2B23_49A9_B41A_2D577189CEE7__INCLUDED_)
