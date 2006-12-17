// TKLCategory_Recordset.cpp : implementation file
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
#include "TKLCategory_Recordset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// TKLCategory_Recordset

IMPLEMENT_DYNAMIC(TKLCategory_Recordset, CRecordset)

TKLCategory_Recordset::TKLCategory_Recordset(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(TKLCategory_Recordset)
	m_KLLiteralDID = 0;
	m_KLCedentDID = 0;
	m_QuantityID = 0;
	m_Ord = 0;
	m_Notice = _T("");
	m_CategoryID = 0;
	m_Name = _T("");
	m_QuantityID2 = 0;
	m_CategorySubTypeID = 0;
	m_BoolTypeID = 0;
	m_XCategory = FALSE;
	m_IncludeNULL = FALSE;
	m_Ord2 = 0;
	m_Notice2 = _T("");
	m_wSavedCountUsed = 0;
	m_QuantityID3 = 0;
	m_Name2 = _T("");
	m_ShortName = _T("");
	m_ShowName = FALSE;
	m_AttributeID = 0;
	m_ItemShift = 0;
	m_ParentGroupID = 0;
	m_wSavedCountUsed2 = 0;
	m_wUpdateVer = 0;
	m_UserID = 0;
	m_Notice3 = _T("");
	m_nFields = 26;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

CString TKLCategory_Recordset::GetDefaultSQL()
{
	return _T("[tdKLLiteralD],[tmCategory],[tmQuantity]");
}

void TKLCategory_Recordset::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(TKLCategory_Recordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[KLLiteralDID]"), m_KLLiteralDID);
	RFX_Long(pFX, _T("[KLCedentDID]"), m_KLCedentDID);
	RFX_Long(pFX, _T("[tdKLLiteralD].[QuantityID]"), m_QuantityID);
	RFX_Long(pFX, _T("[tdKLLiteralD].[Ord]"), m_Ord);
	RFX_Text(pFX, _T("[tdKLLiteralD].[Notice]"), m_Notice);
	RFX_Long(pFX, _T("[CategoryID]"), m_CategoryID);
	RFX_Text(pFX, _T("[tmCategory].[Name]"), m_Name);
	RFX_Long(pFX, _T("[tmCategory].[QuantityID]"), m_QuantityID2);
	RFX_Long(pFX, _T("[CategorySubTypeID]"), m_CategorySubTypeID);
	RFX_Long(pFX, _T("[BoolTypeID]"), m_BoolTypeID);
	RFX_Bool(pFX, _T("[XCategory]"), m_XCategory);
	RFX_Bool(pFX, _T("[IncludeNULL]"), m_IncludeNULL);
	RFX_Long(pFX, _T("[tmCategory].[Ord]"), m_Ord2);
	RFX_Text(pFX, _T("[tmCategory].[Notice]"), m_Notice2);
	RFX_Long(pFX, _T("[tmCategory].[wSavedCountUsed]"), m_wSavedCountUsed);
	RFX_Long(pFX, _T("[tmQuantity].[QuantityID]"), m_QuantityID3);
	RFX_Text(pFX, _T("[tmQuantity].[Name]"), m_Name2);
	RFX_Text(pFX, _T("[ShortName]"), m_ShortName);
	RFX_Bool(pFX, _T("[ShowName]"), m_ShowName);
	RFX_Long(pFX, _T("[AttributeID]"), m_AttributeID);
	RFX_Long(pFX, _T("[ItemShift]"), m_ItemShift);
	RFX_Long(pFX, _T("[ParentGroupID]"), m_ParentGroupID);
	RFX_Long(pFX, _T("[tmQuantity].[wSavedCountUsed]"), m_wSavedCountUsed2);
	RFX_Long(pFX, _T("[wUpdateVer]"), m_wUpdateVer);
	RFX_Long(pFX, _T("[UserID]"), m_UserID);
	RFX_Text(pFX, _T("[tmQuantity].[Notice]"), m_Notice3);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// TKLCategory_Recordset diagnostics

#ifdef _DEBUG
void TKLCategory_Recordset::AssertValid() const
{
	CRecordset::AssertValid();
}

void TKLCategory_Recordset::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
