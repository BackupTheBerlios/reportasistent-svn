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

/////////////////////////////////////////////////////////////////////////////
// CElementTextDialog dialog


CElementTextDialog::CElementTextDialog(IXMLDOMElementPtr & SelXMLElm,CWnd* pParent /*=NULL*/)
	: CDialog(CElementTextDialog::IDD, pParent), m_SelXMLElm(SelXMLElm)
{
	//{{AFX_DATA_INIT(CElementTextDialog)
	m_DialTextEditValue = _T("");
	m_DialTextIDEditValue = _T("");
	//}}AFX_DATA_INIT

//Inicializuji promenne dialogu		
	//Id
	_variant_t varAtr=m_SelXMLElm->getAttribute("id");
	m_OldID=(LPCTSTR) (_bstr_t)  varAtr;
	if (varAtr.vt!=VT_NULL)
		m_DialTextIDEditValue = m_OldID;
	//Text
	m_DialTextEditValue = (LPCTSTR) (_bstr_t)  m_SelXMLElm->text;

}


void CElementTextDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CElementTextDialog)
	DDX_Text(pDX, IDC_DIALTEXT_EDIT, m_DialTextEditValue);
	DDV_MaxChars(pDX, m_DialTextEditValue, 1000);
	DDX_Text(pDX, IDC_DIALTEXT_IDEDIT, m_DialTextIDEditValue);
	DDV_MaxChars(pDX, m_DialTextIDEditValue, 50);
	//}}AFX_DATA_MAP
	DDV_NonDuplicateID(pDX,IDC_DIALTEXT_IDEDIT, m_DialTextIDEditValue);

}


BEGIN_MESSAGE_MAP(CElementTextDialog, CDialog)
	//{{AFX_MSG_MAP(CElementTextDialog)
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
			AfxMessageBox(IDS_INVALID_ELEMENT_ID);
			pDX->Fail();
		}

		CSkeletonDoc * Doc = ((CReportAsistentApp *) AfxGetApp())->FirstDocumentInFirstTemplate();
		if (m_OldID!=csIDEditValue &&  //Iva: if "==", then ID is in tree, but it's OK
			Doc->IsIDInTree(csIDEditValue))
		{
			SetDlgItemText(nId, m_OldID ); //Iva: return old value to edit box
			AfxMessageBox(IDS_DUPLICATE_ELEMENT_ID);
			pDX->Fail();
		}

	}

}
