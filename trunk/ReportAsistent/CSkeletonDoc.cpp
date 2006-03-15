// CSkeletonDoc.cpp : implementation of the CSkeletonDoc class
//

#include "stdafx.h"
#include "ReportAsistent.h"

#include "CSkeletonDoc.h"
//#include "SkeletonManager.h" - uz je v headeru
#include "SkeletonView.h"
#include "GenerateDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CSkeletonDoc

IMPLEMENT_DYNCREATE(CSkeletonDoc, CDocument)

BEGIN_MESSAGE_MAP(CSkeletonDoc, CDocument)
	//{{AFX_MSG_MAP(CSkeletonDoc)
	ON_COMMAND(ID_MMNEW4FTHYP, OnMmnew4fthyp)
	ON_COMMAND(ID_ELEMENT_EDIT, OnElementEdit)
	ON_COMMAND(ID_MMGENREP, OnMmgenrep)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkeletonDoc construction/destruction

CSkeletonDoc::CSkeletonDoc() : m_SkeletonManager(pXMLDom)
{
	// TODO: add one-time construction code here

}

CSkeletonDoc::~CSkeletonDoc()
{
} 

BOOL CSkeletonDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	HRESULT hr;

	if (pXMLDom != NULL) pXMLDom.Release();

	hr= pXMLDom.CreateInstance(_T("Msxml2.DOMDocument"));
	if (FAILED(hr)) 
	{
		//mozna prepsat pomoci string table?
		AfxGetMainWnd()->MessageBox("Failed to instantiate an XML DOM.", "error", MB_ICONERROR);
		return FALSE;
	}

	pXMLDom->async = VARIANT_FALSE; // default - true,

	
	
	//vytvor prazny report
	CGeneralManager * m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager;

	//by bylo fajn, ale pak tam neni DTD
	//pXMLDom->appendChild(m->ElementManager.CreateEmptyExampleElement(ELID_REPORT));

	//docasne reseni:
	pXMLDom->load("../XML/prazdny.xml");


	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSkeletonDoc serialization

void CSkeletonDoc::Serialize(CArchive& ar)
{
	
	
	if (ar.IsStoring())
	{
		//honza: sem by se program nemel dostat - jinak prepisuje soubor po ulozeni
		ASSERT(FALSE);
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSkeletonDoc diagnostics

#ifdef _DEBUG
void CSkeletonDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSkeletonDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSkeletonDoc commands

BOOL CSkeletonDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	HRESULT hr;

	hr= pXMLDom.CreateInstance(_T("Msxml2.DOMDocument"));
	if (FAILED(hr)) 
	{
		//mozna prepsat pomoci string table?
		AfxGetMainWnd()->MessageBox("Failed to instantiate an XML DOM.", "error", MB_ICONERROR);
		return FALSE;
	}

	pXMLDom->async = VARIANT_FALSE; // default - true,

	if(pXMLDom->load((LPCTSTR) lpszPathName) != VARIANT_TRUE)
	{

		CString s;
		CString errstr( (BSTR) pXMLDom->parseError->Getreason());

		//mozna prepsat pomoci string table?
		s.Format("\nError in XML file reading.\n%s", lpszPathName);

		errstr += s;

		AfxGetMainWnd()->MessageBox(errstr, "error", MB_ICONERROR);

		return FALSE;
	}


	return TRUE;
}

void CSkeletonDoc::FillTreeControl(CTreeCtrl  & tree_control)
{
	MSXML2::IXMLDOMElementPtr pTopElement;

	tree_control.DeleteAllItems();

	// ukazu pTopElement na koren XMLDOM stromu  
	pTopElement = pXMLDom->GetdocumentElement();
	if (pTopElement == NULL)
	{
      AfxGetMainWnd()->MessageBox("Invalid top document node.","Invalid top document node.", MB_ICONERROR);
	  //(LPCSTR)pXMLDom->parseError->Getreason()); - popis chyby, TODO: nejlepe do logu chyb
	}
	//a naplnim TreeCtrl
	else
	{
		InsetNodeToTreeCtrl(pTopElement, TVI_ROOT, tree_control);
	}

	
}

void CSkeletonDoc::InsetNodeToTreeCtrl(MSXML2::IXMLDOMElementPtr pElement, 
									   HTREEITEM hParentItem, 
									   CTreeCtrl  & tree_control)
{
	//pridal honza
	if (pElement == NULL) return;
	
	
	
	MSXML2::IXMLDOMNodeListPtr pChildren = pElement->childNodes;//ukazatel na potomky pElementu
	MSXML2::IXMLDOMNodePtr pChild = NULL;
	CString csElementType; //typ prvku XMLstromu: text/chapter/report/...
	char sTextValue [256]; //text ktery se stane jmenem polozky v CtrlTree
	HTREEITEM hTreeItem=NULL;

	
		
		csElementType=(LPCTSTR)(pElement->baseName);

		//pridam prvek do TreeCtrl..pro typ prvku REPORT
		if (0==strcmp("report",csElementType))
		{
			hTreeItem = tree_control.InsertItem((LPCTSTR) (_bstr_t) csElementType,//text prvku TreeCtrl
													IDB_REPORTICO-IDB_BMTREEFIRST-1,//nImage
													IDB_REPORTICO-IDB_BMTREEFIRST-1,//nSelectedImage
													hParentItem);
		}
		else
			//pridam prvek do TreeCtrl..pro typ prvku TEXT:
					//<text value="Vysledky."/> 
			if (0==strcmp("text",csElementType))
			{

/*		prepsal honza
				_variant_t & Value = pElement->getAttribute("value");

				if (Value.vt == VT_NULL) 
*/

				_bstr_t & Value = pElement->text;
				if ((BSTR) Value == NULL) 					
					sprintf(sTextValue,"Text - empty");
				else
				{
					sprintf(sTextValue,"%.*s...",LENGTH_TREE_ITEM_NAME-3,(LPCTSTR) (_bstr_t) Value);
				}

				hTreeItem = tree_control.InsertItem(sTextValue,//text prvku TreeCtrl
													IDB_TEXTICO-IDB_BMTREEFIRST-1,//nImage
													IDB_TEXTICO-IDB_BMTREEFIRST-1,//nSelectedImage
													hParentItem);
			}
			else 
				//pridam prvek do TreeCtrl ..pro typ prvku CHAPTER:
					//<chapter title = "Muzi">
				if (0==strcmp("chapter",csElementType))
				{
					_variant_t & Value = pElement->getAttribute("title");

					if (Value.vt == VT_NULL) 
						sprintf(sTextValue,"Title - missing");
					else
					{
						sprintf(sTextValue,"%.*s...",LENGTH_TREE_ITEM_NAME-3,(LPCTSTR) (_bstr_t) Value);
					}

					hTreeItem = tree_control.InsertItem(sTextValue,//text prvku TreeCtrl
														IDB_CHAPTERICO-IDB_BMTREEFIRST-1,//nImage
														IDB_CHAPTERICO-IDB_BMTREEFIRST-1,//nSelectedImage
														hParentItem);
				}
				//pridam prvek do TreeCtrl ..pro typ prvku PARAGRAPH
				else
					if (0==strcmp("paragraph",csElementType))
					{
						hTreeItem = tree_control.InsertItem((LPCTSTR) (_bstr_t) csElementType,//text prvku TreeCtrl
														IDB_PARAGRAPHICO-IDB_BMTREEFIRST-1,//nImage
														IDB_PARAGRAPHICO-IDB_BMTREEFIRST-1,//nSelectedImage
														hParentItem);
					}
					//pridam prvek do TreeCtrl..pro jiny typ prvku nez vyse uvedeny
					else
						hTreeItem = tree_control.InsertItem((LPCTSTR) (_bstr_t) csElementType,//text prvku TreeCtrl
														IDB_UNKNOWNICO-IDB_BMTREEFIRST-1,//nImage
														IDB_UNKNOWNICO-IDB_BMTREEFIRST-1,//nSelectedImage
													hParentItem);


		pElement.AddRef();

		//ukazu TV_ITEM.lParam na odpovidajici uzel XML stromu

		
		tree_control.SetItemData(hTreeItem, CSkeletonManager::CreateItemData(pElement));



	while ((pChild = pChildren->nextNode()) != NULL)
	{

		//rekurze
		InsetNodeToTreeCtrl(pChild, hTreeItem, tree_control);
	}

}

//pridal honza
BOOL CSkeletonDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	pXMLDom->save(lpszPathName);

	SetModifiedFlag(FALSE);
	
	return TRUE;	//CDocument::OnSaveDocument(lpszPathName); - nepouzivat prepise nam soubor vyse
}

