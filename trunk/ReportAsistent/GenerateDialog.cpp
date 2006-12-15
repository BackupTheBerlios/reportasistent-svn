// GenerateDialog.cpp : implementation file
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
#include "stdafx.h"
#include "ReportAsistent.h"
#include "GenerateDialog.h"
#include "CSkeletonDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGenerateDialog dialog


CGenerateDialog::CGenerateDialog(CSkeletonDoc & DocumentToGenerate, CWnd* pParent /*=NULL*/)
	: CDialog(CGenerateDialog::IDD, pParent), m_SkeletonDocument(DocumentToGenerate)
{
	CWordManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->WordManager;
	m_bNewWordChecked  = ! m.isWordEditorActive();

	//{{AFX_DATA_INIT(CGenerateDialog)
	//}}AFX_DATA_INIT
}


void CGenerateDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGenerateDialog)
	DDX_Check(pDX, IDC_NEW_WORD_CHECK, m_bNewWordChecked);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGenerateDialog, CDialog)
	//{{AFX_MSG_MAP(CGenerateDialog)
	ON_BN_CLICKED(IDC_GENERATE_BUTTON, OnGenerateButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGenerateDialog message handlers

void CGenerateDialog::OnGenerateButton() 
{
	UpdateData();
	
	m_SkeletonDocument.Generate(m_bNewWordChecked);
	
	EndDialog(IDOK);
}

BOOL CGenerateDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	GetDlgItem(IDC_NEW_WORD_CHECK)->EnableWindow(! m_bNewWordChecked);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


