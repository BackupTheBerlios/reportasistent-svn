// CSkeletonDoc.cpp : implementation of the CSkeletonDoc class
//

#include "stdafx.h"
#include "ReportAsistent.h"

#include "CSkeletonDoc.h"

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
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkeletonDoc construction/destruction

CSkeletonDoc::CSkeletonDoc()
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

	pXMLDom.Release();

	hr= pXMLDom.CreateInstance(_T("Msxml2.DOMDocument"));
	if (FAILED(hr)) 
	{
		//mozna prepsat pomoci string table?
		AfxGetMainWnd()->MessageBox("Failed to instantiate an XML DOM.", "error", MB_ICONERROR);
		return FALSE;
	}

	pXMLDom->async = VARIANT_FALSE; // default - true,


	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSkeletonDoc serialization

void CSkeletonDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
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
		tree_control.SetItemData(hTreeItem, (DWORD) (MSXML2::IXMLDOMNode *) pChild);



	while ((pChild = pChildren->nextNode()) != NULL)
	{

		//rekurze
		InsetNodeToTreeCtrl(pChild, hTreeItem, tree_control);
	}

}
