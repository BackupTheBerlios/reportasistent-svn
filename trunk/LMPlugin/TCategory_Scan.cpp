// TCategory_Scan.cpp : implementation file
//

#include "TCategory_Scan.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// TCategory_Scan

IMPLEMENT_DYNAMIC(TCategory_Scan, CRecordset)

TCategory_Scan::TCategory_Scan(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(TCategory_Scan)
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
	m_nFields = 10;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

CString TCategory_Scan::GetDefaultSQL()
{
	return _T("[tmCategory]");
}

void TCategory_Scan::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(TCategory_Scan)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[CategoryID]"), m_CategoryID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Long(pFX, _T("[QuantityID]"), m_QuantityID);
	RFX_Long(pFX, _T("[CategorySubTypeID]"), m_CategorySubTypeID);
	RFX_Long(pFX, _T("[BoolTypeID]"), m_BoolTypeID);
	RFX_Bool(pFX, _T("[XCategory]"), m_XCategory);
	RFX_Bool(pFX, _T("[IncludeNULL]"), m_IncludeNULL);
	RFX_Long(pFX, _T("[Ord]"), m_Ord);
	RFX_Text(pFX, _T("[Notice]"), m_Notice);
	RFX_Long(pFX, _T("[wSavedCountUsed]"), m_wSavedCountUsed);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// TCategory_Scan diagnostics

#ifdef _DEBUG
void TCategory_Scan::AssertValid() const
{
	CRecordset::AssertValid();
}

void TCategory_Scan::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
