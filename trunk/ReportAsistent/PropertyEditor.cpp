// PropertyEditor.cpp : implementation file
//
/*
This file is part of LM Report Asistent.

Authors: Jan Dedek, Jan Kodym, Martin Chrz, Iva Bartunkova

LM Report Asistent is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

LM Report Asistent is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with LM Report Asistent; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include "stdafx.h"
#include "ReportAsistent.h"
#include "PropertyEditor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define DISP_SPACE 15	//mezera mezi jednotlivymi property 
#define BORDER_SPACE 10 //mezera od kraje m_static_border
#define COMBO_HEIGHT 300 //mezera od kraje m_static_border


#define PROPERTY_CONTROLS_ID_JUMP 300
#define IDs_per_PROPERTY 3

#define PROPINDEX_2_COMBOCTRL(index) (IDC_STATIC1 +PROPERTY_CONTROLS_ID_JUMP +index*IDs_per_PROPERTY)
#define COMBOCTRL_2_PROPINDEX(ctrl) ((ctrl - PROPERTY_CONTROLS_ID_JUMP - IDC_STATIC1)/IDs_per_PROPERTY)
#define IS_COMBO_CONTROL(ctrl) (((ctrl - PROPERTY_CONTROLS_ID_JUMP - IDC_STATIC1) % IDs_per_PROPERTY) == 0)

#define PROPINDEX_2_LABELCTRL(index) (IDC_STATIC1 +PROPERTY_CONTROLS_ID_JUMP +index*IDs_per_PROPERTY +1)
#define LABELCTRL_2_PROPINDEX(ctrl) ((ctrl - PROPERTY_CONTROLS_ID_JUMP - IDC_STATIC1 -1)/IDs_per_PROPERTY)

#define PROPINDEX_2_CUSTOMCTRL(index) (IDC_STATIC1 +PROPERTY_CONTROLS_ID_JUMP +index*IDs_per_PROPERTY +2)
#define CUSTOMCTRL_2_PROPINDEX(ctrl) ((ctrl - PROPERTY_CONTROLS_ID_JUMP - IDC_STATIC1 -2)/IDs_per_PROPERTY)
#define IS_CUSTOM_CONTROL(ctrl) (((ctrl - PROPERTY_CONTROLS_ID_JUMP - IDC_STATIC1) % IDs_per_PROPERTY) == 2)

/////////////////////////////////////////////////////////////////////////////
// CPropertyEditor dialog


CPropertyEditor::CPropertyEditor(LPCTSTR caption, CWnd* pParent)   // standard constructor
	: CDialog(CPropertyEditor::IDD, pParent), m_caption(caption)
{
	//{{AFX_DATA_INIT(CPropertyEditor)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPropertyEditor::~CPropertyEditor()
{
	for (int a=0; a < m_properties.GetSize(); a++)
	{
		delete m_properties[a].prop;
		if (m_properties[a].label != NULL) delete m_properties[a].label;
		if (m_properties[a].combo != NULL) delete m_properties[a].combo;
		if (m_properties[a].custom != NULL) delete m_properties[a].custom;
	}
}


void CPropertyEditor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropertyEditor)
	DDX_Control(pDX, IDC_ERROR_TEXT, m_err_text);
	DDX_Control(pDX, IDC_STATIC1, m_static_border);
	DDX_Control(pDX, IDC_SCROLLBAR1, m_scrollbar);
	DDX_Control(pDX, IDOK, m_ok_button);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropertyEditor, CDialog)
	//{{AFX_MSG_MAP(CPropertyEditor)
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
	ON_STN_CLICKED(IDC_ERROR_TEXT, OnStnClickedErrorText)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropertyEditor message handlers

void CPropertyEditor::OnDestroy() 
{
	CDialog::OnDestroy();
	
	for (int a=0; a<GetPropertiesCount(); a++)
	{
		if (ValidateProp(a))
		{
			//zavola se m_properties[a].prop->SetValue(...) 
			GetValueOfProperty(a);
		}
	}
	
	CDialog::OnDestroy();	
}

HBRUSH CPropertyEditor::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		int index = LABELCTRL_2_PROPINDEX(pWnd->GetDlgCtrlID());

		if ((pWnd->GetDlgCtrlID() == IDC_ERROR_TEXT) || (m_err_props.Find(index) != NULL))
		{
			pDC->SetTextColor(RGB(255, 0, 0));
		}
	}
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CPropertyEditor::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default

	if (IS_CUSTOM_CONTROL(pScrollBar->GetDlgCtrlID()))
	{
		int index = COMBOCTRL_2_PROPINDEX(pScrollBar->GetDlgCtrlID());
		if ((index >= 0) && (index < GetPropertiesCount()))
		{
			OnCmdMsg(pScrollBar->GetDlgCtrlID(), nSBCode, pScrollBar, (AFX_CMDHANDLERINFO*) nPos);
		}
}

	if (pScrollBar != & m_scrollbar) return ;
	
	int new_pos = pScrollBar->GetScrollPos();

	switch (nSBCode)
	{
	case SB_ENDSCROLL:
		return;
	case SB_TOP:
		new_pos = 0;
		break;
	case SB_BOTTOM:
		new_pos = GetPropertiesCount() - GetMaxVisiblePropertiesCount();
		break;
	case SB_THUMBPOSITION:
	case SB_THUMBTRACK:
		new_pos = nPos;
		break;
	case SB_PAGEDOWN:
	case SB_LINEDOWN:
		new_pos++;
		break;
	case SB_PAGEUP:
	case SB_LINEUP:
		new_pos--;
	}

	int pom = m_scrollbar.GetScrollLimit();

	
	if ((new_pos >= 0) && (new_pos <= GetPropertiesCount() - GetMaxVisiblePropertiesCount() ))
	{
		pScrollBar->SetScrollPos(new_pos);
		ShowVisibleProperties();
	}

	//CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

BOOL CPropertyEditor::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	
	// TODO: Add extra initialization here
	SetWindowText(m_caption);

	m_scrollbar.SetScrollRange(0, 0, FALSE);

	for (int a=0; a<GetPropertiesCount(); a++)
	{
		CreateProperty(a);
		ValidateProp(a);
	}

	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


CProperty * CPropertyEditor::GetValueOfProperty(int index)
{
	if ((index < 0) || (index >= GetPropertiesCount()))	return NULL;

	SProperty p = m_properties[index];

	if (IsWindow(m_hWnd))
	{
		CString s;
		p.combo->GetWindowText(s);
		CString err;
		if (p.prop->ValidateValue(s, err))
		{
			p.prop->SetValue(s);
			p.combo->SetWindowText(p.prop->GetValue());
		}
	}

	return p.prop;
}

int CPropertyEditor::GetMaxVisiblePropertiesCount(void)
{
	CRect r;
	m_static_border.GetWindowRect(r);
	int capt_height = GetSystemMetrics(SM_CYCAPTION);

	return (r.Height() - BORDER_SPACE*2) / (DISP_SPACE + capt_height*2);
}

int CPropertyEditor::GetFirstVisibleProperty(void)
{
	return m_scrollbar.GetScrollPos();
}

//vrati maximalni potencialni index property, ktera by jeste mohla byt videt
int CPropertyEditor::GetLastVisibleProperty(void)
{
	return GetFirstVisibleProperty() + GetMaxVisiblePropertiesCount() -1;
}

int CPropertyEditor::GetPropertiesCount(void)
{
	return (int) m_properties.GetSize();
}


void CPropertyEditor::ShowVisibleProperties(void)
{
	int min = GetFirstVisibleProperty();
	int max = GetLastVisibleProperty();

	for (int a = 0; a < GetPropertiesCount(); a++)
	{
		if ((a < min) || (a > max))
		{
			m_properties[a].combo->ShowWindow(SW_HIDE);
			m_properties[a].label->ShowWindow(SW_HIDE);
			if (m_properties[a].custom != NULL) m_properties[a].custom->ShowWindow(SW_HIDE);
		}
		else
		{
			CRect cr, lr, custr;
			CountPropertyRects(lr, cr, custr, a);

			m_properties[a].label->MoveWindow(lr);
			m_properties[a].combo->SetWindowPos(
				NULL, cr.left, cr.top, cr.Width(), cr.Height(),
				SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
			
			m_properties[a].combo->ShowWindow(SW_SHOW);
			m_properties[a].label->ShowWindow(SW_SHOW);

			if (m_properties[a].custom != NULL)
			{
				m_properties[a].custom->SetWindowPos(
					NULL, custr.left, custr.top, custr.Width(), custr.Height(), 
					SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
				
				m_properties[a].custom->ShowWindow(SW_SHOW);
			}

		}
	}

	UpdateWindow();
}


BOOL CPropertyEditor::ValidateProp(int index)
{
	CString err;
	CString new_val, value;
	m_properties[index].combo->GetWindowText(value);
	new_val = value;

	if (m_properties[index].prop->ValidateValue(new_val, err))
	{
		//valid
		/*
		if (new_val != value)
			m_properties[index].combo->SetWindowText(new_val);
	*/
		POSITION pos = m_err_props.Find(index);
		if (pos != NULL)
		{
			m_err_props.RemoveAt(pos);
		}

		m_err_text.SetWindowText("");

		m_properties[index].label->Invalidate(FALSE);
		if (m_err_props.GetCount() == 0) 
		{
			m_ok_button.EnableWindow();
		}
		else
		{
			int next = m_err_props.GetHead();
			CString s;
			ValidateProp(next);
		}

		return TRUE;
	}
	else
	{
		//invalid
		CString err_msg;
		err_msg.Format("%s:\n%s", m_properties[index].prop->GetLabel(), (LPCTSTR) err);
		m_err_text.SetWindowText(err_msg);
		if (m_err_props.Find(index) == NULL) m_err_props.AddHead(index);
		m_ok_button.EnableWindow(FALSE);
		m_properties[index].label->Invalidate(FALSE);

		return FALSE;
	}
}


