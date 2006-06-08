#if !defined(AFX_TATTRIBUTE_RECORDSET_H__C707E60D_8C69_4CE3_8F79_05CE0D9D65CF__INCLUDED_)
#define AFX_TATTRIBUTE_RECORDSET_H__C707E60D_8C69_4CE3_8F79_05CE0D9D65CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TAttribute_Recordset.h : header file
//
#ifndef WINVER
#define WINVER 0x0400
#endif
#include "afxdb.h"
/////////////////////////////////////////////////////////////////////////////
// TAttribute_Recordset recordset

class TAttribute_Recordset : public CRecordset
{
public:
	TAttribute_Recordset(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(TAttribute_Recordset)

// Field/Param Data
	//{{AFX_FIELD(TAttribute_Recordset, CRecordset)
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
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TAttribute_Recordset)
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

#endif // !defined(AFX_TATTRIBUTE_RECORDSET_H__C707E60D_8C69_4CE3_8F79_05CE0D9D65CF__INCLUDED_)
