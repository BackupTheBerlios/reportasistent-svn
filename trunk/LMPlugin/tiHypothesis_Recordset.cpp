// tiHypothesis_Recordset.cpp : implementation file
//
/*
This file is part of LM Report Asistent.

Authors: Jan Dedek, Jan Kodym, Martin Chrz, Iva Bartunkova

LM Report Asistent is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

LM Report Asistent is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with LM Report Asistent; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include "tiHypothesis_Recordset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// tiHypothesis_Recordset

IMPLEMENT_DYNAMIC(tiHypothesis_Recordset, CRecordset)

tiHypothesis_Recordset::tiHypothesis_Recordset(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(tiHypothesis_Recordset)
	m_HypothesisID = 0;
	m_TaskID = 0;
	m_FreqA = 0;
	m_FreqB = 0;
	m_FreqC = 0;
	m_FreqD = 0;
	m_Weight = 0.0;
	m_Ord = 0;
	m_nFields = 8;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

CString tiHypothesis_Recordset::GetDefaultSQL()
{
	return _T("[tiHypothesis]");
}

void tiHypothesis_Recordset::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(tiHypothesis_Recordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[HypothesisID]"), m_HypothesisID);
	RFX_Long(pFX, _T("[TaskID]"), m_TaskID);
	RFX_Long(pFX, _T("[FreqA]"), m_FreqA);
	RFX_Long(pFX, _T("[FreqB]"), m_FreqB);
	RFX_Long(pFX, _T("[FreqC]"), m_FreqC);
	RFX_Long(pFX, _T("[FreqD]"), m_FreqD);
	RFX_Double(pFX, _T("[Weight]"), m_Weight);
	RFX_Long(pFX, _T("[Ord]"), m_Ord);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// tiHypothesis_Recordset diagnostics

#ifdef _DEBUG
void tiHypothesis_Recordset::AssertValid() const
{
	CRecordset::AssertValid();
}

void tiHypothesis_Recordset::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
