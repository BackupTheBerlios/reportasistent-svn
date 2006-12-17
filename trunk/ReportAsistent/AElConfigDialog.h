//AElConfigDialog.h
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
#pragma once
#include "afxwin.h"

#include "complexfilterdialog.h"

// CAElConfigDialog dialog

/**
 * class CAElConfigDialog:
 *
 * @author 
 */
class CAElConfigDialog : public CPropertyPage, CAElDataShare, CFilterResultImpl
{
	DECLARE_DYNAMIC(CAElConfigDialog)


private:
	BOOL m_bSourceIsInit;
	CComboBox m_SourcesCombo;

public:
	CAElConfigDialog(CAElDataShare & data_share);
	virtual ~CAElConfigDialog();

// Dialog Data
	enum { IDD = IDD_AEL_CONFIG_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	BOOL LoadSource(public_source_id_t sId);
	void DDV_NonDuplicateID(CDataExchange *pDX, int nId, CString csIDEditValue);



	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeDataSourceCombo();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	CString m_sIdEdit;
	CString m_OldID;
public:
	afx_msg void OnEnChangeIdEdit();
public:
	virtual BOOL OnApply();
public:
	virtual BOOL OnSetActive();
};
