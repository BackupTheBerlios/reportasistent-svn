// OptionsDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ReportAsistent.h"
#include "OptionsDialog.h"
#include "CSkeletonDoc.h"
#include "SkeletonView.h"
#include "ElementIncludeDialog.h"
#include <Shlwapi.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionsDialog dialog


COptionsDialog::COptionsDialog(CWnd* pParent /*=NULL*/)
	: CDialog(COptionsDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(COptionsDialog)
	//}}AFX_DATA_INIT

	CWordManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->WordManager;
	m_strWordTemplate= m.getWordTemplate();
}


void COptionsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	CWordManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->WordManager;


	//{{AFX_DATA_MAP(COptionsDialog)
	DDX_Control(pDX, IDC_TEXT_EDIT_SIZE, m_TextEditSize);
	DDX_Control(pDX, IDC_MARK_ORPHANS, m_MarkOrphansCheckBox);
	DDX_Control(pDX, IDC_SHOW_ID_IN_TREE, m_IdInTreeCheckBox);
	DDX_Control(pDX, IDC_TREE_HAS_BUTTONS, m_ButtonsCheckBox);
	DDX_Control(pDX, IDC_TREE_HAS_LINES, m_LinesCheckBox);
	DDX_Control(pDX, IDC_TREE_ITEM_INDENT, m_IndentEdit);
	DDX_Control(pDX, IDC_TREE_ITEM_HEIGHT, m_HeightEdit);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_WORD_TEMPLATE_EDIT, m_strWordTemplate);

	CElementIncludeDialog::DDV_ValidFileName(pDX, IDC_WORD_TEMPLATE_EDIT, m_strWordTemplate, m.getWordTemplate());
	DDX_Control(pDX, IDC_TREE_ITEM_NAME_LENGTH, m_NameLengthEdit);
}


BEGIN_MESSAGE_MAP(COptionsDialog, CDialog)
	//{{AFX_MSG_MAP(COptionsDialog)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_TEMPLATE_BROWSE_BOTTON, OnBnClickedTemplateBrowseBotton)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsDialog message handlers

