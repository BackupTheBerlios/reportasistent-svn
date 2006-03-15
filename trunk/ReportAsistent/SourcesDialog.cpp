// SourcesDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ReportAsistent.h"
#include "SourcesDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSourcesDialog dialog


CSourcesDialog::CSourcesDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSourcesDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSourcesDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSourcesDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSourcesDialog)
	DDX_Control(pDX, IDC_SOURCES_LIST, m_SourcesList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSourcesDialog, CDialog)
	//{{AFX_MSG_MAP(CSourcesDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSourcesDialog message handlers

LPCTSTR CSourcesDialog::header_captions [] =
{
	"name", "state", "plugin", "persist_ID"
};

#define LENGTH(array) (sizeof(array) / sizeof(* array))


BOOL CSourcesDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	for (int a=0; a<LENGTH(header_captions); a++)
	{
		m_SourcesList.InsertColumn(a, header_captions[a], LVCFMT_LEFT, 75);
	}

	/* dodelat nacteni jednotlivych zdroju



  */
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
