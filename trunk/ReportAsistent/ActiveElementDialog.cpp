// ActiveElementDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ReportAsistent.h"
#include "ActiveElementDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CActiveElementDialog dialog


CActiveElementDialog::CActiveElementDialog(IXMLDOMElementPtr & active_element, CWnd* pParent /*=NULL*/)
	: CDialog(CActiveElementDialog::IDD, pParent), m_TransformationsDialog(active_element), m_SimpleFilterDialog(active_element)
{
	//{{AFX_DATA_INIT(CActiveElementDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CActiveElementDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CActiveElementDialog)
	DDX_Control(pDX, IDC_TAB1, m_TabControl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CActiveElementDialog, CDialog)
	//{{AFX_MSG_MAP(CActiveElementDialog)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnSelchangeTabControl)
	ON_BN_CLICKED(IDC_SWITCH_BUTTON, OnSwitchButton)
	ON_BN_CLICKED(IDC_APPLY_BUTTON, OnApplyButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CActiveElementDialog message handlers


#define TAB_FILTER 0
#define TAB_TRANSF 1



BOOL CActiveElementDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_TabControl.InsertItem(TAB_FILTER, "Filter");
	m_TabControl.InsertItem(TAB_TRANSF, "Transformations");
	
	
	
	//zjistim rozmery 
	CRect rc_tab;
	CRect rc_wd;
	
	m_TabControl.GetClientRect(& rc_tab);
	m_TabControl.AdjustRect(FALSE, & rc_tab);

	m_TabControl.GetWindowRect(& rc_wd);
	ScreenToClient(& rc_wd);
  
	rc_tab.OffsetRect(rc_wd.left, rc_wd.top);


	
	//trnsforamtions
	m_TransformationsDialog.Create(IDD_TRANSFORMATIONS_DIALOG, this);

	m_TransformationsDialog.SetWindowPos(& wndBottom, rc_tab.left, rc_tab.top, rc_tab.Width() - rc_wd.left, rc_tab.Height() - rc_wd.top, SWP_SHOWWINDOW);

	m_TransformationsDialog.ShowWindow(SW_HIDE);


	//simple filter
	m_SimpleFilterDialog.Create(IDD_SIMPLE_FILTER_DIALOG, this);

	m_SimpleFilterDialog.SetWindowPos(& wndBottom, rc_tab.left, rc_tab.top, rc_tab.Width() - rc_wd.left, rc_tab.Height() - rc_wd.top, SWP_SHOWWINDOW);

	m_SimpleFilterDialog.ShowWindow(SW_SHOW);

	

	


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CActiveElementDialog::OnSelchangeTabControl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_SimpleFilterDialog.ShowWindow(SW_HIDE);
	m_TransformationsDialog.ShowWindow(SW_HIDE);

	switch (m_TabControl.GetCurSel())
	{
	case TAB_FILTER:
		m_SimpleFilterDialog.ShowWindow(SW_SHOW);
		break;
	case TAB_TRANSF:
		m_TransformationsDialog.ShowWindow(SW_SHOW);		
		break;
	};
	
	*pResult = 0;
}

void CActiveElementDialog::OnSwitchButton() 
{
	
	if (m_TabControl.GetCurSel() == TAB_FILTER)
		m_TabControl.SetCurSel(TAB_TRANSF);
	else
		m_TabControl.SetCurSel(TAB_FILTER);


	LRESULT r;
	OnSelchangeTabControl(NULL,  & r);
		
	
}

void CActiveElementDialog::OnApplyButton() 
{
	m_SimpleFilterDialog.SaveAll();
	m_TransformationsDialog.SaveAll();	
}

void CActiveElementDialog::OnOK() 
{
	if (m_SimpleFilterDialog.SaveAll() && m_TransformationsDialog.SaveAll())
	{
		CDialog::OnOK();
	}
}
