// TCatDef.cpp : implementation file
//
#include "TCatDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// TCatDef

IMPLEMENT_DYNAMIC(TCatDef, CRecordset)

TCatDef::TCatDef(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(TCatDef)
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
	m_CategoryEnumValueID = 0;
	m_CategoryID2 = 0;
	m_ValueID = 0;
	m_IntervalID = 0;
	m_CategoryID3 = 0;
	m_FromValueID = 0;
	m_ToValueID = 0;
	m_LeftBracketTypeID = 0;
	m_RightBracketTypeID = 0;
	m_ValueID2 = 0;
	m_ValueSubTypeID = 0;
	m_ValueLong = 0;
	m_ValueFloat = 0.0;
	m_ValueString = _T("");
	m_ValueBool = FALSE;
	m_InfinityTypeID = 0;
	m_IsNULL = FALSE;
	m_BracketTypeID = 0;
	m_Name2 = _T("");
	m_ShortName = _T("");
	m_Ord2 = 0;
	m_LeftBracket = _T("");
	m_RightBracket = _T("");
	m_Notice2 = _T("");
	m_id = 0;
	m_TypeName = _T("");
	m_nFields = 37;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

CString TCatDef::GetDefaultSQL()
{
	return _T("[tmCategory],[tmCategoryEnumValue],[tmInterval],[tmValue],[tsBracketType],[tsValueSubType]");
}

void TCatDef::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(TCatDef)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[tmCategory].[CategoryID]"), m_CategoryID);
	RFX_Text(pFX, _T("[tmCategory].[Name]"), m_Name);
	RFX_Long(pFX, _T("[QuantityID]"), m_QuantityID);
	RFX_Long(pFX, _T("[CategorySubTypeID]"), m_CategorySubTypeID);
	RFX_Long(pFX, _T("[BoolTypeID]"), m_BoolTypeID);
	RFX_Bool(pFX, _T("[XCategory]"), m_XCategory);
	RFX_Bool(pFX, _T("[IncludeNULL]"), m_IncludeNULL);
	RFX_Long(pFX, _T("[tmCategory].[Ord]"), m_Ord);
	RFX_Text(pFX, _T("[tmCategory].[Notice]"), m_Notice);
	RFX_Long(pFX, _T("[wSavedCountUsed]"), m_wSavedCountUsed);
	RFX_Long(pFX, _T("[CategoryEnumValueID]"), m_CategoryEnumValueID);
	RFX_Long(pFX, _T("[tmCategoryEnumValue].[CategoryID]"), m_CategoryID2);
	RFX_Long(pFX, _T("[tmCategoryEnumValue].[ValueID]"), m_ValueID);
	RFX_Long(pFX, _T("[IntervalID]"), m_IntervalID);
	RFX_Long(pFX, _T("[tmInterval].[CategoryID]"), m_CategoryID3);
	RFX_Long(pFX, _T("[FromValueID]"), m_FromValueID);
	RFX_Long(pFX, _T("[ToValueID]"), m_ToValueID);
	RFX_Long(pFX, _T("[LeftBracketTypeID]"), m_LeftBracketTypeID);
	RFX_Long(pFX, _T("[RightBracketTypeID]"), m_RightBracketTypeID);
	RFX_Long(pFX, _T("[tmValue].[ValueID]"), m_ValueID2);
	RFX_Long(pFX, _T("[ValueSubTypeID]"), m_ValueSubTypeID);
	RFX_Long(pFX, _T("[ValueLong]"), m_ValueLong);
	RFX_Double(pFX, _T("[ValueFloat]"), m_ValueFloat);
	RFX_Text(pFX, _T("[ValueString]"), m_ValueString);
	RFX_Bool(pFX, _T("[ValueBool]"), m_ValueBool);
	RFX_Date(pFX, _T("[ValueDate]"), m_ValueDate);
	RFX_Long(pFX, _T("[InfinityTypeID]"), m_InfinityTypeID);
	RFX_Bool(pFX, _T("[IsNULL]"), m_IsNULL);
	RFX_Long(pFX, _T("[BracketTypeID]"), m_BracketTypeID);
	RFX_Text(pFX, _T("[tsBracketType].[Name]"), m_Name2);
	RFX_Text(pFX, _T("[ShortName]"), m_ShortName);
	RFX_Long(pFX, _T("[tsBracketType].[Ord]"), m_Ord2);
	RFX_Text(pFX, _T("[LeftBracket]"), m_LeftBracket);
	RFX_Text(pFX, _T("[RightBracket]"), m_RightBracket);
	RFX_Text(pFX, _T("[tsBracketType].[Notice]"), m_Notice2);
	RFX_Long(pFX, _T("[tsValueSubType].[ValueSubTypeID]"), m_id);
	RFX_Text(pFX, _T("[tsValueSubType].[ShortName]"), m_TypeName);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// TCatDef diagnostics

#ifdef _DEBUG
void TCatDef::AssertValid() const
{
	CRecordset::AssertValid();
}

void TCatDef::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
