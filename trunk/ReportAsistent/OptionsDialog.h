#if !defined(AFX_OPTIONSDIALOG_H__EF3E84D5_FE81_4C44_BB14_EF8285E3132C__INCLUDED_)
#define AFX_OPTIONSDIALOG_H__EF3E84D5_FE81_4C44_BB14_EF8285E3132C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COptionsDialog dialog

class COptionsDialog : public CDialog
{
// Construction
public:
	COptionsDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COptionsDialog)
	enum { IDD = IDD_OPTIONS_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptionsDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COptionsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSDIALOG_H__EF3E84D5_FE81_4C44_BB14_EF8285E3132C__INCLUDED_)