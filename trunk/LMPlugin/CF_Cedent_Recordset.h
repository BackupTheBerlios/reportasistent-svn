#if !defined(AFX_CF_CEDENT_RECORDSET_H__1E06C6EE_6BAA_40C6_B0A4_B1066F8A5221__INCLUDED_)
#define AFX_CF_CEDENT_RECORDSET_H__1E06C6EE_6BAA_40C6_B0A4_B1066F8A5221__INCLUDED_

#ifndef WINVER
#define WINVER 0x0400
#endif

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CF_Cedent_Recordset.h : header file
//
#include "afxdb.h"
/////////////////////////////////////////////////////////////////////////////
// CF_Cedent_Recordset recordset

class CF_Cedent_Recordset : public CRecordset
{
public:
	CF_Cedent_Recordset(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CF_Cedent_Recordset)

// Field/Param Data
	//{{AFX_FIELD(CF_Cedent_Recordset, CRecordset)
	long	m_TaskID;
	CString	m_Name;
	long	m_TaskSubTypeID;
	long	m_TaskGroupID;
	long	m_UserID;
	long	m_MatrixID;
	long	m_ParamBASE;
	BOOL	m_ParamBASERelativ;
	BOOL	m_ReadOnly;
	BOOL	m_HypothesisGenerated;
	BOOL	m_GenerationInterrupted;
	long	m_GenerationNrOfTests;
	CTime	m_GenerationStartTime;
	long	m_GenerationTotalTime;
	CString	m_Notice;
	long	m_CFCedentDID;
	long	m_TaskID2;
	CString	m_Name2;
	long	m_CedentTypeID;
	long	m_MinLen;
	long	m_MaxLen;
	CString	m_Notice2;
	long	m_Ord;
	long	m_MatrixID2;
	CString	m_Name3;
	BOOL	m_Initialised;
	long	m_RecordCount;
	CString	m_Notice3;
	long	m_wSavedCountUsed;
	long	m_CedentTypeID2;
	CString	m_Name4;
	CString	m_ShortName;
	long	m_Ord2;
	CString	m_Notice4;
	long	m_TaskSubTypeID2;
	CString	m_Name5;
	CString	m_ShortName2;
	long	m_Ord3;
	CString	m_Notice5;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CF_Cedent_Recordset)
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

#endif // !defined(AFX_CF_CEDENT_RECORDSET_H__1E06C6EE_6BAA_40C6_B0A4_B1066F8A5221__INCLUDED_)