// TransformationsDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ReportAsistent.h"
#include "TransformationsDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransformationsDialog dialog


CTransformationsDialog::CTransformationsDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CTransformationsDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTransformationsDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTransformationsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTransformationsDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTransformationsDialog, CDialog)
	//{{AFX_MSG_MAP(CTransformationsDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransformationsDialog message handlers


