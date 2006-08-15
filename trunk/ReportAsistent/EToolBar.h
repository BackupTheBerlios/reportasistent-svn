#if !defined(AFX_ETOOLBAR_H__77EDAB19_6435_4D1E_A0F5_427A81A13B94__INCLUDED_)
#define AFX_ETOOLBAR_H__77EDAB19_6435_4D1E_A0F5_427A81A13B94__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EToolBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEToolBar window

class CEToolBar : public CToolBar
{
// Construction
public:
	CEToolBar();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEToolBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEToolBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CEToolBar)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ETOOLBAR_H__77EDAB19_6435_4D1E_A0F5_427A81A13B94__INCLUDED_)
