// AttributeLinkTableDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ReportAsistent.h"
#include "AttributeLinkTableDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAttributeLinkTableDialog dialog


CAttributeLinkTableDialog::CAttributeLinkTableDialog(IXMLDOMElementPtr & edited_element, CWnd* pParent, BOOL show_target)
	: CDialog(CAttributeLinkTableDialog::IDD, pParent), CAttributeLinkDialogBase(edited_element),
	m_bShowTarget(show_target)
{
	//{{AFX_DATA_INIT(CAttributeLinkTableDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAttributeLinkTableDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAttributeLinkTableDialog)
	DDX_Control(pDX, IDC_CAPTIONS_LIST, m_CaptionsList);
	DDX_Control(pDX, IDC_TARGET_COMBO, m_TargetCombo);
	DDX_Control(pDX, IDC_ATTRIBUTES_LIST, m_AttributesList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAttributeLinkTableDialog, CDialog)
	//{{AFX_MSG_MAP(CAttributeLinkTableDialog)
	ON_CBN_SELCHANGE(IDC_TARGET_COMBO, OnSelchangeTargetCombo)
	ON_BN_CLICKED(IDC_REFRESH_BUTTON, OnRefreshButton)
	ON_BN_CLICKED(IDC_ADD_BUTTON, OnAddButton)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_CAPTIONS_LIST, OnEndlabeleditCaptionsList)
	ON_BN_CLICKED(IDC_REMOVE_BUTTON, OnRemoveButton)
	ON_BN_CLICKED(IDC_EDIT_CAPTION_BUTTON, OnEditCaptionButton)
	ON_BN_CLICKED(IDC_MOVE_UP_BUTTON, OnMoveUpButton)
	ON_BN_CLICKED(IDC_MOVE_DOWN_BUTTON2, OnMoveDownButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAttributeLinkTableDialog message handlers

#define CAPTLIST_CL_CAPTION		0
#define CAPTLIST_CL_VALUE		1
#define CAPTLIST_CL_NAME		2

BOOL CAttributeLinkTableDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	if (! m_bShowTarget) m_TargetCombo.EnableWindow(FALSE);
	
	// TODO: Add extra initialization here
	InitBaseDialog(m_AttributesList, m_TargetCombo);


	//dedek: inicialozuj CaptionsList
	CRect r;
	m_CaptionsList.GetWindowRect(& r);
	m_CaptionsList.InsertColumn(CAPTLIST_CL_CAPTION, "caption", LVCFMT_LEFT, r.Width()/3);
	m_CaptionsList.InsertColumn(CAPTLIST_CL_VALUE, "value", LVCFMT_LEFT, r.Width()/3);
	m_CaptionsList.InsertColumn(CAPTLIST_CL_NAME, "name", LVCFMT_LEFT, r.Width()/3);


	//napln CaptionsList hodnotami
	IXMLDOMNodeListPtr links = m_edited_element->selectNodes("link");

	CString target_id;
	m_TargetCombo.GetWindowText(target_id);

	for (int a=0; a < links->length; a++)
	{
		IXMLDOMElementPtr link = links->item[a];

		//caption
		int item = m_CaptionsList.InsertItem(a, (_bstr_t) link->getAttribute("caption"));
		
		//attr_name
		CString attr_name = (LPCTSTR) (_bstr_t) link->getAttribute("attr_name");
		m_CaptionsList.SetItemText(item, CAPTLIST_CL_NAME, attr_name);

		//value
		CString query_str;
		query_str.Format("id(\"%s\")/attributes/element_attributes/attribute[@name=\"%s\"]/@value", target_id, attr_name);

		IXMLDOMNodePtr value_attr = m_edited_element->ownerDocument->selectSingleNode((LPCTSTR) query_str);

		if (value_attr != NULL)
		{
			m_CaptionsList.SetItemText(item, CAPTLIST_CL_VALUE, value_attr->text);
			value_attr.Release();
		}

		
		link.Release();
	}

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAttributeLinkTableDialog::OnSelchangeTargetCombo() 
{
	CString target_id;
	m_TargetCombo.GetWindowText(target_id);
	FillAttributesList(m_AttributesList, target_id);	
}

void CAttributeLinkTableDialog::OnRefreshButton() 
{
	CString target_id;
	m_TargetCombo.GetWindowText(target_id);

	OnRefresh(m_AttributesList, target_id);


	//refresh pro captions list

	for (int a=0; a < m_CaptionsList.GetItemCount(); a++)
	{
		CString attr_name = m_CaptionsList.GetItemText(a, CAPTLIST_CL_NAME);
		
		CString query_str;
		query_str.Format("id(\"%s\")/attributes/element_attributes/attribute[@name=\"%s\"]/@value", target_id, attr_name);


		IXMLDOMNodePtr attr_value = m_edited_element->ownerDocument->selectSingleNode((LPCTSTR) query_str);

		if (attr_value != NULL)
		{
			m_CaptionsList.SetItemText(a, CAPTLIST_CL_VALUE, attr_value->text);

			attr_value.Release();

		}

	}
		
}

void CAttributeLinkTableDialog::OnAddButton() 
{
	//najdi vybranou polozku v attribues listu
	POSITION pos = m_AttributesList.GetFirstSelectedItemPosition();
	if (pos == NULL) return;
	int nItem = m_AttributesList.GetNextSelectedItem(pos);
	
	CString name = m_AttributesList.GetItemText(nItem, ATTRLIST_CL_NAME);
	CString value = m_AttributesList.GetItemText(nItem, ATTRLIST_CL_VALUE);


	//vloz polozku na konec captions listu
	int item = m_CaptionsList.InsertItem(m_CaptionsList.GetItemCount(), name);
	m_CaptionsList.SetItemText(item, CAPTLIST_CL_NAME, name);
	m_CaptionsList.SetItemText(item, CAPTLIST_CL_VALUE, value);

	//edituj caption
	m_CaptionsList.SetFocus();
	m_CaptionsList.EditLabel(item);	
}

void CAttributeLinkTableDialog::OnEndlabeleditCaptionsList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;

	*pResult = FALSE;

	if (pDispInfo->item.pszText != NULL)
	{		
		*pResult = TRUE;	
	}
}

