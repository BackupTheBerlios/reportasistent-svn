#include "stdafx.h"

using namespace LMRA_WordLoader;

using namespace MSXML2;



//rekurzivni procedura - presunuto do CXMLTree
void InsetXMLNodeToTree(IXMLDOMNodePtr iNode, CTreeCtrl * treeCtrl, HTREEITEM hParentItem)
{
	IXMLDOMNodeListPtr iChildren = iNode->childNodes;


	IXMLDOMNodePtr iChild = NULL;

	while ((iChild = iChildren->nextNode()) != NULL)
	{
		CString s((BSTR) iChild->nodeName);

		HTREEITEM i = treeCtrl->InsertItem(s, hParentItem);
	

		//rekurze
		InsetXMLNodeToTree(iChild, treeCtrl, i);
	}

}

//presunuto do CXMLTree
BOOL LoadXMLDOM(LPCTSTR FilePath, CTreeCtrl * treeCtrl)
{
	IXMLDOMDocumentPtr pXMLDom;
	HRESULT hr;

	
//stacizavolat jednou pro cely program - presunuto do startu aplikace
//	CoInitialize(NULL);

	hr= pXMLDom.CreateInstance(_T("Msxml2.DOMDocument"));
	if (FAILED(hr)) 
	{
		MessageBox(NULL, "Failed to instantiate an XML DOM.", "error", MB_ICONERROR);
		return FALSE;
	}


	pXMLDom->async = VARIANT_FALSE; // default - true,



	if(pXMLDom->load(FilePath) != VARIANT_TRUE)
	{

		CString s;

		s.Format("Error in XML file reading.\n%s", FilePath);

		MessageBox(NULL, s, (LPCSTR) pXMLDom->parseError->Getreason(), MB_ICONERROR);

		return FALSE;
	}

	InsetXMLNodeToTree(pXMLDom, treeCtrl, TVI_ROOT);
	
	pXMLDom.Release();
   
	return TRUE;
}


//nacte Word z XML-soubru
void LoadXLMFileToWord(LPCTSTR FilePath)
{
	_LMRA_XML_WordLoader * pWL = NULL;

	IUnknown * pU = NULL;
	
//	CoInitialize(NULL);
	
	
	HRESULT hr = REGDB_E_CLASSNOTREG;
	hr = CoCreateInstance(CLSID_LMRA_XML_WordLoader, NULL, CLSCTX_LOCAL_SERVER, IID_IUnknown, (void **) & pU);
	if (hr == REGDB_E_CLASSNOTREG)
		MessageBox(NULL, "LMRA_WordLoader.exe neni registorvany - spustte LMRA_WordLoader.exe", "chyba", MB_ICONERROR);
	
	if (pU != NULL)
	{
		pU->QueryInterface(IID__LMRA_XML_WordLoader, (void **) & pWL);

		pU->Release();

		
		if (pWL != NULL) 
		{
//			BSTR bs;
			TCHAR full_path[500];
			
			GetFullPathName(FilePath, 500, full_path, NULL);			

//			CString s(cd);
			
			
			//docasne!!!!!!!!!!!!! - opravit
			try 
			{
			/*s = (LPCTSTR) */pWL->LoadFromFile(full_path);
			}
			catch (...)
			{
				MessageBox(NULL, "XML soubor se nepodarilo precist.", "chyba", MB_ICONERROR);
			}
			
			pWL->Release();
		}
	}


}

//nacte Word z XML-soubru
void LoadXLMFromString(BSTR * strXMLSource)
{
	_LMRA_XML_WordLoader * pWL = NULL;

	IUnknown * pU = NULL;
	
	
	HRESULT hr = REGDB_E_CLASSNOTREG;
	hr = CoCreateInstance(CLSID_LMRA_XML_WordLoader, NULL, CLSCTX_LOCAL_SERVER, IID_IUnknown, (void **) & pU);
	if (hr == REGDB_E_CLASSNOTREG)
		MessageBox(NULL, "LMRA_WordLoader.exe neni registorvany - spustte LMRA_WordLoader.exe", "chyba", MB_ICONERROR);
	
	if (pU != NULL)
	{
		pU->QueryInterface(IID__LMRA_XML_WordLoader, (void **) & pWL);

		pU->Release();

		
		if (pWL != NULL) 
		{
//			BSTR bs;
//			TCHAR full_path[500];
			
//			GetFullPathName(FilePath, 500, full_path, NULL);			

//			CString s(cd);
			
			
			//docasne!!!!!!!!!!!!! - opravit
			try 
			{
//				pWL->LoadFromFile(full_path);
				pWL->LoadFromString(strXMLSource);
			}
			catch (...)
			{
				MessageBox(NULL, "XML string nejde prevest.", "chyba", MB_ICONERROR);
			}
			
			pWL->Release();
		}
	}


}