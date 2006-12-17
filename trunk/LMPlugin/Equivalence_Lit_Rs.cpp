// Equivalence_Lit_Rs.cpp : implementation file
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
