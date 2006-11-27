// TColumn_Recordset.cpp : implementation file
//

#include "TColumn_Recordset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// TColumn_Recordset

IMPLEMENT_DYNAMIC(TColumn_Recordset, CRecordset)

TColumn_Recordset::TColumn_Recordset(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(TColumn_Recordset)
	m_AttributeID = 0;
	m_Name = _T("");
	m_MatrixID = 0;
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
	m_Notice = _T("");
	m_wSavedCountUsed = 0;
	m_MatrixID2 = 0;
	m_Name2 = _T("");
	m_Initialised = FALSE;
	m_RecordCount = 0;
	m_Notice2 = _T("");
	m_wSavedCountUsed2 = 0;
	m_AttributeSubTypeID2 = 0;
	m_Name3 = _T("");
	m_ShortName = _T("");
	m_Ord = 0;
	m_Notice3 = _T("");
	m_ValueSubTypeID2 = 0;
	m_Name4 = _T("");
	m_ShortName2 = _T("");
	m_Cardinal = FALSE;
	m_Ord2 = 0;
	m_Notice4 = _T("");
	m_nFields = 35;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString TColumn_Recordset::GetDefaultSQL()
{
	return _T("[tmAttribute],[tmMatrix],[tsAttributeSubType],[tsValueSubType]");
}

void TColumn_Recordset::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(TColumn_Recordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[AttributeID]"), m_AttributeID);
	RFX_Text(pFX, _T("[tmAttribute].[Name]"), m_Name);
	RFX_Long(pFX, _T("[tmAttribute].[MatrixID]"), m_MatrixID);
	RFX_Long(pFX, _T("[tmAttribute].[AttributeSubTypeID]"), m_AttributeSubTypeID);
	RFX_Long(pFX, _T("[tmAttribute].[ValueSubTypeID]"), m_ValueSubTypeID);
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
	RFX_Text(pFX, _T("[tmAttribute].[Notice]"), m_Notice);
	RFX_Long(pFX, _T("[tmAttribute].[wSavedCountUsed]"), m_wSavedCountUsed);
	RFX_Long(pFX, _T("[tmMatrix].[MatrixID]"), m_MatrixID2);
	RFX_Text(pFX, _T("[tmMatrix].[Name]"), m_Name2);
	RFX_Bool(pFX, _T("[Initialised]"), m_Initialised);
	RFX_Long(pFX, _T("[RecordCount]"), m_RecordCount);
	RFX_Text(pFX, _T("[tmMatrix].[Notice]"), m_Notice2);
	RFX_Long(pFX, _T("[tmMatrix].[wSavedCountUsed]"), m_wSavedCountUsed2);
	RFX_Long(pFX, _T("[tsAttributeSubType].[AttributeSubTypeID]"), m_AttributeSubTypeID2);
	RFX_Text(pFX, _T("[tsAttributeSubType].[Name]"), m_Name3);
	RFX_Text(pFX, _T("[tsAttributeSubType].[ShortName]"), m_ShortName);
	RFX_Long(pFX, _T("[tsAttributeSubType].[Ord]"), m_Ord);
	RFX_Text(pFX, _T("[tsAttributeSubType].[Notice]"), m_Notice3);
	RFX_Long(pFX, _T("[tsValueSubType].[ValueSubTypeID]"), m_ValueSubTypeID2);
	RFX_Text(pFX, _T("[tsValueSubType].[Name]"), m_Name4);
	RFX_Text(pFX, _T("[tsValueSubType].[ShortName]"), m_ShortName2);
	RFX_Bool(pFX, _T("[Cardinal]"), m_Cardinal);
	RFX_Long(pFX, _T("[tsValueSubType].[Ord]"), m_Ord2);
	RFX_Text(pFX, _T("[tsValueSubType].[Notice]"), m_Notice4);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// TColumn_Recordset diagnostics

#ifdef _DEBUG
void TColumn_Recordset::AssertValid() const
{
	CRecordset::AssertValid();
}

void TColumn_Recordset::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
