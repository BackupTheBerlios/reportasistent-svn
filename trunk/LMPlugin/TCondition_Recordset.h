#if !defined(AFX_TCONDITION_RECORDSET_H__444E6A0B_7CCE_44FC_800C_1BCFA2EB11F5__INCLUDED_)
#define AFX_TCONDITION_RECORDSET_H__444E6A0B_7CCE_44FC_800C_1BCFA2EB11F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TCondition_Recordset.h : header file
//
#include "afxdb.h"
/////////////////////////////////////////////////////////////////////////////
// TCondition_Recordset recordset

class TCondition_Recordset : public CRecordset
{
public:
	TCondition_Recordset(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(TCondition_Recordset)

// Field/Param Data
	//{{AFX_FIELD(TCondition_Recordset, CRecordset)
	long	m_CoefficientID;
	long	m_LiteralIID;
	long	m_CategoryID;
	long	m_TaskID;
	long	m_LiteralIID2;
	long	m_HypothesisID;
	long	m_CedentTypeID;
	long	m_LiteralDID;
	long	m_ChildIndex;
	BOOL	m_Negation;
	long	m_TaskID2;
	long	m_CategoryID2;
	CString	m_Name;
	long	m_QuantityID;
	long	m_CategorySubTypeID;
	long	m_BoolTypeID;
	BOOL	m_XCategory;
	BOOL	m_IncludeNULL;
	long	m_Ord;
	CString	m_Notice;
	long	m_wSavedCountUsed;
	long	m_QuantityID2;
	CString	m_Name2;
	CString	m_ShortName;
	BOOL	m_ShowName;
	long	m_AttributeID;
	long	m_ItemShift;
	long	m_ParentGroupID;
	long	m_wSavedCountUsed2;
	long	m_wUpdateVer;
	long	m_UserID;
	CString	m_Notice2;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TCondition_Recordset)
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

#endif // !defined(AFX_TCONDITION_RECORDSET_H__444E6A0B_7CCE_44FC_800C_1BCFA2EB11F5__INCLUDED_)
