// AttributeLinkDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ReportAsistent.h"
#include "AttributeLinkDialog.h"
#include "APTransform.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CAttributeLinkDialog dialog


CAttributeLinkDialog::CAttributeLinkDialog(MSXML2::IXMLDOMElementPtr & edited_element, CWnd* pParent /*=NULL*/)
	: CDialog(CAttributeLinkDialog::IDD, pParent), CAttributeLinkDialogBase(edited_element)
{
	//{{AFX_DATA_INIT(CAttributeLinkDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAttributeLinkDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAttributeLinkDialog)
	DDX_Control(pDX, IDC_STYLES_COMBO, m_StylesCombo);
	DDX_Control(pDX, IDC_ATTRIBUTES_LIST, m_AttributesList);
	DDX_Control(pDX, IDC_TARGET_COMBO, m_TargetCombo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAttributeLinkDialog, CDialog)
	//{{AFX_MSG_MAP(CAttributeLinkDialog)
	ON_CBN_SELCHANGE(IDC_TARGET_COMBO, OnSelchangeTargetCombo)
	ON_BN_CLICKED(IDC_REFRESH_BUTTON, OnRefreshButton)
	ON_BN_CLICKED(IDC_STYLES_REFRESH_BUTTON, OnStylesRefreshButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAttributeLinkDialog message handlers

BOOL CAttributeLinkDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitBaseDialog(m_AttributesList, m_TargetCombo);

	
	
	FillStylesCombo();


	//vyber style v comboboxu
	_variant_t style = m_edited_element->getAttribute("style");
	if (style.vt != VT_NULL)
	{
		m_StylesCombo.SelectString(-1, (_bstr_t) style);
	}

	
	
	//najdi vybranou polozku
	LVFINDINFO info;
	ZeroMemory(& info, sizeof info);

	CString attr_n = (LPCTSTR) (_bstr_t) m_edited_element->getAttribute("attr_name");

	info.flags = LVFI_STRING;
	info.psz = attr_n;
	int item = m_AttributesList.FindItem(& info);

	//vyber vybranou
	m_AttributesList.SetItemState(item, LVIS_SELECTED, LVIS_SELECTED);

	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CAttributeLinkDialog::OnSelchangeTargetCombo() 
{
	CString target_id;
	m_TargetCombo.GetWindowText(target_id);
	FillAttributesList(m_AttributesList, target_id);
}

void CAttributeLinkDialog::OnOK() 
{
	CString s;
	
	
	SaveTarget(m_TargetCombo);
	
	//attr name
	POSITION pos = m_AttributesList.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nItem = m_AttributesList.GetNextSelectedItem(pos);
		s = m_AttributesList.GetItemText(nItem, ATTRLIST_CL_NAME);
	}
	m_edited_element->setAttribute("attr_name", (LPCTSTR) s);

	
	
	//style
	
	//vymaz attribyt style z tagu
	if (m_edited_element->attributes->getNamedItem("style") != NULL)
	{
		m_edited_element->attributes->removeNamedItem("style");
	}

	CString style_str;
	m_StylesCombo.GetWindowText(style_str);

	if (style_str.GetLength() != 0)
	{
		MSXML2::IXMLDOMAttributePtr s_atr = m_edited_element->ownerDocument->createAttribute("style");
		s_atr->text = (LPCTSTR) style_str;
		m_edited_element->setAttributeNode(s_atr);
		s_atr.Release();
	}
	
	CDialog::OnOK();
}

void CAttributeLinkDialog::OnRefreshButton() 
{
	
	CString s;
	m_TargetCombo.GetWindowText(s);

	OnRefresh(m_AttributesList, s);
}

void CAttributeLinkDialog::OnStylesRefreshButton() 
{
	CWordManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->WordManager;
	m.LoadWordStyles();

	FillStylesCombo();	
}

void CAttributeLinkDialog::FillStylesCombo()
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
