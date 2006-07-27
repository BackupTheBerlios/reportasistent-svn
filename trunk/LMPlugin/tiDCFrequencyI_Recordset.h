#if !defined(AFX_TIDCFREQUENCYI_RECORDSET_H__927F671F_3600_403B_8457_CA50A10D1DA5__INCLUDED_)
#define AFX_TIDCFREQUENCYI_RECORDSET_H__927F671F_3600_403B_8457_CA50A10D1DA5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// tiDCFrequencyI_Recordset.h : header file
//
#include "afxdb.h"
/////////////////////////////////////////////////////////////////////////////
// tiDCFrequencyI_Recordset recordset

class tiDCFrequencyI_Recordset : public CRecordset
{
public:
	tiDCFrequencyI_Recordset(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(tiDCFrequencyI_Recordset)

// Field/Param Data
	//{{AFX_FIELD(tiDCFrequencyI_Recordset, CRecordset)
	long	m_DCFrequencyIID;
	long	m_HypothesisDCID;
	long	m_CedentTypeID;
	long	m_TaskID;
	long	m_Col;
	long	m_Frequency;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(tiDCFrequencyI_Recordset)
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

#endif // !defined(AFX_TIDCFREQUENCYI_RECORDSET_H__927F671F_3600_403B_8457_CA50A10D1DA5__INCLUDED_)
