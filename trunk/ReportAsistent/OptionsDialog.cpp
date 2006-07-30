// OptionsDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ReportAsistent.h"
#include "OptionsDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionsDialog dialog


COptionsDialog::COptionsDialog(CWnd* pParent /*=NULL*/)
	: CDialog(COptionsDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(COptionsDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void COptionsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionsDialog, CDialog)
	//{{AFX_MSG_MAP(COptionsDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsDialog message handlers

BOOL COptionsDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CGeneralManager * m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager;

	if (m->getLanguage() == CString("cz"))
		CheckRadioButton(IDC_CZECH_RADIO, IDC_ENGLISH_RADIO, IDC_CZECH_RADIO);
	else
		CheckRadioButton(IDC_CZECH_RADIO, IDC_ENGLISH_RADIO, IDC_ENGLISH_RADIO);
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COptionsDialog::OnOK() 
{
	CGeneralManager * m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager;

	if (GetCheckedRadioButton(IDC_CZECH_RADIO, IDC_ENGLISH_RADIO) == IDC_ENGLISH_RADIO)
		m->setLanguage("en");
	else
		m->setLanguage("cz");
	
	CDialog::OnOK();
}
