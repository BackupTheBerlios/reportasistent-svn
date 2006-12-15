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

#include "complexfilterdialog.h"


/**
 * class CSimpleFilterDialog:
 *
 * @author 
 */
class CSimpleFilterDialog : public CPropertyPage, CAElDataShare, CFilterResultImpl
{	
	// Construction
public:
	/**
	 * CSimpleFilterDialog:
	 *
	 * @param data_share 
	 * @param pParent 
	 * @return  
	 */
	CSimpleFilterDialog(CAElDataShare & data_share, CWnd* pParent = NULL);	// nestandard constructor :-)
	~CSimpleFilterDialog();

// Dialog Data
	//{{AFX_DATA(CSimpleFilterDialog)
	enum { IDD = IDD_SIMPLE_FILTER_DIALOG };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimpleFilterDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	/**
	 * UpdateSelection:
	 *
	 * @return void 
	 */
	void UpdateSelection();

	// Generated message map functions
	//{{AFX_MSG(CSimpleFilterDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnDeleteitemFilterList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
  /**
   * OnApply:
   *
   * @return virtual BOOL 
   */
  virtual BOOL OnApply();
  /**
  * OnNMClickFilterList:
  *
  * @param pNMHDR 
  * @param pResult 
  * @return afx_msg void 
  */
 afx_msg void OnNMClickFilterList(NMHDR *pNMHDR, LRESULT *pResult);
  /**
   * OnSetActive:
   *
   * @return virtual BOOL 
   */
  virtual BOOL OnSetActive();
 
  /**
   * OnSimpleFilterDisabledCheck:
   *
   * @return afx_msg void 
   */
  afx_msg void OnSimpleFilterDisabledCheck();
protected:
	/**
	 * SetDisabledCheck:
	 *
	 * @param  
	 * @return void 
	 */
	void SetDisabledCheck(void);
public:
	/**
	 * OnKillActive:
	 *
	 * @return virtual BOOL 
	 */
	virtual BOOL OnKillActive();
protected:

	/**
	 * SaveSelection:
	 *
	 * @param  
	 * @return void 
	 */
	void SaveSelection(void);
	/**
	 * CheckSimpleFilterDisabled:
	 *
	 * @param  
	 * @return void 
	 */
	void CheckSimpleFilterDisabled(void);
	/**
	 * UpdateSimpleView:
	 *
	 * @param  
	 * @return void 
	 */
	void UpdateSimpleView(void);
	BOOL m_bSimpleFilterDisabled;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMPLEFILTERDIALOG_H__8461C43B_3F63_46C2_BD7E_90E9BB9B1EC6__INCLUDED_)