void CPropertyEditor::CreateProperty(int index)
{
	ASSERT(index >= 0);
	ASSERT(index < GetPropertiesCount());
	ASSERT(IsWindow(m_hWnd));
	
	SProperty & p = m_properties[index];

	int pos = index;

	CRect cr, lr, custr;
	CountPropertyRects(lr, cr, custr, index);

	DWORD visible = 
		(pos <= GetLastVisibleProperty()) && (pos >= GetFirstVisibleProperty()) ?
		WS_VISIBLE : 0;



	p.label = new CStatic();
	p.label->Create(p.prop->GetLabel(), WS_CHILD|visible, lr, this, PROPINDEX_2_LABELCTRL(index));
	p.label->SetFont(m_ok_button.GetFont(), FALSE);

	p.combo = new CComboBox();
	p.combo->Create(p.prop->GetComboStyle() | WS_CHILD|visible|WS_VSCROLL|WS_TABSTOP|CBS_AUTOHSCROLL|CBS_SORT,
		cr, this, PROPINDEX_2_COMBOCTRL(index));
	p.combo->SetFont(m_ok_button.GetFont(), FALSE);

	p.prop->InitCombo(p.combo);
	p.custom = p.prop->CreateCustomControl(WS_CHILD|visible, PROPINDEX_2_CUSTOMCTRL(index), this, custr);
	
	//nastav default_value
	int sel = p.combo->SelectString(-1, p.prop->GetValue()); //nejprve zkusime jestli hodnotya jiz v listu neni
	if (sel == CB_ERR)
	{
		//kdyz tam neni tak ji pridame
		p.combo->AddString(p.prop->GetValue());
		p.combo->SelectString(-1, p.prop->GetValue());
	}




	int min=0, max=0;
	m_scrollbar.GetScrollRange(& min, &max);

	if (GetPropertiesCount() > GetMaxVisiblePropertiesCount())
	{
		SCROLLINFO si;
		ZeroMemory(& si, sizeof si);
		si.cbSize = sizeof si;
		si.fMask = SIF_RANGE | SIF_PAGE;
		si.nMin = 0;
		si.nMax = GetPropertiesCount() - GetMaxVisiblePropertiesCount();
		si.nPage = 1;
		m_scrollbar.SetScrollInfo(& si, FALSE);
//		m_scrollbar.SetScrollRange(0, max +1);
	}

	if ((max - min) == 0)
		m_scrollbar.EnableScrollBar(ESB_DISABLE_BOTH);
	else
		m_scrollbar.EnableScrollBar(ESB_ENABLE_BOTH);


	//ShowVisibleProperties();
	//ted nevolat - pada
	return;
}

