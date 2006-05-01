// Equivalence_Lit_Rs.cpp : implementation file
//

#include "Equivalence_Lit_Rs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Equivalence_Lit_Rs

IMPLEMENT_DYNAMIC(Equivalence_Lit_Rs, CRecordset)

Equivalence_Lit_Rs::Equivalence_Lit_Rs(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(Equivalence_Lit_Rs)
	m_EquivalenceClassID = 0;
	m_Name = _T("");
	m_CedentDID = 0;
	m_Notice = _T("");
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

CString Equivalence_Lit_Rs::GetDefaultSQL()
{
	return _T("[tdEquivalenceClass]");
}

void Equivalence_Lit_Rs::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(Equivalence_Lit_Rs)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[EquivalenceClassID]"), m_EquivalenceClassID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Long(pFX, _T("[CedentDID]"), m_CedentDID);
	RFX_Text(pFX, _T("[Notice]"), m_Notice);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// Equivalence_Lit_Rs diagnostics

#ifdef _DEBUG
void Equivalence_Lit_Rs::AssertValid() const
{
	CRecordset::AssertValid();
}

void Equivalence_Lit_Rs::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
