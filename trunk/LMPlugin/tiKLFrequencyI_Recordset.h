#if !defined(AFX_TIKLFREQUENCYI_RECORDSET_H__4D883F02_1E1A_4A85_92BB_814F0EDB4B80__INCLUDED_)
#define AFX_TIKLFREQUENCYI_RECORDSET_H__4D883F02_1E1A_4A85_92BB_814F0EDB4B80__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// tiKLFrequencyI_Recordset.h : header file
//
#include "afxdb.h"
/////////////////////////////////////////////////////////////////////////////
// tiKLFrequencyI_Recordset recordset

class tiKLFrequencyI_Recordset : public CRecordset
{
public:
	tiKLFrequencyI_Recordset(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(tiKLFrequencyI_Recordset)

// Field/Param Data
	//{{AFX_FIELD(tiKLFrequencyI_Recordset, CRecordset)
	long	m_KLFrequencyIID;
	long	m_HypothesisKLID;
	long	m_Row;
	long	m_Col;
	long	m_Frequency;
	long	m_TaskID;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(tiKLFrequencyI_Recordset)
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

#endif // !defined(AFX_TIKLFREQUENCYI_RECORDSET_H__4D883F02_1E1A_4A85_92BB_814F0EDB4B80__INCLUDED_)
