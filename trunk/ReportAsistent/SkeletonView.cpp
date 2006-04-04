// SkeletonView.cpp : implementation of the CSkeletonView class
//

#include "stdafx.h"
#include "ReportAsistent.h"

#include "CSkeletonDoc.h"
#include "SkeletonView.h"
#include "ElementTextDialog.h"


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
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONDOWN()
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

	
/*****   //dedek: zakomentoval pro ladeni

	int			nIDPic; // ID obrazku v resourcich
	CBitmap     oBitmap;// objekt obrazek po natazeni z resourcu

	//Natahne obrazky pro TreeCtrl pro vsechny typy prvku
	for (nIDPic = IDB_BMTREEFIRST; nIDPic <=IDB_BMTREELAST; nIDPic++)  
	{
		oBitmap.LoadBitmap(nIDPic);
		pImageList->Add(&oBitmap, (COLORREF)0xFFFFFF);
		oBitmap.DeleteObject();
	}
/*****/

	//dedek: nova verze
	CElementManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;
	m.FillImageList(* pImageList);


	GetTreeCtrl().SetImageList(pImageList, TVSIL_NORMAL);


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

//honza treba delaokovat item data
void CSkeletonView::OnDeleteitem(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	
	
	
	GetDocument()->DeleteItemData(pNMTreeView->itemOld.lParam);
	
	
	
	*pResult = 0;
}

//Iva:
void CSkeletonView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{


	//zjistim, ktera polozka TreeCtrl je "Selected"
	HTREEITEM hTreeSelItem;
	hTreeSelItem = GetTreeCtrl().GetSelectedItem( );

	
	//Poslu zpravu ID_ELEMENT_EDIT sve aplikaci, coz je zprava akceleratoru na Enter
	 AfxGetApp()->GetMainWnd()->SendMessage(WM_COMMAND, ID_ELEMENT_EDIT, 0);
	

}


//pridal honza - zaradi novy element v lHint jako posledniho potomka selected item
void CSkeletonView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	//duvod proc je zde toto: pri pouhem FillTreeCtrl by se strom zobrazil do nerozbalene podoby
	//a na misto kam bylo pridano by bylo nutne znovu se prolistovat
	if (lHint != NULL)
	{
		CTreeCtrl & tree = GetTreeCtrl();

		IXMLDOMElement * new_element = (IXMLDOMElement *) lHint;


		GetDocument()->InsetNodeToTreeCtrl((IXMLDOMElementPtr) new_element, tree.GetSelectedItem(), tree);
	} else
	{
		//Deda: Naplneni TreeCtrl
		GetDocument()->FillTreeControl(GetTreeCtrl());

	}
}


