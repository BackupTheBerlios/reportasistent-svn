// ElementParagraphDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ReportAsistent.h"
#include "ElementParagraphDialog.h"
#include "CSkeletonDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CElementParagraphDialog dialog


CElementParagraphDialog::CElementParagraphDialog(MSXML2::IXMLDOMElementPtr & SelXMLElm,CWnd* pParent /*=NULL*/)
	: CDialog(CElementParagraphDialog::IDD, pParent), m_SelXMLElm(SelXMLElm)
{
	//{{AFX_DATA_INIT(CElementParagraphDialog)
	m_DialParagraphIDEditValue = _T("");
	//}}AFX_DATA_INIT

	//Inicializuji promenne dialogu		
	//Id
	_variant_t varAtr=m_SelXMLElm->getAttribute("id");
	m_OldID=(LPCTSTR) (_bstr_t)  varAtr;
	if (varAtr.vt!=VT_NULL)
		m_DialParagraphIDEditValue = m_OldID;

}


void CElementParagraphDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CElementParagraphDialog)
	DDX_Control(pDX, IDC_STYLES_COMBO, m_StylesCombo);
	DDX_Text(pDX, IDC_DIALPARAGRAPH_IDEDIT, m_DialParagraphIDEditValue);
	//}}AFX_DATA_MAP
	DDV_NonDuplicateID(pDX,IDC_DIALPARAGRAPH_IDEDIT, m_DialParagraphIDEditValue);

}


BEGIN_MESSAGE_MAP(CElementParagraphDialog, CDialog)
	//{{AFX_MSG_MAP(CElementParagraphDialog)
	ON_BN_CLICKED(IDC_STYLES_REFRESH_BUTTON, OnStylesRefreshButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CElementParagraphDialog message handlers

void CElementParagraphDialog::DDV_NonDuplicateID(CDataExchange *pDX, int nId, CString csIDEditValue)
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

void CElementParagraphDialog::FillStylesCombo()
{
	CWordManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->WordManager;

	CStringTable & st = m.getWordParagraphStyles();

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

void CElementParagraphDialog::OnStylesRefreshButton() 
{
	CWordManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->WordManager;
	m.LoadWordStylesAndTempates();

	FillStylesCombo();	
}

void CElementParagraphDialog::OnOK() 
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
	
	CDialog::OnOK();
}

BOOL CElementParagraphDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	FillStylesCombo();

	//Choose style in the combo box
	_variant_t style = m_SelXMLElm->getAttribute("style");
	if (style.vt != VT_NULL)
	{
		m_StylesCombo.SelectString(-1, (_bstr_t) style);
	}

			
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
