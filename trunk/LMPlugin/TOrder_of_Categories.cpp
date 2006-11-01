// TOrder_of_Categories.cpp : implementation file
//
#include "TOrder_of_Categories.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// TOrder_of_Categories

IMPLEMENT_DYNAMIC(TOrder_of_Categories, CRecordset)

TOrder_of_Categories::TOrder_of_Categories(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(TOrder_of_Categories)
	m_CategoryID = 0;
	m_Name = _T("");
	m_QuantityID = 0;
	m_CategorySubTypeID = 0;
	m_BoolTypeID = 0;
	m_XCategory = FALSE;
	m_IncludeNULL = FALSE;
	m_Ord = 0;
	m_Notice = _T("");
	m_wSavedCountUsed = 0;
	m_QuantityID2 = 0;
	m_Name2 = _T("");
	m_ShortName = _T("");
	m_ShowName = FALSE;
	m_AttributeID = 0;
	m_ItemShift = 0;
	m_ParentGroupID = 0;
	m_wSavedCountUsed2 = 0;
	m_wUpdateVer = 0;
	m_UserID = 0;
	m_Notice2 = _T("");
	m_nFields = 21;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

CString TOrder_of_Categories::GetDefaultSQL()
{
	return _T("[tmCategory],[tmQuantity]");
}

void TOrder_of_Categories::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(TOrder_of_Categories)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[CategoryID]"), m_CategoryID);
	RFX_Text(pFX, _T("[tmCategory].[Name]"), m_Name);
	RFX_Long(pFX, _T("[tmCategory].[QuantityID]"), m_QuantityID);
	RFX_Long(pFX, _T("[CategorySubTypeID]"), m_CategorySubTypeID);
	RFX_Long(pFX, _T("[BoolTypeID]"), m_BoolTypeID);
	RFX_Bool(pFX, _T("[XCategory]"), m_XCategory);
	RFX_Bool(pFX, _T("[IncludeNULL]"), m_IncludeNULL);
	RFX_Long(pFX, _T("[Ord]"), m_Ord);
	RFX_Text(pFX, _T("[tmCategory].[Notice]"), m_Notice);
	RFX_Long(pFX, _T("[tmCategory].[wSavedCountUsed]"), m_wSavedCountUsed);
	RFX_Long(pFX, _T("[tmQuantity].[QuantityID]"), m_QuantityID2);
	RFX_Text(pFX, _T("[tmQuantity].[Name]"), m_Name2);
	RFX_Text(pFX, _T("[ShortName]"), m_ShortName);
	RFX_Bool(pFX, _T("[ShowName]"), m_ShowName);
	RFX_Long(pFX, _T("[AttributeID]"), m_AttributeID);
	RFX_Long(pFX, _T("[ItemShift]"), m_ItemShift);
	RFX_Long(pFX, _T("[ParentGroupID]"), m_ParentGroupID);
	RFX_Long(pFX, _T("[tmQuantity].[wSavedCountUsed]"), m_wSavedCountUsed2);
	RFX_Long(pFX, _T("[wUpdateVer]"), m_wUpdateVer);
	RFX_Long(pFX, _T("[UserID]"), m_UserID);
	RFX_Text(pFX, _T("[tmQuantity].[Notice]"), m_Notice2);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// TOrder_of_Categories diagnostics

#ifdef _DEBUG
void TOrder_of_Categories::AssertValid() const
{
	CRecordset::AssertValid();
}

void TOrder_of_Categories::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