BOOL COptionsDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CGeneralManager * m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager;
	CReportAsistentApp * App = ((CReportAsistentApp *) AfxGetApp());

	//Set Language radio buttons
	//CString lang = App->FirstDocumentInFirstTemplate()->GetReportSettings("language");
	if (m->getLanguage() == CString("cz"))
		CheckRadioButton(IDC_CZECH_RADIO, IDC_ENGLISH_RADIO, IDC_CZECH_RADIO);
	else
		CheckRadioButton(IDC_CZECH_RADIO, IDC_ENGLISH_RADIO, IDC_ENGLISH_RADIO);
		
	//Set Tree Items
	//Height edit
	CString Pom;
	Pom.Format("%d",App->m_iTreeItemHeight);
	m_HeightEdit.SetWindowText(Pom);
	m_HeightEdit.SetLimitText(2);

	//Indent Edit
	Pom.Format("%d",App->m_iTreeItemIndent);
	m_IndentEdit.SetWindowText(Pom);
	m_IndentEdit.SetLimitText(2);

	m_LinesCheckBox.SetCheck( App->m_bTreeHasLines);
	m_IdInTreeCheckBox.SetCheck( App->m_bIdInItemName);
	m_ButtonsCheckBox.SetCheck( App->m_bTreeHasButtons);

	//Name Length Edit
	Pom.Format("%d",App->m_iTreeItemNameLength);
	m_NameLengthEdit.SetWindowText(Pom);
	m_NameLengthEdit.SetLimitText(3);

	// Size of text in TextEdit in Text Element dialog
	Pom.Format("%d",App->m_iTextEditSize);
	m_TextEditSize.SetWindowText(Pom);
	m_TextEditSize.SetLimitText(3);

	//Set orphans radio buttons:
	CString OrphSol = App->FirstDocumentInFirstTemplate()->GetReportSettings("orphans_solution");
	if (OrphSol== CString("ignore"))
			CheckRadioButton( IDC_IGNORE_RADIO , IDC_SET_DEFAULT_RADIO, IDC_IGNORE_RADIO );
	else		
		if (OrphSol== CString("delete"))
			CheckRadioButton( IDC_IGNORE_RADIO , IDC_SET_DEFAULT_RADIO, IDC_DELETE_RADIO );
		else
			if (OrphSol== CString("set_default"))
				CheckRadioButton( IDC_IGNORE_RADIO , IDC_SET_DEFAULT_RADIO, IDC_SET_DEFAULT_RADIO );
			else
			{
				CheckRadioButton( IDC_IGNORE_RADIO , IDC_SET_DEFAULT_RADIO, IDC_IGNORE_RADIO );
				App->FirstDocumentInFirstTemplate()->SetReportSettings("orphans_solution","ignore");
			}
	//set mark orphans
	m_MarkOrphansCheckBox.SetCheck( App->m_bMarkOrphans);


	




	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COptionsDialog::OnOK() 
{
	if (!UpdateData(TRUE))
	{
		TRACE0("UpdateData failed during dialog termination.\n");
		// the UpdateData routine will set focus to correct item
		return;
	}

	CGeneralManager * m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager;
	CString Pom;
	int iPom;
	CUT_Hint oHint;
	CReportAsistentApp * App = ((CReportAsistentApp *) AfxGetApp());

	//dedek: WordTemplate
	m->WordManager.setWordTemplate(m_strWordTemplate);

	//Get Language radio buttons

	if (GetCheckedRadioButton(IDC_CZECH_RADIO, IDC_ENGLISH_RADIO) == IDC_ENGLISH_RADIO)
		m->setLanguage("en");
	else
		m->setLanguage("cz");

	//Get Tree Items
	//Height Edit
	m_HeightEdit.GetWindowText(Pom);
	iPom = StrToInt((LPCTSTR)Pom);
	if ((iPom > 15) && (iPom<= 50))
		App->m_iTreeItemHeight = iPom;

	//Indent Edit
	m_IndentEdit.GetWindowText(Pom);
	iPom =StrToInt((LPCTSTR)Pom);
	if ((iPom > 15) && (iPom<= 50))
		App->m_iTreeItemIndent = iPom;

	App->m_bTreeHasLines = m_LinesCheckBox.GetCheck();
	App->m_bIdInItemName = m_IdInTreeCheckBox.GetCheck();
	App->m_bTreeHasButtons = m_ButtonsCheckBox.GetCheck();

	//Name Length Edit
	m_NameLengthEdit.GetWindowText(Pom);
	iPom =StrToInt((LPCTSTR)Pom);
	if ((iPom > 5) && (iPom<= 999))
		App->m_iTreeItemNameLength = iPom;

	//TextEdit size Edit
	m_TextEditSize.GetWindowText(Pom);
	iPom =StrToInt((LPCTSTR)Pom);
	if ((iPom > 80) && (iPom<= 300))
	App->m_iTextEditSize = iPom;

	//Get orphans radio buttons:
	CString OrphSol = App->FirstDocumentInFirstTemplate()->GetReportSettings("orphans_solution");
	switch (GetCheckedRadioButton(IDC_IGNORE_RADIO,  IDC_SET_DEFAULT_RADIO))
	{
		case IDC_IGNORE_RADIO:
			App->FirstDocumentInFirstTemplate()->SetReportSettings("orphans_solution","ignore");
			break;
		case IDC_DELETE_RADIO:
			App->FirstDocumentInFirstTemplate()->SetReportSettings("orphans_solution","delete");
			break;
		case IDC_SET_DEFAULT_RADIO:
			App->FirstDocumentInFirstTemplate()->SetReportSettings("orphans_solution","set_default");
			break;
	}

	//get mark orphans
	BOOL bChecked = App->m_bMarkOrphans;
	App->m_bMarkOrphans = m_MarkOrphansCheckBox.GetCheck();
	if (bChecked ==App->m_bMarkOrphans) oHint.iMarkOrphans = 0;
	else if (bChecked == 0) oHint.iMarkOrphans = ORP_SIGN;
			else oHint.iMarkOrphans = ORP_UNSIGN;

	//Apply changes
	App->FirstDocumentInFirstTemplate()->SetModifiedFlag();
	App->FirstDocumentInFirstTemplate()->UpdateAllViews(NULL, UT_SETTINGS, &oHint);


	EndDialog(IDOK);
}

void COptionsDialog::OnBnClickedTemplateBrowseBotton()
{
	CString cur_template;
	GetDlgItemText(IDC_WORD_TEMPLATE_EDIT, cur_template);

	CFileDialog OFileDlg(	TRUE, //"open file" type
							_T("dot"), // default ending for given names without extension
							cur_template,
							OFN_HIDEREADONLY|OFN_PATHMUSTEXIST,
							_T("MS Word Templates (*.dot)|*.dot||"));

	if( OFileDlg.DoModal()==IDOK )
	{
		m_strWordTemplate = OFileDlg.GetPathName();
		UpdateData(FALSE);
	}
}


