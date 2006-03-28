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
	//{{AFX_DATA_INIT(CGenerateDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CGenerateDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGenerateDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
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
	m_SkeletonDocument.Generate();
	
	EndDialog(IDOK);
}
