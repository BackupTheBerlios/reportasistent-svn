#if !defined(AFX_TCFLITERAL_H__80D859BE_891D_4366_84CA_F731165D3218__INCLUDED_)
#define AFX_TCFLITERAL_H__80D859BE_891D_4366_84CA_F731165D3218__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TCFLiteral.h : header file
//
#include "afxdb.h"
/////////////////////////////////////////////////////////////////////////////
// TCFLiteral recordset

class TCFLiteral : public CRecordset
{
public:
	TCFLiteral(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(TCFLiteral)

// Field/Param Data
	//{{AFX_FIELD(TCFLiteral, CRecordset)
	long	m_CFLiteralDID;
	long	m_CFCedentDID;
	long	m_QuantityID;
	long	m_Ord;
	CString	m_Notice;
	long	m_AttributeID;
	CString	m_Name;
	long	m_MatrixID;
	long	m_AttributeSubTypeID;
	long	m_ValueSubTypeID;
	BOOL	m_Derived;
	CString	m_Formula;
	long	m_MCPosition;
	long	m_MCLength;
	CString	m_MCDelimiter;
	long	m_PrimaryKeyPosition;
	double	m_ValueMin;
	double	m_ValueMax;
	double	m_ValueAvg;
	double	m_ValueModus;
	double	m_ValueVariability;
	CString	m_Notice2;
	long	m_wSavedCountUsed;
	long	m_QuantityID2;
	CString	m_Name2;
	CString	m_ShortName;
	BOOL	m_ShowName;
	long	m_AttributeID2;
	long	m_ItemShift;
	long	m_ParentGroupID;
	long	m_wSavedCountUsed2;
	long	m_wUpdateVer;
	long	m_UserID;
	CString	m_Notice3;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TCFLiteral)
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

#endif // !defined(AFX_TCFLITERAL_H__80D859BE_891D_4366_84CA_F731165D3218__INCLUDED_)
