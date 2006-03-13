// SkeletonView.cpp : implementation of the CSkeletonView class
//

#include "stdafx.h"
#include "ReportAsistent.h"

#include "CSkeletonDoc.h"
#include "SkeletonView.h"
#include "ElementText.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkeletonView

IMPLEMENT_DYNCREATE(CSkeletonView, CTreeView)

BEGIN_MESSAGE_MAP(CSkeletonView, CTreeView)
	//{{AFX_MSG_MAP(CSkeletonView)
	ON_NOTIFY_REFLECT(TVN_DELETEITEM, OnDeleteitem)
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkeletonView construction/destruction

CSkeletonView::CSkeletonView()
{
	// TODO: add construction code here

}

CSkeletonView::~CSkeletonView()
{
}

BOOL CSkeletonView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CTreeView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSkeletonView drawing

void CSkeletonView::OnDraw(CDC* pDC)
{
	CSkeletonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void CSkeletonView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();
	

//Iva: Uprava stylu TreeCtrl
	long        lStyleOld;

	lStyleOld = GetWindowLong(m_hWnd, GWL_STYLE);
	lStyleOld |= TVS_EDITLABELS|TVS_HASBUTTONS |TVS_HASLINES|TVS_LINESATROOT|TVS_SHOWSELALWAYS;

	SetWindowLong(m_hWnd, GWL_STYLE, lStyleOld);

//Iva: Natahnu obrazky pro TreeCtrl
	CImageList          *pImageList;

	pImageList = new CImageList();
	pImageList->Create(16, 16,  //rozmery obrazku k nacteni do ImageListu
						ILC_MASK, 
						NUM_PICTURES_TREECTRL, //pocatecni pocet obrazku v ImageListu..viz Stdafx.h
						10);//o kolik obrazku se ImageList muze zvetsit.. ??

	int			nIDPic; // ID obrazku v resourcich
	CBitmap     oBitmap;// objekt obrazek po natazeni z resourcu

	//Natahne obrazky pro TreeCtrl pro vsechny typy prvku
	for (nIDPic = IDB_BMTREEFIRST; nIDPic <=IDB_BMTREELAST; nIDPic++)  
	{
		oBitmap.LoadBitmap(nIDPic);
		pImageList->Add(&oBitmap, (COLORREF)0xFFFFFF);
		oBitmap.DeleteObject();
	}
	GetTreeCtrl().SetImageList(pImageList, TVSIL_NORMAL);
	

//Deda: Naplneni TreeCtrl
	GetDocument()->FillTreeControl(GetTreeCtrl());

}

/////////////////////////////////////////////////////////////////////////////
// CSkeletonView diagnostics

#ifdef _DEBUG
void CSkeletonView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CSkeletonView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CSkeletonDoc* CSkeletonView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSkeletonDoc)));
	return (CSkeletonDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSkeletonView message handlers

void CSkeletonView::OnDeleteitem(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	
	
	
	//uvolni referenci alokovanou pro ItemData
	MSXML2::IXMLDOMNode * np = (MSXML2::IXMLDOMNode *) pNMTreeView->itemOld.lParam;

	if (np != NULL) np->Release();

	
	*pResult = 0;
}

//Iva:
void CSkeletonView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	int nImg;
	int nImgSel;

	//zjistim, ktera polozka TreeCtrl je "Selected"
	HTREEITEM hTreeSelItem;
	hTreeSelItem = GetTreeCtrl().GetSelectedItem( );

	//Podle ikony polozky zjistim, o ktery typ polozky jde:
	 if (0!=GetTreeCtrl().GetItemImage(hTreeSelItem,nImg,nImgSel) )
	 {
		 //Je-li to prvek typu TEXT
		 if (nImg== (IDB_TEXTICO-IDB_BMTREEFIRST-1))
		 {
		 	//Vytvorim instanci dialogu pro Prvek Text
			CElementText dlgText;
			//A dialog zobrazim
			dlgText.DoModal();
		 }
	 }

}

