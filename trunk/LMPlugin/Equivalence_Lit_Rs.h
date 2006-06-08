#if !defined(AFX_EQUIVALENCE_LIT_RS_H__875998F5_3A4E_4DBC_BD13_EE640DD6DC44__INCLUDED_)
#define AFX_EQUIVALENCE_LIT_RS_H__875998F5_3A4E_4DBC_BD13_EE640DD6DC44__INCLUDED_

#ifndef WINVER
#define WINVER 0x0400
#endif

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Equivalence_Lit_Rs.h : header file
//
#include "afxdb.h"
/////////////////////////////////////////////////////////////////////////////
// Equivalence_Lit_Rs recordset

class Equivalence_Lit_Rs : public CRecordset
{
public:
	Equivalence_Lit_Rs(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(Equivalence_Lit_Rs)

// Field/Param Data
	//{{AFX_FIELD(Equivalence_Lit_Rs, CRecordset)
	long	m_EquivalenceClassID;
	CString	m_Name;
	long	m_CedentDID;
	CString	m_Notice;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Equivalence_Lit_Rs)
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

#endif // !defined(AFX_EQUIVALENCE_LIT_RS_H__875998F5_3A4E_4DBC_BD13_EE640DD6DC44__INCLUDED_)
