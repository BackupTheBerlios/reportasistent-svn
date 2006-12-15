#if !defined(AFX_TLIT_SCAN_RECORDSET_H__2FCDE908_8D6D_4882_A4E5_B4571617DE8E__INCLUDED_)
#define AFX_TLIT_SCAN_RECORDSET_H__2FCDE908_8D6D_4882_A4E5_B4571617DE8E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TLit_Scan_Recordset.h : header file
//
/*
This file is part of LM Report Asistent.

Authors: Jan Dedek, Jan Kodym, Martin Chrz, Iva Bartunkova

LM Report Asistent is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

Foobar is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Foobar; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#ifndef WINVER
#define WINVER 0x0400
#endif
#include "afxdb.h"
/////////////////////////////////////////////////////////////////////////////
// TLit_Scan_Recordset recordset

/**
 * This class was designed to retrieve the number of literals in the given subcedent.
 *
 * @author Generated by VS.
 */
class TLit_Scan_Recordset : public CRecordset
{
public:
	TLit_Scan_Recordset(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(TLit_Scan_Recordset)

// Field/Param Data
	//{{AFX_FIELD(TLit_Scan_Recordset, CRecordset)
	long	m_LiteralDID;
	long	m_CedentDID;
	long	m_QuantityID;
	long	m_CategoryID;
	long	m_LiteralTypeID;
	long	m_GaceTypeID;
	long	m_EquivalenceClassID;
	long	m_CoefficientTypeID;
	long	m_MinLen;
	long	m_MaxLen;
	long	m_Ord;
	CString	m_Notice;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TLit_Scan_Recordset)
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

#endif // !defined(AFX_TLIT_SCAN_RECORDSET_H__2FCDE908_8D6D_4882_A4E5_B4571617DE8E__INCLUDED_)
