#if !defined(AFX_TFTQUANTIFIER_RECORDSET_H__D15B4764_7A35_45CF_93B4_AA9431D85AF2__INCLUDED_)
#define AFX_TFTQUANTIFIER_RECORDSET_H__D15B4764_7A35_45CF_93B4_AA9431D85AF2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TFTQuantifier_Recordset.h : header file
//
#include "afxdb.h"
/////////////////////////////////////////////////////////////////////////////
// TFTQuantifier_Recordset recordset

class TFTQuantifier_Recordset : public CRecordset
{
public:
	TFTQuantifier_Recordset(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(TFTQuantifier_Recordset)

// Field/Param Data
	//{{AFX_FIELD(TFTQuantifier_Recordset, CRecordset)
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
	long	m_FTQuantifierID;
	long	m_TaskID2;
	long	m_FTQuantifierTypeID;
	double	m_ParamP;
	double	m_ParamAlfa;
	double	m_ParamBeta;
	double	m_ParamDelta;
	long	m_Ord;
	CString	m_Notice2;
	BOOL	m_ParamRelativ;
	long	m_MatrixID2;
	CString	m_Name2;
	BOOL	m_Initialised;
	long	m_RecordCount;
	CString	m_Notice3;
	long	m_wSavedCountUsed;
	long	m_QuantifierTypeID;
	CString	m_Name3;
	CString	m_ShortName;
	CString	m_UsedParams;
	long	m_Ord2;
	CString	m_Notice4;
	long	m_TaskSubTypeID2;
	CString	m_Name4;
	CString	m_ShortName2;
	long	m_Ord3;
	CString	m_Notice5;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TFTQuantifier_Recordset)
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

#endif // !defined(AFX_TFTQUANTIFIER_RECORDSET_H__D15B4764_7A35_45CF_93B4_AA9431D85AF2__INCLUDED_)