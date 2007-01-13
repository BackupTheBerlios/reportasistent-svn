#if !defined(AFX_GENERATEDIALOG_H__B6BE28EE_6665_4B0C_82E9_8F658541580A__INCLUDED_)
#define AFX_GENERATEDIALOG_H__B6BE28EE_6665_4B0C_82E9_8F658541580A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GenerateDialog.h : header file
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
// CGenerateDialog dialog

/**
 * class CGenerateDialog: Class of the Generation dialog.
 *
 * @author 
 */
class CGenerateDialog : public CDialog
{
// Construction
public:
	CGenerateDialog(CSkeletonDoc & DocumentToGenerate, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGenerateDialog)
	enum { IDD = IDD_GENERATE_DIALOG };
	BOOL	m_bNewWordChecked;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGenerateDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGenerateDialog)
	afx_msg void OnGenerateButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CSkeletonDoc & m_SkeletonDocument;
	virtual BOOL OnInitDialog();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GENERATEDIALOG_H__B6BE28EE_6665_4B0C_82E9_8F658541580A__INCLUDED_)
