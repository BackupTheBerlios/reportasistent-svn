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
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_MMDELETE, OnMmdelete)
	ON_WM_CAPTURECHANGED()
	ON_WM_HELPINFO()
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
	lStyleOld |= TVS_HASBUTTONS |TVS_HASLINES|TVS_LINESATROOT|TVS_SHOWSELALWAYS;

	SetWindowLong(m_hWnd, GWL_STYLE, lStyleOld);
	UINT cis = GetTreeCtrl().GetIndent(); //default: 19
	GetTreeCtrl().SetIndent(25);
	cis = GetTreeCtrl().GetItemHeight(); //default: 16
	GetTreeCtrl().SetItemHeight(20 );



//Iva: Natahnu obrazky pro TreeCtrl
	CImageList          *pImageList;

	pImageList = new CImageList();
	pImageList->Create(16, 16,  //rozmery obrazku k nacteni do ImageListu
						ILC_MASK|ILC_COLOR8,  
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

	//Iva: zde bude naplneni TreeCtrl ( fce CSkeletonDocument->FillTreeCtrl(pTree) )
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

	//neni-li specifikovana akce nebo k ni chybi parametry, necham cely strom jenom premalovat
	if (lHint == 0) return;
	if (pHint == NULL) return;

	CTreeCtrl & pTreeCtrl = GetTreeCtrl();
		/*
		ASSERT(FALSE);
		//dedek: zuseno, nepouziva se
		
		MSXML2::IXMLDOMElement * new_element = (MSXML2::IXMLDOMElement *) lHint;


		GetDocument()->InsertNodeToTreeCtrl((MSXML2::IXMLDOMElementPtr) new_element, tree.GetSelectedItem(), tree);

	 
		//Deda: Naplneni TreeCtrl
			GetDocument()->FillTreeControl(GetTreeCtrl());
		*/
	

	//Iva: New version
	switch (lHint)
	{
	case UT_DEL:
		if (NULL != ((CUT_Hint*)pHint)->pTreeItem)
				pTreeCtrl.DeleteItem( ((CUT_Hint*)pHint)->pTreeItem);	
		break;
	case UT_INS:
			if ((NULL != ((CUT_Hint*)pHint)->pTreeItem) && (NULL != ((CUT_Hint*)pHint)->pElement))
			{	
				HTREEITEM inserted_item = GetDocument()->InsertNodeToTreeCtrl(((CUT_Hint*)pHint)->pElement,((CUT_Hint*)pHint)->pTreeItem,pTreeCtrl,((CUT_Hint*)pHint)->pInsertAfter);
			//Pridany prvek by mel byt zviditelnen = v rozbalenem seznamu, pokud neni videt
				if (0!= pTreeCtrl.EnsureVisible(inserted_item))
					pTreeCtrl.Expand(((CUT_Hint*)pHint)->pTreeItem,TVE_EXPAND);  
			}
		break;
	case UT_EDIT:	
			if (NULL != ((CUT_Hint*)pHint)->pTreeItem) 
			{
				CElementManager & OElementManager = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;
				MSXML2::IXMLDOMElementPtr edited_element = GetDocument()->ElementFromItemData(pTreeCtrl.GetItemData(((CUT_Hint*)pHint)->pTreeItem));
				
				pTreeCtrl.SetItemText(((CUT_Hint*)pHint)->pTreeItem, OElementManager.CreateElementCaption( edited_element));
			}	
				//Zde by mohlo byt InvalidateRect !!!
		break;
	default: //new creation of tree
		ASSERT(FALSE); //Invalid update command
		break;
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
		//(MSXML2::IXMLDOMElementPtr)(MSXML2::IXMLDOMElement *) rTreeCtrl.GetItemData( hTreeCtrlItem)
			(MSXML2::IXMLDOMElementPtr) GetDocument()->ElementFromItemData(rTreeCtrl.GetItemData(hTreeCtrlItem))
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
	
	//dedek: zakomentovano, kazi modalni dialogy
	//CTreeView::OnRButtonDown(nFlags, point);
}


// Iva: Puvodni zamer: podle vybraneho prvku TreeCtrl disablovat polozky v Menu->Edit->InsertNew
//Pozn:Pouziji!

// void CSkeletonView::OnCaptureChanged(CWnd *pWnd) 
// {
// 	CElementManager & OElementManager = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;
// 	CTreeCtrl& rTreeCtrl = GetTreeCtrl() ;
// 
// 	CMenu * hMainMenu = AfxGetApp()->GetMainWnd()->GetMenu();
// 	CMenu * hEditMenu = hMainMenu->GetSubMenu(1/*Edit*/)->GetSubMenu(7/*Insert New*/);
 	
// 	HTREEITEM hSelTreeCtrlItem = rTreeCtrl.GetSelectedItem();
 
// 	CElementManager::elId_t idTypeEl =
// 	 OElementManager.IdentifyElement 
// 		(
// 		 (MSXML2::IXMLDOMElementPtr)(MSXML2::IXMLDOMElement *) rTreeCtrl.GetItemData( hTreeCtrlItem)
// 		);
 	
// 	switch (idTypeEl)
// 	{
 //		case ELID_UNKNOWN: break;
 
 //		case ELID_REPORT: 
 //		{
//			//disable:
//			hEditMenu->EnableMenuItem(+ID_MMNEWSTATICFIRST/*ID*/,MF_GRAYED|MF_BYPOSITION)
 	
 //	CTreeView::OnCaptureChanged(pWnd);
 //}
 
void CSkeletonView::OnEditCopy() 
{
	//AfxMessageBox("Bude se kopirovat.",0,0);


	CTreeCtrl & rTreeCtrl = GetTreeCtrl();
	MSXML2::IXMLDOMElementPtr SelXMLDomElement = GetDocument()->ElementFromItemData(rTreeCtrl.GetItemData(rTreeCtrl.GetSelectedItem()));
	
//ziskam XML vybraneho prvku TreeCtrl
	_bstr_t bstrSelElmXML= SelXMLDomElement->xml; 
	//AfxMessageBox((LPTSTR)bstrSelElmXML,0,0);

//Alokuji globalni pamet a XML do ni zkopiruji
	HGLOBAL hgMemForXML = GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE ,    // allocation attributes
						(DWORD) (bstrSelElmXML.length() + 1)   // number of bytes to allocate
						);
	if (0==hgMemForXML) 
	{
		AfxMessageBox("Nepodarilo se alokovat dostatek pameti pro XML podstrom.",0,0);
		return;
	}

	LPTSTR pMemForXML = (LPTSTR) GlobalLock(hgMemForXML);
	strcpy(pMemForXML,(LPTSTR) bstrSelElmXML);
	//AfxMessageBox(pMemForXML,0,0);
	

	GlobalUnlock(hgMemForXML);
	

//Otevru clipboard a soupnu do nej XML
	if (0==OpenClipboard()) 
	{
		AfxMessageBox("Clipboard pouziva nekdo jiny",0,0);
		return;
	}
	
	CWnd * hOwner = GetClipboardOwner();
	EmptyClipboard();
	hOwner = GetClipboardOwner();

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

	//ASSERT(NULL==GlobalFree(hgMemForXML));   globalni pamet nesmim uvolnovat!! - ta uz nyni patri clipboardu
	DWORD dErr = GetLastError();

	return;
	
}

