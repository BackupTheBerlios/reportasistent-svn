// APTransform.cpp: implementation of the CAPTransform class.
//
//////////////////////////////////////////////////////////////////////

#pragma warning( disable : 4786 )

#include "stdafx.h"
#include "ReportAsistent.h"
//#include  "SkeletonManager.h"
#include "CSkeletonDoc.h"
#include "APTransform.h"
#pragma warning( disable : 4786 )


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//zrusi varovani o prilis dlouhem identifikatoru



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAElTransform::CAElTransform(IXMLDOMElementPtr & active_element, IXMLDOMNodePtr & plugin_output)
	:m_active_element(active_element)
{
	m_plug_out = plugin_output;
}


CAElTransform::CAElTransform(IXMLDOMElementPtr & active_element)
	:m_active_element(active_element)
{
	//pouze nacteni pluginoutput
	
	m_plug_out.CreateInstance(_T("Msxml2.DOMDocument"));
	m_plug_out->async = VARIANT_FALSE; // default - true,
	

	CDataSourcesManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->DataSourcesManager;

	
	m_plug_out->loadXML(m.GetPluginOutput(
		(LPCTSTR) (_bstr_t) m_active_element->getAttribute("source"),
		(_bstr_t) m_active_element->getAttribute("type")));

}
 


CAElTransform::~CAElTransform()
{
	m_plug_out.Release();
}

IXMLDOMDocumentFragmentPtr CAElTransform::DoAllTransnformations()
{
	//document fragment kam se budou ukladat jednotlive transformace
	IXMLDOMDocumentFragmentPtr parent_frag =
		m_active_element->ownerDocument->createDocumentFragment();
	
	//provede tranformace na kazdou polozku vybranou v simple filter
	ProcessSimpleFlter( (IXMLDOMNodePtr) parent_frag );


/*****
	//pokud ma aktivni prvek rodice, nahradime ho vysledkem transformaci
	if (m_active_element->parentNode != NULL)
	{
		m_active_element->parentNode->replaceChild(parent_frag, m_active_element);
	}
/*****/
	
	//vysledek vsech transformaci ulozime na misto output element
	m_active_element->replaceChild(parent_frag, m_active_element->selectSingleNode("output"));
	
	
	return parent_frag;
}


#define FILTER_ALL_TRANSFORMATINOS	12345

//projde vsechny vybrane prvky ve filtru a pro kazdy provede vsechny transformace
void CAElTransform::ProcessSimpleFlter(IXMLDOMNodePtr & destination_parent)
{

	ProcessSimpleFlter(* this, FILTER_ALL_TRANSFORMATINOS, (LPARAM) destination_parent.GetInterfacePtr());
/*
	
	IXMLDOMNodeListPtr selected_items;
	selected_items = m_active_element->selectNodes("filter[@type='simple']/selection");

	for (int a=0; a < selected_items->length; a++)
	{
		IXMLDOMElementPtr item = selected_items->item[a];

		CString select = "id('";
		select += (_bstr_t) item->getAttribute("id");
		select += "')";
		//napriklad: select = "id('hyp1')"


		
		IXMLDOMNodePtr node_to_transform = m_plug_out->selectSingleNode((LPCTSTR) select);
		
		if (node_to_transform == NULL)
		{
			CString errs = "Warovani: Volba v simple filtru je neplatna.\n\nSelect string:\n";
			errs += select;
			AfxMessageBox(errs);
		}
		else
		{
			ProcessAllTransformations(node_to_transform, destination_parent);
		}
	}
*/
}


//projde vsechny transformace, aplikuje je na target uzel v m_plugin_output
//a vysledek upozi do destination_parent 
void CAElTransform::ProcessAllTransformations(IXMLDOMNodePtr & target, IXMLDOMNodePtr & destination_parent)
{
	IXMLDOMNodeListPtr tranformations; 
	tranformations = m_active_element->selectNodes("output/transformation");
	
	for (int a=0; a<tranformations->length; a++)
	{
		ProcessSingleTransformation(target, destination_parent, (IXMLDOMElementPtr) tranformations->item[a]);		
	}

}


