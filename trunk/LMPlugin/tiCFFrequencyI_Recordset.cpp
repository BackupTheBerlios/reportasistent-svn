// tiCFFrequencyI_Recordset.cpp : implementation file
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
#include "tiCFFrequencyI_Recordset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// tiCFFrequencyI_Recordset

IMPLEMENT_DYNAMIC(tiCFFrequencyI_Recordset, CRecordset)

tiCFFrequencyI_Recordset::tiCFFrequencyI_Recordset(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(tiCFFrequencyI_Recordset)
	m_CFFrequencyIID = 0;
	m_HypothesisCFID = 0;
	m_Col = 0;
	m_Frequency = 0;
	m_TaskID = 0;
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

CString tiCFFrequencyI_Recordset::GetDefaultSQL()
{
	return _T("[tiCFFrequencyI]");
}

void tiCFFrequencyI_Recordset::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(tiCFFrequencyI_Recordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[CFFrequencyIID]"), m_CFFrequencyIID);
	RFX_Long(pFX, _T("[HypothesisCFID]"), m_HypothesisCFID);
	RFX_Long(pFX, _T("[Col]"), m_Col);
	RFX_Long(pFX, _T("[Frequency]"), m_Frequency);
	RFX_Long(pFX, _T("[TaskID]"), m_TaskID);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// tiCFFrequencyI_Recordset diagnostics

#ifdef _DEBUG
void tiCFFrequencyI_Recordset::AssertValid() const
{
	CRecordset::AssertValid();
}

void tiCFFrequencyI_Recordset::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