void CSkeletonView::OnEditPaste() 
{
	//AfxMessageBox("Bude se paste-ovat.",0,0);	

	CTreeCtrl & rTreeCtrl = GetTreeCtrl();
	MSXML2::IXMLDOMElementPtr SelXMLDomElement = GetDocument()->ElementFromItemData(rTreeCtrl.GetItemData(rTreeCtrl.GetSelectedItem()));

//Otevru clipboard a prectu z nej XML
	if (0==OpenClipboard()) 
	{
		AfxMessageBox("Clipboard pouziva nekdo jiny",0,0);
		return;
	}
	LPCTSTR pMemForXML; //= (LPCTSTR)GetClipboardData(CF_TEXT);
	HANDLE hMem=GetClipboardData(CF_TEXT);
	pMemForXML = (LPCTSTR) GlobalLock(hMem);

	if (NULL==pMemForXML) 
	{
		AfxMessageBox("Precist text z clipboardu se nepodarilo",0,0);
		ASSERT(0!=CloseClipboard());
		return;
	}

	//AfxMessageBox(pMemForXML,0,0);

//vytvorim novy MSXML2::IXMLDOMDoc
	MSXML2::IXMLDOMDocumentPtr pNewXMLDoc;
	pNewXMLDoc.CreateInstance(_T("Msxml2.DOMDocument"));	
//XML do nej natahnu

	HRESULT hRes = pNewXMLDoc->loadXML(pMemForXML);
	if (pNewXMLDoc->parseError->errorCode != S_OK)
	{
		AfxMessageBox(pNewXMLDoc->parseError->reason);
	}

//zavru clipboard
	GlobalUnlock(hMem);
	ASSERT(0!=CloseClipboard());

//zmenim id vsech prvku
	CElementManager & OElementManager = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;
	MSXML2::IXMLDOMElementPtr pNewXMLElm = pNewXMLDoc->GetdocumentElement();

	GetDocument()->ChangeIDsInTree(pNewXMLElm);
	//AfxMessageBox(pNewXMLDoc->xml,0,0);

//zkusim vlozit DOVNITR do existujiciho
	if (0!= OElementManager.CanInsertChildHere(pNewXMLElm,SelXMLDomElement))
	{
		try
		{
			MSXML2::IXMLDOMElementPtr pResElm=SelXMLDomElement->appendChild(pNewXMLElm);
			if (0!=pResElm)
			{
				CUT_Hint oHint(rTreeCtrl.GetSelectedItem(),pNewXMLElm,TVI_LAST);
				GetDocument()->SetModifiedFlag();
				GetDocument()->UpdateAllViews(NULL,UT_INS, &oHint);
				GetDocument()->SetModifiedFlag();		
				GetDocument()->UpdateAllViews(NULL, 0);

			}
			pNewXMLDoc.Release();
			return; //povedlo se prvek vlozit DOVNITR

		}
		catch (_com_error &e)
		{
			AfxMessageBox(e.Description());
			//AfxMessageBox(IDS_INSERT_NEW_ELEMENT_WRONG_LOCATION);	
		}
	}
//zkusim vlozit PRED existujici
	if (0!= OElementManager.CanInsertBefore(pNewXMLElm,SelXMLDomElement))
	{
		try
		{
			MSXML2::IXMLDOMNodePtr pParent=SelXMLDomElement->GetparentNode();
			MSXML2::IXMLDOMElementPtr pResElm=pParent->insertBefore(pNewXMLElm,(MSXML2::IXMLDOMElement*)SelXMLDomElement);
			if (0!=pResElm)
			{
				CUT_Hint oHint(rTreeCtrl.GetParentItem(rTreeCtrl.GetSelectedItem()),pNewXMLElm,rTreeCtrl.GetPrevSiblingItem(rTreeCtrl.GetSelectedItem()));
				GetDocument()->SetModifiedFlag();
				GetDocument()->UpdateAllViews(NULL,UT_INS, &oHint);

				GetDocument()->SetModifiedFlag();		
				GetDocument()->UpdateAllViews(NULL, 0);
			}
			pNewXMLDoc.Release();
			return; //povedlo se prvek vlozit PRED

		}
		catch (_com_error &e)
		{
			AfxMessageBox(e.Description());
		}
	}

	//AfxMessageBox(IDS_INSERT_NEW_ELEMENT_WRONG_LOCATION,0,0); prepsano by dedek
	CReportAsistentApp::ReportError(IDS_INSERT_NEW_ELEMENT_WRONG_LOCATION);

	pNewXMLDoc.Release();	
	return;
}


