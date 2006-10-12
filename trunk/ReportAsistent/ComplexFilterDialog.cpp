// ComplexFilterDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ReportAsistent.h"
#include "ComplexFilterDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CComplexFilterDialog property page

//IMPLEMENT_DYNCREATE(CComplexFilterDialog, CPropertyPage)

CComplexFilterDialog::CComplexFilterDialog(MSXML2::IXMLDOMElementPtr & active_element, CWnd* pParent)	// nestandard constructor :-)
: CPropertyPage(CComplexFilterDialog::IDD), m_active_element(active_element), m_bSourceIsInit(FALSE)
{
	//{{AFX_DATA_INIT(CComplexFilterDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CComplexFilterDialog::~CComplexFilterDialog()
{
}

void CComplexFilterDialog::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CComplexFilterDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_DATA_SOURCE_COMBO, m_SourcesCombo);
}


BEGIN_MESSAGE_MAP(CComplexFilterDialog, CPropertyPage)
	//{{AFX_MSG_MAP(CComplexFilterDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_WM_CTLCOLOR()
	ON_CBN_SELCHANGE(IDC_DATA_SOURCE_COMBO, OnSelchangeDataSourceCombo)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComplexFilterDialog message handlers

BOOL CComplexFilterDialog::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	
	
	CDataSourcesManager & dm = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->DataSourcesManager;
	CElementManager & em = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;

	for (int a=0; a< dm.getSourcesCount(); a++)
	{
		if (em.isElementSupportedBySource(em.IdentifyElement(m_active_element), a))
		{
			m_SourcesCombo.AddString(dm.getSourcePublicID(a));
		}
	}

	int sel = m_SourcesCombo.SelectString(-1, (_bstr_t) m_active_element->getAttribute("source"));
	if (sel == CB_ERR) m_SourcesCombo.SelectString(-1, dm.getDefaultSource());



	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CComplexFilterDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here

	//dedek: tohle se tady vola kvuli inicializaci filtru - kdyz se to delalo uz v init_dialog tak to padalo!!
	if (! m_bSourceIsInit)
	{
		m_bSourceIsInit = TRUE;
		OnSelchangeDataSourceCombo();
		SetModified(FALSE);
		Invalidate(FALSE);
	}

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}

void CComplexFilterDialog::OnSelchangeDataSourceCombo()
{
	// TODO: Add your control notification handler code here
}
