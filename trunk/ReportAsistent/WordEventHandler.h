#if !defined(AFX_WORDEVENTHANDLER_H__B6271273_95E9_4D53_A29B_41F63F14BB5F__INCLUDED_)
#define AFX_WORDEVENTHANDLER_H__B6271273_95E9_4D53_A29B_41F63F14BB5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WordEventHandler.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CWordEventHandler command target

class CWordEventHandler : public CCmdTarget
{
	DECLARE_DYNCREATE(CWordEventHandler)

	CWordEventHandler();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWordEventHandler)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWordEventHandler();

protected:

	// Generated message map functions
	//{{AFX_MSG(CWordEventHandler)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CWordEventHandler)
	afx_msg void onActiveElementSelected(LPCTSTR strElementName);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORDEVENTHANDLER_H__B6271273_95E9_4D53_A29B_41F63F14BB5F__INCLUDED_)
