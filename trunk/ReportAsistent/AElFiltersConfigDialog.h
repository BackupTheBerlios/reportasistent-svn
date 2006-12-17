#include "afxwin.h"
#include "afxcmn.h"
#if !defined(AFX_AELFILTERSCONFIGDIALOG_H__BB057B90_DBD8_44C4_9138_DB1659AA5D98__INCLUDED_)
#define AFX_AELFILTERSCONFIGDIALOG_H__BB057B90_DBD8_44C4_9138_DB1659AA5D98__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AElFiltersConfigDialog.h : header file
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
#include "complexfilterdialog.h"

/////////////////////////////////////////////////////////////////////////////
// CAElFiltersConfigDialog dialog

/**
 * class CAElFiltersConfigDialog:This class encapsulates Complex Filter tab of Active Element dialog with all its functionality.

 *
 * @author 
 */
class CAElFiltersConfigDialog : public CPropertyPage, CFilterResultImpl, CAElDataShare
{
// Construction
public:
	CAElFiltersConfigDialog(CAElDataShare & data_share, CWnd* pParent = NULL);	// nestandard constructor :-)

// Dialog Data
	//{{AFX_DATA(CAElFiltersConfigDialog)
	enum { IDD = IDD_FILTER_AND_CONFIG_DIALOG };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAElFiltersConfigDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL


private:
	int GetCurSelFiltersList();

	CListCtrl m_FiltersList;

// Implementation
protected:
	void ConfigureFilter();
	void AddFilter();
	// Generated message map functions
	//{{AFX_MSG(CAElFiltersConfigDialog)
	afx_msg void OnRemoveFilterButton();
	afx_msg void OnMoveUpButton();
	afx_msg void OnMoveDownButton();
	afx_msg void OnBnClickedAddFilterButton();
	afx_msg void OnBnClickedConfigureFilterButton();
	afx_msg void OnDblclkFiltersList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnInitDialog();
	virtual BOOL OnApply();

	void UpdateFiltersList(void);
	void UpdateResult(void);

public:
	MSXML2::IXMLDOMElementPtr & getActiveElement(void);
	MSXML2::IXMLDOMElementPtr & getClonedActiveElement(void);
public:
	virtual BOOL OnSetActive();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AELFILTERSCONFIGDIALOG_H__BB057B90_DBD8_44C4_9138_DB1659AA5D98__INCLUDED_)
