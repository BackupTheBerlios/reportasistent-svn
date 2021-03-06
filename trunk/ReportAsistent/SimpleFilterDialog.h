#if !defined(AFX_SIMPLEFILTERDIALOG_H__8461C43B_3F63_46C2_BD7E_90E9BB9B1EC6__INCLUDED_)
#define AFX_SIMPLEFILTERDIALOG_H__8461C43B_3F63_46C2_BD7E_90E9BB9B1EC6__INCLUDED_





#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SimpleFilterDialog.h : header file
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
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CSimpleFilterDialog dialog
//honza:
//univerzalni dialog, ktery implementuje simple filter
//z vystupu ze savuvky si XSLT transformci vytvori data, podle kterych nastavi svuj vzhled
//a naplni ovladaci prvky

#include "complexfilterdialog.h"


/**
 * class CSimpleFilterDialog:The class of tab Simple Filter of Active Element dialog.
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
