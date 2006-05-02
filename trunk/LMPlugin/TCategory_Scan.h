#if !defined(AFX_TCATEGORY_SCAN_H__A729BC9A_F856_47F2_BCE3_096056B4D233__INCLUDED_)
#define AFX_TCATEGORY_SCAN_H__A729BC9A_F856_47F2_BCE3_096056B4D233__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TCategory_Scan.h : header file
//
#include "afxdb.h"
/////////////////////////////////////////////////////////////////////////////
// TCategory_Scan recordset

class TCategory_Scan : public CRecordset
{
public:
	TCategory_Scan(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(TCategory_Scan)

// Field/Param Data
	//{{AFX_FIELD(TCategory_Scan, CRecordset)
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
	//{{AFX_VIRTUAL(TCategory_Scan)
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

#endif // !defined(AFX_TCATEGORY_SCAN_H__A729BC9A_F856_47F2_BCE3_096056B4D233__INCLUDED_)
