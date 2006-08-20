// TKLquant_Recordset.cpp : implementation file
//
#include "TKLquant_Recordset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// TKLquant_Recordset

IMPLEMENT_DYNAMIC(TKLquant_Recordset, CRecordset)

TKLquant_Recordset::TKLquant_Recordset(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(TKLquant_Recordset)
	m_KLLiteralDID = 0;
	m_KLCedentDID = 0;
	m_QuantityID = 0;
	m_Ord = 0;
	m_Notice = _T("");
	m_QuantityID2 = 0;
	m_Name = _T("");
	m_ShortName = _T("");
	m_ShowName = FALSE;
	m_AttributeID = 0;
	m_ItemShift = 0;
	m_ParentGroupID = 0;
	m_wSavedCountUsed = 0;
	m_wUpdateVer = 0;
	m_UserID = 0;
	m_Notice2 = _T("");
	m_nFields = 16;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

CString TKLquant_Recordset::GetDefaultSQL()
{
	return _T("[tdKLLiteralD],[tmQuantity]");
}

void TKLquant_Recordset::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(TKLquant_Recordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[KLLiteralDID]"), m_KLLiteralDID);
	RFX_Long(pFX, _T("[KLCedentDID]"), m_KLCedentDID);
	RFX_Long(pFX, _T("[tdKLLiteralD].[QuantityID]"), m_QuantityID);
	RFX_Long(pFX, _T("[Ord]"), m_Ord);
	RFX_Text(pFX, _T("[tdKLLiteralD].[Notice]"), m_Notice);
	RFX_Long(pFX, _T("[tmQuantity].[QuantityID]"), m_QuantityID2);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Text(pFX, _T("[ShortName]"), m_ShortName);
	RFX_Bool(pFX, _T("[ShowName]"), m_ShowName);
	RFX_Long(pFX, _T("[AttributeID]"), m_AttributeID);
	RFX_Long(pFX, _T("[ItemShift]"), m_ItemShift);
	RFX_Long(pFX, _T("[ParentGroupID]"), m_ParentGroupID);
	RFX_Long(pFX, _T("[wSavedCountUsed]"), m_wSavedCountUsed);
	RFX_Long(pFX, _T("[wUpdateVer]"), m_wUpdateVer);
	RFX_Long(pFX, _T("[UserID]"), m_UserID);
	RFX_Text(pFX, _T("[tmQuantity].[Notice]"), m_Notice2);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// TKLquant_Recordset diagnostics

#ifdef _DEBUG
void TKLquant_Recordset::AssertValid() const
{
	CRecordset::AssertValid();
}

void TKLquant_Recordset::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
