#if !defined(AFX_TIHYPOTHESIS_RECORDSET_H__F5C08499_6880_4695_A958_4C7A160AAB98__INCLUDED_)
#define AFX_TIHYPOTHESIS_RECORDSET_H__F5C08499_6880_4695_A958_4C7A160AAB98__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// tiHypothesis_Recordset.h : header file
//
#include "afxdb.h"
/////////////////////////////////////////////////////////////////////////////
// tiHypothesis_Recordset recordset

class tiHypothesis_Recordset : public CRecordset
{
public:
	tiHypothesis_Recordset(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(tiHypothesis_Recordset)

// Field/Param Data
	//{{AFX_FIELD(tiHypothesis_Recordset, CRecordset)
	long	m_HypothesisID;
	long	m_TaskID;
	long	m_FreqA;
	long	m_FreqB;
	long	m_FreqC;
	long	m_FreqD;
	double	m_Weight;
	long	m_Ord;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(tiHypothesis_Recordset)
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

#endif // !defined(AFX_TIHYPOTHESIS_RECORDSET_H__F5C08499_6880_4695_A958_4C7A160AAB98__INCLUDED_)
