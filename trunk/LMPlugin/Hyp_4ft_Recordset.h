#if !defined(AFX_HYP_4FT_RECORDSET_H__EC5E9217_3B6C_4CD2_8D52_E278F024EE7E__INCLUDED_)
#define AFX_HYP_4FT_RECORDSET_H__EC5E9217_3B6C_4CD2_8D52_E278F024EE7E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Hyp_4ft_Recordset.h : header file
//

/////////////////////////////////////////////////////////////////////////////
#include "afxdb.h"
// Hyp_4ft_Recordset recordset
class Hyp_4ft_Recordset : public CRecordset
{
public:
	Hyp_4ft_Recordset(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(Hyp_4ft_Recordset)

// Field/Param Data
	//{{AFX_FIELD(Hyp_4ft_Recordset, CRecordset)
	long m_HypothesisID;
	long m_MatrixID;
	CString m_MatrixName;
	long m_TaskID;
	CString m_TaskName;
	long m_FreqA;
	long m_FreqB;
	long m_FreqC;
	long m_FreqD;
	long m_LiteralID;
	CString m_CedentTypeName;
	long m_CategoryID;
	CString m_QuantityID;
	CString m_Qvalue;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Hyp_4ft_Recordset)
	public:
	//virtual CString GetDefaultConnect();    // Default connection string
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

#endif // !defined(AFX_HYP_4FT_RECORDSET_H__EC5E9217_3B6C_4CD2_8D52_E278F024EE7E__INCLUDED_)
