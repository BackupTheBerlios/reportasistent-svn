// SourcesDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ReportAsistent.h"
#include "SourcesDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSourcesDialog dialog


CSourcesDialog::CSourcesDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSourcesDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSourcesDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSourcesDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSourcesDialog)
	DDX_Control(pDX, IDC_PLUGINS_COMBO, m_PluginCombo);
	DDX_Control(pDX, IDC_SOURCES_LIST, m_SourcesList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSourcesDialog, CDialog)
	//{{AFX_MSG_MAP(CSourcesDialog)
	ON_BN_CLICKED(IDC_ADD_SOURCE_BUTTON, OnAddSourceButton)
	ON_BN_CLICKED(IDC_OPEN_BUTTON, OnOpenButton)
	ON_BN_CLICKED(IDC_CLOSE_BUTTON, OnCloseButton)
	ON_BN_CLICKED(IDC_REMOVE_BUTTON, OnRemoveButton)
	ON_BN_CLICKED(IDC_RENAME_BUTTON, OnRenameButton)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_SOURCES_LIST, OnEndlabeleditSourcesList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSourcesDialog message handlers

LPCTSTR CSourcesDialog::header_captions [] =
{
	"name", "state", "plugin", "persist_ID"
};

#define SRCL_NAME		0
#define SRCL_STATE		1
#define SRCL_PLUGIN		2
#define SRCL_PERSISTID	3

#define LENGTH(array) (sizeof(array) / sizeof(* array))


BOOL CSourcesDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	int a;

	for (a=0; a<LENGTH(header_captions); a++)
	{
		m_SourcesList.InsertColumn(a, header_captions[a], LVCFMT_LEFT, 75);
	}

	CDataSourcesManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->DataSourcesManager;

	
	//nacte plugins
	for (a=0; a<m.getPlugsCount(); a++)
	{
		if (m.isPluginValid(a))
		{
			m_PluginCombo.AddString(m.getPluginID(a));

		}
		/****/ //ladici
		else
		{
			CString s = "*** invalid: ";
			s += m.getPluginID(a);
			s += " ladici vypis";
			m_PluginCombo.AddString(s);

		}
		/****/
	}

	m_PluginCombo.SelectString(-1, m.getPluginID(0));

	UpDateList();


	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSourcesDialog::UpDateList()
{
	CString selected;	
	m_PluginCombo.GetWindowText(selected);

	CDataSourcesManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->DataSourcesManager;

	m_SourcesList.DeleteAllItems();
	
	for (int a=0; a < m.getSourcesCount(); a++)
	{
		m_SourcesList.InsertItem(a, "");

		m_SourcesList.SetItemText(a, SRCL_NAME, m.getSourcePublicID(a));
		
		m_SourcesList.SetItemText(a, SRCL_PLUGIN, m.getSourcePlugin(a));
		m_SourcesList.SetItemText(a, SRCL_PERSISTID, m.getSourcePersistentID(a));

		CString state;

		if (! m.isSourceValid(a)) 
		{
			state = "invalid";
		}
		else 
		{
			if (m.isSourceConnected(a)) state = "open";
			else						state = "closed";
		}

		m_SourcesList.SetItemText(a, SRCL_STATE, state);
		
	}
}

void CSourcesDialog::OnAddSourceButton() 
{
	CDataSourcesManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->DataSourcesManager;

	CString plugin;
	m_PluginCombo.GetWindowText(plugin);

	int index = m.ConnectNewSource(plugin);

	UpDateList();

	
	
	//najdi pridanou polozku
	LVFINDINFO info;
	ZeroMemory(& info, sizeof info);

	info.flags = LVFI_STRING;
	info.psz = m.getSourcePublicID(index);
	int item = m_SourcesList.FindItem(& info);

	
	
	//edituj text
	m_SourcesList.SetFocus();
	m_SourcesList.EditLabel(item);
	
}

void CSourcesDialog::OnOpenButton() 
{
	CDataSourcesManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->DataSourcesManager;


	//nalezeni selecte source
	POSITION pos = m_SourcesList.GetFirstSelectedItemPosition();
	if (pos == NULL) return;
	int nItem = m_SourcesList.GetNextSelectedItem(pos);
	CString source = m_SourcesList.GetItemText(nItem, SRCL_NAME);


	m.ConnectSource(m.FindSourceByPublicID(source));

	
	
	
	UpDateList();
	
}

void CSourcesDialog::OnCloseButton() 
{
	CDataSourcesManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->DataSourcesManager;


	//nalezeni selecte source
	POSITION pos = m_SourcesList.GetFirstSelectedItemPosition();
	if (pos == NULL) return;
	int nItem = m_SourcesList.GetNextSelectedItem(pos);
	CString source = m_SourcesList.GetItemText(nItem, SRCL_NAME);


	
	m.CloseSource(m.FindSourceByPublicID(source));


	
	UpDateList();
	
}

void CSourcesDialog::OnRemoveButton() 
{
	CDataSourcesManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->DataSourcesManager;


	//nalezeni selecte source
	POSITION pos = m_SourcesList.GetFirstSelectedItemPosition();
	if (pos == NULL) return;
	int nItem = m_SourcesList.GetNextSelectedItem(pos);
	CString source = m_SourcesList.GetItemText(nItem, SRCL_NAME);


	
	m.RemoveSource(m.FindSourceByPublicID(source));


	
	UpDateList();
	
}

void CSourcesDialog::OnRenameButton() 
{
	//nalezeni selecte source
	POSITION pos = m_SourcesList.GetFirstSelectedItemPosition();
	if (pos == NULL) return;
	int nItem = m_SourcesList.GetNextSelectedItem(pos);

	m_SourcesList.SetFocus();
	m_SourcesList.EditLabel(nItem);	
}

void CSourcesDialog::OnEndlabeleditSourcesList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	*pResult = FALSE;

	if (pDispInfo->item.pszText != NULL)
	{
	
		CDataSourcesManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->DataSourcesManager;

		m.setSourcePublicID(
			m.FindSourceByPublicID(
			m_SourcesList.GetItemText(pDispInfo->item.iItem, SRCL_NAME)), pDispInfo->item.pszText);
			
		*pResult = TRUE;	
	}

	
}