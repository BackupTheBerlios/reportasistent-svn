// TDCQuantifier_Recordset.cpp : implementation file
//

#include "TDCQuantifier_Recordset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// TDCQuantifier_Recordset

IMPLEMENT_DYNAMIC(TDCQuantifier_Recordset, CRecordset)

TDCQuantifier_Recordset::TDCQuantifier_Recordset(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(TDCQuantifier_Recordset)
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
	m_DCQuantifierID = 0;
	m_TaskID2 = 0;
	m_DCQuantifierTypeID = 0;
	m_SDQuantifierSourceTypeID = 0;
	m_FromCol = 0;
	m_ToCol = 0;
	m_CompareTypeID = 0;
	m_ValuePar = 0.0;
	m_DCQuantifierValueTypeID = 0;
	m_Threshold = 0.0;
	m_Formula = _T("");
	m_Ord = 0;
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
	m_DCQuantifierTypeID2 = 0;
	m_Name4 = _T("");
	m_ShortName2 = _T("");
	m_Ord3 = 0;
	m_Notice5 = _T("");
	m_DCQuantifierValueTypeID2 = 0;
	m_Name5 = _T("");
	m_ShortName3 = _T("");
	m_Ord4 = 0;
	m_Notice6 = _T("");
	m_SDQuantifierSourceTypeID2 = 0;
	m_Name6 = _T("");
	m_ShortName4 = _T("");
	m_Ord5 = 0;
	m_Notice7 = _T("");
	m_TaskSubTypeID2 = 0;
	m_Name7 = _T("");
	m_ShortName5 = _T("");
	m_Ord6 = 0;
	m_Notice8 = _T("");
	m_nFields = 59;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

CString TDCQuantifier_Recordset::GetDefaultSQL()
{
	return _T("[taTask],[tdDCQuantifier],[tmMatrix],[tsCompareType],[tsDCQuantifierType],[tsDCQuantifierValueType],[tsSDQuantifierSourceType],[tsTaskSubType]");
}

void TDCQuantifier_Recordset::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(TDCQuantifier_Recordset)
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
	RFX_Long(pFX, _T("[DCQuantifierID]"), m_DCQuantifierID);
	RFX_Long(pFX, _T("[tdDCQuantifier].[TaskID]"), m_TaskID2);
	RFX_Long(pFX, _T("[tdDCQuantifier].[DCQuantifierTypeID]"), m_DCQuantifierTypeID);
	RFX_Long(pFX, _T("[tdDCQuantifier].[SDQuantifierSourceTypeID]"), m_SDQuantifierSourceTypeID);
	RFX_Long(pFX, _T("[FromCol]"), m_FromCol);
	RFX_Long(pFX, _T("[ToCol]"), m_ToCol);
	RFX_Long(pFX, _T("[tdDCQuantifier].[CompareTypeID]"), m_CompareTypeID);
	RFX_Double(pFX, _T("[ValuePar]"), m_ValuePar);
	RFX_Long(pFX, _T("[tdDCQuantifier].[DCQuantifierValueTypeID]"), m_DCQuantifierValueTypeID);
	RFX_Double(pFX, _T("[Threshold]"), m_Threshold);
	RFX_Text(pFX, _T("[Formula]"), m_Formula);
	RFX_Long(pFX, _T("[tdDCQuantifier].[Ord]"), m_Ord);
	RFX_Text(pFX, _T("[tdDCQuantifier].[Notice]"), m_Notice2);
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
	RFX_Long(pFX, _T("[tsDCQuantifierType].[DCQuantifierTypeID]"), m_DCQuantifierTypeID2);
	RFX_Text(pFX, _T("[tsDCQuantifierType].[Name]"), m_Name4);
	RFX_Text(pFX, _T("[tsDCQuantifierType].[ShortName]"), m_ShortName2);
	RFX_Long(pFX, _T("[tsDCQuantifierType].[Ord]"), m_Ord3);
	RFX_Text(pFX, _T("[tsDCQuantifierType].[Notice]"), m_Notice5);
	RFX_Long(pFX, _T("[tsDCQuantifierValueType].[DCQuantifierValueTypeID]"), m_DCQuantifierValueTypeID2);
	RFX_Text(pFX, _T("[tsDCQuantifierValueType].[Name]"), m_Name5);
	RFX_Text(pFX, _T("[tsDCQuantifierValueType].[ShortName]"), m_ShortName3);
	RFX_Long(pFX, _T("[tsDCQuantifierValueType].[Ord]"), m_Ord4);
	RFX_Text(pFX, _T("[tsDCQuantifierValueType].[Notice]"), m_Notice6);
	RFX_Long(pFX, _T("[tsSDQuantifierSourceType].[SDQuantifierSourceTypeID]"), m_SDQuantifierSourceTypeID2);
	RFX_Text(pFX, _T("[tsSDQuantifierSourceType].[Name]"), m_Name6);
	RFX_Text(pFX, _T("[tsSDQuantifierSourceType].[ShortName]"), m_ShortName4);
	RFX_Long(pFX, _T("[tsSDQuantifierSourceType].[Ord]"), m_Ord5);
	RFX_Text(pFX, _T("[tsSDQuantifierSourceType].[Notice]"), m_Notice7);
	RFX_Long(pFX, _T("[tsTaskSubType].[TaskSubTypeID]"), m_TaskSubTypeID2);
	RFX_Text(pFX, _T("[tsTaskSubType].[Name]"), m_Name7);
	RFX_Text(pFX, _T("[tsTaskSubType].[ShortName]"), m_ShortName5);
	RFX_Long(pFX, _T("[tsTaskSubType].[Ord]"), m_Ord6);
	RFX_Text(pFX, _T("[tsTaskSubType].[Notice]"), m_Notice8);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// TDCQuantifier_Recordset diagnostics

#ifdef _DEBUG
void TDCQuantifier_Recordset::AssertValid() const
{
	CRecordset::AssertValid();
}

void TDCQuantifier_Recordset::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
