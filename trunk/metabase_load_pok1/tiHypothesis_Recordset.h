#if !defined(AFX_TIHYPOTHESIS_RECORDSET_H__795ED39D_0FE2_4952_82F4_F7BA57D466EB__INCLUDED_)
#define AFX_TIHYPOTHESIS_RECORDSET_H__795ED39D_0FE2_4952_82F4_F7BA57D466EB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// tiHypothesis_Recordset.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CtiHypothesis_Recordset recordset

class CtiHypothesis_Recordset : public CRecordset
{
public:
	CtiHypothesis_Recordset(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CtiHypothesis_Recordset)

// Field/Param Data
	//{{AFX_FIELD(CtiHypothesis_Recordset, CRecordset)
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
	//{{AFX_VIRTUAL(CtiHypothesis_Recordset)
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

#endif // !defined(AFX_TIHYPOTHESIS_RECORDSET_H__795ED39D_0FE2_4952_82F4_F7BA57D466EB__INCLUDED_)
