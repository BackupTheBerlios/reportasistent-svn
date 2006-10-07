#if !defined(AFX_HYP_KL_RECORDSET_H__83D64A35_9AC2_4990_810C_9210E2899C63__INCLUDED_)
#define AFX_HYP_KL_RECORDSET_H__83D64A35_9AC2_4990_810C_9210E2899C63__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Hyp_KL_Recordset.h : header file
//
#include "afxdb.h"
/////////////////////////////////////////////////////////////////////////////
// Hyp_KL_Recordset recordset

class Hyp_KL_Recordset : public CRecordset
{
public:
	Hyp_KL_Recordset(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(Hyp_KL_Recordset)

// Field/Param Data
	//{{AFX_FIELD(Hyp_KL_Recordset, CRecordset)
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
	long	m_HypothesisKLID;
	long	m_HypothesisID;
	long	m_TaskID2;
	long	m_Rows;
	long	m_Cols;
	long	m_KLLiteralDRowID;
	long	m_KLLiteralDColID;
	long	m_QuantityRowUpdateVer;
	long	m_QuantityColUpdateVer;
	long	m_MatrixID2;
	CString	m_Name2;
	BOOL	m_Initialised;
	long	m_RecordCount;
	CString	m_Notice2;
	long	m_wSavedCountUsed;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Hyp_KL_Recordset)
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

#endif // !defined(AFX_HYP_KL_RECORDSET_H__83D64A35_9AC2_4990_810C_9210E2899C63__INCLUDED_)