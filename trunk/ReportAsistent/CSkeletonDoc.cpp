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

	m_XMLDOMDoc.Release();

	hr= m_XMLDOMDoc.CreateInstance(_T("Msxml2.DOMDocument"));
	if (FAILED(hr)) 
	{
		//mozna prepsat pomoci string table?
		AfxGetMainWnd()->MessageBox("Failed to instantiate an XML DOM.", "error", MB_ICONERROR);
		return FALSE;
	}

	m_XMLDOMDoc->async = VARIANT_FALSE; // default - true,


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

	hr= m_XMLDOMDoc.CreateInstance(_T("Msxml2.DOMDocument"));
	if (FAILED(hr)) 
	{
		//mozna prepsat pomoci string table?
		AfxGetMainWnd()->MessageBox("Failed to instantiate an XML DOM.", "error", MB_ICONERROR);
		return FALSE;
	}

	m_XMLDOMDoc->async = VARIANT_FALSE; // default - true,

	if(m_XMLDOMDoc->load((LPCTSTR) lpszPathName) != VARIANT_TRUE)
	{

		CString s;
		CString errstr( (BSTR) m_XMLDOMDoc->parseError->Getreason());

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
	tree_control.DeleteAllItems();

	InsetNodeToTreeCtrl(m_XMLDOMDoc, TVI_ROOT, tree_control);
}

void CSkeletonDoc::InsetNodeToTreeCtrl(MSXML2::IXMLDOMNodePtr iNode, 
									   HTREEITEM hParentItem, 
									   CTreeCtrl  & tree_control)
{
	MSXML2::IXMLDOMNodeListPtr iChildren = iNode->childNodes;


	MSXML2::IXMLDOMNodePtr iChild = NULL;
	
	MSXML2::IXMLDOMNodePtr Atrib = NULL;

	

	while ((iChild = iChildren->nextNode()) != NULL)
	{
		//Iva: Misto pouziti nodeName bych chtela pouzit attribute title/value, 
			//ale nedari se mi to z IXMLDOMNode vykuchat.
		CString s((BSTR) iChild->nodeName);
		//CString s((BSTR) iChild->nodeTypeString);
		

		HTREEITEM hTreeItem = tree_control.InsertItem(s, hParentItem);
		iChild.AddRef();
		tree_control.SetItemData(hTreeItem, (DWORD) (MSXML2::IXMLDOMNode *) iChild);
	

		//rekurze
		InsetNodeToTreeCtrl(iChild, hTreeItem, tree_control);
	}

}
