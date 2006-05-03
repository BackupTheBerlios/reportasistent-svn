// TCatOrder.cpp : implementation file
//

#include "TCatOrder.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// TCatOrder

IMPLEMENT_DYNAMIC(TCatOrder, CRecordset)

TCatOrder::TCatOrder(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(TCatOrder)
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
	m_CategoryID = 0;
	m_Name2 = _T("");
	m_QuantityID = 0;
	m_CategorySubTypeID = 0;
	m_BoolTypeID = 0;
	m_XCategory = FALSE;
	m_IncludeNULL = FALSE;
	m_Ord = 0;
	m_Notice2 = _T("");
	m_wSavedCountUsed2 = 0;
	m_QuantityID2 = 0;
	m_Name3 = _T("");
	m_ShortName = _T("");
	m_ShowName = FALSE;
	m_AttributeID2 = 0;
	m_ItemShift = 0;
	m_ParentGroupID = 0;
	m_wSavedCountUsed3 = 0;
	m_wUpdateVer = 0;
	m_UserID = 0;
	m_Notice3 = _T("");
	m_nFields = 39;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

CString TCatOrder::GetDefaultSQL()
{
	return _T("[tmAttribute],[tmCategory],[tmQuantity]");
}

void TCatOrder::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(TCatOrder)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[tmAttribute].[AttributeID]"), m_AttributeID);
	RFX_Text(pFX, _T("[tmAttribute].[Name]"), m_Name);
	RFX_Long(pFX, _T("[MatrixID]"), m_MatrixID);
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
	RFX_Text(pFX, _T("[tmAttribute].[Notice]"), m_Notice);
	RFX_Long(pFX, _T("[tmAttribute].[wSavedCountUsed]"), m_wSavedCountUsed);
	RFX_Long(pFX, _T("[CategoryID]"), m_CategoryID);
	RFX_Text(pFX, _T("[tmCategory].[Name]"), m_Name2);
	RFX_Long(pFX, _T("[tmCategory].[QuantityID]"), m_QuantityID);
	RFX_Long(pFX, _T("[CategorySubTypeID]"), m_CategorySubTypeID);
	RFX_Long(pFX, _T("[BoolTypeID]"), m_BoolTypeID);
	RFX_Bool(pFX, _T("[XCategory]"), m_XCategory);
	RFX_Bool(pFX, _T("[IncludeNULL]"), m_IncludeNULL);
	RFX_Long(pFX, _T("[Ord]"), m_Ord);
	RFX_Text(pFX, _T("[tmCategory].[Notice]"), m_Notice2);
	RFX_Long(pFX, _T("[tmCategory].[wSavedCountUsed]"), m_wSavedCountUsed2);
	RFX_Long(pFX, _T("[tmQuantity].[QuantityID]"), m_QuantityID2);
	RFX_Text(pFX, _T("[tmQuantity].[Name]"), m_Name3);
	RFX_Text(pFX, _T("[ShortName]"), m_ShortName);
	RFX_Bool(pFX, _T("[ShowName]"), m_ShowName);
	RFX_Long(pFX, _T("[tmQuantity].[AttributeID]"), m_AttributeID2);
	RFX_Long(pFX, _T("[ItemShift]"), m_ItemShift);
	RFX_Long(pFX, _T("[ParentGroupID]"), m_ParentGroupID);
	RFX_Long(pFX, _T("[tmQuantity].[wSavedCountUsed]"), m_wSavedCountUsed3);
	RFX_Long(pFX, _T("[wUpdateVer]"), m_wUpdateVer);
	RFX_Long(pFX, _T("[UserID]"), m_UserID);
	RFX_Text(pFX, _T("[tmQuantity].[Notice]"), m_Notice3);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// TCatOrder diagnostics

#ifdef _DEBUG
void TCatOrder::AssertValid() const
{
	CRecordset::AssertValid();
}

void TCatOrder::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG