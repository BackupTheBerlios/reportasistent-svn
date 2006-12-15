// tiDKFrequencyI_Recordset.cpp : implementation file
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
