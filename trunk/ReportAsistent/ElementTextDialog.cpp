// ElementTextDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ReportAsistent.h"
#include "ElementTextDialog.h"
#include "CSkeletonDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#ifndef MAX_TEXT_LENGTH
#define MAX_TEXT_LENGTH 2000
#endif
/////////////////////////////////////////////////////////////////////////////
// CElementTextDialog dialog


CElementTextDialog::CElementTextDialog(MSXML2::IXMLDOMElementPtr & SelXMLElm,CWnd* pParent /*=NULL*/)
	: CDialog(CElementTextDialog::IDD, pParent), m_SelXMLElm(SelXMLElm)
{
	//{{AFX_DATA_INIT(CElementTextDialog)
	m_DialTextIDEditValue = _T("");
	//}}AFX_DATA_INIT

//Inicializuji promenne dialogu		
	//Id
	_variant_t varAtr=m_SelXMLElm->getAttribute("id");
	m_OldID=(LPCTSTR) (_bstr_t)  varAtr;
	if (varAtr.vt!=VT_NULL)
		m_DialTextIDEditValue = m_OldID;
}


void CElementTextDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CElementTextDialog)
	DDX_Control(pDX, IDC_DIALTEXT_EDIT, m_REdit);
	DDX_Control(pDX, IDC_STYLES_COMBO, m_StylesCombo);
	DDX_Text(pDX, IDC_DIALTEXT_IDEDIT, m_DialTextIDEditValue);
	DDV_MaxChars(pDX, m_DialTextIDEditValue, 50);
	//}}AFX_DATA_MAP
	DDV_NonDuplicateID(pDX,IDC_DIALTEXT_IDEDIT, m_DialTextIDEditValue);

}


BEGIN_MESSAGE_MAP(CElementTextDialog, CDialog)
	//{{AFX_MSG_MAP(CElementTextDialog)
	ON_BN_CLICKED(IDC_STYLES_REFRESH_BUTTON, OnStylesRefreshButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CElementTextDialog message handlers


void CElementTextDialog::DDV_NonDuplicateID(CDataExchange *pDX, int nId, CString csIDEditValue)
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

void CElementTextDialog::OnStylesRefreshButton() 
{
	CWordManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->WordManager;
	m.LoadWordStylesAndTempates();

	FillStylesCombo();	
}

void CElementTextDialog::FillStylesCombo()
{
	CWordManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->WordManager;

	CStringTable & st = m.getWordCharacterStyles();

	CString sel;
	m_StylesCombo.GetWindowText(sel);
	
	//vymaze cele combo
	m_StylesCombo.ResetContent();
/*
	for (int i=0; i < m_StylesCombo.GetCount(); i++)
	{
		m_StylesCombo.DeleteString(0);
	}
*/
	//styl - neuveden
	m_StylesCombo.AddString("");

	for (int a=0; a < st.getCount(); a++)
	{
		m_StylesCombo.AddString(st.getItem(a));
	}

	if (CB_ERR == m_StylesCombo.SelectString(-1, sel))
	{
		CString s;
		m_StylesCombo.GetLBText(0, s);
		m_StylesCombo.SelectString(-1, s);
	}


}

void CElementTextDialog::OnOK() 
{
	//style
	
	//vymaz attribut style z tagu
	if (m_SelXMLElm->attributes->getNamedItem("style") != NULL)
	{
		m_SelXMLElm->attributes->removeNamedItem("style");
	}

	CString style_str;
	m_StylesCombo.GetWindowText(style_str);

	if (style_str.GetLength() != 0)
	{
		MSXML2::IXMLDOMAttributePtr s_atr = m_SelXMLElm->ownerDocument->createAttribute("style");
		s_atr->text = (LPCTSTR) style_str;
		m_SelXMLElm->setAttributeNode(s_atr);
		s_atr.Release();
	}

	//Text from Rich Edit is saved to the skeleton:
	CString sText;
	m_REdit.GetWindowText(sText);
	//white spaces at the end and at the beginning of the text are replaced by nbsp;
	sText = CSkeletonDoc::StrToHtml(sText);
	m_SelXMLElm->text = (LPCTSTR)sText;

	CDialog::OnOK();
}

BOOL CElementTextDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	FillStylesCombo();


	//Choose style in combobox m_StylesCombo
	_variant_t style = m_SelXMLElm->getAttribute("style");
	if (style.vt != VT_NULL)
	{
		m_StylesCombo.SelectString(-1, (_bstr_t) style);
	}


	//Set settings of RichEditCtrl
	CReportAsistentApp * App = ((CReportAsistentApp *) AfxGetApp());
	CHARFORMAT  cf;
	m_REdit.GetDefaultCharFormat(cf);
	cf.yHeight =App->m_iTextEditSize;
	cf.dwMask=CFM_SIZE;
	cf.cbSize=sizeof(cf);
	int Res = m_REdit.SetDefaultCharFormat(cf);	
	
	//Put text of the element into RichEditCtrl
	CString sText = CSkeletonDoc::HtmlToStr((LPCTSTR) (_bstr_t)  m_SelXMLElm->text);
	m_REdit.SetWindowText(sText);

	m_REdit.CanPaste(0);

		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
