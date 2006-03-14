// APTransform.cpp: implementation of the CAPTransform class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SkeletonManager.h"
#include "APTransform.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//zrusi varovani o prilis dlouhem identifikatoru
#pragma warning( disable : 4786 )



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAPTransform::CAPTransform(IXMLDOMElementPtr & node, CSkeletonManager & skel)
	:m_active_element(node), m_skel_manager(skel)
{
	//nacteni pluginoutput
	
	m_plug_out.CreateInstance(_T("Msxml2.DOMDocument"));
	m_plug_out->async = VARIANT_FALSE; // default - true,
	
	m_plug_out->loadXML(m_skel_manager.GetPluginOutput(
		(_bstr_t) m_active_element->getAttribute("source"),
		(_bstr_t) m_active_element->getAttribute("type")));

}



CAPTransform::~CAPTransform()
{
	m_plug_out.Release();
}

IXMLDOMDocumentFragmentPtr CAPTransform::DoAllTransnformations()
{
	IXMLDOMDocumentFragmentPtr parent_frag =
		m_active_element->ownerDocument->createDocumentFragment();
	
	ProcessSimpleFlter( (IXMLDOMNodePtr) parent_frag );


	if (m_active_element->parentNode != NULL)
	{
		m_active_element->parentNode->replaceChild(parent_frag, m_active_element);
	}

	return parent_frag;
}


//projde vsechny vybrane prvky ve filtru a pro kazdy provede vsechny transformace
void CAPTransform::ProcessSimpleFlter(IXMLDOMNodePtr & destination_parent)
{
	IXMLDOMNodeListPtr selected_items;
	selected_items = m_active_element->selectNodes("filter[@type='simple']/selection");

	for (int a=0; a < selected_items->length; a++)
	{
		IXMLDOMElementPtr item = selected_items->item[a];

		CString select = "id('";
		select += (_bstr_t) item->getAttribute("id");
		select += "')";
		//napriklad: select = "id('hyp1')"


		ProcessAllTransformations(
			m_plug_out->selectSingleNode((LPCTSTR) select), destination_parent);

	}
}


//projde vsechny transformace, aplikuje je na target uzel v m_plugin_output
//a vysledek upozi do destination_parent 
void CAPTransform::ProcessAllTransformations(IXMLDOMNodePtr & target, IXMLDOMNodePtr & destination_parent)
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
void CAPTransform::ProcessSingleTransformation(IXMLDOMNodePtr & target,
	IXMLDOMNodePtr & destination_parent, IXMLDOMElementPtr & tr_definition_element)
{
	//nacteni ransformace
	
	IXMLDOMDocumentPtr transformation_doc;	
	transformation_doc.CreateInstance(_T("Msxml2.DOMDocument"));
	transformation_doc->async = VARIANT_FALSE; // default - true,
	
	transformation_doc->load( tr_definition_element->getAttribute("file"));



	//privit misto pro vystup
	IXMLDOMDocumentPtr transofmed_node;
	transofmed_node.CreateInstance(_T("Msxml2.DOMDocument"));
	transofmed_node->async = VARIANT_FALSE; // default - true,


	//provedeni transformace
	transofmed_node->loadXML(target->transformNode(transformation_doc));

	
	//ulozeni vysledku tranformace na sve misto
	destination_parent->appendChild(transofmed_node->documentElement);



	transofmed_node.Release();
	transformation_doc.Release();
}


#pragma warning( default : 4786 )