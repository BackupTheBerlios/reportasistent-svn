#if !defined(AFX_TCATDEF_H__9BBBA927_758B_447B_B95F_20EBE78EF590__INCLUDED_)
#define AFX_TCATDEF_H__9BBBA927_758B_447B_B95F_20EBE78EF590__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TCatDef.h : header file
//
#include "afxdb.h"
/////////////////////////////////////////////////////////////////////////////
// TCatDef recordset

class TCatDef : public CRecordset
{
public:
	TCatDef(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(TCatDef)

// Field/Param Data
	//{{AFX_FIELD(TCatDef, CRecordset)
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
	long	m_CategoryEnumValueID;
	long	m_CategoryID2;
	long	m_ValueID;
	long	m_IntervalID;
	long	m_CategoryID3;
	long	m_FromValueID;
	long	m_ToValueID;
	long	m_LeftBracketTypeID;
	long	m_RightBracketTypeID;
	long	m_ValueID2;
	long	m_ValueSubTypeID;
	long	m_ValueLong;
	double	m_ValueFloat;
	CString	m_ValueString;
	BOOL	m_ValueBool;
	CTime	m_ValueDate;
	long	m_InfinityTypeID;
	BOOL	m_IsNULL;
	long	m_BracketTypeID;
	CString	m_Name2;
	CString	m_ShortName;
	long	m_Ord2;
	CString	m_LeftBracket;
	CString	m_RightBracket;
	CString	m_Notice2;
	long	m_id;
	CString m_TypeName;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TCatDef)
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

#endif // !defined(AFX_TCATDEF_H__9BBBA927_758B_447B_B95F_20EBE78EF590__INCLUDED_)
