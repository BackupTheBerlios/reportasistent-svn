#if !defined(AFX_TORDER_OF_CATEGORIES_H__A3D6FCA3_60DB_4F69_BB53_94D0157C4896__INCLUDED_)
#define AFX_TORDER_OF_CATEGORIES_H__A3D6FCA3_60DB_4F69_BB53_94D0157C4896__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TOrder_of_Categories.h : header file
//
#include "afxdb.h"
/////////////////////////////////////////////////////////////////////////////
// TOrder_of_Categories recordset

class TOrder_of_Categories : public CRecordset
{
public:
	TOrder_of_Categories(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(TOrder_of_Categories)

// Field/Param Data
	//{{AFX_FIELD(TOrder_of_Categories, CRecordset)
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
	long	m_QuantityID2;
	CString	m_Name2;
	CString	m_ShortName;
	BOOL	m_ShowName;
	long	m_AttributeID;
	long	m_ItemShift;
	long	m_ParentGroupID;
	long	m_wSavedCountUsed2;
	long	m_wUpdateVer;
	long	m_UserID;
	CString	m_Notice2;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TOrder_of_Categories)
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

#endif // !defined(AFX_TORDER_OF_CATEGORIES_H__A3D6FCA3_60DB_4F69_BB53_94D0157C4896__INCLUDED_)
