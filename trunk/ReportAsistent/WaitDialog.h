#if !defined(AFX_WAITDIALOG_H__0B638672_B800_4827_965C_AA552188BC84__INCLUDED_)
#define AFX_WAITDIALOG_H__0B638672_B800_4827_965C_AA552188BC84__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WaitDialog.h : header file
//

#include "WaitAnimation.h"

/////////////////////////////////////////////////////////////////////////////
// CWaitDialog dialog

class CWaitDialog : public CDialog
{
// Construction
public:
	CWaitDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWaitDialog)
	enum { IDD = IDD_WAIT_DIALOG };
	CWaitAnimation	m_wait_animation;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWaitDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWaitDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WAITDIALOG_H__0B638672_B800_4827_965C_AA552188BC84__INCLUDED_)
