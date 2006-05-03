// TCatDefEnum.cpp : implementation file
//

#include "TCatDefEnum.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// TCatDefEnum

IMPLEMENT_DYNAMIC(TCatDefEnum, CRecordset)

TCatDefEnum::TCatDefEnum(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(TCatDefEnum)
	m_CategoryEnumValueID = 0;
	m_CategoryID = 0;
	m_ValueID = 0;
	m_ValueID2 = 0;
	m_ValueSubTypeID = 0;
	m_ValueLong = 0;
	m_ValueFloat = 0.0;
	m_ValueString = _T("");
	m_ValueBool = FALSE;
	m_InfinityTypeID = 0;
	m_IsNULL = FALSE;
	m_ValueSubTypeID2 = 0;
	m_Name = _T("");
	m_ShortName = _T("");
	m_Ord = 0;
	m_Notice = _T("");
	m_Cardinal = FALSE;
	m_nFields = 18;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString TCatDefEnum::GetDefaultSQL()
{
	return _T("[tmCategoryEnumValue],[tmValue],[tsValueSubType]");
}

void TCatDefEnum::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(TCatDefEnum)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[CategoryEnumValueID]"), m_CategoryEnumValueID);
	RFX_Long(pFX, _T("[CategoryID]"), m_CategoryID);
	RFX_Long(pFX, _T("[tmCategoryEnumValue].[ValueID]"), m_ValueID);
	RFX_Long(pFX, _T("[tmValue].[ValueID]"), m_ValueID2);
	RFX_Long(pFX, _T("[tmValue].[ValueSubTypeID]"), m_ValueSubTypeID);
	RFX_Long(pFX, _T("[ValueLong]"), m_ValueLong);
	RFX_Double(pFX, _T("[ValueFloat]"), m_ValueFloat);
	RFX_Text(pFX, _T("[ValueString]"), m_ValueString);
	RFX_Bool(pFX, _T("[ValueBool]"), m_ValueBool);
	RFX_Date(pFX, _T("[ValueDate]"), m_ValueDate);
	RFX_Long(pFX, _T("[InfinityTypeID]"), m_InfinityTypeID);
	RFX_Bool(pFX, _T("[IsNULL]"), m_IsNULL);
	RFX_Long(pFX, _T("[tsValueSubType].[ValueSubTypeID]"), m_ValueSubTypeID2);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Text(pFX, _T("[ShortName]"), m_ShortName);
	RFX_Long(pFX, _T("[Ord]"), m_Ord);
	RFX_Text(pFX, _T("[Notice]"), m_Notice);
	RFX_Bool(pFX, _T("[Cardinal]"), m_Cardinal);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// TCatDefEnum diagnostics

#ifdef _DEBUG
void TCatDefEnum::AssertValid() const
{
	CRecordset::AssertValid();
}

void TCatDefEnum::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG