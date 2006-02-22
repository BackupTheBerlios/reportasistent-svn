// WordView.cpp : implementation file
//

#include "stdafx.h"
#include "metabase_load_pok1.h"
#include "WordView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWordView

CWordView::CWordView()
{
	m_pDoc = new COleDocument();
	m_pItem = new CMyOleClientItem(this, m_pDoc);

	CLSID cid;
	CLSIDFromProgID(L"Word.Document", & cid);

	
	
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//asi by se melo osetrit
//nebo nekam dat try blok
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
	m_pItem->CreateNewItem(cid);
	m_pItem->Activate(OLEIVERB_UIACTIVATE, NULL);
}

CWordView::~CWordView()
{
	delete m_pItem;
	delete m_pDoc;
}


BEGIN_MESSAGE_MAP(CWordView, CStatic)
	//{{AFX_MSG_MAP(CWordView)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWordView message handlers

void CWordView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	RECT r;
	GetClientRect(& r);
	CBrush b(0xEFEFEF);
	dc.FillRect(& r, & b);
	
	CSize size;
	CRect rect(10, 10, 210, 210);

	
	if (SUCCEEDED(m_pItem->GetExtent(&size, m_pItem->m_nDrawAspect)))
	{

			dc.HIMETRICtoLP(&size);
			rect.right = size.cx + 10;
			rect.bottom = size.cy + 10;
	}

	m_pItem->Draw(& dc, & rect);

	// Do not call CStatic::OnPaint() for painting messages
}



void CMyOleClientItem::OnChange(OLE_NOTIFICATION nCode, DWORD dwParam)
{
	if (m_wdpParent->m_hWnd != 0) m_wdpParent->Invalidate();

	COleClientItem::OnChange(nCode, dwParam);
}


LPOLEOBJECT CWordView::GetWordObject(void)
{
	return m_pItem->m_lpObject;
}

