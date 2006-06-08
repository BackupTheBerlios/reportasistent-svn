#if !defined(AFX_TCATDEFINT_H__C5318E11_E71B_4386_B4D7_E1E7822103DD__INCLUDED_)
#define AFX_TCATDEFINT_H__C5318E11_E71B_4386_B4D7_E1E7822103DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TCatDefInt.h : header file
//
#ifndef WINVER
#define WINVER 0x0500
#endif
#include "afxdb.h"
/////////////////////////////////////////////////////////////////////////////
// TCatDefInt recordset

class TCatDefInt : public CRecordset
{
public:
	TCatDefInt(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(TCatDefInt)

// Field/Param Data
	//{{AFX_FIELD(TCatDefInt, CRecordset)
	long	m_IntervalID;
	long	m_CategoryID;
	long	m_FromValueID;
	long	m_ToValueID;
	long	m_LeftBracketTypeID;
	long	m_RightBracketTypeID;
	long	m_ValueID;
	long	m_ValueSubTypeID;
	long	m_ValueLong;
	double	m_ValueFloat;
	CString	m_ValueString;
	BOOL	m_ValueBool;
	CTime	m_ValueDate;
	long	m_InfinityTypeID;
	BOOL	m_IsNULL;
	long	m_BracketTypeID;
	CString	m_Name;
	CString	m_ShortName;
	long	m_Ord;
	CString	m_LeftBracket;
	CString	m_RightBracket;
	CString	m_Notice;
	long	m_ValueSubTypeID2;
	CString	m_Name2;
	CString	m_ShortName2;
	long	m_Ord2;
	CString	m_Notice2;
	BOOL	m_Cardinal;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TCatDefInt)
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

#endif // !defined(AFX_TCATDEFINT_H__C5318E11_E71B_4386_B4D7_E1E7822103DD__INCLUDED_)
