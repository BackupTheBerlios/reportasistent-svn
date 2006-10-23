// TCoef_type_Recordset.cpp : implementation file
//
#include "TCoef_type_Recordset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// TCoef_type_Recordset

IMPLEMENT_DYNAMIC(TCoef_type_Recordset, CRecordset)

TCoef_type_Recordset::TCoef_type_Recordset(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(TCoef_type_Recordset)
	m_LiteralDID = 0;
	m_CedentDID = 0;
	m_QuantityID = 0;
	m_CategoryID = 0;
	m_LiteralTypeID = 0;
	m_GaceTypeID = 0;
	m_EquivalenceClassID = 0;
	m_CoefficientTypeID = 0;
	m_MinLen = 0;
	m_MaxLen = 0;
	m_Ord = 0;
	m_Notice = _T("");
	m_CoefficientTypeID2 = 0;
	m_Name = _T("");
	m_ShortName = _T("");
	m_Ord2 = 0;
	m_Notice2 = _T("");
	m_nFields = 17;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

CString TCoef_type_Recordset::GetDefaultSQL()
{
	return _T("[tdLiteralD],[tsCoefficientType]");
}

void TCoef_type_Recordset::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(TCoef_type_Recordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[LiteralDID]"), m_LiteralDID);
	RFX_Long(pFX, _T("[CedentDID]"), m_CedentDID);
	RFX_Long(pFX, _T("[QuantityID]"), m_QuantityID);
	RFX_Long(pFX, _T("[CategoryID]"), m_CategoryID);
	RFX_Long(pFX, _T("[LiteralTypeID]"), m_LiteralTypeID);
	RFX_Long(pFX, _T("[GaceTypeID]"), m_GaceTypeID);
	RFX_Long(pFX, _T("[EquivalenceClassID]"), m_EquivalenceClassID);
	RFX_Long(pFX, _T("[tdLiteralD].[CoefficientTypeID]"), m_CoefficientTypeID);
	RFX_Long(pFX, _T("[MinLen]"), m_MinLen);
	RFX_Long(pFX, _T("[MaxLen]"), m_MaxLen);
	RFX_Long(pFX, _T("[tdLiteralD].[Ord]"), m_Ord);
	RFX_Text(pFX, _T("[tdLiteralD].[Notice]"), m_Notice);
	RFX_Long(pFX, _T("[tsCoefficientType].[CoefficientTypeID]"), m_CoefficientTypeID2);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Text(pFX, _T("[ShortName]"), m_ShortName);
	RFX_Long(pFX, _T("[tsCoefficientType].[Ord]"), m_Ord2);
	RFX_Text(pFX, _T("[tsCoefficientType].[Notice]"), m_Notice2);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// TCoef_type_Recordset diagnostics

#ifdef _DEBUG
void TCoef_type_Recordset::AssertValid() const
{
	CRecordset::AssertValid();
}

void TCoef_type_Recordset::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
