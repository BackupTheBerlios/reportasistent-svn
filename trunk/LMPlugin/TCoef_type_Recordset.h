#if !defined(AFX_TCOEF_TYPE_RECORDSET_H__82DC5086_CB41_4348_ADEB_B301D7DB1486__INCLUDED_)
#define AFX_TCOEF_TYPE_RECORDSET_H__82DC5086_CB41_4348_ADEB_B301D7DB1486__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TCoef_type_Recordset.h : header file
//
#include "afxdb.h"
/////////////////////////////////////////////////////////////////////////////
// TCoef_type_Recordset recordset

class TCoef_type_Recordset : public CRecordset
{
public:
	TCoef_type_Recordset(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(TCoef_type_Recordset)

// Field/Param Data
	//{{AFX_FIELD(TCoef_type_Recordset, CRecordset)
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
	long	m_CoefficientTypeID2;
	CString	m_Name;
	CString	m_ShortName;
	long	m_Ord2;
	CString	m_Notice2;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TCoef_type_Recordset)
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

#endif // !defined(AFX_TCOEF_TYPE_RECORDSET_H__82DC5086_CB41_4348_ADEB_B301D7DB1486__INCLUDED_)
