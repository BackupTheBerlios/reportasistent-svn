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
	DDX_Text(pDX, IDC_DIALPARAGRAPH_IDEDIT, m_DialParagraphIDEditValue);
	//}}AFX_DATA_MAP
	DDV_NonDuplicateID(pDX,IDC_DIALPARAGRAPH_IDEDIT, m_DialParagraphIDEditValue);

}


BEGIN_MESSAGE_MAP(CElementParagraphDialog, CDialog)
	//{{AFX_MSG_MAP(CElementParagraphDialog)
		// NOTE: the ClassWizard will add message map macros here
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
