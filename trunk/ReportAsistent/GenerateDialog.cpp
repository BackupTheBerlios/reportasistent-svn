// GenerateDialog.cpp : implementation file
//

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


