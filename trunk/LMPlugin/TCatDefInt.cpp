// TCatDefInt.cpp : implementation file
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
#include "TCatDefInt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// TCatDefInt

IMPLEMENT_DYNAMIC(TCatDefInt, CRecordset)

TCatDefInt::TCatDefInt(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(TCatDefInt)
	m_IntervalID = 0;
	m_CategoryID = 0;
	m_FromValueID = 0;
	m_ToValueID = 0;
	m_LeftBracketTypeID = 0;
	m_RightBracketTypeID = 0;
	m_ValueID = 0;
	m_ValueSubTypeID = 0;
	m_ValueLong = 0;
	m_ValueFloat = 0.0;
	m_ValueString = _T("");
	m_ValueBool = FALSE;
	m_InfinityTypeID = 0;
	m_IsNULL = FALSE;
	m_BracketTypeID = 0;
	m_Name = _T("");
	m_ShortName = _T("");
	m_Ord = 0;
	m_LeftBracket = _T("");
	m_RightBracket = _T("");
	m_Notice = _T("");
	m_ValueSubTypeID2 = 0;
	m_Name2 = _T("");
	m_ShortName2 = _T("");
	m_Cardinal = FALSE;
	m_Ord2 = 0;
	m_Notice2 = _T("");
	m_nFields = 28;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

CString TCatDefInt::GetDefaultSQL()
{
	return _T("[tmInterval],[tmValue],[tsBracketType],[tsValueSubType]");
}

void TCatDefInt::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(TCatDefInt)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[IntervalID]"), m_IntervalID);
	RFX_Long(pFX, _T("[CategoryID]"), m_CategoryID);
	RFX_Long(pFX, _T("[FromValueID]"), m_FromValueID);
	RFX_Long(pFX, _T("[ToValueID]"), m_ToValueID);
	RFX_Long(pFX, _T("[LeftBracketTypeID]"), m_LeftBracketTypeID);
	RFX_Long(pFX, _T("[RightBracketTypeID]"), m_RightBracketTypeID);
	RFX_Long(pFX, _T("[ValueID]"), m_ValueID);
	RFX_Long(pFX, _T("[tmValue].[ValueSubTypeID]"), m_ValueSubTypeID);
	RFX_Long(pFX, _T("[ValueLong]"), m_ValueLong);
	RFX_Double(pFX, _T("[ValueFloat]"), m_ValueFloat);
	RFX_Text(pFX, _T("[ValueString]"), m_ValueString);
	RFX_Bool(pFX, _T("[ValueBool]"), m_ValueBool);
	RFX_Date(pFX, _T("[ValueDate]"), m_ValueDate);
	RFX_Long(pFX, _T("[InfinityTypeID]"), m_InfinityTypeID);
	RFX_Bool(pFX, _T("[IsNULL]"), m_IsNULL);
	RFX_Long(pFX, _T("[BracketTypeID]"), m_BracketTypeID);
	RFX_Text(pFX, _T("[tsBracketType].[Name]"), m_Name);
	RFX_Text(pFX, _T("[tsBracketType].[ShortName]"), m_ShortName);
	RFX_Long(pFX, _T("[tsBracketType].[Ord]"), m_Ord);
	RFX_Text(pFX, _T("[LeftBracket]"), m_LeftBracket);
	RFX_Text(pFX, _T("[RightBracket]"), m_RightBracket);
	RFX_Text(pFX, _T("[tsBracketType].[Notice]"), m_Notice);
	RFX_Long(pFX, _T("[tsValueSubType].[ValueSubTypeID]"), m_ValueSubTypeID2);
	RFX_Text(pFX, _T("[tsValueSubType].[Name]"), m_Name2);
	RFX_Text(pFX, _T("[tsValueSubType].[ShortName]"), m_ShortName2);
	RFX_Bool(pFX, _T("[Cardinal]"), m_Cardinal);
	RFX_Long(pFX, _T("[tsValueSubType].[Ord]"), m_Ord2);
	RFX_Text(pFX, _T("[tsValueSubType].[Notice]"), m_Notice2);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// TCatDefInt diagnostics

#ifdef _DEBUG
void TCatDefInt::AssertValid() const
{
	CRecordset::AssertValid();
}

void TCatDefInt::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
