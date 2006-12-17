#include "afxwin.h"
#if !defined(AFX_OPTIONSDIALOG_H__EF3E84D5_FE81_4C44_BB14_EF8285E3132C__INCLUDED_)
#define AFX_OPTIONSDIALOG_H__EF3E84D5_FE81_4C44_BB14_EF8285E3132C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsDialog.h : header file
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
/////////////////////////////////////////////////////////////////////////////
// COptionsDialog dialog

/**
 * class COptionsDialog: Class of the Options Dialog.
 *
 * @author 
 */
class COptionsDialog : public CDialog
{
// Construction
public:
	COptionsDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COptionsDialog)
	enum { IDD = IDD_OPTIONS_DIALOG };
	CEdit	m_TextEditSize;
	CButton	m_MarkOrphansCheckBox;
	CButton	m_IdInTreeCheckBox;
	CButton	m_ButtonsCheckBox;
	CButton	m_LinesCheckBox;
	CEdit	m_IndentEdit;
	CEdit	m_HeightEdit;
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
public:
	CString m_strWordTemplate;
public:
	afx_msg void OnBnClickedTemplateBrowseBotton();
public:
	afx_msg void OnEnChangeTreeItemNameLength();
public:
	CEdit m_NameLengthEdit;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSDIALOG_H__EF3E84D5_FE81_4C44_BB14_EF8285E3132C__INCLUDED_)
