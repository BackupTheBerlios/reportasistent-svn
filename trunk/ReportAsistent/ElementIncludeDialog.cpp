// ElementIncludeDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ReportAsistent.h"
#include "ElementIncludeDialog.h"
#include "CSkeletonDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CElementIncludeDialog dialog


CElementIncludeDialog::CElementIncludeDialog(MSXML2::IXMLDOMElementPtr & SelXMLElm,CWnd* pParent /*=NULL*/)
	: CDialog(CElementIncludeDialog::IDD, pParent), m_SelXMLElm(SelXMLElm)
{
	//{{AFX_DATA_INIT(CElementIncludeDialog)
	m_Include_IdEdit = _T("");
	m_IncludeFileName = _T("");
	//}}AFX_DATA_INIT

	//Iva: Preparation of editboxes for Data Exchange:
	



	//Inicializuji promenne dialogu		
	//Id
	_variant_t varAtr=m_SelXMLElm->getAttribute("id");
	m_OldID=(LPCTSTR) (_bstr_t)  varAtr;
	if (varAtr.vt!=VT_NULL)
		m_Include_IdEdit = m_OldID;
	//FileName
	varAtr=m_SelXMLElm->getAttribute("file");
	m_OldFileName=(LPCTSTR) (_bstr_t)  varAtr;
	m_IncludeFileName = m_OldFileName;
	
}


void CElementIncludeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CElementIncludeDialog)
	DDX_Text(pDX, IDC_INCLUDE_ID_EDIT, m_Include_IdEdit);
	DDV_MaxChars(pDX, m_Include_IdEdit, 50);
	DDX_Text(pDX, IDC_INCLUDE_FILENAME_EDIT, m_IncludeFileName);
	//}}AFX_DATA_MAP
	DDV_NonDuplicateID(pDX,IDC_INCLUDE_ID_EDIT, m_Include_IdEdit);
	DDV_ValidFileName(pDX, IDC_INCLUDE_FILENAME_EDIT, m_IncludeFileName);

}


BEGIN_MESSAGE_MAP(CElementIncludeDialog, CDialog)
	//{{AFX_MSG_MAP(CElementIncludeDialog)
	ON_BN_CLICKED(IDC_BROWSE_BUTTON, OnBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CElementIncludeDialog message handlers

void CElementIncludeDialog::DDV_NonDuplicateID(CDataExchange *pDX, int nId, CString csIDEditValue)
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


void CElementIncludeDialog::OnBrowse() 
{
	CFileDialog OFileDlg(	TRUE, //"open file" type
							_T("doc"), // default ending for given names without extension
							_T("*.doc"),
							OFN_HIDEREADONLY|OFN_PATHMUSTEXIST,
							_T("MS Word Documents (*.doc)|*.doc|Rich Text Format Files (*.rtf)|*.rtf|Text files (*.txt)|*.txt|All Documents (*.doc; *.rtf;*.txt)|*.doc; *.rtf;*.txt|All Files (*.*)|*.*||"));

	if( OFileDlg.DoModal()==IDOK )
		SetDlgItemText( IDC_INCLUDE_FILENAME_EDIT, OFileDlg.GetPathName() );	
}

void CElementIncludeDialog::DDV_ValidFileName(CDataExchange *pDX, int nIdc, CString csFileName)
{
	CFileStatus status;

	
	if (0!=pDX->m_bSaveAndValidate) //Iva: if it's end of dialog, not beginning
	{
		pDX->PrepareEditCtrl(IDC_INCLUDE_ID_EDIT);	
		pDX->PrepareEditCtrl(IDC_INCLUDE_FILENAME_EDIT);

		if( FALSE == CFile::GetStatus( (LPCTSTR) csFileName, status ) ) //Iva: If file with such name does not exist
		{
			SetDlgItemText(nIdc, m_OldFileName ); //Iva: return old value to edit box
			CReportAsistentApp::ReportError(IDS_INVALID_FILE_NAME);
			pDX->Fail();
		}
	}
}
