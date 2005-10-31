// metabase_load_pok1Dlg.h : header file
//

#if !defined(AFX_METABASE_LOAD_POK1DLG_H__525FE872_C154_414B_887C_6A4D8350361C__INCLUDED_)
#define AFX_METABASE_LOAD_POK1DLG_H__525FE872_C154_414B_887C_6A4D8350361C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMetabase_load_pok1Dlg dialog

class CMetabase_load_pok1Dlg : public CDialog
{
// Construction
public:
	BOOL NactiMetabazi();
	CMetabase_load_pok1Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMetabase_load_pok1Dlg)
	enum { IDD = IDD_METABASE_LOAD_POK1_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMetabase_load_pok1Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMetabase_load_pok1Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLoadButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_METABASE_LOAD_POK1DLG_H__525FE872_C154_414B_887C_6A4D8350361C__INCLUDED_)
