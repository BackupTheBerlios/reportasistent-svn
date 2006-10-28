// AElFiltersConfigDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ReportAsistent.h"
#include "AElFiltersConfigDialog.h"
#include "ComplexFilterDialog.h"
#include "CSkeletonDoc.h"

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
	m_CF_IdEdit = _T("");
	//}}AFX_DATA_INIT
	
	//Iva: Inicialisation of ID edit:
	_variant_t varAtr=m_active_element->getAttribute("id");
	m_OldID=(LPCTSTR) (_bstr_t)  varAtr;
	if (varAtr.vt!=VT_NULL)
		m_CF_IdEdit = m_OldID;
}


void CAElFiltersConfigDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAElFiltersConfigDialog)
	DDX_Text(pDX, IDC_CF_ID_EDIT, m_CF_IdEdit);
	DDV_MaxChars(pDX, m_CF_IdEdit, 50);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_DATA_SOURCE_COMBO, m_SourcesCombo);
	DDV_NonDuplicateID(pDX,IDC_CF_ID_EDIT, m_CF_IdEdit);

}


BEGIN_MESSAGE_MAP(CAElFiltersConfigDialog, CDialog)
	//{{AFX_MSG_MAP(CAElFiltersConfigDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAElFiltersConfigDialog message handlers




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

void CAElFiltersConfigDialog::DDV_NonDuplicateID(CDataExchange *pDX, int nId, CString csIDEditValue)
{
	if (0!=pDX->m_bSaveAndValidate) //Iva: if it's end of dialog, not beginning
	{

		if (""==csIDEditValue) //Iva: ID can't be empty string
		{
			SetDlgItemText(nId, m_OldID );
			//dedek: ?CReportAsistentApp::ReportError?
			AfxMessageBox(IDS_INVALID_ELEMENT_ID);
			pDX->Fail();
		}

		CSkeletonDoc * Doc = ((CReportAsistentApp *) AfxGetApp())->FirstDocumentInFirstTemplate();
		if (m_OldID!=csIDEditValue &&  //Iva: if "==", then ID is in tree, but it's OK
			Doc->IsIDInTree(csIDEditValue))
		{
			SetDlgItemText(nId, m_OldID ); //Iva: return old value to edit box
			AfxMessageBox(IDS_DUPLICATE_ELEMENT_ID);
			//dedek: ?CReportAsistentApp::ReportError(IDS_DUPLICATE_ELEMENT_ID);?
			pDX->Fail();
		}

	}

}
