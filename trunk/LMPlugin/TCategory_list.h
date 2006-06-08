#if !defined(AFX_TCATEGORY_LIST_H__03BC0CDA_00D0_4B5B_848A_9E7488318244__INCLUDED_)
#define AFX_TCATEGORY_LIST_H__03BC0CDA_00D0_4B5B_848A_9E7488318244__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TCategory_list.h : header file
//
#ifndef WINVER
#define WINVER 0x0500
#endif
#include "afxdb.h"
/////////////////////////////////////////////////////////////////////////////
// TCategory_list recordset

class TCategory_list : public CRecordset
{
public:
	TCategory_list(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(TCategory_list)

// Field/Param Data
	//{{AFX_FIELD(TCategory_list, CRecordset)
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
	long	m_QuantityID2;
	CString	m_Name3;
	CString	m_ShortName;
	BOOL	m_ShowName;
	long	m_AttributeID2;
	long	m_ItemShift;
	long	m_ParentGroupID;
	long	m_wSavedCountUsed3;
	long	m_wUpdateVer;
	long	m_UserID;
	CString	m_Notice3;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TCategory_list)
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

#endif // !defined(AFX_TCATEGORY_LIST_H__03BC0CDA_00D0_4B5B_848A_9E7488318244__INCLUDED_)
