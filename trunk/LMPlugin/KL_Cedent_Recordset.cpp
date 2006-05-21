// KL_Cedent_Recordset.cpp : implementation file
//
#include "KL_Cedent_Recordset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// KL_Cedent_Recordset

IMPLEMENT_DYNAMIC(KL_Cedent_Recordset, CRecordset)

KL_Cedent_Recordset::KL_Cedent_Recordset(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(KL_Cedent_Recordset)
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
	m_KLCedentDID = 0;
	m_TaskID2 = 0;
	m_Name2 = _T("");
	m_CedentTypeID = 0;
	m_MinLen = 0;
	m_MaxLen = 0;
	m_Notice2 = _T("");
	m_Ord = 0;
	m_MatrixID2 = 0;
	m_Name3 = _T("");
	m_Initialised = FALSE;
	m_RecordCount = 0;
	m_Notice3 = _T("");
	m_wSavedCountUsed = 0;
	m_CedentTypeID2 = 0;
	m_Name4 = _T("");
	m_ShortName = _T("");
	m_Ord2 = 0;
	m_Notice4 = _T("");
	m_TaskSubTypeID2 = 0;
	m_Name5 = _T("");
	m_ShortName2 = _T("");
	m_Ord3 = 0;
	m_Notice5 = _T("");
	m_nFields = 39;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

CString KL_Cedent_Recordset::GetDefaultSQL()
{
	return _T("[taTask],[tdKLCedentD],[tmMatrix],[tsCedentType],[tsTaskSubType]");
}

void KL_Cedent_Recordset::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(KL_Cedent_Recordset)
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
	RFX_Long(pFX, _T("[KLCedentDID]"), m_KLCedentDID);
	RFX_Long(pFX, _T("[tdKLCedentD].[TaskID]"), m_TaskID2);
	RFX_Text(pFX, _T("[tdKLCedentD].[Name]"), m_Name2);
	RFX_Long(pFX, _T("[tdKLCedentD].[CedentTypeID]"), m_CedentTypeID);
	RFX_Long(pFX, _T("[MinLen]"), m_MinLen);
	RFX_Long(pFX, _T("[MaxLen]"), m_MaxLen);
	RFX_Text(pFX, _T("[tdKLCedentD].[Notice]"), m_Notice2);
	RFX_Long(pFX, _T("[tdKLCedentD].[Ord]"), m_Ord);
	RFX_Long(pFX, _T("[tmMatrix].[MatrixID]"), m_MatrixID2);
	RFX_Text(pFX, _T("[tmMatrix].[Name]"), m_Name3);
	RFX_Bool(pFX, _T("[Initialised]"), m_Initialised);
	RFX_Long(pFX, _T("[RecordCount]"), m_RecordCount);
	RFX_Text(pFX, _T("[tmMatrix].[Notice]"), m_Notice3);
	RFX_Long(pFX, _T("[wSavedCountUsed]"), m_wSavedCountUsed);
	RFX_Long(pFX, _T("[tsCedentType].[CedentTypeID]"), m_CedentTypeID2);
	RFX_Text(pFX, _T("[tsCedentType].[Name]"), m_Name4);
	RFX_Text(pFX, _T("[tsCedentType].[ShortName]"), m_ShortName);
	RFX_Long(pFX, _T("[tsCedentType].[Ord]"), m_Ord2);
	RFX_Text(pFX, _T("[tsCedentType].[Notice]"), m_Notice4);
	RFX_Long(pFX, _T("[tsTaskSubType].[TaskSubTypeID]"), m_TaskSubTypeID2);
	RFX_Text(pFX, _T("[tsTaskSubType].[Name]"), m_Name5);
	RFX_Text(pFX, _T("[tsTaskSubType].[ShortName]"), m_ShortName2);
	RFX_Long(pFX, _T("[tsTaskSubType].[Ord]"), m_Ord3);
	RFX_Text(pFX, _T("[tsTaskSubType].[Notice]"), m_Notice5);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// KL_Cedent_Recordset diagnostics

#ifdef _DEBUG
void KL_Cedent_Recordset::AssertValid() const
{
	CRecordset::AssertValid();
}

void KL_Cedent_Recordset::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
