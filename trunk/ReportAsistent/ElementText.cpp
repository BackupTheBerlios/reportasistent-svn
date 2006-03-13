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
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CElementText message handlers
