#if !defined(AFX_TICFFREQUENCYI_RECORDSET_H__0E630C3A_01A3_4492_A522_52597BF6BE37__INCLUDED_)
#define AFX_TICFFREQUENCYI_RECORDSET_H__0E630C3A_01A3_4492_A522_52597BF6BE37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// tiCFFrequencyI_Recordset.h : header file
//
#include "afxdb.h"
/////////////////////////////////////////////////////////////////////////////
// tiCFFrequencyI_Recordset recordset

class tiCFFrequencyI_Recordset : public CRecordset
{
public:
	tiCFFrequencyI_Recordset(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(tiCFFrequencyI_Recordset)

// Field/Param Data
	//{{AFX_FIELD(tiCFFrequencyI_Recordset, CRecordset)
	long	m_CFFrequencyIID;
	long	m_HypothesisCFID;
	long	m_Col;
	long	m_Frequency;
	long	m_TaskID;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(tiCFFrequencyI_Recordset)
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

#endif // !defined(AFX_TICFFREQUENCYI_RECORDSET_H__0E630C3A_01A3_4492_A522_52597BF6BE37__INCLUDED_)
