#if !defined(AFX_STARTDIALOG_H__C776C704_F621_40B0_B6B9_F80C4906344B__INCLUDED_)
#define AFX_STARTDIALOG_H__C776C704_F621_40B0_B6B9_F80C4906344B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StartDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStartDialog dialog

/** CStartDialog is a class for the dialog, that is shown at 
*the startup of LM-RA application, before the main window of 
*the application is initialized.
*/


class CStartDialog : public CDialog
{
// Construction
public:
	CStartDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStartDialog)
	enum { IDD = IDD_START_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStartDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStartDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STARTDIALOG_H__C776C704_F621_40B0_B6B9_F80C4906344B__INCLUDED_)
