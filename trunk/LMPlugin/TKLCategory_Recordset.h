#if !defined(AFX_TKLCATEGORY_RECORDSET_H__9E217D79_F0B5_4C1F_8A5D_7E5880849E0E__INCLUDED_)
#define AFX_TKLCATEGORY_RECORDSET_H__9E217D79_F0B5_4C1F_8A5D_7E5880849E0E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TKLCategory_Recordset.h : header file
//
#include "afxdb.h"
/////////////////////////////////////////////////////////////////////////////
// TKLCategory_Recordset recordset

class TKLCategory_Recordset : public CRecordset
{
public:
	TKLCategory_Recordset(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(TKLCategory_Recordset)

// Field/Param Data
	//{{AFX_FIELD(TKLCategory_Recordset, CRecordset)
	long	m_KLLiteralDID;
	long	m_KLCedentDID;
	long	m_QuantityID;
	long	m_Ord;
	CString	m_Notice;
	long	m_CategoryID;
	CString	m_Name;
	long	m_QuantityID2;
	long	m_CategorySubTypeID;
	long	m_BoolTypeID;
	BOOL	m_XCategory;
	BOOL	m_IncludeNULL;
	long	m_Ord2;
	CString	m_Notice2;
	long	m_wSavedCountUsed;
	long	m_QuantityID3;
	CString	m_Name2;
	CString	m_ShortName;
	BOOL	m_ShowName;
	long	m_AttributeID;
	long	m_ItemShift;
	long	m_ParentGroupID;
	long	m_wSavedCountUsed2;
	long	m_wUpdateVer;
	long	m_UserID;
	CString	m_Notice3;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TKLCategory_Recordset)
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

#endif // !defined(AFX_TKLCATEGORY_RECORDSET_H__9E217D79_F0B5_4C1F_8A5D_7E5880849E0E__INCLUDED_)
