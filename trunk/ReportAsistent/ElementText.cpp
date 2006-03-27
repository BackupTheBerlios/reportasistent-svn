// ElementText.cpp : implementation file
//

#include "stdafx.h"
#include "ReportAsistent.h"
#include "ElementText.h"
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
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CElementTextDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CElementTextDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
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

//Poslu Editboxu, ktery je moji soucasti zpravu, ze se ma naplnit textem z XMLDom stromu

	/* Rozpracovano: 
	MSXML2::IXMLDOMElementPtr pElement;

	pElement=(MSXML2::IXMLDOMElementPtr) tree_control.GetItemData(hTreeItem);
	_variant_t & Value = pElement->getAttribute("value");
	*/

	SetDlgItemText(IDC_DIALTEXT_EDIT,"Text k zobrazeni");
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
