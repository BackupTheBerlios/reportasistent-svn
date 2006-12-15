// TLit_Scan_Recordset.cpp : implementation file
//
/*
This file is part of LM Report Asistent.

Authors: Jan Dedek, Jan Kodym, Martin Chrz, Iva Bartunkova

LM Report Asistent is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

Foobar is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Foobar; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include "TLit_Scan_Recordset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// TLit_Scan_Recordset

IMPLEMENT_DYNAMIC(TLit_Scan_Recordset, CRecordset)

TLit_Scan_Recordset::TLit_Scan_Recordset(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(TLit_Scan_Recordset)
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
	m_nFields = 12;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

CString TLit_Scan_Recordset::GetDefaultSQL()
{
	return _T("[tdLiteralD]");
}

void TLit_Scan_Recordset::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(TLit_Scan_Recordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[LiteralDID]"), m_LiteralDID);
	RFX_Long(pFX, _T("[CedentDID]"), m_CedentDID);
	RFX_Long(pFX, _T("[QuantityID]"), m_QuantityID);
	RFX_Long(pFX, _T("[CategoryID]"), m_CategoryID);
	RFX_Long(pFX, _T("[LiteralTypeID]"), m_LiteralTypeID);
	RFX_Long(pFX, _T("[GaceTypeID]"), m_GaceTypeID);
	RFX_Long(pFX, _T("[EquivalenceClassID]"), m_EquivalenceClassID);
	RFX_Long(pFX, _T("[CoefficientTypeID]"), m_CoefficientTypeID);
	RFX_Long(pFX, _T("[MinLen]"), m_MinLen);
	RFX_Long(pFX, _T("[MaxLen]"), m_MaxLen);
	RFX_Long(pFX, _T("[Ord]"), m_Ord);
	RFX_Text(pFX, _T("[Notice]"), m_Notice);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// TLit_Scan_Recordset diagnostics

#ifdef _DEBUG
void TLit_Scan_Recordset::AssertValid() const
{
	CRecordset::AssertValid();
}

void TLit_Scan_Recordset::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
