#if !defined(AFX_TCATDEFENUM_H__6AC0FE42_53F8_49A2_98BD_6174A5EB36D0__INCLUDED_)
#define AFX_TCATDEFENUM_H__6AC0FE42_53F8_49A2_98BD_6174A5EB36D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TCatDefEnum.h : header file
//
#include "afxdb.h"
/////////////////////////////////////////////////////////////////////////////
// TCatDefEnum recordset

class TCatDefEnum : public CRecordset
{
public:
	TCatDefEnum(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(TCatDefEnum)

// Field/Param Data
	//{{AFX_FIELD(TCatDefEnum, CRecordset)
	long	m_CategoryEnumValueID;
	long	m_CategoryID;
	long	m_ValueID;
	long	m_ValueID2;
	long	m_ValueSubTypeID;
	long	m_ValueLong;
	double	m_ValueFloat;
	CString	m_ValueString;
	BOOL	m_ValueBool;
	CTime	m_ValueDate;
	long	m_InfinityTypeID;
	BOOL	m_IsNULL;
	long	m_ValueSubTypeID2;
	CString	m_Name;
	CString	m_ShortName;
	BOOL	m_Cardinal;
	long	m_Ord;
	CString	m_Notice;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TCatDefEnum)
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

#endif // !defined(AFX_TCATDEFENUM_H__6AC0FE42_53F8_49A2_98BD_6174A5EB36D0__INCLUDED_)