void CSkeletonView::OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//tohle je struktura informaci o teto notification message
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	CElementManager & OElementManager = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;
	CPoint      ptAction;
	UINT        nFlags;
	CTreeCtrl&  rTreeCtrl=GetTreeCtrl(); 

	GetCursorPos(&ptAction);
	ScreenToClient(&ptAction);
	ASSERT(!m_bDragging);
	m_hitemDrag = rTreeCtrl.HitTest(ptAction, &nFlags);

	MSXML2::IXMLDOMElementPtr pDragXMLDomElement = GetDocument()->ElementFromItemData(rTreeCtrl.GetItemData(m_hitemDrag));
	//prvky ktere nelze presouvat:	jen report
	if (ELID_REPORT==OElementManager.IdentifyElement(pDragXMLDomElement))
		return;

	m_hitemDrop = NULL;
	m_bDragging = TRUE;

	ASSERT(m_pimagelist == NULL);
	m_pimagelist = rTreeCtrl.CreateDragImage(m_hitemDrag);  // get the image list for dragging
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
		BOOL bDropped = FALSE;


		CElementManager & OElementManager = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;
		MSXML2::IXMLDOMElementPtr pXMLElmDrag= (MSXML2::IXMLDOMElement*)GetTreeCtrl().GetItemData(m_hitemDrag);
		MSXML2::IXMLDOMElementPtr pXMLElmDrop= (MSXML2::IXMLDOMElement*)GetTreeCtrl().GetItemData(m_hitemDrop);
		MSXML2::IXMLDOMElementPtr pNewXMLElm=NULL;
		MSXML2::IXMLDOMElementPtr pResElm=NULL;
		MSXML2::IXMLDOMElementPtr pParentDrag=NULL;
		MSXML2::IXMLDOMElementPtr pParentDrop=NULL;
		MSXML2::IXMLDOMElementPtr pRSiblingDrag=NULL;

		//AfxMessageBox(pXMLElmDrag->xml);
		//AfxMessageBox(pXMLElmDrop->xml);

		if (m_hitemDrag != m_hitemDrop)
		{
			//zkontroluji, neni-li Drop potomkem Dragu
				if (GetDocument()->IsDescendantOfElement(pXMLElmDrop,pXMLElmDrag))
				{
					AfxMessageBox("Nelze presunout prvek do jeho podstromu");
					goto end_place;
				}
	
			//Odstranim Drag ze stromu do NewElm
				pParentDrag=pXMLElmDrag->GetparentNode();
				pRSiblingDrag=pXMLElmDrag->GetnextSibling();
				try
				{
					pNewXMLElm =pParentDrag->removeChild((MSXML2::IXMLDOMElement*)pXMLElmDrag);
				}						
				catch (_com_error &e)
				{
					AfxMessageBox(e.Description());
				}

				//AfxMessageBox("Odebran drag do:");

				//AfxMessageBox(pNewXMLElm->xml);
			
			//otestuji, lze-li dat NewElm PRED Drop
				if (0!= OElementManager.CanInsertBefore(pNewXMLElm,pXMLElmDrop))
				{
					try
					{
						pParentDrop=pXMLElmDrop->GetparentNode();
						pResElm=pParentDrop->insertBefore(pNewXMLElm,(MSXML2::IXMLDOMElement*)pXMLElmDrop);
						if (0!=pResElm)
						{
							CUT_Hint oHint(GetTreeCtrl().GetParentItem(m_hitemDrop),pNewXMLElm,GetTreeCtrl().GetPrevSiblingItem(m_hitemDrop));
							GetDocument()->SetModifiedFlag();
							GetDocument()->UpdateAllViews(NULL,UT_INS, &oHint);
							/*
							GetDocument()->SetModifiedFlag();		
							GetDocument()->UpdateAllViews(NULL, 0);*/
							bDropped = TRUE;
							goto end_place;	 //povedlo se prvek vlozit PRED
						}

					}
					catch (_com_error &e)
					{
						AfxMessageBox(e.Description());
					}
				}


			//otestuji, lze-li dat NewElm DOVNITR do Dropu
				if (0!= OElementManager.CanInsertChildHere(pNewXMLElm,pXMLElmDrop))
				{				
					try
					{
						pResElm=pXMLElmDrop->appendChild(pNewXMLElm);
						if (0!=pResElm)
						{
							CUT_Hint oHint(m_hitemDrop,pNewXMLElm,TVI_LAST);
							GetDocument()->SetModifiedFlag();
							GetDocument()->UpdateAllViews(NULL,UT_INS, &oHint);
/*
							GetDocument()->SetModifiedFlag();		
							GetDocument()->UpdateAllViews(NULL, 0);
*/							bDropped = TRUE;
							goto end_place; //povedlo se dat prvek DOVNITR 
						}
					}
					catch (_com_error &e)
					{
						AfxMessageBox(e.Description());
					}
				}

			//vratim Drag do stromu
				try
				{
					if (NULL==pRSiblingDrag) pParentDrag->appendChild(pNewXMLElm);
					else
						pParentDrag->insertBefore(pNewXMLElm,(MSXML2::IXMLDOMElement*) pRSiblingDrag);
						
				}
				catch (_com_error &e)
				{
					AfxMessageBox(e.Description());
				}
				//AfxMessageBox(IDS_INSERT_NEW_ELEMENT_WRONG_LOCATION,0,0);
				CReportAsistentApp::ReportError(IDS_INSERT_NEW_ELEMENT_WRONG_LOCATION);

				
											
		}
		//sem se dostanu jen pri neuspechu:
		MessageBeep(0);
		
		end_place:
		if (bDropped==TRUE)
		{
             //Iva:Update of TreeCtrl
             CUT_Hint oHint(m_hitemDrag,0,0);
             GetDocument()->SetModifiedFlag();
             GetDocument()->UpdateAllViews(NULL,UT_DEL, &oHint);
		}

		ReleaseCapture();
		m_bDragging = FALSE;
		GetTreeCtrl().SelectDropTarget(NULL);
	}	
	CTreeView::OnLButtonUp(nFlags, point);
}

