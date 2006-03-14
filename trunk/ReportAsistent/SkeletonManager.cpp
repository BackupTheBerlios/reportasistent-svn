// SkeletonManager.cpp: implementation of the CSkeletonManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "filter_dlg.h"
#include "simplefilterdialog.h"
#include "SkeletonManager.h"
#include "APTransform.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSkeletonManager::CSkeletonManager(IXMLDOMDocumentPtr & skeleton) :	m_skeleton(skeleton)
{
/*
	m_skeleton.CreateInstance(_T("Msxml2.DOMDocument"));
	m_skeleton->async = VARIANT_FALSE; // default - true,

	m_skeleton->load((LPCTSTR) _T("..\\skeleton.xml"));
//	m_skeleton->load((LPCTSTR) _T("../euroregion_dedek3.xml"));
//	m_skeleton->load((LPCTSTR) _T("../out.xml"));
*/	

}

CSkeletonManager::~CSkeletonManager()
{
	//m_skeleton.Release();
}

void CSkeletonManager::FillTreeCtrl(CTreeCtrl &tree_ctrl)
{
	tree_ctrl.DeleteAllItems();

	RecurentTreeFill(tree_ctrl, (IXMLDOMNodePtr) m_skeleton, TVI_ROOT);	
}

void CSkeletonManager::RecurentTreeFill(CTreeCtrl &tree_ctrl, MSXML2::IXMLDOMNodePtr & iNode, HTREEITEM hParentItem)
{
	IXMLDOMNodeListPtr iChildren = iNode->childNodes;

	IXMLDOMNodePtr iChild = NULL;

	while ((iChild = iChildren->nextNode()) != NULL)
	{
		


		HTREEITEM i = tree_ctrl.InsertItem(iChild->nodeName, hParentItem);

		tree_ctrl.Expand(hParentItem, TVE_EXPAND);
		
		
		iChild.AddRef();
		tree_ctrl.SetItemData(i, (DWORD) (IXMLDOMNode *) iChild);

		//rekurze
		RecurentTreeFill(tree_ctrl, iChild, i);
	}
}

void CSkeletonManager::DeleteItemData(LPARAM data)
{
	IXMLDOMNode * np = (IXMLDOMNode *) data;

	if (np != NULL) np->Release();
}

void CSkeletonManager::AddElement()
{
	IXMLDOMDocumentPtr element_example;
	element_example.CreateInstance(_T("Msxml2.DOMDocument"));	
	element_example->async = VARIANT_FALSE; // default - true,

	element_example->load((LPCTSTR) _T("..\\skeleton.xml"));

	
	m_skeleton->documentElement->appendChild(element_example->selectSingleNode("//active_element[@type = 'hyp_4ft']"));

	element_example.Release();

}

void CSkeletonManager::EditElenemt(LPARAM item_data)
{
	if (item_data == NULL) return;

	IXMLDOMNode * np = (IXMLDOMNode *) item_data;

	
	CString s = (BSTR) np->baseName;
	if (s == "active_element")
	{
		ConfigureFilter((IXMLDOMElementPtr) np);
	}
	else if (s == "text")
	{
		AfxMessageBox(np->text, 0, 0);

		np->text = "novy text sdjk asjdh </br>ui efkj  ksdfjsk fjjf konec";
	}
	else
	{
		AfxMessageBox(np->xml, 0, 0);
	}


}



void CSkeletonManager::ConfigureFilter(IXMLDOMElementPtr & active_element)
{
	CSimpleFilterDialog dlg(active_element, 
		GetPluginOutput((_bstr_t) active_element->getAttribute("source"),
						(_bstr_t) active_element->getAttribute("type")),
		AfxGetMainWnd());

	int nResponse = dlg.DoModal();
	
	if (nResponse == IDOK)
	{
//		MessageBox(NULL, dlg.m_result_id, "ggg", MB_OK);
	}
	else if (nResponse == IDCANCEL)
	{
//		MessageBox(NULL, "cancel", "ggg", MB_OK);
	}

}

_bstr_t CSkeletonManager::GetPluginOutput(CDataSorcesManager::public_source_id_t source, CDataSorcesManager::ap_id_t ap)
{

	CString ft = (BSTR) ap;

	if (ft != "hyp_4ft") return (BSTR) NULL;

	IXMLDOMDocumentPtr dom;
	dom.CreateInstance(_T("Msxml2.DOMDocument"));
	dom->async = VARIANT_FALSE; // default - true,
	
	dom->load((LPCTSTR) _T("..\\4ft_hyp.xml"));

	return dom->xml;
}