void CPropertyEditor::CountPropertyRects(CRect & label_rect, CRect & combo_rect, CRect & custom_rect, int property_index)
{
	ASSERT(property_index >= 0);
	ASSERT(property_index < GetPropertiesCount());

	
	CRect r, sr;
	m_static_border.GetWindowRect(r);
	m_scrollbar.GetWindowRect(sr);
	ScreenToClient(r);

	int first = GetFirstVisibleProperty();
	int capt_height = GetSystemMetrics(SM_CYCAPTION);

	int x = r.left + BORDER_SPACE;
	int y = r.top +BORDER_SPACE+ (DISP_SPACE + capt_height*2)*(property_index - first);
	int w = r.Width()-BORDER_SPACE*2 - sr.Width();

	label_rect.left = x;
	label_rect.top = y;
	label_rect.right = x + w;
	label_rect.bottom = y + capt_height;

	combo_rect.left = x;
	combo_rect.top = y + capt_height;
	combo_rect.right = x + w - m_properties[property_index].prop->GetCustomControlWidth();
	combo_rect.bottom = y + capt_height + COMBO_HEIGHT;

	custom_rect.left = combo_rect.right;
	custom_rect.top = y + capt_height;
	custom_rect.right = x + w;
	custom_rect.bottom = y + capt_height*2;
}

