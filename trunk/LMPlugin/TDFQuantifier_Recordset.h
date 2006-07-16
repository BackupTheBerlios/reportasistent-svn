#if !defined(AFX_TDFQUANTIFIER_RECORDSET_H__08C20191_0540_4CC0_ADA1_B588A21A465C__INCLUDED_)
#define AFX_TDFQUANTIFIER_RECORDSET_H__08C20191_0540_4CC0_ADA1_B588A21A465C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TDFQuantifier_Recordset.h : header file
//
#include "afxdb.h"
/////////////////////////////////////////////////////////////////////////////
// TDFQuantifier_Recordset recordset

class TDFQuantifier_Recordset : public CRecordset
{
public:
	TDFQuantifier_Recordset(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(TDFQuantifier_Recordset)

// Field/Param Data
	//{{AFX_FIELD(TDFQuantifier_Recordset, CRecordset)
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
	long	m_DFQuantifierID;
	long	m_TaskID2;
	long	m_DFQuantifierTypeID;
	long	m_SDQuantifierSourceTypeID;
	double	m_ParamP;
	double	m_ParamAlfa;
	double	m_ParamBeta;
	double	m_ParamDelta;
	long	m_CompareTypeID;
	double	m_ValuePar;
	long	m_DFQuantifierValueTypeID;
	long	m_Ord;
	CString	m_Notice2;
	long	m_MatrixID2;
	CString	m_Name2;
	BOOL	m_Initialised;
	long	m_RecordCount;
	CString	m_Notice3;
	long	m_wSavedCountUsed;
	long	m_CompareTypeID2;
	CString	m_Name3;
	CString	m_ShortName;
	long	m_Ord2;
	CString	m_Notice4;
	long	m_DFQuantifierTypeID2;
	CString	m_Name4;
	CString	m_ShortName2;
	long	m_Ord3;
	CString	m_Notice5;
	long	m_DFQuantifierValueTypeID2;
	CString	m_Name5;
	CString	m_ShortName3;
	long	m_Ord4;
	CString	m_Notice6;
	long	m_SDQuantifierSourceTypeID2;
	CString	m_Name6;
	CString	m_ShortName4;
	long	m_Ord5;
	CString	m_Notice7;
	long	m_TaskSubTypeID2;
	CString	m_Name7;
	CString	m_ShortName5;
	long	m_Ord6;
	CString	m_Notice8;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TDFQuantifier_Recordset)
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

#endif // !defined(AFX_TDFQUANTIFIER_RECORDSET_H__08C20191_0540_4CC0_ADA1_B588A21A465C__INCLUDED_)
