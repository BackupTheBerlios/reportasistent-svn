#if !defined(AFX_SOURCESDIALOG_H__1B8DB1D2_2E88_4F12_925B_F44666BF5D43__INCLUDED_)
#define AFX_SOURCESDIALOG_H__1B8DB1D2_2E88_4F12_925B_F44666BF5D43__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SourcesDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSourcesDialog dialog

class CSourcesDialog : public CDialog
{

private:
	//pracovni asi tez nejak Resource.. jak?
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