void CAttributeLinkTableDialog::OnRemoveButton() 
{
	POSITION pos = m_CaptionsList.GetFirstSelectedItemPosition();
	if (pos == NULL) return;
	int nItem = m_CaptionsList.GetNextSelectedItem(pos);

	m_CaptionsList.DeleteItem(nItem);
	
}

void CAttributeLinkTableDialog::OnEditCaptionButton() 
{
	POSITION pos = m_CaptionsList.GetFirstSelectedItemPosition();
	if (pos == NULL) return;
	int nItem = m_CaptionsList.GetNextSelectedItem(pos);

	//edituj caption
	m_CaptionsList.SetFocus();
	m_CaptionsList.EditLabel(nItem);		
}

void CAttributeLinkTableDialog::OnMoveUpButton() 
{
	POSITION pos = m_CaptionsList.GetFirstSelectedItemPosition();
	if (pos == NULL) return;
	int nItem = m_CaptionsList.GetNextSelectedItem(pos);

	if (nItem <= 0) return;


	CString name = m_CaptionsList.GetItemText(nItem, CAPTLIST_CL_NAME);
	CString value = m_CaptionsList.GetItemText(nItem, CAPTLIST_CL_VALUE);
	CString caption = m_CaptionsList.GetItemText(nItem, CAPTLIST_CL_CAPTION);

		
	m_CaptionsList.DeleteItem(nItem);

	nItem = m_CaptionsList.InsertItem(--nItem, caption);
	m_CaptionsList.SetItemText(nItem, CAPTLIST_CL_NAME, name);
	m_CaptionsList.SetItemText(nItem, CAPTLIST_CL_VALUE, value);

	m_CaptionsList.SetItemState(nItem, LVIS_SELECTED, LVIS_SELECTED);
}

void CAttributeLinkTableDialog::OnMoveDownButton() 
{
	POSITION pos = m_CaptionsList.GetFirstSelectedItemPosition();
	if (pos == NULL) return;
	int nItem = m_CaptionsList.GetNextSelectedItem(pos);

	if (nItem >= m_CaptionsList.GetItemCount()) return;


	CString name = m_CaptionsList.GetItemText(nItem, CAPTLIST_CL_NAME);
	CString value = m_CaptionsList.GetItemText(nItem, CAPTLIST_CL_VALUE);
	CString caption = m_CaptionsList.GetItemText(nItem, CAPTLIST_CL_CAPTION);

		
	m_CaptionsList.DeleteItem(nItem);

	nItem = m_CaptionsList.InsertItem(++nItem, caption);
	m_CaptionsList.SetItemText(nItem, CAPTLIST_CL_NAME, name);
	m_CaptionsList.SetItemText(nItem, CAPTLIST_CL_VALUE, value);

	m_CaptionsList.SetItemState(nItem, LVIS_SELECTED, LVIS_SELECTED);
	
}

void CAttributeLinkTableDialog::OnOK() 
{

	SaveTarget(m_TargetCombo);

	//smaz vsecky link elementy
	IXMLDOMSelectionPtr sel = m_edited_element->selectNodes("link");
	sel->removeAll();
	sel.Release();

	//vytvor vzorovy element
	IXMLDOMElementPtr link_elenet = m_edited_element->ownerDocument->createElement("link");
	link_elenet->setAttributeNode(m_edited_element->ownerDocument->createAttribute("attr_name"));
	link_elenet->setAttributeNode(m_edited_element->ownerDocument->createAttribute("caption"));

	//pridej elementy podle listu
	for (int a=0; a < m_CaptionsList.GetItemCount(); a++)
	{
		link_elenet->setAttribute("attr_name", (LPCTSTR) m_CaptionsList.GetItemText(a, CAPTLIST_CL_NAME));
		link_elenet->setAttribute("caption", (LPCTSTR) m_CaptionsList.GetItemText(a, CAPTLIST_CL_CAPTION));

		m_edited_element->appendChild(link_elenet->cloneNode(VARIANT_FALSE));
	}

	link_elenet.Release();
	
	CDialog::OnOK();
}
