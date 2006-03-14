// SkeletonManager.cpp: implementation of the CSkeletonManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "filter_dlg.h"
#include "simplefilterdialog.h"
#include "SkeletonManager.h"
#include "ReportAsistent.h"
#include "ElementManager.h"
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


	//inicializuje generator nahodnych cisel - kvuli generovani novych ID - docasne
	srand( (unsigned)time( NULL ) );



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


LPARAM CSkeletonManager::CreateItemData(IXMLDOMElementPtr & element)
{
	IXMLDOMElement * np = element;

	np->AddRef();

	return (LPARAM) np;
}


void CSkeletonManager::DeleteItemData(LPARAM data)
{
	IXMLDOMElement * np = (IXMLDOMElement *) data;

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
	

//honza: kvuli bezpecnosti a modifikovatelnosti a cistote kodu :)
//mozna planuju v item datat uchovavat id misto IXMLDOMElement *
IXMLDOMElement * CSkeletonManager::ElementFromItemData(LPARAM item_data)
{
	return (MSXML2::IXMLDOMElement *) item_data;
}

//pokusi se vlozit novy element jako child parent_element uzlu, novy element vrati
IXMLDOMElementPtr CSkeletonManager::InsertNewElement(CElementManager::elId elementID, IXMLDOMElementPtr & parent_element)
{
	CGeneralManager * m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager;

	
	IXMLDOMElementPtr new_example = m->ElementManager.CreateEmptyExampleElement(elementID);

	if (m->ElementManager.CanAppendChildHere(new_example, parent_element))
	{
		//ladici
		//AfxMessageBox(new_example->xml);	
		//AfxMessageBox(parent_element->xml);	
		
		
		//a tohle je sranda nejvetsi :-) hazi to chyby jak na bezicim pasu
		//kontroluje to tozi DTD dokumentu tak bacha, nejde vsecko vsude vlozit
		//az bude funkcni CanAppendChildHere tak by uz chyby nemely nastat
		try
		{
			parent_element->appendChild(new_example);
			return new_example;

		}
		catch (_com_error &e)
		{
			//AfxMessageBox(e.ErrorMessage());
			//AfxMessageBox(e.Description());
		}

	}
		
	
	AfxMessageBox(IDS_INSERT_NEW_ELEMENT_WRONG_LOCATION);	
	
	new_example.Release();
	
	return NULL;
}

//jen prelozi volani na metodu vyse
IXMLDOMElementPtr CSkeletonManager::InsertNewElement(LPCTSTR element_name, IXMLDOMElementPtr & parent_element)
{

	CGeneralManager * m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager;

	return InsertNewElement(m->ElementManager.ElementIdFromName(element_name), parent_element);

}

//vytvori novy id string pro eletment typu element_type
CString CSkeletonManager::CreateNewID(CElementManager::elId element_type)
{
	
	LPCTSTR el_name = //priradi nazev elementu z ElementManageru
		((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager.ElementName(element_type);

	CString id;

	id.Format("%s%d", el_name, rand());


	return id;
}
