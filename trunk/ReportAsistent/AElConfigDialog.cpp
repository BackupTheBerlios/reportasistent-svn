// AElConfigDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ReportAsistent.h"
#include "AElConfigDialog.h"
#include "APTransform.h"
#include "CSkeletonDoc.h"


// CAElConfigDialog dialog

IMPLEMENT_DYNAMIC(CAElConfigDialog, CPropertyPage)

CAElConfigDialog::CAElConfigDialog(CAElDataShare & data_share)
	: CPropertyPage(CAElConfigDialog::IDD)
	, CAElDataShare(data_share)
	, m_bSourceIsInit(FALSE)
	, m_sIdEdit("")
{

	//Iva: Inicialisation 
	//Id:
	_variant_t varAtr=m_active_element->getAttribute("id");
	m_OldID=(LPCTSTR) (_bstr_t)  varAtr;
	if (varAtr.vt!=VT_NULL)
		m_sIdEdit = m_OldID;

}

CAElConfigDialog::~CAElConfigDialog()
{
}


void CAElConfigDialog::DDV_NonDuplicateID(CDataExchange *pDX, int nId, CString csIDEditValue)
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
		if (m_OldID!=csIDEditValue)  //Iva: if "==", then ID is in tree, but it's OK
		{
			if (Doc->IsIDInTree(csIDEditValue))
			{
				SetDlgItemText(nId, m_OldID ); //Iva: return old value to edit box
				AfxMessageBox(IDS_DUPLICATE_ELEMENT_ID);
				//dedek: ?CReportAsistentApp::ReportError(IDS_DUPLICATE_ELEMENT_ID);?
				pDX->Fail();
			}
			else
			{
				//Iva: I try to set ID to new value
				try
				{
					m_active_element->setAttribute("id", (LPCTSTR)csIDEditValue); 
				}
				catch(_com_error &e)
				{
					SetDlgItemText(nId, m_OldID ); //Iva: return old value to edit box
					m_active_element->setAttribute("id", (LPCTSTR)m_OldID);
					//AfxMessageBox(e.Description());
					CReportAsistentApp::ReportError(IDS_INVALID_ELEMENT_ID,e.Description() );
					pDX->Fail();
				}
				m_active_element->setAttribute("id", (LPCTSTR)m_OldID); 

			}

		}

	}

}

void CAElConfigDialog::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATA_SOURCE_COMBO, m_SourcesCombo);
	DDX_Text(pDX, IDC_ID_EDIT, m_sIdEdit);
	DDV_NonDuplicateID(pDX, IDC_ID_EDIT, m_sIdEdit);

}


BEGIN_MESSAGE_MAP(CAElConfigDialog, CPropertyPage)
	ON_CBN_SELCHANGE(IDC_DATA_SOURCE_COMBO, &CAElConfigDialog::OnCbnSelchangeDataSourceCombo)
	ON_WM_CTLCOLOR()
	ON_EN_CHANGE(IDC_ID_EDIT, &CAElConfigDialog::OnEnChangeIdEdit)
END_MESSAGE_MAP()


// CAElConfigDialog message handlers



BOOL CAElConfigDialog::LoadSource(public_source_id_t sId)
{
	CAElTransform tr(m_active_element);

	return tr.LoadFilterDOM(sId, m_filter_DOM);
}


BOOL CAElConfigDialog::OnInitDialog()
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

void CAElConfigDialog::OnCbnSelchangeDataSourceCombo()
{
	CString cur_source;
	
	m_SourcesCombo.GetWindowText(cur_source);
	m_cloned_active_element->setAttribute("source", (LPCTSTR) cur_source);

	LoadSource(cur_source);

	SetModified();
}

HBRUSH CAElConfigDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here

	if (! m_bSourceIsInit)
	{
		m_bSourceIsInit = TRUE;
		OnCbnSelchangeDataSourceCombo();
		SetModified(FALSE);
		Invalidate(FALSE);
	}


	// TODO:  Return a different brush if the default is not desired
	return hbr;
}

void CAElConfigDialog::OnEnChangeIdEdit()
{
	SetModified();
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the __super::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