//transformuje target uzel v m_plugin_output podle transormace definovane v tr_definition_element
//a vysledek upozi do destination_parent
void CAElTransform::ProcessSingleTransformation(IXMLDOMNodePtr & target,
	IXMLDOMNodePtr & destination_parent, IXMLDOMElementPtr & tr_definition_element)
{
	CElementManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;

	
	//nacteni ransformace
	
	CAElInfo * el_info = m.getActiveElementInfo(m.IdentifyElement(m_active_element));
	
	IXMLDOMNodePtr & transformation_node = el_info->getTranformationNode(
		el_info->FindTransformationByName((_bstr_t) tr_definition_element->getAttribute("name")));
			

	
/*	transformation_doc.CreateInstance(_T("Msxml2.DOMDocument"));
	transformation_doc->async = VARIANT_FALSE; // default - true,
	
	transformation_doc->load( tr_definition_element->getAttribute("file"));
*/


	//privit misto pro vystup
	IXMLDOMDocumentPtr transofmed_node;
	transofmed_node.CreateInstance(_T("Msxml2.DOMDocument"));
	transofmed_node->async = VARIANT_FALSE; // default - true,

	
	//provedeni transformace
	transofmed_node->loadXML(target->transformNode(transformation_node));

	
	//ulozeni vysledku tranformace na sve misto
	destination_parent->appendChild(transofmed_node->documentElement);



	transofmed_node.Release();
	transformation_node.Release();
}


void CAElTransform::ProcessSimpleFlter(CFilterProcessor & processor, LPARAM user1, LPARAM user2)
{
	IXMLDOMNodeListPtr selected_items;
	selected_items = m_active_element->selectNodes("filter[@type='simple']/selection");

	for (int a=0; a < selected_items->length; a++)
	{
		int order = 0;
		
		IXMLDOMElementPtr item = selected_items->item[a];

		CString select = "id('";
		select += (_bstr_t) item->getAttribute("id");
		select += "')";
		//napriklad: select = "id('hyp1')"


		
		IXMLDOMNodePtr node_to_transform = m_plug_out->selectSingleNode((LPCTSTR) select);
		
		if (node_to_transform == NULL)
		{
			CString errs = "Warovani: Volba v simple filtru je neplatna.\n\nSelect string:\n";
			errs += select;
			AfxMessageBox(errs);
		}
		else
		{
			//ProcessAllTransformations(node_to_transform, destination_parent);
			processor.ProcessFilteredOut(node_to_transform, order++, user1, user2);
		}
	}
}


#define FILTER_FILL_ELEMENT_ATTRIBUTES 54321

void CAElTransform::ProcessFilteredOut(IXMLDOMNodePtr filtered_output_node, int node_order, LPARAM user1, LPARAM user2)
{
	if (user1 == FILTER_ALL_TRANSFORMATINOS)
	{
		ProcessAllTransformations(filtered_output_node,
			/*destination_parent*/ (IXMLDOMNodePtr) (IXMLDOMNode *) user2);
	}
	else if (user1 == FILTER_FILL_ELEMENT_ATTRIBUTES)
	{
		if (user2 /*index_of_filtered_out*/ == node_order)
		{
			FillElementAttributes(filtered_output_node);
		}

	}
}



//naplni atributy (<element_attributes>) v m_active_element podle index_of_filtered_out-teho uzlu z filtru
BOOL CAElTransform::FillElementAttributes(int index_of_filtered_out)
{

	ProcessSimpleFlter(* this, FILTER_FILL_ELEMENT_ATTRIBUTES, index_of_filtered_out);

	//predelat na detekci chyb uvnitr call backu
	return TRUE;
}


//naplni atributy (<element_attributes>) v m_active_element podle uzlu output_node
void CAElTransform::FillElementAttributes(IXMLDOMNodePtr &output_node)
{
	CElementManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;

	IXMLDOMDocumentPtr attributes_DOM;
	attributes_DOM.CreateInstance(_T("Msxml2.DOMDocument"));
	attributes_DOM->async = VARIANT_FALSE;

	//provede tranformaci
	attributes_DOM->loadXML(
		output_node->transformNode(
			m.getActiveElementInfo(
				m.IdentifyElement(m_active_element))->getFillElementAttributesTransformation()));

/*********/	
	
	//ulozi atributy do m_active_element
	IXMLDOMNodePtr attributes_node = m_active_element->selectSingleNode("attributes");
	attributes_node->replaceChild(
		attributes_DOM->documentElement,
		attributes_node->selectSingleNode("element_attributes"));
	attributes_node.Release();

/****
	m_active_element->replaceChild(
		attributes_DOM->documentElement,
		m_active_element->selectSingleNode("attributes/element_attributes"));
/*****/
	
	attributes_DOM.Release();
}





#pragma warning( default : 4786 )
