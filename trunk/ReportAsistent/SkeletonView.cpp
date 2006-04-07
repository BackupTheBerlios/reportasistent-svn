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
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_NOTIFY_REFLECT(TVN_BEGINDRAG, OnBegindrag)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkeletonView construction/destruction

CSkeletonView::CSkeletonView()
{
	m_bDragging = FALSE;
	m_pimagelist = NULL;
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
		//dedek: spravne o radek nize
		//(IXMLDOMElementPtr)(IXMLDOMElement *) rTreeCtrl.GetItemData( hTreeCtrlItem)
			(IXMLDOMElementPtr) GetDocument()->ElementFromItemData(rTreeCtrl.GetItemData(hTreeCtrlItem))
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
			
			//dedek: nefungovalo pro posledni AP chyba nejspis v idTypeEl<OElementManager.getLastElementId())
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

				//AfxMessageBox("active",0,0);

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

// Iva: Puvodni zamer: podle vybraneho prvku TreeCtrl disablovat polozky v Menu->Edit->InsertNew
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
void CSkeletonView::OnEditCopy() 
{
	AfxMessageBox("Bude se kopirovat.",0,0);


	CTreeCtrl & rTreeCtrl = GetTreeCtrl();
	IXMLDOMElementPtr SelXMLDomElement = GetDocument()->ElementFromItemData(rTreeCtrl.GetItemData(rTreeCtrl.GetSelectedItem()));
	
//ziskam XML vybraneho prvku TreeCtrl
	_bstr_t bstrSelElmXML= SelXMLDomElement->xml; 

//Alokuji globalni pamet a XML do ni zkopiruji
	HGLOBAL hgMemForXML = GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE ,    // allocation attributes
						(DWORD) (bstrSelElmXML.length() + 1)   // number of bytes to allocate
						);
	if (0==hgMemForXML) 
	{
		AfxMessageBox("Nepodarilo se alokovat dostatek pameti pro XML podstromu",0,0);
		return;
	}

	LPTSTR pMemForXML = (LPTSTR) GlobalLock(hgMemForXML);
	strcpy(pMemForXML,(LPTSTR) bstrSelElmXML);
	AfxMessageBox(pMemForXML,0,0);
	

	GlobalUnlock(hgMemForXML);
	

//Otevru clipboard a soupnu do nej XML
	if (0==OpenClipboard()) 
	{
		AfxMessageBox("Clipboard pouziva nekdo jiny",0,0);
		return;
	}

	//??Jaky mam dat format??
	if(0== SetClipboardData(CF_TEXT, // clipboard format - pripadne:CF_TEXT
							hgMemForXML))   // data handle
	{
		AfxMessageBox("Umistit data do clipboardu se nepodarilo",0,0);
		DWORD dErr = GetLastError();
		ASSERT(0!=CloseClipboard());
		return;

	}

//zavru clipboard
	ASSERT(0!=CloseClipboard());


// uvolnim globalni pamet
	ASSERT(NULL==GlobalFree(hgMemForXML));
	DWORD dErr = GetLastError();

	return;
	
}

void CSkeletonView::OnEditPaste() 
{
	AfxMessageBox("Bude se paste-ovat.",0,0);	

	CTreeCtrl & rTreeCtrl = GetTreeCtrl();
	IXMLDOMElementPtr SelXMLDomElement = GetDocument()->ElementFromItemData(rTreeCtrl.GetItemData(rTreeCtrl.GetSelectedItem()));

//Otevru clipboard a prectu z nej XML
	if (0==OpenClipboard()) 
	{
		AfxMessageBox("Clipboard pouziva nekdo jiny",0,0);
		return;
	}
	LPCTSTR pMemForXML = (LPCTSTR)GetClipboardData(CF_TEXT);

	if (NULL==pMemForXML) 
	{
		AfxMessageBox("Precist text z clipboardu se nepodarilo",0,0);
		ASSERT(0!=CloseClipboard());
		return;
	}

	AfxMessageBox(pMemForXML,0,0);

//vytvorim novy IXMLDOMDoc
	IXMLDOMDocumentPtr pNewXMLDoc;
	pNewXMLDoc.CreateInstance(_T("Msxml2.DOMDocument"));	
//XML do nej natahnu

	HRESULT hRes = pNewXMLDoc->loadXML(pMemForXML);//"<text id=\"text111\">moje</text>");
	if (pNewXMLDoc->parseError->errorCode != S_OK)
	{
		AfxMessageBox(pNewXMLDoc->parseError->reason);
	}

//zavru clipboard
	ASSERT(0!=CloseClipboard());

//zmenim id vsech prvku
	CElementManager & OElementManager = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;
	IXMLDOMElementPtr pNewXMLElm = pNewXMLDoc->GetdocumentElement();

	GetDocument()->ChangeIDsInTree(pNewXMLElm);
	AfxMessageBox(pNewXMLDoc->xml,0,0);

//pripojim ho do existujiciho
	if (0== OElementManager.CanInsertChildHere(pNewXMLElm,SelXMLDomElement))
	{
		AfxMessageBox(IDS_INSERT_NEW_ELEMENT_WRONG_LOCATION,0,0);
		pNewXMLDoc.Release();	
		return;
	}
	
	try
	{
		IXMLDOMElementPtr pResElm=SelXMLDomElement->appendChild(pNewXMLElm);
		if (0!=pResElm)
		{
			GetDocument()->SetModifiedFlag();		
			GetDocument()->UpdateAllViews(NULL, 0);
		}
		return;


	}
	catch (_com_error &e)
	{
		//AfxMessageBox(e.ErrorMessage());
		AfxMessageBox(e.Description());
	}


	AfxMessageBox(IDS_INSERT_NEW_ELEMENT_WRONG_LOCATION);	

	return;

/*
	UINT EnumClipboardFormats(
	UINT format   // specifies a known available clipboard format
	);
*/

}