void CSkeletonManager::Generate()
{
/*	
	//pridat klonovani
	
	GenerTransform1(m_skeleton->documentElement);

	m_skeleton->save("../out.xml");


	
	
	
	LMRA_WordLoader::_LMRA_XML_WordLoaderPtr word;
	word.CreateInstance(CLSID_LMRA_XML_WordLoader);
	
	word->LoadFromString(m_skeleton->xml);

	word.Release();
*/
}



//tahle metoda asi prijde zrusit
void CSkeletonManager::GenerTransform1(IXMLDOMElementPtr & doc)
{
	Transform1Node(doc);
}



//rekurzivni
void CSkeletonManager::Transform1Node(IXMLDOMElementPtr & element)
{
	if (element == NULL) return;


	CString ft_name = "active_element";

	if (((BSTR) element->baseName != 0) && (ft_name == element->baseName))
	{
		TransformActiveElement(element);
	}
	else
	{
		IXMLDOMNodeListPtr iChildren = element->childNodes;

		IXMLDOMElementPtr iChild = NULL;

		while ((iChild = iChildren->nextNode()) != NULL)
		{
			
			//rekurze
			Transform1Node(iChild);
		}
	}
	
}

void CSkeletonManager::TransformActiveElement(IXMLDOMElementPtr & element)
{

	CAPTransform tr(element, * this);
	tr.DoAllTransnformations();


/***
	IXMLDOMElementPtr klon = element->cloneNode(VARIANT_TRUE);

	CAPTransform tr(klon, * this);

	AfxMessageBox(tr.DoAllTransnformations()->xml, 0, 0);

	klon.Release();

/***/
}
	
	
	/*
void CSkeletonManager::TransformActiveElement(IXMLDOMElementPtr node_ft)
{
	//nacteni ransformace
	
	IXMLDOMDocumentPtr output_transform;
	
	output_transform.CreateInstance(_T("Msxml2.DOMDocument"));
	output_transform->async = VARIANT_FALSE; // default - true,
//	output_transform->preserveWhiteSpace = VARIANT_TRUE;
	

	//predelat pro vic transformaci
	IXMLDOMElementPtr el_transform = node_ft->selectSingleNode("output/transformation");
	output_transform->load( el_transform->getAttribute("file"));


	
	//nacteni pluginoutput
	
	IXMLDOMDocumentPtr plug_out;
	plug_out.CreateInstance(_T("Msxml2.DOMDocument"));
	plug_out->async = VARIANT_FALSE; // default - true,
//	plug_out->preserveWhiteSpace = VARIANT_TRUE;
	
	plug_out->loadXML(GetPluginOutput(
		(_bstr_t) node_ft->getAttribute("source"),
		(_bstr_t) node_ft->getAttribute("type")));



	//provedeni transformace
	
	IXMLDOMDocumentPtr transofmed_node;
	transofmed_node.CreateInstance(_T("Msxml2.DOMDocument"));
	transofmed_node->async = VARIANT_FALSE; // default - true,
//	transofmed_node->preserveWhiteSpace = VARIANT_TRUE;

	
//	AfxMessageBox(plug_out->selectSingleNode("/active_list/hyp_4ft")->xml, 0, 0);
	//pracovni: transformuje se jen prvni hypoteza	
	transofmed_node->loadXML(
		plug_out->selectSingleNode("/active_list/hyp_4ft")->transformNode(output_transform));


	AfxMessageBox(transofmed_node->xml, 0, 0);

	//ulozeni transformace na misto puvodniho uzlu

//	node_ft->parentNode->insertBefore(transofmed_node->documentElement, node_ft);
//	node_ft->parentNode->removeChild(node_ft);
	node_ft->parentNode->replaceChild(transofmed_node->documentElement, node_ft);



	output_transform.Release();
	plug_out.Release();
	transofmed_node.Release();

}
	*/











/*
void LoadXLMFromString(_bstr_t strXMLSource, LPOLEOBJECT doc)
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
				IDispatch * d = NULL;
				doc->QueryInterface(& d);
				pWL->LoadFromStringToDoc( strXMLSource, & d);
				d->Release();
			}
			catch (...)
			{
				MessageBox(NULL, "XML string nejde prevest.", "chyba", MB_ICONERROR);
			}
			
			pWL->Release();
		}
	}


}

  */