void CSkeletonView::OnContextMenu(CWnd* pWnd, CPoint pointWnd) 
{

	CTreeCtrl& rTreeCtrl = GetTreeCtrl( ) ;
	CElementManager & OElementManager = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;
	CPoint point = pointWnd;
	ScreenToClient(&point); //prevod okennich souradnic okna CSkeletonView na klientske


	HTREEITEM hTreeCtrlItem = rTreeCtrl.HitTest( point, NULL); //zjistim nad jakym prvkem TreeCtrl je prave mys
	
	rTreeCtrl.Select(hTreeCtrlItem,TVGN_CARET);
	if (hTreeCtrlItem == NULL) return; //neni-li mys nad zadnym prvkem TreeCtrl

	CElementManager::elId_t idTypeEl =
	 OElementManager.IdentifyElement 
		(
		 (IXMLDOMElementPtr)(IXMLDOMElement *) rTreeCtrl.GetItemData( hTreeCtrlItem)
		);
	
	switch (idTypeEl)
	{
		case ELID_UNKNOWN: return;

		case ELID_REPORT: 
		{
			//AfxMessageBox("report",0,0);

			//TODO: patricne menu - zatim pracovne mainmenu->edit
			CMenu * hMainMenu = AfxGetApp()->GetMainWnd()->GetMenu();
			CMenu * hEditMenu = hMainMenu->GetSubMenu(1/*Edit*/);

			hEditMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,pointWnd.x,pointWnd.y,AfxGetMainWnd());

			return;
		}

		default:
		{
			
			//dedek: nefungovalo pro prvni AP
			/***********************
			//Typ prvku: staticky
			if (idTypeEl>=OElementManager.getFirstStaticElementID()
				&&
				idTypeEl<OElementManager.getFirstActiveElementID())
			{
				//AfxMessageBox("static",0,0);		

				//TODO: patricne menu - zatim pracovne mainmenu->edit
				CMenu * hMainMenu = AfxGetApp()->GetMainWnd()->GetMenu();
				CMenu * hEditMenu = hMainMenu->GetSubMenu(1); //SubMenu 1 = Edit

				hEditMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,pointWnd.x,pointWnd.y,AfxGetMainWnd());

				return;
			}
			//Typ prvku: aktivni
			if (idTypeEl>=OElementManager.getFirstActiveElementID()
				&&
				idTypeEl<OElementManager.getLastElementId())
			{
				//AfxMessageBox("active",0,0);

				//TODO: patricne menu - zatim pracovne mainmenu->edit
				CMenu * hMainMenu = AfxGetApp()->GetMainWnd()->GetMenu();
				CMenu * hEditMenu = hMainMenu->GetSubMenu(1); //SubMenu 1 = Edit

				hEditMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,pointWnd.x,pointWnd.y,AfxGetMainWnd());

				return;//TODO: patricne menu
			}

			/***********************/
			//dedek: nova verze

			
			if (OElementManager.isElementActive(idTypeEl))
			{	
				//aktivni

				//TODO: patricne menu - zatim pracovne mainmenu->edit
				CMenu * hMainMenu = AfxGetApp()->GetMainWnd()->GetMenu();
				CMenu * hEditMenu = hMainMenu->GetSubMenu(1); //SubMenu 1 = Edit

				hEditMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,pointWnd.x,pointWnd.y,AfxGetMainWnd());

				return;//TODO: patricne menu
			}
			else 
			{
				//staticke

				//AfxMessageBox("static",0,0);		

				//TODO: patricne menu - zatim pracovne mainmenu->edit
				CMenu * hMainMenu = AfxGetApp()->GetMainWnd()->GetMenu();
				CMenu * hEditMenu = hMainMenu->GetSubMenu(1); //SubMenu 1 = Edit

				hEditMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,pointWnd.x,pointWnd.y,AfxGetMainWnd());

				return;
			}
				
			/***********************/
		}
	}

	return;
	
}

void CSkeletonView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	ClientToScreen(&point);
	OnContextMenu(this,point);
	
	CTreeView::OnRButtonDown(nFlags, point);
}

// Puvodni zamer: podle vybraneho prvku TreeCtrl disablovat polozky v Menu->Edit->InsertNew
//Lepsi reseni: pridavani je vzdy mozne a to na nejblizsi nasledujici vhodne misto
//DEL void CSkeletonView::OnCaptureChanged(CWnd *pWnd) 
//DEL {
//DEL 	CElementManager & OElementManager = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;
//DEL 	CTreeCtrl& rTreeCtrl = GetTreeCtrl() ;
//DEL 
//DEL 	CMenu * hMainMenu = AfxGetApp()->GetMainWnd()->GetMenu();
//DEL 	CMenu * hEditMenu = hMainMenu->GetSubMenu(1/*Edit*/)->GetSubMenu(7/*Insert Nes*/);
//DEL 	
//DEL 	HTREEITEM hSelTreeCtrlItem = rTreeCtrl.GetSelectedItem();
//DEL 
//DEL 	CElementManager::elId_t idTypeEl =
//DEL 	 OElementManager.IdentifyElement 
//DEL 		(
//DEL 		 (IXMLDOMElementPtr)(IXMLDOMElement *) rTreeCtrl.GetItemData( hTreeCtrlItem)
//DEL 		);
//DEL 	
//DEL 	switch (idTypeEl)
//DEL 	{
//DEL 		case ELID_UNKNOWN: return;
//DEL 
//DEL 		case ELID_REPORT: 
//DEL 		{
//DEL 	
//DEL 	CTreeView::OnCaptureChanged(pWnd);
//DEL }
//DEL 