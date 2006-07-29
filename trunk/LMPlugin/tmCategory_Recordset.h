#if !defined(AFX_TMCATEGORY_RECORDSET_H__94C4CFCD_B93D_4704_ADFB_E71E7CF7D233__INCLUDED_)
#define AFX_TMCATEGORY_RECORDSET_H__94C4CFCD_B93D_4704_ADFB_E71E7CF7D233__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// tmCategory_Recordset.h : header file
//
#include "afxdb.h"
/////////////////////////////////////////////////////////////////////////////
// tmCategory_Recordset recordset

class tmCategory_Recordset : public CRecordset
{
public:
	tmCategory_Recordset(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(tmCategory_Recordset)

// Field/Param Data
	//{{AFX_FIELD(tmCategory_Recordset, CRecordset)
	long	m_CategoryID;
	CString	m_Name;
	long	m_QuantityID;
	long	m_CategorySubTypeID;
	long	m_BoolTypeID;
	BOOL	m_XCategory;
	BOOL	m_IncludeNULL;
	long	m_Ord;
	CString	m_Notice;
	long	m_wSavedCountUsed;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(tmCategory_Recordset)
	public:
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TMCATEGORY_RECORDSET_H__94C4CFCD_B93D_4704_ADFB_E71E7CF7D233__INCLUDED_)