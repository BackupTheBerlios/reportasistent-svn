#if !defined(AFX_TEMPTY_CEDENTS_RECORDSET_H__49DB4165_DB46_43B0_987B_F2232EF244C8__INCLUDED_)
#define AFX_TEMPTY_CEDENTS_RECORDSET_H__49DB4165_DB46_43B0_987B_F2232EF244C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TEmpty_Cedents_Recordset.h : header file
//
#include "afxdb.h"
/////////////////////////////////////////////////////////////////////////////
// TEmpty_Cedents_Recordset recordset

class TEmpty_Cedents_Recordset : public CRecordset
{
public:
	TEmpty_Cedents_Recordset(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(TEmpty_Cedents_Recordset)

// Field/Param Data
	//{{AFX_FIELD(TEmpty_Cedents_Recordset, CRecordset)
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
	long	m_CedentDID;
	long	m_TaskID2;
	long	m_CedentTypeID;
	CString	m_Name2;
	long	m_Ord;
	long	m_MinLen;
	long	m_MaxLen;
	CString	m_Notice2;
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
	//{{AFX_VIRTUAL(TEmpty_Cedents_Recordset)
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

#endif // !defined(AFX_TEMPTY_CEDENTS_RECORDSET_H__49DB4165_DB46_43B0_987B_F2232EF244C8__INCLUDED_)
