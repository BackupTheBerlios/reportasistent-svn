// ElementChapterDialog.cpp : implementation file
//

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


CElementChapterDialog::CElementChapterDialog(IXMLDOMElementPtr & SelXMLElm,CWnd* pParent /*=NULL*/)
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