void CSkeletonView::OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//tohle je struktura informaci o teto notification message
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	CPoint      ptAction;
	UINT        nFlags;

	GetCursorPos(&ptAction);
	ScreenToClient(&ptAction);
	ASSERT(!m_bDragging);
	m_bDragging = TRUE;
	m_hitemDrag = GetTreeCtrl().HitTest(ptAction, &nFlags);
	m_hitemDrop = NULL;

	ASSERT(m_pimagelist == NULL);
	m_pimagelist = GetTreeCtrl().CreateDragImage(m_hitemDrag);  // get the image list for dragging
	m_pimagelist->DragShowNolock(TRUE);
	m_pimagelist->SetDragCursorImage(0, CPoint(0, 0));
	m_pimagelist->BeginDrag(0, CPoint(0,0));
	m_pimagelist->DragMove(ptAction);
	m_pimagelist->DragEnter(this, ptAction);
	SetCapture();	
	*pResult = 0;

	return;
}

void CSkeletonView::OnMouseMove(UINT nFlags, CPoint point) 
{
	HTREEITEM           hitem;
	UINT                flags;

	if (m_bDragging)
	{
		ASSERT(m_pimagelist != NULL);
		m_pimagelist->DragMove(point);
		if ((hitem = GetTreeCtrl().HitTest(point, &flags)) != NULL)
		{
			m_pimagelist->DragLeave(this);
			GetTreeCtrl().SelectDropTarget(hitem);
			m_hitemDrop = hitem;
			m_pimagelist->DragEnter(this, point);
		}
	}
	
	CTreeView::OnMouseMove(nFlags, point);
}

void CSkeletonView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (m_bDragging)
	{
		ASSERT(m_pimagelist != NULL);
		m_pimagelist->DragLeave(this);
		m_pimagelist->EndDrag();
		delete m_pimagelist;
		m_pimagelist = NULL;

		CElementManager & OElementManager = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;
		IXMLDOMElementPtr pXMLElmDrag= (IXMLDOMElement*)GetTreeCtrl().GetItemData(m_hitemDrag);
		IXMLDOMElementPtr pXMLElmDrop= (IXMLDOMElement*)GetTreeCtrl().GetItemData(m_hitemDrop);
		IXMLDOMElementPtr pNewXMLElm=NULL;
		AfxMessageBox("Drag a taky drop:");
		AfxMessageBox(pXMLElmDrag->xml);
		AfxMessageBox(pXMLElmDrop->xml);

		if (m_hitemDrag != m_hitemDrop)
		{
		//zkopiruji XML Dragu do noveho uzlu XML stromu
			//vytvorim novy IXMLDOMDoc
				IXMLDOMDocumentPtr pNewXMLDoc;
				pNewXMLDoc.CreateInstance(_T("Msxml2.DOMDocument"));	
			//XML do nej natahnu
				HRESULT hRes = pNewXMLDoc->loadXML(pXMLElmDrag->xml);
				if (pNewXMLDoc->parseError->errorCode != S_OK)
				{
					AfxMessageBox(pNewXMLDoc->parseError->reason);
				}
			//zmenim id vsech prvku
				CElementManager & OElementManager = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;
				pNewXMLElm = pNewXMLDoc->GetdocumentElement();

				GetDocument()->ChangeIDsInTree(pNewXMLElm);

			//pripojim ho do existujiciho
				if (0== OElementManager.CanInsertChildHere(pNewXMLElm,pXMLElmDrop))
				{
					AfxMessageBox(IDS_INSERT_NEW_ELEMENT_WRONG_LOCATION,0,0);
					pNewXMLDoc.Release();
					MessageBeep(0);
					
				}
				else
				{

					AfxMessageBox("Novy:");
					AfxMessageBox(pNewXMLElm->xml);
				//novy XML uzel vlozim do XML stromu
					try
					{
						IXMLDOMElementPtr pResElm=pXMLElmDrop->appendChild(pNewXMLElm);
						if (0!=pResElm)
						{
							GetDocument()->SetModifiedFlag();		
							GetDocument()->UpdateAllViews(NULL, 0);
						}

					}
					catch (_com_error &e)
					{
						//AfxMessageBox(e.ErrorMessage());
						AfxMessageBox(e.Description());
					}
				}
		}
		else
			MessageBeep(0);

		ReleaseCapture();
		m_bDragging = FALSE;
		GetTreeCtrl().SelectDropTarget(NULL);
	}	
	CTreeView::OnLButtonUp(nFlags, point);
}
