#pragma once
#include "afxwin.h"

#include "complexfilterdialog.h"

// CAElConfigDialog dialog

class CAElConfigDialog : public CPropertyPage, CAElDataShare
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
};
