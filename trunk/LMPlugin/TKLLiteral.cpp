// TKLLiteral.cpp : implementation file
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
#include "TKLLiteral.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// TKLLiteral

IMPLEMENT_DYNAMIC(TKLLiteral, CRecordset)

TKLLiteral::TKLLiteral(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(TKLLiteral)
	m_KLLiteralDID = 0;
	m_KLCedentDID = 0;
	m_QuantityID = 0;
	m_Ord = 0;
	m_Notice = _T("");
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
	m_Notice2 = _T("");
	m_wSavedCountUsed = 0;
	m_QuantityID2 = 0;
	m_Name2 = _T("");
	m_ShortName = _T("");
	m_ShowName = FALSE;
	m_AttributeID2 = 0;
	m_ItemShift = 0;
	m_ParentGroupID = 0;
	m_wSavedCountUsed2 = 0;
	m_wUpdateVer = 0;
	m_UserID = 0;
	m_Notice3 = _T("");
	m_nFields = 34;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

CString TKLLiteral::GetDefaultSQL()
{
	return _T("[tdKLLiteralD],[tmAttribute],[tmQuantity]");
}

void TKLLiteral::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(TKLLiteral)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[KLLiteralDID]"), m_KLLiteralDID);
	RFX_Long(pFX, _T("[KLCedentDID]"), m_KLCedentDID);
	RFX_Long(pFX, _T("[tdKLLiteralD].[QuantityID]"), m_QuantityID);
	RFX_Long(pFX, _T("[Ord]"), m_Ord);
	RFX_Text(pFX, _T("[tdKLLiteralD].[Notice]"), m_Notice);
	RFX_Long(pFX, _T("[tmAttribute].[AttributeID]"), m_AttributeID);
	RFX_Text(pFX, _T("[tmAttribute].[Name]"), m_Name);
	RFX_Long(pFX, _T("[MatrixID]"), m_MatrixID);
	RFX_Long(pFX, _T("[AttributeSubTypeID]"), m_AttributeSubTypeID);
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
	RFX_Text(pFX, _T("[tmAttribute].[Notice]"), m_Notice2);
	RFX_Long(pFX, _T("[tmAttribute].[wSavedCountUsed]"), m_wSavedCountUsed);
	RFX_Long(pFX, _T("[tmQuantity].[QuantityID]"), m_QuantityID2);
	RFX_Text(pFX, _T("[tmQuantity].[Name]"), m_Name2);
	RFX_Text(pFX, _T("[ShortName]"), m_ShortName);
	RFX_Bool(pFX, _T("[ShowName]"), m_ShowName);
	RFX_Long(pFX, _T("[tmQuantity].[AttributeID]"), m_AttributeID2);
	RFX_Long(pFX, _T("[ItemShift]"), m_ItemShift);
	RFX_Long(pFX, _T("[ParentGroupID]"), m_ParentGroupID);
	RFX_Long(pFX, _T("[tmQuantity].[wSavedCountUsed]"), m_wSavedCountUsed2);
	RFX_Long(pFX, _T("[wUpdateVer]"), m_wUpdateVer);
	RFX_Long(pFX, _T("[UserID]"), m_UserID);
	RFX_Text(pFX, _T("[tmQuantity].[Notice]"), m_Notice3);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// TKLLiteral diagnostics

#ifdef _DEBUG
void TKLLiteral::AssertValid() const
{
	CRecordset::AssertValid();
}

void TKLLiteral::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
