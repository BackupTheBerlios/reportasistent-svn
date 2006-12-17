#if !defined(AFX_WAITDIALOG_H__0B638672_B800_4827_965C_AA552188BC84__INCLUDED_)
#define AFX_WAITDIALOG_H__0B638672_B800_4827_965C_AA552188BC84__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WaitDialog.h : header file
//
/*
This file is part of LM Report Asistent.

Authors: Jan Dedek, Jan Kodym, Martin Chrz, Iva Bartunkova

LM Report Asistent is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

LM Report Asistent is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with LM Report Asistent; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include "WaitAnimation.h"

/////////////////////////////////////////////////////////////////////////////
// CWaitDialog dialog

/**
 * class CWaitDialog: Class of Wait Dialog, used for long time operations of LM-RA.
 *
 * @author 
 */
class CWaitDialog : public CDialog
{
private:
	/**
	 * struct SThreadPramas:
	 *
	 * @author 
	 */
	struct SThreadPramas
	{
		HWND hWaitDlg;
		void * pUserFunction;
		int nParams;	//number of prametrs
		LPARAM params[5];
	} * m_pThreadPramas;

public:
//	DoThreadFunction(WaitUserThreadFunction5 f, LPARAM Param1,  LPARAM Param2, LPARAM Param3, LPARAM Param4, LPARAM Param5)
	/**
	 * WaitUserThreadFunction0:
	 */
	typedef void (* WaitUserThreadFunction0) ();
	/**
	 * WaitUserThreadFunction1:
	 */
	typedef void (* WaitUserThreadFunction1) (LPARAM Param1);
	/**
	 * WaitUserThreadFunction2:
	 */
	typedef void (* WaitUserThreadFunction2) (LPARAM Param1,  LPARAM Param2);
	/**
	 * WaitUserThreadFunction3:
	 */
	typedef void (* WaitUserThreadFunction3) (LPARAM Param1,  LPARAM Param2, LPARAM Param3);
	/**
	 * WaitUserThreadFunction4:
	 */
	typedef void (* WaitUserThreadFunction4) (LPARAM Param1,  LPARAM Param2, LPARAM Param3, LPARAM Param4);
	/**
	 * WaitUserThreadFunction5:
	 */
	typedef void (* WaitUserThreadFunction5) (LPARAM Param1,  LPARAM Param2, LPARAM Param3, LPARAM Param4, LPARAM Param5);

	
// Construction
public:
	/**
	 * DoThreadFunction:
	 *
	 * @param f 
	 * @param Param1 
	 * @param Param2 
	 * @param Param3 
	 * @param Param4 
	 * @param Param5 
	 * @return void 
	 */
	void DoThreadFunction(WaitUserThreadFunction5 f, LPARAM Param1,  LPARAM Param2, LPARAM Param3, LPARAM Param4, LPARAM Param5);
	/**
	 * DoThreadFunction:
	 *
	 * @param f 
	 * @param Param1 
	 * @param Param2 
	 * @param Param3 
	 * @param Param4 
	 * @return void 
	 */
	void DoThreadFunction(WaitUserThreadFunction4 f, LPARAM Param1,  LPARAM Param2, LPARAM Param3, LPARAM Param4);
	/**
	 * DoThreadFunction:
	 *
	 * @param f 
	 * @param Param1 
	 * @param Param2 
	 * @param Param3 
	 * @return void 
	 */
	void DoThreadFunction(WaitUserThreadFunction3 f, LPARAM Param1,  LPARAM Param2, LPARAM Param3);
	/**
	 * DoThreadFunction:
	 *
	 * @param f 
	 * @param Param1 
	 * @param Param2 
	 * @return void 
	 */
	void DoThreadFunction(WaitUserThreadFunction2 f, LPARAM Param1,  LPARAM Param2);
	/**
	 * DoThreadFunction:
	 *
	 * @param f 
	 * @param Param1 
	 * @return void 
	 */
	void DoThreadFunction(WaitUserThreadFunction1 f, LPARAM Param1);
	/**
	 * DoThreadFunction:
	 *
	 * @param f 
	 * @return void 
	 */
	void DoThreadFunction(WaitUserThreadFunction0 f);
	
	
	/**
	 * CWaitDialog:
	 *
	 * @param strDlgText 
	 * @param bShowKillButtons 
	 * @param pParent 
	 * @return  
	 */
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
	/**
	 * DoThreadFunctionImpl:
	 *
	 * @param f 
	 * @return void 
	 */
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
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WAITDIALOG_H__0B638672_B800_4827_965C_AA552188BC84__INCLUDED_)
