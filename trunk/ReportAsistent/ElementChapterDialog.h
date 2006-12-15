#if !defined(AFX_ELEMENTCHAPTERDIALOG_H__DFC68060_75E1_44D8_84D6_F29E5A7FED10__INCLUDED_)
#define AFX_ELEMENTCHAPTERDIALOG_H__DFC68060_75E1_44D8_84D6_F29E5A7FED10__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ElementChapterDialog.h : header file
//
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
/////////////////////////////////////////////////////////////////////////////
// CElementChapterDialog dialog

/**
 * class CElementChapterDialog:
 *
 * @author 
 */
class CElementChapterDialog : public CDialog
{
// Construction
public:
	MSXML2::IXMLDOMElementPtr m_SelXMLElm;
	CElementChapterDialog(MSXML2::IXMLDOMElementPtr & SelXMLElm, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CElementChapterDialog)
	enum { IDD = IDD_DIALOG_CHAPTER };
	CString	m_DialChapterIDEditValue;
	CString	m_DialChapterTitleEditValue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CElementChapterDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void DDV_NonDuplicateID(CDataExchange* pDX,int nId, CString csIDEditValue);
	CString m_OldID;
	

	// Generated message map functions
	//{{AFX_MSG(CElementChapterDialog)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ELEMENTCHAPTERDIALOG_H__DFC68060_75E1_44D8_84D6_F29E5A7FED10__INCLUDED_)
