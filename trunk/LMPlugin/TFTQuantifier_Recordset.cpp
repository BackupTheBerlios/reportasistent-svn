// TFTQuantifier_Recordset.cpp : implementation file
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
#include "TFTQuantifier_Recordset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// TFTQuantifier_Recordset

IMPLEMENT_DYNAMIC(TFTQuantifier_Recordset, CRecordset)

TFTQuantifier_Recordset::TFTQuantifier_Recordset(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(TFTQuantifier_Recordset)
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
	m_FTQuantifierID = 0;
	m_TaskID2 = 0;
	m_FTQuantifierTypeID = 0;
	m_ParamP = 0.0;
	m_ParamAlfa = 0.0;
	m_ParamBeta = 0.0;
	m_ParamDelta = 0.0;
	m_Ord = 0;
	m_Notice2 = _T("");
	m_ParamRelativ = FALSE;
	m_MatrixID2 = 0;
	m_Name2 = _T("");
	m_Initialised = FALSE;
	m_RecordCount = 0;
	m_Notice3 = _T("");
	m_wSavedCountUsed = 0;
	m_QuantifierTypeID = 0;
	m_Name3 = _T("");
	m_ShortName = _T("");
	m_UsedParams = _T("");
	m_Ord2 = 0;
	m_Notice4 = _T("");
	m_TaskSubTypeID2 = 0;
	m_Name4 = _T("");
	m_ShortName2 = _T("");
	m_Ord3 = 0;
	m_Notice5 = _T("");
	m_nFields = 42;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

CString TFTQuantifier_Recordset::GetDefaultSQL()
{
	return _T("[taTask],[tdFTQuantifier],[tmMatrix],[tsQuantifierType],[tsTaskSubType]");
}

void TFTQuantifier_Recordset::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(TFTQuantifier_Recordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[taTask].[TaskID]"), m_TaskID);
	RFX_Text(pFX, _T("[taTask].[Name]"), m_Name);
	RFX_Long(pFX, _T("[taTask].[TaskSubTypeID]"), m_TaskSubTypeID);
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
	RFX_Long(pFX, _T("[FTQuantifierID]"), m_FTQuantifierID);
	RFX_Long(pFX, _T("[tdFTQuantifier].[TaskID]"), m_TaskID2);
	RFX_Long(pFX, _T("[FTQuantifierTypeID]"), m_FTQuantifierTypeID);
	RFX_Double(pFX, _T("[ParamP]"), m_ParamP);
	RFX_Double(pFX, _T("[ParamAlfa]"), m_ParamAlfa);
	RFX_Double(pFX, _T("[ParamBeta]"), m_ParamBeta);
	RFX_Double(pFX, _T("[ParamDelta]"), m_ParamDelta);
	RFX_Long(pFX, _T("[tdFTQuantifier].[Ord]"), m_Ord);
	RFX_Text(pFX, _T("[tdFTQuantifier].[Notice]"), m_Notice2);
	RFX_Bool(pFX, _T("[ParamRelativ]"), m_ParamRelativ);
	RFX_Long(pFX, _T("[tmMatrix].[MatrixID]"), m_MatrixID2);
	RFX_Text(pFX, _T("[tmMatrix].[Name]"), m_Name2);
	RFX_Bool(pFX, _T("[Initialised]"), m_Initialised);
	RFX_Long(pFX, _T("[RecordCount]"), m_RecordCount);
	RFX_Text(pFX, _T("[tmMatrix].[Notice]"), m_Notice3);
	RFX_Long(pFX, _T("[wSavedCountUsed]"), m_wSavedCountUsed);
	RFX_Long(pFX, _T("[QuantifierTypeID]"), m_QuantifierTypeID);
	RFX_Text(pFX, _T("[tsQuantifierType].[Name]"), m_Name3);
	RFX_Text(pFX, _T("[tsQuantifierType].[ShortName]"), m_ShortName);
	RFX_Text(pFX, _T("[UsedParams]"), m_UsedParams);
	RFX_Long(pFX, _T("[tsQuantifierType].[Ord]"), m_Ord2);
	RFX_Text(pFX, _T("[tsQuantifierType].[Notice]"), m_Notice4);
	RFX_Long(pFX, _T("[tsTaskSubType].[TaskSubTypeID]"), m_TaskSubTypeID2);
	RFX_Text(pFX, _T("[tsTaskSubType].[Name]"), m_Name4);
	RFX_Text(pFX, _T("[tsTaskSubType].[ShortName]"), m_ShortName2);
	RFX_Long(pFX, _T("[tsTaskSubType].[Ord]"), m_Ord3);
	RFX_Text(pFX, _T("[tsTaskSubType].[Notice]"), m_Notice5);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// TFTQuantifier_Recordset diagnostics

#ifdef _DEBUG
void TFTQuantifier_Recordset::AssertValid() const
{
	CRecordset::AssertValid();
}

void TFTQuantifier_Recordset::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
