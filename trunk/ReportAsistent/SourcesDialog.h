#if !defined(AFX_SOURCESDIALOG_H__1B8DB1D2_2E88_4F12_925B_F44666BF5D43__INCLUDED_)
#define AFX_SOURCESDIALOG_H__1B8DB1D2_2E88_4F12_925B_F44666BF5D43__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SourcesDialog.h : header file
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
// CSourcesDialog dialog

/**
 * class CSourcesDialog:
 *
 * @author 
 */
class CSourcesDialog : public CDialog
{

private:
	static LPCTSTR header_captions [];
// Construction
public:
	void UpDateList();
	CSourcesDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSourcesDialog)
	enum { IDD = IDD_SOURCES_DIALOG };
	CComboBox	m_PluginCombo;
	CListCtrl	m_SourcesList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSourcesDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	/**
	 * SetDefault: Sets the selected data source to be default.
	 *
	 * @return void 
	 */
	void SetDefault();

	// Generated message map functions
	//{{AFX_MSG(CSourcesDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnAddSourceButton();
	afx_msg void OnOpenButton();
	afx_msg void OnCloseButton();
	afx_msg void OnRemoveButton();
	afx_msg void OnRenameButton();
	afx_msg void OnEndlabeleditSourcesList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSetDefaultButton();
	afx_msg void OnDblclkSourcesList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOURCESDIALOG_H__1B8DB1D2_2E88_4F12_925B_F44666BF5D43__INCLUDED_)
