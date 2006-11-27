#if !defined(AFX_TCOLUMN_RECORDSET_H__6BD56890_5555_49FA_B864_8351DDE384AA__INCLUDED_)
#define AFX_TCOLUMN_RECORDSET_H__6BD56890_5555_49FA_B864_8351DDE384AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TColumn_Recordset.h : header file
//
#include "afxdb.h"
/////////////////////////////////////////////////////////////////////////////
// TColumn_Recordset recordset

class TColumn_Recordset : public CRecordset
{
public:
	TColumn_Recordset(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(TColumn_Recordset)

// Field/Param Data
	//{{AFX_FIELD(TColumn_Recordset, CRecordset)
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
	long	m_MatrixID2;
	CString	m_Name2;
	BOOL	m_Initialised;
	long	m_RecordCount;
	CString	m_Notice2;
	long	m_wSavedCountUsed2;
	long	m_AttributeSubTypeID2;
	CString	m_Name3;
	CString	m_ShortName;
	long	m_Ord;
	CString	m_Notice3;
	long	m_ValueSubTypeID2;
	CString	m_Name4;
	CString	m_ShortName2;
	BOOL	m_Cardinal;
	long	m_Ord2;
	CString	m_Notice4;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TColumn_Recordset)
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

#endif // !defined(AFX_TCOLUMN_RECORDSET_H__6BD56890_5555_49FA_B864_8351DDE384AA__INCLUDED_)