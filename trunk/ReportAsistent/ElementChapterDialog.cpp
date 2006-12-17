// ElementChapterDialog.cpp : implementation file
//
//
// This file is part of LM Report Asistent. (http://reportasistent.berlios.de, reportasistent-list@lists.berlios.de)
//
// Authors: Jan Dedek, Jan Kodym, Martin Chrz, Iva Bartunkova 
//
// LM Report Asistent is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// LM Report Asistent is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with LM Report Asistent; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
#include "stdafx.h"
#include "ReportAsistent.h"
#include "ElementChapterDialog.h"
#include "CSkeletonDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CElementChapterDialog dialog


CElementChapterDialog::CElementChapterDialog(MSXML2::IXMLDOMElementPtr & SelXMLElm,CWnd* pParent /*=NULL*/)
	: CDialog(CElementChapterDialog::IDD, pParent), m_SelXMLElm(SelXMLElm)
{
	//{{AFX_DATA_INIT(CElementChapterDialog)
	m_DialChapterIDEditValue = _T("");
	m_DialChapterTitleEditValue = _T("");
	//}}AFX_DATA_INIT

//Inicializuji promenne dialogu		
	//Id
	_variant_t varAtr=m_SelXMLElm->getAttribute("id");
	m_OldID=(LPCTSTR) (_bstr_t)  varAtr;
	if (varAtr.vt!=VT_NULL)
		m_DialChapterIDEditValue = m_OldID;
	//Title
	varAtr=m_SelXMLElm->getAttribute("title");
	if (varAtr.vt!=VT_NULL)
		m_DialChapterTitleEditValue = (LPCTSTR) (_bstr_t)  varAtr;

}


void CElementChapterDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CElementChapterDialog)
	DDX_Text(pDX, IDC_DIALCHAPTER_TITLEEDIT, m_DialChapterTitleEditValue);
	DDV_MaxChars(pDX, m_DialChapterTitleEditValue, 200);
	DDX_Text(pDX, IDC_DIALCHAPTER_IDEDIT, m_DialChapterIDEditValue);
	DDV_MaxChars(pDX, m_DialChapterIDEditValue, 50);
	//}}AFX_DATA_MAP
	DDV_NonDuplicateID(pDX,IDC_DIALCHAPTER_IDEDIT, m_DialChapterIDEditValue);

}


BEGIN_MESSAGE_MAP(CElementChapterDialog, CDialog)
	//{{AFX_MSG_MAP(CElementChapterDialog)
	//}}AFX_MSG_MAP


END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CElementChapterDialog message handlers



/*BOOL CElementChapterDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

//Inicializuji promenne dialogu		
 	_variant_t varAtr=m_SelXMLElm->getAttribute("id");
 	m_OldID=(LPCTSTR) (_bstr_t)  varAtr;
 	m_DialChapterIDEditValue = m_OldID;
 	varAtr=m_SelXMLElm->getAttribute("title");
 	if (varAtr.vt!=VT_NULL)
 		m_DialChapterTitleEditValue = (LPCTSTR) (_bstr_t)  varAtr;
 	
 	return TRUE;  // return TRUE unless you set the focus to a control
 	              // EXCEPTION: OCX Property Pages should return FALSE
 }
*/



void CElementChapterDialog::DDV_NonDuplicateID(CDataExchange *pDX, int nId, CString csIDEditValue)
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
					m_SelXMLElm->setAttribute("id", (LPCTSTR)csIDEditValue); 
				}
				catch(_com_error &e)
				{
					SetDlgItemText(nId, m_OldID ); //Iva: return old value to edit box
					m_SelXMLElm->setAttribute("id", (LPCTSTR)m_OldID);
					//AfxMessageBox(e.Description());
					CReportAsistentApp::ReportError(IDS_INVALID_ELEMENT_ID,e.Description() );
					pDX->Fail();
				}
				m_SelXMLElm->setAttribute("id", (LPCTSTR)m_OldID); 

			}

		}

	}

}




