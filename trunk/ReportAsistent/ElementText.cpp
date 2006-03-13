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
// CElementText dialog


CElementText::CElementText(CWnd* pParent /*=NULL*/)
	: CDialog(CElementText::IDD, pParent)
{
	//{{AFX_DATA_INIT(CElementText)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CElementText::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CElementText)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CElementText, CDialog)
	//{{AFX_MSG_MAP(CElementText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CElementText message handlers

BOOL CElementText::OnInitDialog() 
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
