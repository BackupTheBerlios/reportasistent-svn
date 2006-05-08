#if !defined(AFX_TLIT_SCAN_RECORDSET_H__2FCDE908_8D6D_4882_A4E5_B4571617DE8E__INCLUDED_)
#define AFX_TLIT_SCAN_RECORDSET_H__2FCDE908_8D6D_4882_A4E5_B4571617DE8E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TLit_Scan_Recordset.h : header file
//
#include "afxdb.h"
/////////////////////////////////////////////////////////////////////////////
// TLit_Scan_Recordset recordset

class TLit_Scan_Recordset : public CRecordset
{
public:
	TLit_Scan_Recordset(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(TLit_Scan_Recordset)

// Field/Param Data
	//{{AFX_FIELD(TLit_Scan_Recordset, CRecordset)
	long	m_LiteralDID;
	long	m_CedentDID;
	long	m_QuantityID;
	long	m_CategoryID;
	long	m_LiteralTypeID;
	long	m_GaceTypeID;
	long	m_EquivalenceClassID;
	long	m_CoefficientTypeID;
	long	m_MinLen;
	long	m_MaxLen;
	long	m_Ord;
	CString	m_Notice;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TLit_Scan_Recordset)
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

#endif // !defined(AFX_TLIT_SCAN_RECORDSET_H__2FCDE908_8D6D_4882_A4E5_B4571617DE8E__INCLUDED_)
