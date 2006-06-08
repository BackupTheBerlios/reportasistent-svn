#if !defined(AFX_TKLLITERAL_H__7D2019F7_6232_4DCB_9A30_FD277FA93BBD__INCLUDED_)
#define AFX_TKLLITERAL_H__7D2019F7_6232_4DCB_9A30_FD277FA93BBD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TKLLiteral.h : header file
//
#ifndef WINVER
#define WINVER 0x0400
#endif
#include "afxdb.h"
/////////////////////////////////////////////////////////////////////////////
// TKLLiteral recordset

class TKLLiteral : public CRecordset
{
public:
	TKLLiteral(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(TKLLiteral)

// Field/Param Data
	//{{AFX_FIELD(TKLLiteral, CRecordset)
	long	m_KLLiteralDID;
	long	m_KLCedentDID;
	long	m_QuantityID;
	long	m_Ord;
	CString	m_Notice;
	long	m_AttributeID;
	CString	m_Name;
	long	m_MatrixID;
	long	m_AttributeSubTypeID;
	long	m_ValueSubTypeID;
	BOOL	m_Derived;
	CString	m_Formula;
	long	m_MCPosition;
	long	m_MCLength;
	CString	m_MCDelimiter;
	long	m_PrimaryKeyPosition;
	double	m_ValueMin;
	double	m_ValueMax;
	double	m_ValueAvg;
	double	m_ValueModus;
	double	m_ValueVariability;
	CString	m_Notice2;
	long	m_wSavedCountUsed;
	long	m_QuantityID2;
	CString	m_Name2;
	CString	m_ShortName;
	BOOL	m_ShowName;
	long	m_AttributeID2;
	long	m_ItemShift;
	long	m_ParentGroupID;
	long	m_wSavedCountUsed2;
	long	m_wUpdateVer;
	long	m_UserID;
	CString	m_Notice3;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TKLLiteral)
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

#endif // !defined(AFX_TKLLITERAL_H__7D2019F7_6232_4DCB_9A30_FD277FA93BBD__INCLUDED_)
