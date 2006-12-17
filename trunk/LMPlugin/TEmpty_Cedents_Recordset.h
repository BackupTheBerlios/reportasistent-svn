#if !defined(AFX_TEMPTY_CEDENTS_RECORDSET_H__49DB4165_DB46_43B0_987B_F2232EF244C8__INCLUDED_)
#define AFX_TEMPTY_CEDENTS_RECORDSET_H__49DB4165_DB46_43B0_987B_F2232EF244C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TEmpty_Cedents_Recordset.h : header file
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
#ifndef WINVER
#define WINVER 0x0400
#endif
#include "afxdb.h"
/////////////////////////////////////////////////////////////////////////////
// TEmpty_Cedents_Recordset recordset

/**
 * This class was designed to retrieve all the empty boolean subcedents in the given data source.
 *
 * @author Generated by VS.
 */
class TEmpty_Cedents_Recordset : public CRecordset
{
public:
	TEmpty_Cedents_Recordset(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(TEmpty_Cedents_Recordset)

// Field/Param Data
	//{{AFX_FIELD(TEmpty_Cedents_Recordset, CRecordset)
	long	m_TaskID;
	CString	m_Name;
	long	m_TaskSubTypeID;
	long	m_TaskGroupID;
	long	m_UserID;
	long	m_MatrixID;
	long	m_ParamBASE;
	BOOL	m_ParamBASERelativ;
	BOOL	m_ReadOnly;
	BOOL	m_HypothesisGenerated;
	BOOL	m_GenerationInterrupted;
	long	m_GenerationNrOfTests;
	CTime	m_GenerationStartTime;
	long	m_GenerationTotalTime;
	CString	m_Notice;
	long	m_CedentDID;
	long	m_TaskID2;
	long	m_CedentTypeID;
	CString	m_Name2;
	long	m_Ord;
	long	m_MinLen;
	long	m_MaxLen;
	CString	m_Notice2;
	long	m_MatrixID2;
	CString	m_Name3;
	BOOL	m_Initialised;
	long	m_RecordCount;
	CString	m_Notice3;
	long	m_wSavedCountUsed;
	long	m_CedentTypeID2;
	CString	m_Name4;
	CString	m_ShortName;
	long	m_Ord2;
	CString	m_Notice4;
	long	m_TaskSubTypeID2;
	CString	m_Name5;
	CString	m_ShortName2;
	long	m_Ord3;
	CString	m_Notice5;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TEmpty_Cedents_Recordset)
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

#endif // !defined(AFX_TEMPTY_CEDENTS_RECORDSET_H__49DB4165_DB46_43B0_987B_F2232EF244C8__INCLUDED_)
