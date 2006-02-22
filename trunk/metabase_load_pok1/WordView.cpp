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

	m_ptStartDrag.x = 0;
	m_ptStartDrag.y = 0;

	m_ptMove.x = 0;
	m_ptMove.y = 0;

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


BEGIN_MESSAGE_MAP(CWordView, CButton)
	//{{AFX_MSG_MAP(CWordView)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
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
	CRect rect = r;

	
	if (SUCCEEDED(m_pItem->GetExtent(&size, m_pItem->m_nDrawAspect)))
	{

			dc.HIMETRICtoLP(&size);
			rect.right = size.cx + rect.left;
			rect.bottom = size.cy + rect.top;
	}


	//	rect.IntersectRect(rect,& r); 
	dc.IntersectClipRect(& r);
	rect += m_ptMove;
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


void CWordView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_ptStartDrag = point - m_ptMove;
	SetCapture();
	
//	SetCursor(LoadCursor(NULL, IDC_HAND));
	
//	CButton::OnLButtonDown(nFlags, point);
}

void CWordView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_ptStartDrag.x = 0;
	m_ptStartDrag.y = 0;
	ReleaseCapture();

//	SetCursor(LoadCursor(NULL, IDC_ARROW));
	
//	CButton::OnLButtonUp(nFlags, point);
}

void CWordView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if ((m_ptStartDrag.x == 0) && (m_ptStartDrag.y == 0)) return;


	CSize size;
	CRect rect;

	m_pItem->GetExtent(&size, m_pItem->m_nDrawAspect);
	

	CDC * dc = GetDC();
	dc->HIMETRICtoLP(&size);
	ReleaseDC(dc);
	GetClientRect(rect);

	if ((rect.Width() >= size.cx) && (rect.Height() >= size.cy))
	{
		m_ptMove.x = m_ptMove.y = 0;
		return ;
	}

	m_ptMove.x = point.x - m_ptStartDrag.x;
	m_ptMove.y = point.y - m_ptStartDrag.y;



	if (m_ptMove.x > 0) m_ptMove.x = 0;
	if (m_ptMove.y > 0) m_ptMove.y = 0;

	if (size.cx + m_ptMove.x < rect.Width()) m_ptMove.x = rect.Width() - size.cx;
	if (size.cy + m_ptMove.y < rect.Height()) m_ptMove.y = rect.Height() - size.cy;


	Invalidate();
	
//	CButton::OnMouseMove(nFlags, point);
}
