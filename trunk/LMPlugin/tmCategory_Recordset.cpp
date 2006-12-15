// tmCategory_Recordset.cpp : implementation file
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
#include "tmCategory_Recordset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// tmCategory_Recordset

IMPLEMENT_DYNAMIC(tmCategory_Recordset, CRecordset)

tmCategory_Recordset::tmCategory_Recordset(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(tmCategory_Recordset)
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

CString tmCategory_Recordset::GetDefaultSQL()
{
	return _T("[tmCategory]");
}

void tmCategory_Recordset::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(tmCategory_Recordset)
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
// tmCategory_Recordset diagnostics

#ifdef _DEBUG
void tmCategory_Recordset::AssertValid() const
{
	CRecordset::AssertValid();
}

void tmCategory_Recordset::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
