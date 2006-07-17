// Hyp_4ft_Recordset.cpp : implementation file
//

#include "Hyp_4ft_Recordset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Hyp_4ft_Recordset

IMPLEMENT_DYNAMIC(Hyp_4ft_Recordset, CRecordset)

Hyp_4ft_Recordset::Hyp_4ft_Recordset(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(Hyp_4ft_Recordset)
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
	m_CoefficientID = 0;
	m_LiteralIID = 0;
	m_CategoryID = 0;
	m_TaskID2 = 0;
	m_HypothesisID = 0;
	m_TaskID3 = 0;
	m_FreqA = 0;
	m_FreqB = 0;
	m_FreqC = 0;
	m_FreqD = 0;
	m_Weight = 0.0;
	m_Ord = 0;
	m_LiteralIID2 = 0;
	m_HypothesisID2 = 0;
	m_CedentTypeID = 0;
	m_LiteralDID = 0;
	m_ChildIndex = 0;
	m_Negation = FALSE;
	m_TaskID4 = 0;
	m_CategoryID2 = 0;
	m_Name2 = _T("");
	m_QuantityID = 0;
	m_CategorySubTypeID = 0;
	m_BoolTypeID = 0;
	m_XCategory = FALSE;
	m_IncludeNULL = FALSE;
	m_Ord2 = 0;
	m_Notice2 = _T("");
	m_wSavedCountUsed = 0;
	m_MatrixID2 = 0;
	m_Name3 = _T("");
	m_Initialised = FALSE;
	m_RecordCount = 0;
	m_Notice3 = _T("");
	m_wSavedCountUsed2 = 0;
	m_QuantityID2 = 0;
	m_Name4 = _T("");
	m_ShortName = _T("");
	m_ShowName = FALSE;
	m_AttributeID = 0;
	m_ItemShift = 0;
	m_ParentGroupID = 0;
	m_wSavedCountUsed3 = 0;
	m_wUpdateVer = 0;
	m_UserID2 = 0;
	m_Notice4 = _T("");
	m_CedentTypeID2 = 0;
	m_Name5 = _T("");
	m_ShortName2 = _T("");
	m_Ord3 = 0;
	m_Notice5 = _T("");
	m_TaskSubTypeID2 = 0;
	m_Name6 = _T("");
	m_ShortName3 = _T("");
	m_Ord4 = 0;
	m_Notice6 = _T("");
	m_nFields = 71;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

CString Hyp_4ft_Recordset::GetDefaultSQL()
{
	return _T("[taTask],[tiCoefficient],[tiHypothesis],[tiLiteralI],[tmCategory],[tmMatrix],[tmQuantity],[tsCedentType],[tsTaskSubType]");
}

void Hyp_4ft_Recordset::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(Hyp_4ft_Recordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[taTask].[TaskID]"), m_TaskID);
	RFX_Text(pFX, _T("[taTask].[Name]"), m_Name);
	RFX_Long(pFX, _T("[taTask].[TaskSubTypeID]"), m_TaskSubTypeID);
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
	RFX_Long(pFX, _T("[CoefficientID]"), m_CoefficientID);
	RFX_Long(pFX, _T("[tiCoefficient].[LiteralIID]"), m_LiteralIID);
	RFX_Long(pFX, _T("[tiCoefficient].[CategoryID]"), m_CategoryID);
	RFX_Long(pFX, _T("[tiCoefficient].[TaskID]"), m_TaskID2);
	RFX_Long(pFX, _T("[tiHypothesis].[HypothesisID]"), m_HypothesisID);
	RFX_Long(pFX, _T("[tiHypothesis].[TaskID]"), m_TaskID3);
	RFX_Long(pFX, _T("[FreqA]"), m_FreqA);
	RFX_Long(pFX, _T("[FreqB]"), m_FreqB);
	RFX_Long(pFX, _T("[FreqC]"), m_FreqC);
	RFX_Long(pFX, _T("[FreqD]"), m_FreqD);
	RFX_Double(pFX, _T("[Weight]"), m_Weight);
	RFX_Long(pFX, _T("[tiHypothesis].[Ord]"), m_Ord);
	RFX_Long(pFX, _T("[tiLiteralI].[LiteralIID]"), m_LiteralIID2);
	RFX_Long(pFX, _T("[tiLiteralI].[HypothesisID]"), m_HypothesisID2);
	RFX_Long(pFX, _T("[tiLiteralI].[CedentTypeID]"), m_CedentTypeID);
	RFX_Long(pFX, _T("[LiteralDID]"), m_LiteralDID);
	RFX_Long(pFX, _T("[ChildIndex]"), m_ChildIndex);
	RFX_Bool(pFX, _T("[Negation]"), m_Negation);
	RFX_Long(pFX, _T("[tiLiteralI].[TaskID]"), m_TaskID4);
	RFX_Long(pFX, _T("[tmCategory].[CategoryID]"), m_CategoryID2);
	RFX_Text(pFX, _T("[tmCategory].[Name]"), m_Name2);
	RFX_Long(pFX, _T("[tmCategory].[QuantityID]"), m_QuantityID);
	RFX_Long(pFX, _T("[CategorySubTypeID]"), m_CategorySubTypeID);
	RFX_Long(pFX, _T("[BoolTypeID]"), m_BoolTypeID);
	RFX_Bool(pFX, _T("[XCategory]"), m_XCategory);
	RFX_Bool(pFX, _T("[IncludeNULL]"), m_IncludeNULL);
	RFX_Long(pFX, _T("[tmCategory].[Ord]"), m_Ord2);
	RFX_Text(pFX, _T("[tmCategory].[Notice]"), m_Notice2);
	RFX_Long(pFX, _T("[tmCategory].[wSavedCountUsed]"), m_wSavedCountUsed);
	RFX_Long(pFX, _T("[tmMatrix].[MatrixID]"), m_MatrixID2);
	RFX_Text(pFX, _T("[tmMatrix].[Name]"), m_Name3);
	RFX_Bool(pFX, _T("[Initialised]"), m_Initialised);
	RFX_Long(pFX, _T("[RecordCount]"), m_RecordCount);
	RFX_Text(pFX, _T("[tmMatrix].[Notice]"), m_Notice3);
	RFX_Long(pFX, _T("[tmMatrix].[wSavedCountUsed]"), m_wSavedCountUsed2);
	RFX_Long(pFX, _T("[tmQuantity].[QuantityID]"), m_QuantityID2);
	RFX_Text(pFX, _T("[tmQuantity].[Name]"), m_Name4);
	RFX_Text(pFX, _T("[tmQuantity].[ShortName]"), m_ShortName);
	RFX_Bool(pFX, _T("[ShowName]"), m_ShowName);
	RFX_Long(pFX, _T("[AttributeID]"), m_AttributeID);
	RFX_Long(pFX, _T("[ItemShift]"), m_ItemShift);
	RFX_Long(pFX, _T("[ParentGroupID]"), m_ParentGroupID);
	RFX_Long(pFX, _T("[tmQuantity].[wSavedCountUsed]"), m_wSavedCountUsed3);
	RFX_Long(pFX, _T("[wUpdateVer]"), m_wUpdateVer);
	RFX_Long(pFX, _T("[tmQuantity].[UserID]"), m_UserID2);
	RFX_Text(pFX, _T("[tmQuantity].[Notice]"), m_Notice4);
	RFX_Long(pFX, _T("[tsCedentType].[CedentTypeID]"), m_CedentTypeID2);
	RFX_Text(pFX, _T("[tsCedentType].[Name]"), m_Name5);
	RFX_Text(pFX, _T("[tsCedentType].[ShortName]"), m_ShortName2);
	RFX_Long(pFX, _T("[tsCedentType].[Ord]"), m_Ord3);
	RFX_Text(pFX, _T("[tsCedentType].[Notice]"), m_Notice5);
	RFX_Long(pFX, _T("[tsTaskSubType].[TaskSubTypeID]"), m_TaskSubTypeID2);
	RFX_Text(pFX, _T("[tsTaskSubType].[Name]"), m_Name6);
	RFX_Text(pFX, _T("[tsTaskSubType].[ShortName]"), m_ShortName3);
	RFX_Long(pFX, _T("[tsTaskSubType].[Ord]"), m_Ord4);
	RFX_Text(pFX, _T("[tsTaskSubType].[Notice]"), m_Notice6);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// Hyp_4ft_Recordset diagnostics

#ifdef _DEBUG
void Hyp_4ft_Recordset::AssertValid() const
{
	CRecordset::AssertValid();
}

void Hyp_4ft_Recordset::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
