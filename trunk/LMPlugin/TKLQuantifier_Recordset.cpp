// TKLQuantifier_Recordset.cpp : implementation file
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
#include "TKLQuantifier_Recordset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// TKLQuantifier_Recordset

IMPLEMENT_DYNAMIC(TKLQuantifier_Recordset, CRecordset)

TKLQuantifier_Recordset::TKLQuantifier_Recordset(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(TKLQuantifier_Recordset)
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
	m_KLQuantifierID = 0;
	m_TaskID2 = 0;
	m_KLQuantifierTypeID = 0;
	m_FromRow = 0;
	m_FromCol = 0;
	m_ToRow = 0;
	m_ToCol = 0;
	m_CompareTypeID = 0;
	m_ValuePar = 0.0;
	m_KLQuantifierValueTypeID = 0;
	m_Threshold = 0.0;
	m_Formula = _T("");
	m_Ord = 0;
	m_KendalAbsValueTauB = FALSE;
	m_Notice2 = _T("");
	m_MatrixID2 = 0;
	m_Name2 = _T("");
	m_Initialised = FALSE;
	m_RecordCount = 0;
	m_Notice3 = _T("");
	m_wSavedCountUsed = 0;
	m_CompareTypeID2 = 0;
	m_Name3 = _T("");
	m_ShortName = _T("");
	m_Ord2 = 0;
	m_Notice4 = _T("");
	m_KLQuantifierTypeID2 = 0;
	m_Name4 = _T("");
	m_ShortName2 = _T("");
	m_Ord3 = 0;
	m_Notice5 = _T("");
	m_KLQuantifierValueTypeID2 = 0;
	m_Name5 = _T("");
	m_ShortName3 = _T("");
	m_Ord4 = 0;
	m_Notice6 = _T("");
	m_TaskSubTypeID2 = 0;
	m_Name6 = _T("");
	m_ShortName4 = _T("");
	m_Ord5 = 0;
	m_Notice7 = _T("");
	m_nFields = 56;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

CString TKLQuantifier_Recordset::GetDefaultSQL()
{
	return _T("[taTask],[tdKLQuantifier],[tmMatrix],[tsCompareType],[tsKLQuantifierType],[tsKLQuantifierValueType],[tsTaskSubType]");
}

void TKLQuantifier_Recordset::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(TKLQuantifier_Recordset)
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
	RFX_Long(pFX, _T("[KLQuantifierID]"), m_KLQuantifierID);
	RFX_Long(pFX, _T("[tdKLQuantifier].[TaskID]"), m_TaskID2);
	RFX_Long(pFX, _T("[tdKLQuantifier].[KLQuantifierTypeID]"), m_KLQuantifierTypeID);
	RFX_Long(pFX, _T("[FromRow]"), m_FromRow);
	RFX_Long(pFX, _T("[FromCol]"), m_FromCol);
	RFX_Long(pFX, _T("[ToRow]"), m_ToRow);
	RFX_Long(pFX, _T("[ToCol]"), m_ToCol);
	RFX_Long(pFX, _T("[tdKLQuantifier].[CompareTypeID]"), m_CompareTypeID);
	RFX_Double(pFX, _T("[ValuePar]"), m_ValuePar);
	RFX_Long(pFX, _T("[tdKLQuantifier].[KLQuantifierValueTypeID]"), m_KLQuantifierValueTypeID);
	RFX_Double(pFX, _T("[Threshold]"), m_Threshold);
	RFX_Text(pFX, _T("[Formula]"), m_Formula);
	RFX_Long(pFX, _T("[tdKLQuantifier].[Ord]"), m_Ord);
	RFX_Bool(pFX, _T("[KendalAbsValueTauB]"), m_KendalAbsValueTauB);
	RFX_Text(pFX, _T("[tdKLQuantifier].[Notice]"), m_Notice2);
	RFX_Long(pFX, _T("[tmMatrix].[MatrixID]"), m_MatrixID2);
	RFX_Text(pFX, _T("[tmMatrix].[Name]"), m_Name2);
	RFX_Bool(pFX, _T("[Initialised]"), m_Initialised);
	RFX_Long(pFX, _T("[RecordCount]"), m_RecordCount);
	RFX_Text(pFX, _T("[tmMatrix].[Notice]"), m_Notice3);
	RFX_Long(pFX, _T("[wSavedCountUsed]"), m_wSavedCountUsed);
	RFX_Long(pFX, _T("[tsCompareType].[CompareTypeID]"), m_CompareTypeID2);
	RFX_Text(pFX, _T("[tsCompareType].[Name]"), m_Name3);
	RFX_Text(pFX, _T("[tsCompareType].[ShortName]"), m_ShortName);
	RFX_Long(pFX, _T("[tsCompareType].[Ord]"), m_Ord2);
	RFX_Text(pFX, _T("[tsCompareType].[Notice]"), m_Notice4);
	RFX_Long(pFX, _T("[tsKLQuantifierType].[KLQuantifierTypeID]"), m_KLQuantifierTypeID2);
	RFX_Text(pFX, _T("[tsKLQuantifierType].[Name]"), m_Name4);
	RFX_Text(pFX, _T("[tsKLQuantifierType].[ShortName]"), m_ShortName2);
	RFX_Long(pFX, _T("[tsKLQuantifierType].[Ord]"), m_Ord3);
	RFX_Text(pFX, _T("[tsKLQuantifierType].[Notice]"), m_Notice5);
	RFX_Long(pFX, _T("[tsKLQuantifierValueType].[KLQuantifierValueTypeID]"), m_KLQuantifierValueTypeID2);
	RFX_Text(pFX, _T("[tsKLQuantifierValueType].[Name]"), m_Name5);
	RFX_Text(pFX, _T("[tsKLQuantifierValueType].[ShortName]"), m_ShortName3);
	RFX_Long(pFX, _T("[tsKLQuantifierValueType].[Ord]"), m_Ord4);
	RFX_Text(pFX, _T("[tsKLQuantifierValueType].[Notice]"), m_Notice6);
	RFX_Long(pFX, _T("[tsTaskSubType].[TaskSubTypeID]"), m_TaskSubTypeID2);
	RFX_Text(pFX, _T("[tsTaskSubType].[Name]"), m_Name6);
	RFX_Text(pFX, _T("[tsTaskSubType].[ShortName]"), m_ShortName4);
	RFX_Long(pFX, _T("[tsTaskSubType].[Ord]"), m_Ord5);
	RFX_Text(pFX, _T("[tsTaskSubType].[Notice]"), m_Notice7);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// TKLQuantifier_Recordset diagnostics

#ifdef _DEBUG
void TKLQuantifier_Recordset::AssertValid() const
{
	CRecordset::AssertValid();
}

void TKLQuantifier_Recordset::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
