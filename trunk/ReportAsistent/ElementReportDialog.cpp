// ElementReportDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ReportAsistent.h"
#include "ElementReportDialog.h"
#include "CSkeletonDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CElementReportDialog dialog


CElementReportDialog::CElementReportDialog(MSXML2::IXMLDOMElementPtr & SelXMLElm,CWnd* pParent /*=NULL*/)
	: CDialog(CElementReportDialog::IDD, pParent), m_SelXMLElm(SelXMLElm)
{
	//{{AFX_DATA_INIT(CElementReportDialog)
	m_DialReportIDEditValue = _T("");
	m_DialReportTitleEditValue = _T("");
	//}}AFX_DATA_INIT
	
	//Inicializuji promenne dialogu		
	//Id
	_variant_t varAtr=m_SelXMLElm->getAttribute("id");
	m_OldID=(LPCTSTR) (_bstr_t)  varAtr;
	if (varAtr.vt!=VT_NULL)
		m_DialReportIDEditValue = m_OldID;
	//Title
	varAtr=m_SelXMLElm->getAttribute("title");
	if (varAtr.vt!=VT_NULL)
		m_DialReportTitleEditValue = (LPCTSTR) (_bstr_t)  varAtr;

}

void CElementReportDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CElementReportDialog)
	DDX_Text(pDX, IDC_DIALREPORT_IDEDIT, m_DialReportIDEditValue);
	DDX_Text(pDX, IDC_DIALREPORT_TITLEEDIT, m_DialReportTitleEditValue);
	//}}AFX_DATA_MAP
	DDV_NonDuplicateID(pDX,IDC_DIALREPORT_IDEDIT, m_DialReportIDEditValue);	
}



BEGIN_MESSAGE_MAP(CElementReportDialog, CDialog)
	//{{AFX_MSG_MAP(CElementReportDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CElementReportDialog message handlers

void CElementReportDialog::DDV_NonDuplicateID(CDataExchange *pDX, int nId, CString csIDEditValue)
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