BOOL CPropertyEditor::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	// TODO: Add your specialized code here and/or call the base class

	if (IS_COMBO_CONTROL(nID))
	{

		int index = COMBOCTRL_2_PROPINDEX(nID);
		CString s, err;

		if ((index >= 0) && (index < GetPropertiesCount()))
		{
			switch (nCode)
			{
			case CBN_SELCHANGE:
				m_properties[index].combo->GetLBText(m_properties[index].combo->GetCurSel(), s);
				m_properties[index].combo->SetWindowText(s);
				ValidateProp(index);
				break;
			case CBN_KILLFOCUS:
				//do comboboxu zapise skutecnou hodnotu
				GetValueOfProperty(index);
				break;
			case CBN_EDITCHANGE:
				ValidateProp(index);
				break;
			case CBN_EDITUPDATE:
				if (index < GetFirstVisibleProperty())
				{
					m_scrollbar.SetScrollPos(index);
					ShowVisibleProperties();
				}
				else if (index > GetLastVisibleProperty())
				{
					m_scrollbar.SetScrollPos(index - GetMaxVisiblePropertiesCount() +1);
					ShowVisibleProperties();
				}
				break;
			}
		}
	}
	else if (IS_CUSTOM_CONTROL(nID))
	{
		int index = COMBOCTRL_2_PROPINDEX(nID);
		if ((index >= 0) && (index < GetPropertiesCount()))
		{
			if (m_properties[index].prop->OnCustomCommand(nID, nCode, pExtra, pHandlerInfo))
			{
				//prepsat hodnotu
				m_properties[index].combo->SetWindowText(
					m_properties[index].prop->GetValue());
				ValidateProp(index);
				//do comboboxu zapise skutecnou hodnotu
			}
		}
	}

	
	return CDialog::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

int CPropertyEditor::AddProperty(CProperty * prop)
{
//	SProperty & sp = AddProperty(prop->GetLabel(), prop->GetComboStyle());

	ASSERT(prop != NULL);
	
	SProperty sp;

	sp.combo = NULL;
	sp.label = NULL;
	sp.custom = NULL;
	sp.prop = prop;

	int index = (int) m_properties.Add(sp);

	if (IsWindow(m_hWnd))
	{
		CreateProperty(index);
	}

	return 0;
}


void CPropertyEditor::OnStnClickedErrorText()
{
	// TODO: Add your control notification handler code here
}
