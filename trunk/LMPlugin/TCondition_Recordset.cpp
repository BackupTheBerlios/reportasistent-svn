// TCondition_Recordset.cpp : implementation file
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
#include "TCondition_Recordset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// TCondition_Recordset

IMPLEMENT_DYNAMIC(TCondition_Recordset, CRecordset)

TCondition_Recordset::TCondition_Recordset(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(TCondition_Recordset)
	m_CoefficientID = 0;
	m_LiteralIID = 0;
	m_CategoryID = 0;
	m_TaskID = 0;
	m_LiteralIID2 = 0;
	m_HypothesisID = 0;
	m_CedentTypeID = 0;
	m_LiteralDID = 0;
	m_ChildIndex = 0;
	m_Negation = FALSE;
	m_TaskID2 = 0;
	m_CategoryID2 = 0;
	m_Name = _T("");
	m_QuantityID = 0;
	m_CategorySubTypeID = 0;
	m_BoolTypeID = 0;
	m_XCategory = FALSE;
	m_IncludeNULL = FALSE;
	m_Ord = 0;
	m_Notice = _T("");
	m_wSavedCountUsed = 0;
	m_QuantityID2 = 0;
	m_Name2 = _T("");
	m_ShortName = _T("");
	m_ShowName = FALSE;
	m_AttributeID = 0;
	m_ItemShift = 0;
	m_ParentGroupID = 0;
	m_wSavedCountUsed2 = 0;
	m_wUpdateVer = 0;
	m_UserID = 0;
	m_Notice2 = _T("");
	m_nFields = 32;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

CString TCondition_Recordset::GetDefaultSQL()
{
	return _T("[tiCoefficient],[tiLiteralI],[tmCategory],[tmQuantity]");
}

void TCondition_Recordset::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(TCondition_Recordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[CoefficientID]"), m_CoefficientID);
	RFX_Long(pFX, _T("[tiCoefficient].[LiteralIID]"), m_LiteralIID);
	RFX_Long(pFX, _T("[tiCoefficient].[CategoryID]"), m_CategoryID);
	RFX_Long(pFX, _T("[tiCoefficient].[TaskID]"), m_TaskID);
	RFX_Long(pFX, _T("[tiLiteralI].[LiteralIID]"), m_LiteralIID2);
	RFX_Long(pFX, _T("[HypothesisID]"), m_HypothesisID);
	RFX_Long(pFX, _T("[CedentTypeID]"), m_CedentTypeID);
	RFX_Long(pFX, _T("[LiteralDID]"), m_LiteralDID);
	RFX_Long(pFX, _T("[ChildIndex]"), m_ChildIndex);
	RFX_Bool(pFX, _T("[Negation]"), m_Negation);
	RFX_Long(pFX, _T("[tiLiteralI].[TaskID]"), m_TaskID2);
	RFX_Long(pFX, _T("[tmCategory].[CategoryID]"), m_CategoryID2);
	RFX_Text(pFX, _T("[tmCategory].[Name]"), m_Name);
	RFX_Long(pFX, _T("[tmCategory].[QuantityID]"), m_QuantityID);
	RFX_Long(pFX, _T("[CategorySubTypeID]"), m_CategorySubTypeID);
	RFX_Long(pFX, _T("[BoolTypeID]"), m_BoolTypeID);
	RFX_Bool(pFX, _T("[XCategory]"), m_XCategory);
	RFX_Bool(pFX, _T("[IncludeNULL]"), m_IncludeNULL);
	RFX_Long(pFX, _T("[Ord]"), m_Ord);
	RFX_Text(pFX, _T("[tmCategory].[Notice]"), m_Notice);
	RFX_Long(pFX, _T("[tmCategory].[wSavedCountUsed]"), m_wSavedCountUsed);
	RFX_Long(pFX, _T("[tmQuantity].[QuantityID]"), m_QuantityID2);
	RFX_Text(pFX, _T("[tmQuantity].[Name]"), m_Name2);
	RFX_Text(pFX, _T("[ShortName]"), m_ShortName);
	RFX_Bool(pFX, _T("[ShowName]"), m_ShowName);
	RFX_Long(pFX, _T("[AttributeID]"), m_AttributeID);
	RFX_Long(pFX, _T("[ItemShift]"), m_ItemShift);
	RFX_Long(pFX, _T("[ParentGroupID]"), m_ParentGroupID);
	RFX_Long(pFX, _T("[tmQuantity].[wSavedCountUsed]"), m_wSavedCountUsed2);
	RFX_Long(pFX, _T("[wUpdateVer]"), m_wUpdateVer);
	RFX_Long(pFX, _T("[UserID]"), m_UserID);
	RFX_Text(pFX, _T("[tmQuantity].[Notice]"), m_Notice2);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// TCondition_Recordset diagnostics

#ifdef _DEBUG
void TCondition_Recordset::AssertValid() const
{
	CRecordset::AssertValid();
}

void TCondition_Recordset::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
