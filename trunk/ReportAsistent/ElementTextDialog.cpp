// ElementTextDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ReportAsistent.h"
#include "ElementTextDialog.h"
#include "CSkeletonDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CElementTextDialog dialog


CElementTextDialog::CElementTextDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CElementTextDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CElementTextDialog)
	m_DialTextEditValue = _T("");
	//}}AFX_DATA_INIT
}


void CElementTextDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CElementTextDialog)
	DDX_Text(pDX, IDC_DIALTEXT_EDIT, m_DialTextEditValue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CElementTextDialog, CDialog)
	//{{AFX_MSG_MAP(CElementTextDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CElementTextDialog message handlers

BOOL CElementTextDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
