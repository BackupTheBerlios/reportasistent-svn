#if !defined(AFX_SIMPLEFILTERDIALOG_H__8461C43B_3F63_46C2_BD7E_90E9BB9B1EC6__INCLUDED_)
#define AFX_SIMPLEFILTERDIALOG_H__8461C43B_3F63_46C2_BD7E_90E9BB9B1EC6__INCLUDED_





#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SimpleFilterDialog.h : header file
//

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CSimpleFilterDialog dialog
//honza:
//univerzalni dialog, ktery implementuje simple filter
//z vystupu ze savuvky si XSLT transformci vytvori data, podle kterych nastavi svuj vzhled
//a naplni ovladaci prvky
//v konstruktoru dostane odkaz na prvek kostry active_element
//pri IDOK zmeni simple filter tag v tomto prvku podle volby uzivatele

class CSimpleFilterDialog : public CDialog
{
// Construction
public:
	CSimpleFilterDialog(IXMLDOMElementPtr & active_element, BSTR plugin_output, CWnd* pParent);	// nestandard constructor :-)

// Dialog Data
	//{{AFX_DATA(CSimpleFilterDialog)
	enum { IDD = IDD_SIMPLE_FILTER_DIALOG };
	CListCtrl	m_FilterList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimpleFilterDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSimpleFilterDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDeleteitemFilterList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	IXMLDOMElementPtr & m_active_element;
	MSXML2::IXMLDOMDocument2Ptr m_filter_dom;	//data pouzita na naplneni list veiw
	MSXML2::IXMLDOMElementPtr m_filter_node;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMPLEFILTERDIALOG_H__8461C43B_3F63_46C2_BD7E_90E9BB9B1EC6__INCLUDED_)
