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
private:
	struct SThreadPramas
	{
		HWND hWaitDlg;
		void * pUserFunction;
		int nParams;	//number of prametrs
		LPARAM params[5];
	} * m_pThreadPramas;

public:
//	DoThreadFunction(WaitUserThreadFunction5 f, LPARAM Param1,  LPARAM Param2, LPARAM Param3, LPARAM Param4, LPARAM Param5)
	typedef void (* WaitUserThreadFunction0) ();
	typedef void (* WaitUserThreadFunction1) (LPARAM Param1);
	typedef void (* WaitUserThreadFunction2) (LPARAM Param1,  LPARAM Param2);
	typedef void (* WaitUserThreadFunction3) (LPARAM Param1,  LPARAM Param2, LPARAM Param3);
	typedef void (* WaitUserThreadFunction4) (LPARAM Param1,  LPARAM Param2, LPARAM Param3, LPARAM Param4);
	typedef void (* WaitUserThreadFunction5) (LPARAM Param1,  LPARAM Param2, LPARAM Param3, LPARAM Param4, LPARAM Param5);

	
// Construction
public:
	void DoThreadFunction(WaitUserThreadFunction5 f, LPARAM Param1,  LPARAM Param2, LPARAM Param3, LPARAM Param4, LPARAM Param5);
	void DoThreadFunction(WaitUserThreadFunction4 f, LPARAM Param1,  LPARAM Param2, LPARAM Param3, LPARAM Param4);
	void DoThreadFunction(WaitUserThreadFunction3 f, LPARAM Param1,  LPARAM Param2, LPARAM Param3);
	void DoThreadFunction(WaitUserThreadFunction2 f, LPARAM Param1,  LPARAM Param2);
	void DoThreadFunction(WaitUserThreadFunction1 f, LPARAM Param1);
	void DoThreadFunction(WaitUserThreadFunction0 f);
	
	
	CWaitDialog(LPCTSTR strDlgText, BOOL bShowKillButtons = TRUE, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWaitDialog)
	enum { IDD = IDD_WAIT_DIALOG };
	CStatic	m_ReasonText;
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
	void DoThreadFunctionImpl(void * f);

	// Generated message map functions
	//{{AFX_MSG(CWaitDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnExitButton();
	virtual void OnCancel();
	afx_msg void OnKillThreadButton();
	afx_msg void OnResumeAppButton();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bShowKillButtons;
	UINT m_nTimer;
	CWinThread * m_pWorkerThread;
	static UINT ThreadControllingFunction( LPVOID pParam );
	LPCTSTR m_strDlgText;
	BOOL m_bEndDialog;
	afx_msg void OnStnClickedReasonText();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WAITDIALOG_H__0B638672_B800_4827_965C_AA552188BC84__INCLUDED_)
