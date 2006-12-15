// Hyp_SDKL_Recordset.cpp : implementation file
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
#include "Hyp_SDKL_Recordset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Hyp_SDKL_Recordset

IMPLEMENT_DYNAMIC(Hyp_SDKL_Recordset, CRecordset)

Hyp_SDKL_Recordset::Hyp_SDKL_Recordset(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(Hyp_SDKL_Recordset)
	m_TaskID = 0;
	m_Name = _T("");
	m_TaskSubTypeID = 0;
	m_TaskGroupID = 0;
	m_UserID = 0;
	m_MatrixID = 0;
	m_ParamBASE = 0;
	m_ParamBASERelativ = FALSE;
	m_ReadOnly = FALSE;
	m_HypothesisGenerated = FALSE;
	m_GenerationInterrupted = FALSE;
	m_GenerationNrOfTests = 0;
	m_GenerationTotalTime = 0;
	m_Notice = _T("");
	m_HypothesisDKID = 0;
	m_HypothesisID = 0;
	m_TaskID2 = 0;
	m_Rows = 0;
	m_Cols = 0;
	m_KLLiteralDRowID = 0;
	m_KLLiteralDColID = 0;
	m_QuantityRowUpdateVer = 0;
	m_QuantityColUpdateVer = 0;
	m_MatrixID2 = 0;
	m_Name2 = _T("");
	m_Initialised = FALSE;
	m_RecordCount = 0;
	m_Notice2 = _T("");
	m_wSavedCountUsed = 0;
	m_nFields = 30;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

CString Hyp_SDKL_Recordset::GetDefaultSQL()
{
	return _T("[taTask],[tiHypothesisDK],[tmMatrix]");
}

void Hyp_SDKL_Recordset::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(Hyp_SDKL_Recordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[taTask].[TaskID]"), m_TaskID);
	RFX_Text(pFX, _T("[taTask].[Name]"), m_Name);
	RFX_Long(pFX, _T("[TaskSubTypeID]"), m_TaskSubTypeID);
	RFX_Long(pFX, _T("[TaskGroupID]"), m_TaskGroupID);
	RFX_Long(pFX, _T("[UserID]"), m_UserID);
	RFX_Long(pFX, _T("[taTask].[MatrixID]"), m_MatrixID);
	RFX_Long(pFX, _T("[ParamBASE]"), m_ParamBASE);
	RFX_Bool(pFX, _T("[ParamBASERelativ]"), m_ParamBASERelativ);
	RFX_Bool(pFX, _T("[ReadOnly]"), m_ReadOnly);
	RFX_Bool(pFX, _T("[HypothesisGenerated]"), m_HypothesisGenerated);
	RFX_Bool(pFX, _T("[GenerationInterrupted]"), m_GenerationInterrupted);
	RFX_Long(pFX, _T("[GenerationNrOfTests]"), m_GenerationNrOfTests);
	RFX_Date(pFX, _T("[GenerationStartTime]"), m_GenerationStartTime);
	RFX_Long(pFX, _T("[GenerationTotalTime]"), m_GenerationTotalTime);
	RFX_Text(pFX, _T("[taTask].[Notice]"), m_Notice);
	RFX_Long(pFX, _T("[HypothesisDKID]"), m_HypothesisDKID);
	RFX_Long(pFX, _T("[HypothesisID]"), m_HypothesisID);
	RFX_Long(pFX, _T("[tiHypothesisDK].[TaskID]"), m_TaskID2);
	RFX_Long(pFX, _T("[Rows]"), m_Rows);
	RFX_Long(pFX, _T("[Cols]"), m_Cols);
	RFX_Long(pFX, _T("[KLLiteralDRowID]"), m_KLLiteralDRowID);
	RFX_Long(pFX, _T("[KLLiteralDColID]"), m_KLLiteralDColID);
	RFX_Long(pFX, _T("[QuantityRowUpdateVer]"), m_QuantityRowUpdateVer);
	RFX_Long(pFX, _T("[QuantityColUpdateVer]"), m_QuantityColUpdateVer);
	RFX_Long(pFX, _T("[tmMatrix].[MatrixID]"), m_MatrixID2);
	RFX_Text(pFX, _T("[tmMatrix].[Name]"), m_Name2);
	RFX_Bool(pFX, _T("[Initialised]"), m_Initialised);
	RFX_Long(pFX, _T("[RecordCount]"), m_RecordCount);
	RFX_Text(pFX, _T("[tmMatrix].[Notice]"), m_Notice2);
	RFX_Long(pFX, _T("[wSavedCountUsed]"), m_wSavedCountUsed);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// Hyp_SDKL_Recordset diagnostics

#ifdef _DEBUG
void Hyp_SDKL_Recordset::AssertValid() const
{
	CRecordset::AssertValid();
}

void Hyp_SDKL_Recordset::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
