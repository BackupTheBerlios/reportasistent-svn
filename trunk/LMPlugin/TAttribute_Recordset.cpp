// TAttribute_Recordset.cpp : implementation file
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
#include "TAttribute_Recordset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// TAttribute_Recordset

IMPLEMENT_DYNAMIC(TAttribute_Recordset, CRecordset)

TAttribute_Recordset::TAttribute_Recordset(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(TAttribute_Recordset)
	m_AttributeID = 0;
	m_Name = _T("");
	m_MatrixID = 0;
	m_AttributeSubTypeID = 0;
	m_ValueSubTypeID = 0;
	m_Derived = FALSE;
	m_Formula = _T("");
	m_MCPosition = 0;
	m_MCLength = 0;
	m_MCDelimiter = _T("");
	m_PrimaryKeyPosition = 0;
	m_ValueMin = 0.0;
	m_ValueMax = 0.0;
	m_ValueAvg = 0.0;
	m_ValueModus = 0.0;
	m_ValueVariability = 0.0;
	m_Notice = _T("");
	m_wSavedCountUsed = 0;
	m_MatrixID2 = 0;
	m_Name2 = _T("");
	m_Initialised = FALSE;
	m_RecordCount = 0;
	m_Notice2 = _T("");
	m_wSavedCountUsed2 = 0;
	m_AttributeSubTypeID2 = 0;
	m_Name3 = _T("");
	m_ShortName = _T("");
	m_Ord = 0;
	m_Notice3 = _T("");
	m_nFields = 29;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

CString TAttribute_Recordset::GetDefaultSQL()
{
	return _T("[tmAttribute],[tmMatrix],[tsAttributeSubType]");
}

void TAttribute_Recordset::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(TAttribute_Recordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[AttributeID]"), m_AttributeID);
	RFX_Text(pFX, _T("[tmAttribute].[Name]"), m_Name);
	RFX_Long(pFX, _T("[tmAttribute].[MatrixID]"), m_MatrixID);
	RFX_Long(pFX, _T("[tmAttribute].[AttributeSubTypeID]"), m_AttributeSubTypeID);
	RFX_Long(pFX, _T("[ValueSubTypeID]"), m_ValueSubTypeID);
	RFX_Bool(pFX, _T("[Derived]"), m_Derived);
	RFX_Text(pFX, _T("[Formula]"), m_Formula);
	RFX_Long(pFX, _T("[MCPosition]"), m_MCPosition);
	RFX_Long(pFX, _T("[MCLength]"), m_MCLength);
	RFX_Text(pFX, _T("[MCDelimiter]"), m_MCDelimiter);
	RFX_Long(pFX, _T("[PrimaryKeyPosition]"), m_PrimaryKeyPosition);
	RFX_Double(pFX, _T("[ValueMin]"), m_ValueMin);
	RFX_Double(pFX, _T("[ValueMax]"), m_ValueMax);
	RFX_Double(pFX, _T("[ValueAvg]"), m_ValueAvg);
	RFX_Double(pFX, _T("[ValueModus]"), m_ValueModus);
	RFX_Double(pFX, _T("[ValueVariability]"), m_ValueVariability);
	RFX_Text(pFX, _T("[tmAttribute].[Notice]"), m_Notice);
	RFX_Long(pFX, _T("[tmAttribute].[wSavedCountUsed]"), m_wSavedCountUsed);
	RFX_Long(pFX, _T("[tmMatrix].[MatrixID]"), m_MatrixID2);
	RFX_Text(pFX, _T("[tmMatrix].[Name]"), m_Name2);
	RFX_Bool(pFX, _T("[Initialised]"), m_Initialised);
	RFX_Long(pFX, _T("[RecordCount]"), m_RecordCount);
	RFX_Text(pFX, _T("[tmMatrix].[Notice]"), m_Notice2);
	RFX_Long(pFX, _T("[tmMatrix].[wSavedCountUsed]"), m_wSavedCountUsed2);
	RFX_Long(pFX, _T("[tsAttributeSubType].[AttributeSubTypeID]"), m_AttributeSubTypeID2);
	RFX_Text(pFX, _T("[tsAttributeSubType].[Name]"), m_Name3);
	RFX_Text(pFX, _T("[ShortName]"), m_ShortName);
	RFX_Long(pFX, _T("[Ord]"), m_Ord);
	RFX_Text(pFX, _T("[tsAttributeSubType].[Notice]"), m_Notice3);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// TAttribute_Recordset diagnostics

#ifdef _DEBUG
void TAttribute_Recordset::AssertValid() const
{
	CRecordset::AssertValid();
}

void TAttribute_Recordset::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
