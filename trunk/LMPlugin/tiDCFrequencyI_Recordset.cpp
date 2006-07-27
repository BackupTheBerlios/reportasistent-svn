// tiDCFrequencyI_Recordset.cpp : implementation file
//

#include "tiDCFrequencyI_Recordset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// tiDCFrequencyI_Recordset

IMPLEMENT_DYNAMIC(tiDCFrequencyI_Recordset, CRecordset)

tiDCFrequencyI_Recordset::tiDCFrequencyI_Recordset(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(tiDCFrequencyI_Recordset)
	m_DCFrequencyIID = 0;
	m_HypothesisDCID = 0;
	m_CedentTypeID = 0;
	m_TaskID = 0;
	m_Col = 0;
	m_Frequency = 0;
	m_nFields = 6;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

CString tiDCFrequencyI_Recordset::GetDefaultSQL()
{
	return _T("[tiDCFrequencyI]");
}

void tiDCFrequencyI_Recordset::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(tiDCFrequencyI_Recordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[DCFrequencyIID]"), m_DCFrequencyIID);
	RFX_Long(pFX, _T("[HypothesisDCID]"), m_HypothesisDCID);
	RFX_Long(pFX, _T("[CedentTypeID]"), m_CedentTypeID);
	RFX_Long(pFX, _T("[TaskID]"), m_TaskID);
	RFX_Long(pFX, _T("[Col]"), m_Col);
	RFX_Long(pFX, _T("[Frequency]"), m_Frequency);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// tiDCFrequencyI_Recordset diagnostics

#ifdef _DEBUG
void tiDCFrequencyI_Recordset::AssertValid() const
{
	CRecordset::AssertValid();
}

void tiDCFrequencyI_Recordset::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
