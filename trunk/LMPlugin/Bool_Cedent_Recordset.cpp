// Bool_Cedent_Recordset.cpp : implementation file
//

#include "Bool_Cedent_Recordset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Bool_Cedent_Recordset

IMPLEMENT_DYNAMIC(Bool_Cedent_Recordset, CRecordset)

Bool_Cedent_Recordset::Bool_Cedent_Recordset(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(Bool_Cedent_Recordset)
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
	m_CedentDID = 0;
	m_TaskID2 = 0;
	m_CedentTypeID = 0;
	m_Name2 = _T("");
	m_Ord = 0;
	m_MinLen = 0;
	m_MaxLen = 0;
	m_Notice2 = _T("");
	m_LiteralDID = 0;
	m_CedentDID2 = 0;
	m_QuantityID = 0;
	m_CategoryID = 0;
	m_LiteralTypeID = 0;
	m_GaceTypeID = 0;
	m_EquivalenceClassID = 0;
	m_CoefficientTypeID = 0;
	m_MinLen2 = 0;
	m_MaxLen2 = 0;
	m_Ord2 = 0;
	m_Notice3 = _T("");
	m_AttributeID = 0;
	m_Name3 = _T("");
	m_MatrixID2 = 0;
	m_AttributeSubTypeID = 0;
	m_ValueSubTypeID = 0;
	m_Derived = FALSE;
	m_Formula = _T("");
	m_MCPosition = 0;
	m_MCLength = 0;
	m_MCDelimiter = _T("");
	m_PrimaryKeyPosition = 0;
	m_ValueMin = 0.0;
	m_ValueMax = 0.0;
	m_ValueAvg = 0.0;
	m_ValueModus = 0.0;
	m_ValueVariability = 0.0;
	m_Notice4 = _T("");
	m_wSavedCountUsed = 0;
	m_MatrixID3 = 0;
	m_Name4 = _T("");
	m_Initialised = FALSE;
	m_RecordCount = 0;
	m_Notice5 = _T("");
	m_wSavedCountUsed2 = 0;
	m_QuantityID2 = 0;
	m_Name5 = _T("");
	m_ShortName = _T("");
	m_ShowName = FALSE;
	m_AttributeID2 = 0;
	m_ItemShift = 0;
	m_ParentGroupID = 0;
	m_wSavedCountUsed3 = 0;
	m_wUpdateVer = 0;
	m_UserID2 = 0;
	m_Notice6 = _T("");
	m_CedentTypeID2 = 0;
	m_Name6 = _T("");
	m_ShortName2 = _T("");
	m_Ord3 = 0;
	m_Notice7 = _T("");
	m_CoefficientTypeID2 = 0;
	m_Name7 = _T("");
	m_ShortName3 = _T("");
	m_Ord4 = 0;
	m_Notice8 = _T("");
	m_GaceTypeID2 = 0;
	m_Name8 = _T("");
	m_ShortName4 = _T("");
	m_Ord5 = 0;
	m_Notice9 = _T("");
	m_LiteralTypeID2 = 0;
	m_Name9 = _T("");
	m_ShortName5 = _T("");
	m_Ord6 = 0;
	m_Notice10 = _T("");
	m_TaskSubTypeID2 = 0;
	m_Name10 = _T("");
	m_ShortName6 = _T("");
	m_Ord7 = 0;
	m_Notice11 = _T("");
	m_nFields = 95;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

CString Bool_Cedent_Recordset::GetDefaultSQL()
{
	return _T("[taTask],[tdCedentD],[tdLiteralD],[tmAttribute],[tmMatrix],[tmQuantity],[tsCedentType],[tsCoefficientType],[tsGaceType],[tsLiteralType],[tsTaskSubType]");
}

void Bool_Cedent_Recordset::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(Bool_Cedent_Recordset)
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
	RFX_Long(pFX, _T("[tdCedentD].[CedentDID]"), m_CedentDID);
	RFX_Long(pFX, _T("[tdCedentD].[TaskID]"), m_TaskID2);
	RFX_Long(pFX, _T("[tdCedentD].[CedentTypeID]"), m_CedentTypeID);
	RFX_Text(pFX, _T("[tdCedentD].[Name]"), m_Name2);
	RFX_Long(pFX, _T("[tdCedentD].[Ord]"), m_Ord);
	RFX_Long(pFX, _T("[tdCedentD].[MinLen]"), m_MinLen);
	RFX_Long(pFX, _T("[tdCedentD].[MaxLen]"), m_MaxLen);
	RFX_Text(pFX, _T("[tdCedentD].[Notice]"), m_Notice2);
	RFX_Long(pFX, _T("[LiteralDID]"), m_LiteralDID);
	RFX_Long(pFX, _T("[tdLiteralD].[CedentDID]"), m_CedentDID2);
	RFX_Long(pFX, _T("[tdLiteralD].[QuantityID]"), m_QuantityID);
	RFX_Long(pFX, _T("[CategoryID]"), m_CategoryID);
	RFX_Long(pFX, _T("[tdLiteralD].[LiteralTypeID]"), m_LiteralTypeID);
	RFX_Long(pFX, _T("[tdLiteralD].[GaceTypeID]"), m_GaceTypeID);
	RFX_Long(pFX, _T("[EquivalenceClassID]"), m_EquivalenceClassID);
	RFX_Long(pFX, _T("[tdLiteralD].[CoefficientTypeID]"), m_CoefficientTypeID);
	RFX_Long(pFX, _T("[tdLiteralD].[MinLen]"), m_MinLen2);
	RFX_Long(pFX, _T("[tdLiteralD].[MaxLen]"), m_MaxLen2);
	RFX_Long(pFX, _T("[tdLiteralD].[Ord]"), m_Ord2);
	RFX_Text(pFX, _T("[tdLiteralD].[Notice]"), m_Notice3);
	RFX_Long(pFX, _T("[tmAttribute].[AttributeID]"), m_AttributeID);
	RFX_Text(pFX, _T("[tmAttribute].[Name]"), m_Name3);
	RFX_Long(pFX, _T("[tmAttribute].[MatrixID]"), m_MatrixID2);
	RFX_Long(pFX, _T("[AttributeSubTypeID]"), m_AttributeSubTypeID);
	RFX_Long(pFX, _T("[ValueSubTypeID]"), m_ValueSubTypeID);
	RFX_Bool(pFX, _T("[Derived]"), m_Derived);
	RFX_Text(pFX, _T("[Formula]"), m_Formula);
	RFX_Long(pFX, _T("[MCPosition]"), m_MCPosition);
	RFX_Long(pFX, _T("[MCLength]"), m_MCLength);
	RFX_Text(pFX, _T("[MCDelimiter]"), m_MCDelimiter);
	RFX_Long(pFX, _T("[PrimaryKeyPosition]"), m_PrimaryKeyPosition);
	RFX_Double(pFX, _T("[ValueMin]"), m_ValueMin);
	RFX_Double(pFX, _T("[ValueMax]"), m_ValueMax);
	RFX_Double(pFX, _T("[ValueAvg]"), m_ValueAvg);
	RFX_Double(pFX, _T("[ValueModus]"), m_ValueModus);
	RFX_Double(pFX, _T("[ValueVariability]"), m_ValueVariability);
	RFX_Text(pFX, _T("[tmAttribute].[Notice]"), m_Notice4);
	RFX_Long(pFX, _T("[tmAttribute].[wSavedCountUsed]"), m_wSavedCountUsed);
	RFX_Long(pFX, _T("[tmMatrix].[MatrixID]"), m_MatrixID3);
	RFX_Text(pFX, _T("[tmMatrix].[Name]"), m_Name4);
	RFX_Bool(pFX, _T("[Initialised]"), m_Initialised);
	RFX_Long(pFX, _T("[RecordCount]"), m_RecordCount);
	RFX_Text(pFX, _T("[tmMatrix].[Notice]"), m_Notice5);
	RFX_Long(pFX, _T("[tmMatrix].[wSavedCountUsed]"), m_wSavedCountUsed2);
	RFX_Long(pFX, _T("[tmQuantity].[QuantityID]"), m_QuantityID2);
	RFX_Text(pFX, _T("[tmQuantity].[Name]"), m_Name5);
	RFX_Text(pFX, _T("[tmQuantity].[ShortName]"), m_ShortName);
	RFX_Bool(pFX, _T("[ShowName]"), m_ShowName);
	RFX_Long(pFX, _T("[tmQuantity].[AttributeID]"), m_AttributeID2);
	RFX_Long(pFX, _T("[ItemShift]"), m_ItemShift);
	RFX_Long(pFX, _T("[ParentGroupID]"), m_ParentGroupID);
	RFX_Long(pFX, _T("[tmQuantity].[wSavedCountUsed]"), m_wSavedCountUsed3);
	RFX_Long(pFX, _T("[wUpdateVer]"), m_wUpdateVer);
	RFX_Long(pFX, _T("[tmQuantity].[UserID]"), m_UserID2);
	RFX_Text(pFX, _T("[tmQuantity].[Notice]"), m_Notice6);
	RFX_Long(pFX, _T("[tsCedentType].[CedentTypeID]"), m_CedentTypeID2);
	RFX_Text(pFX, _T("[tsCedentType].[Name]"), m_Name6);
	RFX_Text(pFX, _T("[tsCedentType].[ShortName]"), m_ShortName2);
	RFX_Long(pFX, _T("[tsCedentType].[Ord]"), m_Ord3);
	RFX_Text(pFX, _T("[tsCedentType].[Notice]"), m_Notice7);
	RFX_Long(pFX, _T("[tsCoefficientType].[CoefficientTypeID]"), m_CoefficientTypeID2);
	RFX_Text(pFX, _T("[tsCoefficientType].[Name]"), m_Name7);
	RFX_Text(pFX, _T("[tsCoefficientType].[ShortName]"), m_ShortName3);
	RFX_Long(pFX, _T("[tsCoefficientType].[Ord]"), m_Ord4);
	RFX_Text(pFX, _T("[tsCoefficientType].[Notice]"), m_Notice8);
	RFX_Long(pFX, _T("[tsGaceType].[GaceTypeID]"), m_GaceTypeID2);
	RFX_Text(pFX, _T("[tsGaceType].[Name]"), m_Name8);
	RFX_Text(pFX, _T("[tsGaceType].[ShortName]"), m_ShortName4);
	RFX_Long(pFX, _T("[tsGaceType].[Ord]"), m_Ord5);
	RFX_Text(pFX, _T("[tsGaceType].[Notice]"), m_Notice9);
	RFX_Long(pFX, _T("[tsLiteralType].[LiteralTypeID]"), m_LiteralTypeID2);
	RFX_Text(pFX, _T("[tsLiteralType].[Name]"), m_Name9);
	RFX_Text(pFX, _T("[tsLiteralType].[ShortName]"), m_ShortName5);
	RFX_Long(pFX, _T("[tsLiteralType].[Ord]"), m_Ord6);
	RFX_Text(pFX, _T("[tsLiteralType].[Notice]"), m_Notice10);
	RFX_Long(pFX, _T("[tsTaskSubType].[TaskSubTypeID]"), m_TaskSubTypeID2);
	RFX_Text(pFX, _T("[tsTaskSubType].[Name]"), m_Name10);
	RFX_Text(pFX, _T("[tsTaskSubType].[ShortName]"), m_ShortName6);
	RFX_Long(pFX, _T("[tsTaskSubType].[Ord]"), m_Ord7);
	RFX_Text(pFX, _T("[tsTaskSubType].[Notice]"), m_Notice11);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// Bool_Cedent_Recordset diagnostics

#ifdef _DEBUG
void Bool_Cedent_Recordset::AssertValid() const
{
	CRecordset::AssertValid();
}

void Bool_Cedent_Recordset::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
