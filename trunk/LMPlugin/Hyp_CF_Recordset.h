#if !defined(AFX_HYP_CF_RECORDSET_H__4949ADC5_A259_47DC_821E_3C08BA75EC26__INCLUDED_)
#define AFX_HYP_CF_RECORDSET_H__4949ADC5_A259_47DC_821E_3C08BA75EC26__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Hyp_CF_Recordset.h : header file
//
#include "afxdb.h"
/////////////////////////////////////////////////////////////////////////////
// Hyp_CF_Recordset recordset

class Hyp_CF_Recordset : public CRecordset
{
public:
	Hyp_CF_Recordset(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(Hyp_CF_Recordset)

// Field/Param Data
	//{{AFX_FIELD(Hyp_CF_Recordset, CRecordset)
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
	long	m_CFLiteralDID;
	long	m_CFCedentDID;
	long	m_QuantityID;
	long	m_Ord;
	CString	m_Notice2;
	long	m_HypothesisCFID;
	long	m_HypothesisID;
	long	m_TaskID2;
	long	m_Cols;
	long	m_CFLiteralDID2;
	long	m_QuantityUpdateVer;
	long	m_MatrixID2;
	CString	m_Name2;
	BOOL	m_Initialised;
	long	m_RecordCount;
	CString	m_Notice3;
	long	m_wSavedCountUsed;
	long	m_QuantityID2;
	CString	m_Name3;
	CString	m_ShortName;
	BOOL	m_ShowName;
	long	m_AttributeID;
	long	m_ItemShift;
	long	m_ParentGroupID;
	long	m_wSavedCountUsed2;
	long	m_wUpdateVer;
	long	m_UserID2;
	CString	m_Notice4;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Hyp_CF_Recordset)
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

#endif // !defined(AFX_HYP_CF_RECORDSET_H__4949ADC5_A259_47DC_821E_3C08BA75EC26__INCLUDED_)
