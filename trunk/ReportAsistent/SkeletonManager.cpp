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

//docasne
void CSkeletonManager::AddElement()
{
	IXMLDOMDocumentPtr element_example;
	element_example.CreateInstance(_T("Msxml2.DOMDocument"));	
	element_example->async = VARIANT_FALSE; // default - true,

	element_example->load((LPCTSTR) _T("..\\skeleton.xml"));

	
	m_skeleton->documentElement->appendChild(element_example->selectSingleNode("//active_element[@type = 'hyp_4ft']"));

	element_example.Release();

}

//docasne
void CSkeletonManager::EditElement(LPARAM item_data)
{
	if (item_data == NULL) return;

	//ziskej element
	IXMLDOMElementPtr selected_element = ElementFromItemData(item_data);
	//ziskej manager
	CElementManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;
	//ziskej typ elementu
	CElementManager::elId_t selected_elementId = m.IdentifyElement(selected_element);

	

	
	//jedna se o aktivni prvek?
	if (m.IsElementActive(selected_elementId))
	{
		EditActiveElement(selected_element);
	}	//jedna se o prvek text?
	else if (selected_elementId == elId_t_TEXT)
	{
		AfxMessageBox(selected_element->text);
	}
	else
	{	//ostatni prvky
		AfxMessageBox(selected_element->xml);
	}


}



void CSkeletonManager::ConfigureFilter(IXMLDOMElementPtr & active_element)
{
	//sem prijdou i jiny fitry
	
	//dialog prepise active_element podle uzivatelovy volby
	CSimpleFilterDialog dlg(active_element, /*
		GetPluginOutput((_bstr_t) active_element->getAttribute("source"),
						(_bstr_t) active_element->getAttribute("type")),*/
		AfxGetMainWnd());

	int nResponse = dlg.DoModal();	
}

_bstr_t CSkeletonManager::GetPluginOutput(public_source_id_t source, LPCTSTR ap_name)
{
	CDataSourcesManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->DataSourcesManager;

	int src_index = m.FindSourceByPublicID(source);
	if (! m.isSourceConnected(src_index)) 
	{
		if (! m.ConnectSource(src_index)) return "";
	}

	return m.CallPerformProc(src_index, ap_name);
/*
	CString ft = ap_name;

	if (ft != "hyp_4ft") return (BSTR) NULL;

	IXMLDOMDocumentPtr dom;
	dom.CreateInstance(_T("Msxml2.DOMDocument"));
	dom->async = VARIANT_FALSE; // default - true,
	
	dom->load((LPCTSTR) _T("../XML/4ft_hyp.xml"));

	IXMLDOMElementPtr el_hyp = dom->selectSingleNode("/active_list/hyp_4ft");

	el_hyp->setAttribute("db_name", (LPCTSTR) source);

	return dom->xml;
*/
}

void CSkeletonManager::Generate()
{
	IXMLDOMElementPtr doc_element;
	

#ifdef DONT_CLONE_REPORT_BEFORE_GENERATE
	doc_element = m_skeleton->documentElement;
#else
	//klonuje cely dokumnet
	doc_element = m_skeleton->documentElement->cloneNode(VARIANT_TRUE);
#endif
	
	//provede transformace
	GenerTransform1(doc_element);

	

//	doc_element->save("../out.xml");


	
/*****///generovani do Wordu	

	LMRA_WordLoader::_LMRA_XML_WordLoaderPtr word;
	word.CreateInstance(CLSID_LMRA_XML_WordLoader);

	try
	{	
		word->LoadFromString(doc_element->xml);
	}
	catch (_com_error & e)
	{
		CString err = "Chyba pri generovani.\n\nposledni zpracovavane id:   ";
		err += word->GetstrLastProcessedId();
		err += "\n\n";
		err += word->GetstrLastError();
		err += "\n";
		err += e.Description();
		err += "\n";
		err += e.ErrorMessage();
		AfxMessageBox(err);
	}

	word.Release();
/******/
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

	CElementManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;


	if (m.IsElementActive(m.IdentifyElement(element)))
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


//honza: ladici - lze pouzit pro generovani preview
/***
	IXMLDOMElementPtr klon = element->cloneNode(VARIANT_TRUE);

	CAPTransform tr(klon, * this);

	AfxMessageBox(tr.DoAllTransnformations()->xml);

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
IXMLDOMElementPtr CSkeletonManager::InsertNewElement(CElementManager::elId_t elementID, IXMLDOMElementPtr & parent_element)
{
	CGeneralManager * m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager;

	
	IXMLDOMElementPtr new_example = m->ElementManager.CreateEmptyElement(elementID);

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
			AfxMessageBox(e.Description());
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
CString CSkeletonManager::CreateNewID(CElementManager::elId_t element_type)
{
	
	LPCTSTR el_name = //priradi nazev elementu z ElementManageru
		((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager.getElementName(element_type);

	CString id;

	id.Format("%s%d", el_name, rand());


	return id;
}


//honza: az budou lepsi dialogy, jejich volani prijde sem
void CSkeletonManager::EditActiveElement(IXMLDOMElementPtr &element)
{
	ConfigureFilter(element);
}
 