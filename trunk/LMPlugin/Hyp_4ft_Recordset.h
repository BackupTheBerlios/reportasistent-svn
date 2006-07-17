#if !defined(AFX_HYP_4FT_RECORDSET_H__EA56CD3A_96F1_48AB_9250_9685A487C415__INCLUDED_)
#define AFX_HYP_4FT_RECORDSET_H__EA56CD3A_96F1_48AB_9250_9685A487C415__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Hyp_4ft_Recordset.h : header file
//
#include "afxdb.h"
/////////////////////////////////////////////////////////////////////////////
// Hyp_4ft_Recordset recordset

class Hyp_4ft_Recordset : public CRecordset
{
public:
	Hyp_4ft_Recordset(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(Hyp_4ft_Recordset)

// Field/Param Data
	//{{AFX_FIELD(Hyp_4ft_Recordset, CRecordset)
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
	long	m_CoefficientID;
	long	m_LiteralIID;
	long	m_CategoryID;
	long	m_TaskID2;
	long	m_HypothesisID;
	long	m_TaskID3;
	long	m_FreqA;
	long	m_FreqB;
	long	m_FreqC;
	long	m_FreqD;
	double	m_Weight;
	long	m_Ord;
	long	m_LiteralIID2;
	long	m_HypothesisID2;
	long	m_CedentTypeID;
	long	m_LiteralDID;
	long	m_ChildIndex;
	BOOL	m_Negation;
	long	m_TaskID4;
	long	m_CategoryID2;
	CString	m_Name2;
	long	m_QuantityID;
	long	m_CategorySubTypeID;
	long	m_BoolTypeID;
	BOOL	m_XCategory;
	BOOL	m_IncludeNULL;
	long	m_Ord2;
	CString	m_Notice2;
	long	m_wSavedCountUsed;
	long	m_MatrixID2;
	CString	m_Name3;
	BOOL	m_Initialised;
	long	m_RecordCount;
	CString	m_Notice3;
	long	m_wSavedCountUsed2;
	long	m_QuantityID2;
	CString	m_Name4;
	CString	m_ShortName;
	BOOL	m_ShowName;
	long	m_AttributeID;
	long	m_ItemShift;
	long	m_ParentGroupID;
	long	m_wSavedCountUsed3;
	long	m_wUpdateVer;
	long	m_UserID2;
	CString	m_Notice4;
	long	m_CedentTypeID2;
	CString	m_Name5;
	CString	m_ShortName2;
	long	m_Ord3;
	CString	m_Notice5;
	long	m_TaskSubTypeID2;
	CString	m_Name6;
	CString	m_ShortName3;
	long	m_Ord4;
	CString	m_Notice6;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Hyp_4ft_Recordset)
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

#endif // !defined(AFX_HYP_4FT_RECORDSET_H__EA56CD3A_96F1_48AB_9250_9685A487C415__INCLUDED_)
