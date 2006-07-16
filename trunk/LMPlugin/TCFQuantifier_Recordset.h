#if !defined(AFX_TCFQUANTIFIER_RECORDSET_H__C4D2FD9F_E538_404B_8CA9_CEEBF3568B59__INCLUDED_)
#define AFX_TCFQUANTIFIER_RECORDSET_H__C4D2FD9F_E538_404B_8CA9_CEEBF3568B59__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TCFQuantifier_Recordset.h : header file
//
#include "afxdb.h"
/////////////////////////////////////////////////////////////////////////////
// TCFQuantifier_Recordset recordset

class TCFQuantifier_Recordset : public CRecordset
{
public:
	TCFQuantifier_Recordset(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(TCFQuantifier_Recordset)

// Field/Param Data
	//{{AFX_FIELD(TCFQuantifier_Recordset, CRecordset)
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
	long	m_CFQuantifierID;
	long	m_TaskID2;
	long	m_CFQuantifierTypeID;
	long	m_FromCol;
	long	m_ToCol;
	long	m_CompareTypeID;
	double	m_ValuePar;
	long	m_CFQuantifierValueTypeID;
	double	m_Threshold;
	CString	m_Formula;
	long	m_Ord;
	CString	m_Notice2;
	long	m_MatrixID2;
	CString	m_Name2;
	BOOL	m_Initialised;
	long	m_RecordCount;
	CString	m_Notice3;
	long	m_wSavedCountUsed;
	long	m_CFQuantifierTypeID2;
	CString	m_Name3;
	CString	m_ShortName;
	long	m_Ord2;
	CString	m_Notice4;
	long	m_CFQuantifierValueTypeID2;
	CString	m_Name4;
	CString	m_ShortName2;
	long	m_Ord3;
	CString	m_Notice5;
	long	m_CompareTypeID2;
	CString	m_Name5;
	CString	m_ShortName3;
	long	m_Ord4;
	CString	m_Notice6;
	long	m_TaskSubTypeID2;
	CString	m_Name6;
	CString	m_ShortName4;
	long	m_Ord5;
	CString	m_Notice7;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TCFQuantifier_Recordset)
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

#endif // !defined(AFX_TCFQUANTIFIER_RECORDSET_H__C4D2FD9F_E538_404B_8CA9_CEEBF3568B59__INCLUDED_)