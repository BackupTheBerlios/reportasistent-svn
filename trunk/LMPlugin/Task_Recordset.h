#if !defined(AFX_TASK_RECORDSET_H__51C4BB60_FF7C_4A60_AB60_49A60DDF7EF4__INCLUDED_)
#define AFX_TASK_RECORDSET_H__51C4BB60_FF7C_4A60_AB60_49A60DDF7EF4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Task_Recordset.h : header file
//
#include "afxdb.h"
/////////////////////////////////////////////////////////////////////////////
// Task_Recordset recordset

/**
 * This class was designed to retrieve all the Tasks from the given data source.
 *
 * @author Generated by VS.
 */
class Task_Recordset : public CRecordset
{
public:
	Task_Recordset(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(Task_Recordset)

// Field/Param Data
	//{{AFX_FIELD(Task_Recordset, CRecordset)
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
	long	m_MatrixID2;
	CString	m_Name2;
	BOOL	m_Initialised;
	long	m_RecordCount;
	CString	m_Notice2;
	long	m_wSavedCountUsed;
	long	m_TaskSubTypeID2;
	CString	m_Name3;
	CString	m_ShortName;
	long	m_Ord;
	CString	m_Notice3;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Task_Recordset)
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

#endif // !defined(AFX_TASK_RECORDSET_H__51C4BB60_FF7C_4A60_AB60_49A60DDF7EF4__INCLUDED_)
