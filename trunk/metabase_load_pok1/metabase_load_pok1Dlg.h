// metabase_load_pok1Dlg.h : header file
//

#if !defined(AFX_METABASE_LOAD_POK1DLG_H__525FE872_C154_414B_887C_6A4D8350361C__INCLUDED_)
#define AFX_METABASE_LOAD_POK1DLG_H__525FE872_C154_414B_887C_6A4D8350361C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XMLTree.h"
#include "WordView.h"


/////////////////////////////////////////////////////////////////////////////
// CMetabase_load_pok1Dlg dialog

class CMetabase_load_pok1Dlg : public CDialog
{
// Construction
public:
	BOOL NactiMetabazi();
	CMetabase_load_pok1Dlg(CWnd* pParent = NULL);	// standard constructor



#ifdef USE_WORD	
	CWordView	m_WordView;
	CXMLTree	m_XMLTree1;
#endif
//dat mezi   //}}AFX_DATA


	
// Dialog Data
	//{{AFX_DATA(CMetabase_load_pok1Dlg)
	enum { IDD = IDD_METABASE_LOAD_POK1_DIALOG };
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
	afx_msg void OnXmlButton();
	afx_msg void OnGenerxmlButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#define EDIT_NEWLINE "\r\n"


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_METABASE_LOAD_POK1DLG_H__525FE872_C154_414B_887C_6A4D8350361C__INCLUDED_)
