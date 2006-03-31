#if !defined(AFX_CATEGORY_RECORDSET_H__E5C368EA_6196_4C93_9616_234BDE0A57A0__INCLUDED_)
#define AFX_CATEGORY_RECORDSET_H__E5C368EA_6196_4C93_9616_234BDE0A57A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Category_Recordset.h : header file
//
#include "afxdb.h"
/////////////////////////////////////////////////////////////////////////////
// Category_Recordset recordset

class Category_Recordset : public CRecordset
{
public:
	Category_Recordset(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(Category_Recordset)

// Field/Param Data
	//{{AFX_FIELD(Category_Recordset, CRecordset)
	long	m_AttributeID;
	CString	m_Name;
	long	m_MatrixID;
	long	m_AttributeSubTypeID;
	long	m_ValueSubTypeID;
	BOOL	m_Derived;
	CString	m_Formula;
	long	m_MCPosition;
	long	m_MCLength;
	CString	m_MCDelimiter;
	long	m_PrimaryKeyPosition;
	double	m_ValueMin;
	double	m_ValueMax;
	double	m_ValueAvg;
	double	m_ValueModus;
	double	m_ValueVariability;
	CString	m_Notice;
	long	m_wSavedCountUsed;
	long	m_CategoryID;
	CString	m_Name2;
	long	m_QuantityID;
	long	m_CategorySubTypeID;
	long	m_BoolTypeID;
	BOOL	m_XCategory;
	BOOL	m_IncludeNULL;
	long	m_Ord;
	CString	m_Notice2;
	long	m_wSavedCountUsed2;
	long	m_MatrixID2;
	CString	m_Name3;
	BOOL	m_Initialised;
	long	m_RecordCount;
	CString	m_Notice3;
	long	m_wSavedCountUsed3;
	long	m_QuantityID2;
	CString	m_Name4;
	CString	m_ShortName;
	BOOL	m_ShowName;
	long	m_AttributeID2;
	long	m_ItemShift;
	long	m_ParentGroupID;
	long	m_wSavedCountUsed4;
	long	m_wUpdateVer;
	long	m_UserID;
	CString	m_Notice4;
	long	m_CategorySubTypeID2;
	CString	m_Name5;
	CString	m_ShortName2;
	long	m_Ord2;
	CString	m_Notice5;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Category_Recordset)
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

#endif // !defined(AFX_CATEGORY_RECORDSET_H__E5C368EA_6196_4C93_9616_234BDE0A57A0__INCLUDED_)