void CSkeletonView::OnEditCut() 
{
	OnEditCopy();
	OnMmdelete();
}

void CSkeletonView::OnMmdelete() 
{

	
	HTREEITEM hSelTreeItem = GetTreeCtrl().GetSelectedItem();

	//dedek:
	if (hSelTreeItem == NULL) return;

	MSXML2::IXMLDOMElementPtr selected_element = GetDocument()->ElementFromItemData(GetTreeCtrl().GetItemData( hSelTreeItem ));
	
	MSXML2::IXMLDOMElementPtr parent_element= selected_element->parentNode;
	
	CElementManager & OElementManager = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;
	//prvky ktere nelze mazat:	jen report
	if (ELID_REPORT==OElementManager.IdentifyElement(selected_element))
		return;


	parent_element->removeChild((MSXML2::IXMLDOMElement*)selected_element);

	//Iva: update of the TreeCtrl
	CUT_Hint oHint(hSelTreeItem,0,0);
	GetDocument()->SetModifiedFlag();
	GetDocument()->UpdateAllViews(NULL,UT_DEL, &oHint);
	
}

void CSkeletonView::OnCaptureChanged(CWnd *pWnd) 
{
	// TODO: Add your message handler code here
	
	CTreeView::OnCaptureChanged(pWnd);
}

BOOL CSkeletonView::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	AfxMessageBox("Nazdar");
	return CTreeView::OnHelpInfo(pHelpInfo);
}
