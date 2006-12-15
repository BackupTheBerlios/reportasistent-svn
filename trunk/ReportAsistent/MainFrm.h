// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////
/*
This file is part of LM Report Asistent.

Authors: Jan Dedek, Jan Kodym, Martin Chrz, Iva Bartunkova

LM Report Asistent is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

Foobar is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Foobar; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include "EToolBar.h"
#if !defined(AFX_MAINFRM_H__E34B981C_C7C4_458F_ADD4_1E455C86A3D3__INCLUDED_)
#define AFX_MAINFRM_H__E34B981C_C7C4_458F_ADD4_1E455C86A3D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/**
 * class CMainFrame:
 *
 * @author 
 */
class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);
	//}}AFX_VIRTUAL

// Implementation
public:
	CImageList mSImageList;
	CImageList mAImageList;
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CReBar      m_wndReBar;
//	CDialogBar      m_wndDlgBar;
	CEToolBar m_wndAEToolBar;
	CEToolBar m_wndSEToolBar;
// Generated message map functions
protected:
	CToolTipCtrl m_AEToolTips;
	BOOL CreateSEToolBar();
	BOOL CreateAEToolBar();
	CToolTipCtrl m_SEToolTips;
	
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnUpdateViewStaticelementstoolbar(CCmdUI* pCmdUI);
	afx_msg void OnViewStaticelementstoolbar();
	afx_msg void OnViewActiveelementtoolbar();
	afx_msg void OnUpdateViewActiveelementtoolbar(CCmdUI* pCmdUI);
	afx_msg void OnWordEditorEditActiveElement();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
public:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__E34B981C_C7C4_458F_ADD4_1E455C86A3D3__INCLUDED_)
