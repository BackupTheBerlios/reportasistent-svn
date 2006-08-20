#if !defined(AFX_TIDKFREQUENCYI_RECORDSET_H__24CD6824_5DAA_4458_9ACA_C84272DB1A69__INCLUDED_)
#define AFX_TIDKFREQUENCYI_RECORDSET_H__24CD6824_5DAA_4458_9ACA_C84272DB1A69__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// tiDKFrequencyI_Recordset.h : header file
//
#include "afxdb.h"
/////////////////////////////////////////////////////////////////////////////
// tiDKFrequencyI_Recordset recordset

class tiDKFrequencyI_Recordset : public CRecordset
{
public:
	tiDKFrequencyI_Recordset(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(tiDKFrequencyI_Recordset)

// Field/Param Data
	//{{AFX_FIELD(tiDKFrequencyI_Recordset, CRecordset)
	long	m_DKFrequencyIID;
	long	m_HypothesisDKID;
	long	m_CedentTypeID;
	long	m_Row;
	long	m_Col;
	long	m_Frequency;
	long	m_TaskID;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(tiDKFrequencyI_Recordset)
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

#endif // !defined(AFX_TIDKFREQUENCYI_RECORDSET_H__24CD6824_5DAA_4458_9ACA_C84272DB1A69__INCLUDED_)
