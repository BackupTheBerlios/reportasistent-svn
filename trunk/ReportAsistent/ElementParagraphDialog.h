#if !defined(AFX_ELEMENTPARAGRAPHDIALOG_H__BF12F658_F56C_4F06_8464_9C689F26DD93__INCLUDED_)
#define AFX_ELEMENTPARAGRAPHDIALOG_H__BF12F658_F56C_4F06_8464_9C689F26DD93__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// ElementParagraphDialog.h : header file
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
// CElementParagraphDialog dialog

/**
 * class CElementParagraphDialog:
 *
 * @author 
 */
class CElementParagraphDialog : public CDialog
{
// Construction
public:
	MSXML2::IXMLDOMElementPtr m_SelXMLElm;
	void DDV_NonDuplicateID(CDataExchange *pDX, int nId, CString csIDEditValue);
	CElementParagraphDialog(MSXML2::IXMLDOMElementPtr & SelXMLElm,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CElementParagraphDialog)
	enum { IDD = IDD_DIALOG_PARAGRAPH };
	CComboBox	m_StylesCombo;
	CString	m_DialParagraphIDEditValue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CElementParagraphDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void FillStylesCombo();
	CString m_OldID;

	// Generated message map functions
	//{{AFX_MSG(CElementParagraphDialog)
	afx_msg void OnStylesRefreshButton();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ELEMENTPARAGRAPHDIALOG_H__BF12F658_F56C_4F06_8464_9C689F26DD93__INCLUDED_)
