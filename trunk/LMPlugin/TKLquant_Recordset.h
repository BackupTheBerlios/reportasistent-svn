#if !defined(AFX_TKLQUANT_RECORDSET_H__9FF548B9_E5C6_4E1B_BB18_DDB18555580E__INCLUDED_)
#define AFX_TKLQUANT_RECORDSET_H__9FF548B9_E5C6_4E1B_BB18_DDB18555580E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TKLquant_Recordset.h : header file
//
/*
This file is part of LM Report Asistent.

Authors: Jan Dedek, Jan Kodym, Martin Chrz, Iva Bartunkova

LM Report Asistent is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

LM Report Asistent is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with LM Report Asistent; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include "afxdb.h"
/////////////////////////////////////////////////////////////////////////////
// TKLquant_Recordset recordset

/**
 * This class was designed to retrieve attribute name for the given KL literal.
 *
 * @author Generated by VS.
 */
class TKLquant_Recordset : public CRecordset
{
public:
	TKLquant_Recordset(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(TKLquant_Recordset)

// Field/Param Data
	//{{AFX_FIELD(TKLquant_Recordset, CRecordset)
	long	m_KLLiteralDID;
	long	m_KLCedentDID;
	long	m_QuantityID;
	long	m_Ord;
	CString	m_Notice;
	long	m_QuantityID2;
	CString	m_Name;
	CString	m_ShortName;
	BOOL	m_ShowName;
	long	m_AttributeID;
	long	m_ItemShift;
	long	m_ParentGroupID;
	long	m_wSavedCountUsed;
	long	m_wUpdateVer;
	long	m_UserID;
	CString	m_Notice2;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TKLquant_Recordset)
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

#endif // !defined(AFX_TKLQUANT_RECORDSET_H__9FF548B9_E5C6_4E1B_BB18_DDB18555580E__INCLUDED_)
