// tiDKFrequencyI_Recordset.cpp : implementation file
//

#include "tiDKFrequencyI_Recordset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// tiDKFrequencyI_Recordset

IMPLEMENT_DYNAMIC(tiDKFrequencyI_Recordset, CRecordset)

tiDKFrequencyI_Recordset::tiDKFrequencyI_Recordset(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(tiDKFrequencyI_Recordset)
	m_DKFrequencyIID = 0;
	m_HypothesisDKID = 0;
	m_CedentTypeID = 0;
	m_Row = 0;
	m_Col = 0;
	m_Frequency = 0;
	m_TaskID = 0;
	m_nFields = 7;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

CString tiDKFrequencyI_Recordset::GetDefaultSQL()
{
	return _T("[tiDKFrequencyI]");
}

void tiDKFrequencyI_Recordset::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(tiDKFrequencyI_Recordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[DKFrequencyIID]"), m_DKFrequencyIID);
	RFX_Long(pFX, _T("[HypothesisDKID]"), m_HypothesisDKID);
	RFX_Long(pFX, _T("[CedentTypeID]"), m_CedentTypeID);
	RFX_Long(pFX, _T("[Row]"), m_Row);
	RFX_Long(pFX, _T("[Col]"), m_Col);
	RFX_Long(pFX, _T("[Frequency]"), m_Frequency);
	RFX_Long(pFX, _T("[TaskID]"), m_TaskID);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// tiDKFrequencyI_Recordset diagnostics

#ifdef _DEBUG
void tiDKFrequencyI_Recordset::AssertValid() const
{
	CRecordset::AssertValid();
}

void tiDKFrequencyI_Recordset::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
