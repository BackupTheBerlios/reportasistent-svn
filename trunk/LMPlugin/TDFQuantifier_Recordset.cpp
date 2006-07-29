// TDFQuantifier_Recordset.cpp : implementation file
//

#include "TDFQuantifier_Recordset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// TDFQuantifier_Recordset

IMPLEMENT_DYNAMIC(TDFQuantifier_Recordset, CRecordset)

TDFQuantifier_Recordset::TDFQuantifier_Recordset(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(TDFQuantifier_Recordset)
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
	m_DFQuantifierID = 0;
	m_TaskID2 = 0;
	m_DFQuantifierTypeID = 0;
	m_SDQuantifierSourceTypeID = 0;
	m_ParamP = 0.0;
	m_ParamAlfa = 0.0;
	m_ParamBeta = 0.0;
	m_ParamDelta = 0.0;
	m_CompareTypeID = 0;
	m_ValuePar = 0.0;
	m_DFQuantifierValueTypeID = 0;
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
	m_DFQuantifierTypeID2 = 0;
	m_Name4 = _T("");
	m_ShortName2 = _T("");
	m_Ord3 = 0;
	m_Notice5 = _T("");
	m_DFQuantifierValueTypeID2 = 0;
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

CString TDFQuantifier_Recordset::GetDefaultSQL()
{
	return _T("[taTask],[tdDFQuantifier],[tmMatrix],[tsCompareType],[tsDFQuantifierType],[tsDFQuantifierValueType],[tsSDQuantifierSourceType],[tsTaskSubType]");
}

void TDFQuantifier_Recordset::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(TDFQuantifier_Recordset)
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
	RFX_Long(pFX, _T("[DFQuantifierID]"), m_DFQuantifierID);
	RFX_Long(pFX, _T("[tdDFQuantifier].[TaskID]"), m_TaskID2);
	RFX_Long(pFX, _T("[tdDFQuantifier].[DFQuantifierTypeID]"), m_DFQuantifierTypeID);
	RFX_Long(pFX, _T("[tdDFQuantifier].[SDQuantifierSourceTypeID]"), m_SDQuantifierSourceTypeID);
	RFX_Double(pFX, _T("[ParamP]"), m_ParamP);
	RFX_Double(pFX, _T("[ParamAlfa]"), m_ParamAlfa);
	RFX_Double(pFX, _T("[ParamBeta]"), m_ParamBeta);
	RFX_Double(pFX, _T("[ParamDelta]"), m_ParamDelta);
	RFX_Long(pFX, _T("[tdDFQuantifier].[CompareTypeID]"), m_CompareTypeID);
	RFX_Double(pFX, _T("[ValuePar]"), m_ValuePar);
	RFX_Long(pFX, _T("[tdDFQuantifier].[DFQuantifierValueTypeID]"), m_DFQuantifierValueTypeID);
	RFX_Long(pFX, _T("[tdDFQuantifier].[Ord]"), m_Ord);
	RFX_Text(pFX, _T("[tdDFQuantifier].[Notice]"), m_Notice2);
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
	RFX_Long(pFX, _T("[tsDFQuantifierType].[DFQuantifierTypeID]"), m_DFQuantifierTypeID2);
	RFX_Text(pFX, _T("[tsDFQuantifierType].[Name]"), m_Name4);
	RFX_Text(pFX, _T("[tsDFQuantifierType].[ShortName]"), m_ShortName2);
	RFX_Long(pFX, _T("[tsDFQuantifierType].[Ord]"), m_Ord3);
	RFX_Text(pFX, _T("[tsDFQuantifierType].[Notice]"), m_Notice5);
	RFX_Long(pFX, _T("[tsDFQuantifierValueType].[DFQuantifierValueTypeID]"), m_DFQuantifierValueTypeID2);
	RFX_Text(pFX, _T("[tsDFQuantifierValueType].[Name]"), m_Name5);
	RFX_Text(pFX, _T("[tsDFQuantifierValueType].[ShortName]"), m_ShortName3);
	RFX_Long(pFX, _T("[tsDFQuantifierValueType].[Ord]"), m_Ord4);
	RFX_Text(pFX, _T("[tsDFQuantifierValueType].[Notice]"), m_Notice6);
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
// TDFQuantifier_Recordset diagnostics

#ifdef _DEBUG
void TDFQuantifier_Recordset::AssertValid() const
{
	CRecordset::AssertValid();
}

void TDFQuantifier_Recordset::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG