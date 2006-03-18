// Hyp_4ft_Recordset.cpp : implementation file
//
#include "Hyp_4ft_Recordset.h"

//extern CMetabase_load_pok1App theApp;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Hyp_4ft_Recordset

IMPLEMENT_DYNAMIC(Hyp_4ft_Recordset, CRecordset)

Hyp_4ft_Recordset::Hyp_4ft_Recordset(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(Hyp_4ft_Recordset)
	m_HypothesisID = 0;
	m_MatrixID = 0;
	m_MatrixName = "";
	m_TaskID = 0;
	m_TaskName = "";
	m_FreqA = 0;
	m_FreqB = 0;
	m_FreqC = 0;
	m_FreqD = 0;
	m_LiteralID = 0;
	m_CedentTypeName = "";
	m_CategoryID = 0;
	m_QuantityID = "";
	m_Qvalue = "";
	m_nFields = 14;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


/*CString Hyp_4ft_Recordset::GetDefaultConnect()
{
	return _T("ODBC;DSN=LM LMEntry.mdb Metabase");
}*/

CString Hyp_4ft_Recordset::GetDefaultSQL()
{
	return _T("[taTask], [tsCedentType],[tiCoefficient],[tiHypothesis],[tiLiteralI],[tmCategory],[tmMatrix],[tmQuantity]");
}

void Hyp_4ft_Recordset::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(Hyp_4ft_Recordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[tiHypothesis.HypothesisID]"), m_HypothesisID);
	RFX_Long(pFX, _T("[taTask.MatrixID]"), m_MatrixID);
	RFX_Text(pFX, _T("[tmMatrix.Name]"), m_MatrixName);
	RFX_Long(pFX, _T("[tiHypothesis.TaskID]"), m_TaskID);
	RFX_Text(pFX, _T("[taTask.Name]"), m_TaskName);
	RFX_Long(pFX, _T("[FreqA]"), m_FreqA);
	RFX_Long(pFX, _T("[FreqB]"), m_FreqB);
	RFX_Long(pFX, _T("[FreqC]"), m_FreqC);
	RFX_Long(pFX, _T("[FreqD]"), m_FreqD);
	RFX_Long(pFX, _T("[LiteralIID]"), m_LiteralID);
	RFX_Text(pFX, _T("[tsCedentType.Name]"), m_CedentTypeName);
	RFX_Long(pFX, _T("[tmCategory.CategoryID]"), m_CategoryID);
	RFX_Text(pFX, _T("[tmCategory.QuantityID]"), m_QuantityID);
	RFX_Text(pFX, _T("[tmCategory.Name]"), m_Qvalue);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// Hyp_4ft_Recordset diagnostics

#ifdef _DEBUG
void Hyp_4ft_Recordset::AssertValid() const
{
	CRecordset::AssertValid();
}

void Hyp_4ft_Recordset::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
