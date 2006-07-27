// Hyp_SDCF_Recordset.cpp : implementation file
//

#include "Hyp_SDCF_Recordset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Hyp_SDCF_Recordset

IMPLEMENT_DYNAMIC(Hyp_SDCF_Recordset, CRecordset)

Hyp_SDCF_Recordset::Hyp_SDCF_Recordset(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(Hyp_SDCF_Recordset)
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
	m_CFLiteralDID = 0;
	m_CFCedentDID = 0;
	m_QuantityID = 0;
	m_Ord = 0;
	m_Notice2 = _T("");
	m_HypothesisDCID = 0;
	m_HypothesisID = 0;
	m_TaskID2 = 0;
	m_Cols = 0;
	m_CFLiteralDID2 = 0;
	m_QuantityUpdateVer = 0;
	m_MatrixID2 = 0;
	m_Name2 = _T("");
	m_Initialised = FALSE;
	m_RecordCount = 0;
	m_Notice3 = _T("");
	m_wSavedCountUsed = 0;
	m_QuantityID2 = 0;
	m_Name3 = _T("");
	m_ShortName = _T("");
	m_ShowName = FALSE;
	m_AttributeID = 0;
	m_ItemShift = 0;
	m_ParentGroupID = 0;
	m_wSavedCountUsed2 = 0;
	m_wUpdateVer = 0;
	m_UserID2 = 0;
	m_Notice4 = _T("");
	m_nFields = 43;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

CString Hyp_SDCF_Recordset::GetDefaultSQL()
{
	return _T("[taTask],[tdCFLiteralD],[tiHypothesisDC],[tmMatrix],[tmQuantity]");
}

void Hyp_SDCF_Recordset::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(Hyp_SDCF_Recordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[taTask].[TaskID]"), m_TaskID);
	RFX_Text(pFX, _T("[taTask].[Name]"), m_Name);
	RFX_Long(pFX, _T("[TaskSubTypeID]"), m_TaskSubTypeID);
	RFX_Long(pFX, _T("[TaskGroupID]"), m_TaskGroupID);
	RFX_Long(pFX, _T("[taTask].[UserID]"), m_UserID);
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
	RFX_Long(pFX, _T("[tdCFLiteralD].[CFLiteralDID]"), m_CFLiteralDID);
	RFX_Long(pFX, _T("[CFCedentDID]"), m_CFCedentDID);
	RFX_Long(pFX, _T("[tdCFLiteralD].[QuantityID]"), m_QuantityID);
	RFX_Long(pFX, _T("[Ord]"), m_Ord);
	RFX_Text(pFX, _T("[tdCFLiteralD].[Notice]"), m_Notice2);
	RFX_Long(pFX, _T("[HypothesisDCID]"), m_HypothesisDCID);
	RFX_Long(pFX, _T("[HypothesisID]"), m_HypothesisID);
	RFX_Long(pFX, _T("[tiHypothesisDC].[TaskID]"), m_TaskID2);
	RFX_Long(pFX, _T("[Cols]"), m_Cols);
	RFX_Long(pFX, _T("[tiHypothesisDC].[CFLiteralDID]"), m_CFLiteralDID2);
	RFX_Long(pFX, _T("[QuantityUpdateVer]"), m_QuantityUpdateVer);
	RFX_Long(pFX, _T("[tmMatrix].[MatrixID]"), m_MatrixID2);
	RFX_Text(pFX, _T("[tmMatrix].[Name]"), m_Name2);
	RFX_Bool(pFX, _T("[Initialised]"), m_Initialised);
	RFX_Long(pFX, _T("[RecordCount]"), m_RecordCount);
	RFX_Text(pFX, _T("[tmMatrix].[Notice]"), m_Notice3);
	RFX_Long(pFX, _T("[tmMatrix].[wSavedCountUsed]"), m_wSavedCountUsed);
	RFX_Long(pFX, _T("[tmQuantity].[QuantityID]"), m_QuantityID2);
	RFX_Text(pFX, _T("[tmQuantity].[Name]"), m_Name3);
	RFX_Text(pFX, _T("[ShortName]"), m_ShortName);
	RFX_Bool(pFX, _T("[ShowName]"), m_ShowName);
	RFX_Long(pFX, _T("[AttributeID]"), m_AttributeID);
	RFX_Long(pFX, _T("[ItemShift]"), m_ItemShift);
	RFX_Long(pFX, _T("[ParentGroupID]"), m_ParentGroupID);
	RFX_Long(pFX, _T("[tmQuantity].[wSavedCountUsed]"), m_wSavedCountUsed2);
	RFX_Long(pFX, _T("[wUpdateVer]"), m_wUpdateVer);
	RFX_Long(pFX, _T("[tmQuantity].[UserID]"), m_UserID2);
	RFX_Text(pFX, _T("[tmQuantity].[Notice]"), m_Notice4);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// Hyp_SDCF_Recordset diagnostics

#ifdef _DEBUG
void Hyp_SDCF_Recordset::AssertValid() const
{
	CRecordset::AssertValid();
}

void Hyp_SDCF_Recordset::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
