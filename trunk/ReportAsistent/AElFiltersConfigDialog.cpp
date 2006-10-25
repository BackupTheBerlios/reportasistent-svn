// AElFiltersConfigDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ReportAsistent.h"
#include "AElFiltersConfigDialog.h"
#include "ComplexFilterDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAElFiltersConfigDialog dialog


CAElFiltersConfigDialog::CAElFiltersConfigDialog(MSXML2::IXMLDOMElementPtr & active_element, CWnd* pParent)
	: CPropertyPage(CAElFiltersConfigDialog::IDD), m_active_element(active_element)
{
	//{{AFX_DATA_INIT(CAElFiltersConfigDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAElFiltersConfigDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAElFiltersConfigDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_DATA_SOURCE_COMBO, m_SourcesCombo);
}


BEGIN_MESSAGE_MAP(CAElFiltersConfigDialog, CDialog)
	//{{AFX_MSG_MAP(CAElFiltersConfigDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_ADD_FILTER_BUTTON, OnBnClickedAddFilterButton)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAElFiltersConfigDialog message handlers

void CAElFiltersConfigDialog::OnBnClickedAddFilterButton()
{
	CComplexFilterDialog dlg(m_active_element);

	dlg.DoModal();
}


BOOL CAElFiltersConfigDialog::OnInitDialog()
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

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