//pridal honza - reakce na insert 4ft command
void CSkeletonDoc::OnMmnew4fthyp() 
{
	CTreeCtrl & tree = GetFirstView()->GetTreeCtrl();		
	HTREEITEM item = tree.GetSelectedItem();
	IXMLDOMElementPtr selected_element = m_SkeletonManager.ElementFromItemData(tree.GetItemData( item ));			
	
	//zobrazi zpravu s typem vybraneho elementu
	//honza: ladici klidne zakomentujte
	/****/
	CGeneralManager * m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager;
	CElementManager::elId id = m->ElementManager.IdentifyElement(selected_element);
	AfxMessageBox(m->ElementManager.ElementName(id));
	/***/


	
	
	IXMLDOMElementPtr new_element = 
		m_SkeletonManager.InsertNewElement("hyp_4ft", selected_element);

	//pridani se zdarilo
	if (new_element != NULL)
	{
		m_SkeletonManager.EditActiveElement(new_element); 

		SetModifiedFlag();		
		UpdateAllViews(NULL, (LPARAM) (IXMLDOMElement *) new_element);
	}	

}



//pridal honza - vrati prvni view ve kterem je zobrazovan tento dokument
CSkeletonView * CSkeletonDoc::GetFirstView()
{
	POSITION pos = GetFirstViewPosition();
	return (CSkeletonView *) GetNextView( pos );
}

void CSkeletonDoc::OnElementEdit() 
{
	CTreeCtrl & tree = GetFirstView()->GetTreeCtrl();
	
	m_SkeletonManager.EditElenemt(tree.GetItemData(tree.GetSelectedItem()));

}

void CSkeletonDoc::OnMmgenrep() 
{
	CGenerateDialog dlg(m_SkeletonManager, AfxGetMainWnd());
	
	//pozor vlastni kod generovani je ve CSkeletonManager::Generate()
	dlg.DoModal();


//zobrazi vysledek transformaci v kostre
#ifdef DONT_CLONE_REPORT_BEFORE_GENERATE
	UpdateAllViews(NULL);
#endif
}
