// TData_Matrix_Recordset.cpp : implementation file
//
#include "TData_Matrix_Recordset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// TData_Matrix_Recordset

IMPLEMENT_DYNAMIC(TData_Matrix_Recordset, CRecordset)

TData_Matrix_Recordset::TData_Matrix_Recordset(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(TData_Matrix_Recordset)
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
	m_ValueSubTypeID2 = 0;
	m_Name3 = _T("");
	m_ShortName = _T("");
	m_Cardinal = FALSE;
	m_Ord = 0;
	m_Notice3 = _T("");
	m_nFields = 30;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

CString TData_Matrix_Recordset::GetDefaultSQL()
{
	return _T("[tmAttribute],[tmMatrix],[tsValueSubType]");
}

void TData_Matrix_Recordset::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(TData_Matrix_Recordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[AttributeID]"), m_AttributeID);
	RFX_Text(pFX, _T("[tmAttribute].[Name]"), m_Name);
	RFX_Long(pFX, _T("[tmAttribute].[MatrixID]"), m_MatrixID);
	RFX_Long(pFX, _T("[AttributeSubTypeID]"), m_AttributeSubTypeID);
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
	RFX_Long(pFX, _T("[tsValueSubType].[ValueSubTypeID]"), m_ValueSubTypeID2);
	RFX_Text(pFX, _T("[tsValueSubType].[Name]"), m_Name3);
	RFX_Text(pFX, _T("[ShortName]"), m_ShortName);
	RFX_Bool(pFX, _T("[Cardinal]"), m_Cardinal);
	RFX_Long(pFX, _T("[Ord]"), m_Ord);
	RFX_Text(pFX, _T("[tsValueSubType].[Notice]"), m_Notice3);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// TData_Matrix_Recordset diagnostics

#ifdef _DEBUG
void TData_Matrix_Recordset::AssertValid() const
{
	CRecordset::AssertValid();
}

void TData_Matrix_Recordset::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
