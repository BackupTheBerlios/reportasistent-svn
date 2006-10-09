#if !defined(AFX_SIMPLEFILTERDIALOG_H__8461C43B_3F63_46C2_BD7E_90E9BB9B1EC6__INCLUDED_)
#define AFX_SIMPLEFILTERDIALOG_H__8461C43B_3F63_46C2_BD7E_90E9BB9B1EC6__INCLUDED_





#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SimpleFilterDialog.h : header file
//

#include "resource.h"
//#include "DataSourceManager.h"

/////////////////////////////////////////////////////////////////////////////
// CSimpleFilterDialog dialog
//honza:
//univerzalni dialog, ktery implementuje simple filter
//z vystupu ze savuvky si XSLT transformci vytvori data, podle kterych nastavi svuj vzhled
//a naplni ovladaci prvky
//v konstruktoru dostane odkaz na prvek kostry active_element
//pri IDOK zmeni simple filter tag v tomto prvku podle volby uzivatele

class CSimpleFilterDialog : public CPropertyPage
{
// Construction
public:
	BOOL SaveAll();
	CSimpleFilterDialog(MSXML2::IXMLDOMElementPtr & active_element, CWnd* pParent = NULL);	// nestandard constructor :-)
	~CSimpleFilterDialog();

// Dialog Data
	//{{AFX_DATA(CSimpleFilterDialog)
	enum { IDD = IDD_SIMPLE_FILTER_DIALOG };
	CComboBox	m_SourcesCombo;
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
	void UpDateDialog();
	BOOL LoadSource(public_source_id_t sId);

	// Generated message map functions
	//{{AFX_MSG(CSimpleFilterDialog)
	virtual BOOL OnInitDialog();
//	virtual void OnOK();
	afx_msg void OnDeleteitemFilterList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeDataSourceCombo();
//	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	MSXML2::IXMLDOMElementPtr & m_active_element;
//	MSXML2::MSXML2::IXMLDOMDocument2Ptr m_filter_dom;	
	MSXML2::IXMLDOMElementPtr m_filter_DOM;	//data pouzita na naplneni list veiw
//	MSXML2::IXMLDOMDocumentPtr m_filter_transform;

//  afx_msg void OnEnterIdle(UINT nWhy, CWnd* pWho);
private:
  BOOL m_bSourceIsInit;
//  virtual BOOL OnSetActive();
//  afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
  afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
  virtual BOOL OnApply();
  virtual void OnOK();
//  afx_msg void OnLvnOdstatechangedFilterList(NMHDR *pNMHDR, LRESULT *pResult);
  afx_msg void OnNMClickFilterList(NMHDR *pNMHDR, LRESULT *pResult);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMPLEFILTERDIALOG_H__8461C43B_3F63_46C2_BD7E_90E9BB9B1EC6__INCLUDED_)
