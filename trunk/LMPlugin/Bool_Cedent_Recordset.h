#if !defined(AFX_BOOL_CEDENT_RECORDSET_H__9A726ED7_F7BC_4AD5_8D18_403C5394BF82__INCLUDED_)
#define AFX_BOOL_CEDENT_RECORDSET_H__9A726ED7_F7BC_4AD5_8D18_403C5394BF82__INCLUDED_

#ifndef WINVER
#define WINVER 0x0400
#endif


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Bool_Cedent_Recordset.h : header file
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
// Bool_Cedent_Recordset recordset

/**
 * This class was designed to retrieve all the boolean cedents from the given data source.
 *
 * @author : Generted by VS.
 */
class Bool_Cedent_Recordset : public CRecordset
{
public:
	Bool_Cedent_Recordset(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(Bool_Cedent_Recordset)

// Field/Param Data
	//{{AFX_FIELD(Bool_Cedent_Recordset, CRecordset)
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
	long	m_LiteralDID;
	long	m_CedentDID2;
	long	m_QuantityID;
	long	m_CategoryID;
	long	m_LiteralTypeID;
	long	m_GaceTypeID;
	long	m_EquivalenceClassID;
	long	m_CoefficientTypeID;
	long	m_MinLen2;
	long	m_MaxLen2;
	long	m_Ord2;
	CString	m_Notice3;
	long	m_AttributeID;
	CString	m_Name3;
	long	m_MatrixID2;
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
	CString	m_Notice4;
	long	m_wSavedCountUsed;
	long	m_MatrixID3;
	CString	m_Name4;
	BOOL	m_Initialised;
	long	m_RecordCount;
	CString	m_Notice5;
	long	m_wSavedCountUsed2;
	long	m_QuantityID2;
	CString	m_Name5;
	CString	m_ShortName;
	BOOL	m_ShowName;
	long	m_AttributeID2;
	long	m_ItemShift;
	long	m_ParentGroupID;
	long	m_wSavedCountUsed3;
	long	m_wUpdateVer;
	long	m_UserID2;
	CString	m_Notice6;
	long	m_CedentTypeID2;
	CString	m_Name6;
	CString	m_ShortName2;
	long	m_Ord3;
	CString	m_Notice7;
	long	m_CoefficientTypeID2;
	CString	m_Name7;
	CString	m_ShortName3;
	long	m_Ord4;
	CString	m_Notice8;
	long	m_GaceTypeID2;
	CString	m_Name8;
	CString	m_ShortName4;
	long	m_Ord5;
	CString	m_Notice9;
	long	m_LiteralTypeID2;
	CString	m_Name9;
	CString	m_ShortName5;
	long	m_Ord6;
	CString	m_Notice10;
	long	m_TaskSubTypeID2;
	CString	m_Name10;
	CString	m_ShortName6;
	long	m_Ord7;
	CString	m_Notice11;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Bool_Cedent_Recordset)
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

#endif // !defined(AFX_BOOL_CEDENT_RECORDSET_H__9A726ED7_F7BC_4AD5_8D18_403C5394BF82__INCLUDED_)
