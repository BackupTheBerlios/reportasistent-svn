// AElConfigDialog.cpp : implementation file
//
/*
This file is part of LM Report Asistent.

Authors: Jan Dedek, Jan Kodym, Martin Chrz, Iva Bartunkova

LM Report Asistent is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

Foobar is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Foobar; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
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
	, CFilterResultImpl(data_share.m_filter_DOM)
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
			CReportAsistentApp::ReportError(IDS_INVALID_ELEMENT_ID);
			pDX->Fail();
		}

		CSkeletonDoc * Doc = ((CReportAsistentApp *) AfxGetApp())->FirstDocumentInFirstTemplate();
		if (m_OldID!=csIDEditValue)  //Iva: if "==", then ID is in tree, but it's OK
		{
			if (Doc->IsIDInTree(csIDEditValue))
			{
				SetDlgItemText(nId, m_OldID ); //Iva: return old value to edit box
				CReportAsistentApp::ReportError(IDS_DUPLICATE_ELEMENT_ID);
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
	DDX_Control(pDX, IDC_RESULT_LIST, m_ResultList);
	DDX_Control(pDX, IDC_DATA_SOURCE_COMBO, m_SourcesCombo);
	DDX_Text(pDX, IDC_ID_EDIT, m_sIdEdit);
	DDV_NonDuplicateID(pDX, IDC_ID_EDIT, m_sIdEdit);

}


BEGIN_MESSAGE_MAP(CAElConfigDialog, CPropertyPage)
	ON_CBN_SELCHANGE(IDC_DATA_SOURCE_COMBO, OnCbnSelchangeDataSourceCombo)
	ON_WM_CTLCOLOR()
	ON_EN_CHANGE(IDC_ID_EDIT, OnEnChangeIdEdit)
END_MESSAGE_MAP()


// CAElConfigDialog message handlers



BOOL CAElConfigDialog::LoadSource(public_source_id_t sId)
{
	CAElTransform tr(m_active_element);
	
	if (tr.LoadFilterDOM(sId, m_filter_DOM))
	{
		return TRUE;
	}

	m_filter_DOM = NULL;
	return FALSE;
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
	
	CFont f;
	f.CreateFont(
	   12,                        // nHeight
	   0,                         // nWidth
	   0,                         // nEscapement
	   0,                         // nOrientation
	   FW_NORMAL,                 // nWeight
	   FALSE,                     // bItalic
	   FALSE,                     // bUnderline
	   0,                         // cStrikeOut
	   ANSI_CHARSET,              // nCharSet
	   OUT_DEFAULT_PRECIS,        // nOutPrecision
	   CLIP_DEFAULT_PRECIS,       // nClipPrecision
	   DEFAULT_QUALITY,           // nQuality
	   DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
	   "Arial");                 // lpszFacename
	
	GetDlgItem(IDC_NO_FILTERS)->SetFont(& f, FALSE);


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CAElConfigDialog::OnCbnSelchangeDataSourceCombo()
{
	CString cur_source;
	
	m_SourcesCombo.GetWindowText(cur_source);
	m_cloned_active_element->setAttribute("source", (LPCTSTR) cur_source);

	LoadSource(cur_source);

	OnSetActive();

	SetModified();

	Invalidate(FALSE);
}

HBRUSH CAElConfigDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
//	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here

	if (! m_bSourceIsInit)
	{
		m_bSourceIsInit = TRUE;
		OnCbnSelchangeDataSourceCombo();
		SetModified(FALSE);
		Invalidate(FALSE);
	}

	if (pWnd->GetDlgCtrlID() == IDC_NO_FILTERS)
	{		
		pDC->SetTextColor(RGB(255, 0, 0));
		return (HBRUSH) GetStockObject(WHITE_BRUSH);
	}


	// TODO:  Return a different brush if the default is not desired
	return CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);
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

BOOL CAElConfigDialog::OnApply()
{
	m_cloned_active_element->setAttribute("id", (LPCTSTR) m_sIdEdit);        
	
	m_OldID = m_sIdEdit;
	ApplyChanges();

	return TRUE;
}

BOOL CAElConfigDialog::OnSetActive()
{
	if (! m_bSourceIsInit) return CPropertyPage::OnSetActive();

	InitResultView();

	MSXML2::IXMLDOMNodePtr simple_f = m_cloned_active_element->selectSingleNode("filter[@type='simple']");
	MSXML2::IXMLDOMNodePtr complex_f = m_cloned_active_element->selectSingleNode("filter[@type='complex']");

	if ((simple_f->firstChild == NULL) && (complex_f->firstChild == NULL))
	{
		GetDlgItem(IDC_NO_FILTERS)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_NO_FLTER_FRAME)->ShowWindow(SW_SHOW);
		m_ResultList.DeleteAllItems();
		m_ResultList.EnableWindow(FALSE);
		
		return CPropertyPage::OnSetActive();
	}

	GetDlgItem(IDC_NO_FILTERS)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_NO_FLTER_FRAME)->ShowWindow(SW_HIDE);
	m_ResultList.EnableWindow();
	

	if (m_filter_DOM != NULL)
	{
		
		//zaloha dat
		MSXML2::IXMLDOMElementPtr values_clone = m_filter_DOM->selectSingleNode("/dialog_data/values")->cloneNode(VARIANT_TRUE);
		
	//	simple_f = simple_f->cloneNode(VARIANT_TRUE);

		CAElTransform tr(m_cloned_active_element);

	//	AfxMessageBox(simple_f->xml);

		tr.ApplyAllFilters(m_filter_DOM);

		CFilterResultImpl::UpdateResult(m_filter_DOM);
		
		//obnova dat
		m_filter_DOM->selectSingleNode("/dialog_data")->replaceChild(values_clone,
			m_filter_DOM->selectSingleNode("/dialog_data/values"));
	
		return CPropertyPage::OnSetActive();
	}

	CFilterResultImpl::UpdateResult(m_filter_DOM);

	return CPropertyPage::OnSetActive();
}
