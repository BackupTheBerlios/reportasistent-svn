// XMLTree.cpp : implementation file
//

#include "stdafx.h"
#include "metabase_load_pok1.h"
#include "XMLTree.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXMLTree

CXMLTree::CXMLTree()
{
}

CXMLTree::~CXMLTree()
{
}


BEGIN_MESSAGE_MAP(CXMLTree, CTreeCtrl)
	//{{AFX_MSG_MAP(CXMLTree)
	ON_NOTIFY_REFLECT(TVN_DELETEITEM, OnDeleteitem)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXMLTree message handlers

using namespace LMRA_WordLoader;
using namespace MSXML2;

BOOL CXMLTree::LoadFromFile(CString FileName)
{
	DeleteAllItems();
	HRESULT hr;

	hr= m_XMLDOMDoc.CreateInstance(_T("Msxml2.DOMDocument"));
	if (FAILED(hr)) 
	{
		MessageBox("Failed to instantiate an XML DOM.", "error", MB_ICONERROR);
		return FALSE;
	}

	m_XMLDOMDoc->async = VARIANT_FALSE; // default - true,

	if(m_XMLDOMDoc->load((LPCTSTR) FileName) != VARIANT_TRUE)
	{

		CString s;
		CString errstr( (BSTR) m_XMLDOMDoc->parseError->Getreason());

		s.Format("\nError in XML file reading.\n%s", FileName);

		errstr += s;

		MessageBox(errstr, "error", MB_ICONERROR);

		return FALSE;
	}

	InsetXMLNode(m_XMLDOMDoc, TVI_ROOT);

	return TRUE;
}

void CXMLTree::InsetXMLNode(MSXML2::IXMLDOMNodePtr iNode, HTREEITEM hParentItem)
{
	IXMLDOMNodeListPtr iChildren = iNode->childNodes;


	IXMLDOMNodePtr iChild = NULL;

	while ((iChild = iChildren->nextNode()) != NULL)
	{
		CString s((BSTR) iChild->nodeName);

		HTREEITEM i = InsertItem(s, hParentItem);
		iChild.AddRef();
		SetItemData(i, (DWORD) (IXMLDOMNode *) iChild);
	

		//rekurze
		InsetXMLNode(iChild, i);
	}

}



void LoadXLMFromString(_bstr_t strXMLSource, LPOLEOBJECT doc);



BOOL CXMLTree::GenerSelectedSubtree(LPOLEOBJECT doc)
{
	HTREEITEM i = GetSelectedItem();

	if (i == NULL)
	{
		MessageBox("No item selected!");
		return FALSE;
	}

	IXMLDOMNodePtr np((IXMLDOMNode *) GetItemData(i));

	MessageBox(np->xml);

//	BSTR bs = np->xml;
	
	LoadXLMFromString(np->xml, doc);

	


	return TRUE;
}


//uvolni referenci alokovanou pro ItemData
void CXMLTree::OnDeleteitem(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	IXMLDOMNode * np = (IXMLDOMNode *) pNMTreeView->itemOld.lParam;

	if (np != NULL) np->Release();

	
	*pResult = 0;
}
