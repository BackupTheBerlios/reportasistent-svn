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

CAElTransform::CAElTransform(MSXML2::IXMLDOMElementPtr & active_element, MSXML2::IXMLDOMNodePtr & plugin_output)
	:m_active_element(active_element)
{
	m_plug_out = plugin_output;
}


CAElTransform::CAElTransform(MSXML2::IXMLDOMElementPtr & active_element)
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

MSXML2::IXMLDOMDocumentFragmentPtr CAElTransform::DoAllTransnformations()
{
	//document fragment kam se budou ukladat jednotlive transformace
	MSXML2::IXMLDOMDocumentFragmentPtr parent_frag =
		m_active_element->ownerDocument->createDocumentFragment();
	
	//provede tranformace na kazdou polozku vybranou v simple filter
	ProcessSimpleFlter( (MSXML2::IXMLDOMNodePtr) parent_frag );

	FillElementAttributes(0);


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
void CAElTransform::ProcessSimpleFlter(MSXML2::IXMLDOMNodePtr & destination_parent)
{

	ProcessSimpleFlter(* this, FILTER_ALL_TRANSFORMATINOS, (LPARAM) destination_parent.GetInterfacePtr());
/*
	
	MSXML2::IXMLDOMNodeListPtr selected_items;
	selected_items = m_active_element->selectNodes("filter[@type='simple']/selection");

	for (int a=0; a < selected_items->length; a++)
	{
		MSXML2::IXMLDOMElementPtr item = selected_items->item[a];

		CString select = "id('";
		select += (_bstr_t) item->getAttribute("id");
		select += "')";
		//napriklad: select = "id('hyp1')"


		
		MSXML2::IXMLDOMNodePtr node_to_transform = m_plug_out->selectSingleNode((LPCTSTR) select);
		
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
void CAElTransform::ProcessAllTransformations(MSXML2::IXMLDOMNodePtr & target, MSXML2::IXMLDOMNodePtr & destination_parent)
{
	CElementManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;

	MSXML2::IXMLDOMNodeListPtr tranformations; 
	tranformations = m_active_element->selectNodes("output/transformation");

	for (int a=0; a<tranformations->length; a++)
	{
		//sem prijde rozlyseni na attr_link_table

		MSXML2::IXMLDOMElementPtr el_transformation = tranformations->item[a];

		CString transformation_type_str = (LPCTSTR) (_bstr_t) el_transformation->getAttribute("type");


		//nacteni ransformace	
		CAElInfo * el_info = m.getActiveElementInfo(m.IdentifyElement(m_active_element));

		MSXML2::IXMLDOMNodePtr & transformation_node = el_info->getTranformationNode(
			el_info->FindTransformationByName((_bstr_t) el_transformation->getAttribute("name")));


		if (transformation_type_str == "simple")
		{
			ProcessSingleTransformation(target, destination_parent, transformation_node);		
		}
		else if (transformation_type_str == "with_options")
		{
			SetTransformationOptions(transformation_node, el_transformation->selectSingleNode("visualization_values"));
			ProcessSingleTransformation(target, destination_parent, transformation_node);		
		}
		else
		{
			ASSERT(transformation_type_str == "attr_link_table");

			FillElementAttributes(target);

			MSXML2::IXMLDOMDocumentPtr tr_table = m.TransformAttrLinkTableNoReplaceSource(
					(MSXML2::IXMLDOMElementPtr) el_transformation->selectSingleNode("attr_link_table"));

			if (tr_table != NULL)
			{
				destination_parent->appendChild(tr_table->documentElement);
				tr_table.Release();
			}
		}

		el_transformation.Release();
	}
}

void CAElTransform::SetTransformationOptions(MSXML2::IXMLDOMNodePtr & el_transformation, MSXML2::IXMLDOMNodePtr & values_node)
{
	MSXML2::IXMLDOMNodeListPtr values = values_node->selectNodes("variable");

	for (int a = 0; a < values->length; a++)
	{
		MSXML2::IXMLDOMElementPtr value_element = values->item[a];

		MSXML2::IXMLDOMElementPtr variable_element;

		CString variable_qury_str;
		variable_qury_str.Format("/xsl:stylesheet/xsl:variable[@name=\'%s\']",
			(LPCTSTR) (_bstr_t) value_element->getAttribute("name"));
		variable_element = el_transformation->selectSingleNode((LPCTSTR) variable_qury_str);

		if (variable_element == NULL)
		{
			//vytvori element <xsl:variable >
			variable_element = el_transformation->ownerDocument->createNode(
				_variant_t((long) MSXML2::NODE_ELEMENT), "xsl:variable", "http://www.w3.org/1999/XSL/Transform");

			MSXML2::IXMLDOMAttributePtr name_attr =
				el_transformation->ownerDocument->createAttribute("name");

			name_attr->value = value_element->getAttribute("name");
			variable_element->setAttributeNode(name_attr);
			name_attr.Release();

			MSXML2::IXMLDOMNodePtr first_node = el_transformation->selectSingleNode("/xsl:stylesheet/*");

			if (first_node == NULL)
			{
				//asi by nemelo nastat, ale pro jistotu..
				el_transformation->selectSingleNode("/xsl:stylesheet")->
					appendChild(variable_element);

			}
			else
			{
				el_transformation->selectSingleNode("/xsl:stylesheet")->
					insertBefore(variable_element, 
						(MSXML2::IXMLDOMNode *) first_node);
			}
		}

		variable_element->text = (_bstr_t) value_element->getAttribute("value");
		
		variable_element.Release();
		value_element.Release();
	}
}

//transformuje target uzel v m_plugin_output podle transormace definovane v tr_definition_element
//a vysledek upozi do destination_parent
void CAElTransform::ProcessSingleTransformation(
						MSXML2::IXMLDOMNodePtr & target,
						MSXML2::IXMLDOMNodePtr & destination_parent,
						MSXML2::IXMLDOMNodePtr & transformation_node)
{
	//privit misto pro vystup
	MSXML2::IXMLDOMDocumentPtr transofmed_node;
	transofmed_node.CreateInstance(_T("Msxml2.DOMDocument"));
	transofmed_node->async = VARIANT_FALSE; // default - true,

	
	//provedeni transformace
	transofmed_node->loadXML(target->transformNode(transformation_node));

	
	//ulozeni vysledku tranformace na sve misto
	destination_parent->appendChild(transofmed_node->documentElement);



	transofmed_node.Release();
	transformation_node.Release();
}


//varati TRUE pokud processor.ProcessFilteredOut alespon jednou uspela, pokud je filter prazdy vrati FALSE
BOOL CAElTransform::ProcessSimpleFlter(CFilterProcessor & processor, LPARAM user1, LPARAM user2)
{
	MSXML2::IXMLDOMNodeListPtr selected_items;
	selected_items = m_active_element->selectNodes("filter[@type='simple']/selection");

	BOOL ret = FALSE;

	int order = 0;
	for (int a=0; a < selected_items->length; a++)
	{
		
		MSXML2::IXMLDOMElementPtr item = selected_items->item[a];

		CString select = "id('";
		select += (LPCTSTR) (_bstr_t) item->getAttribute("id");
		select += "')";
		//napriklad: select = "id('hyp1')"


		
		MSXML2::IXMLDOMNodePtr node_to_transform = m_plug_out->selectSingleNode((LPCTSTR) select);
		
		if (node_to_transform == NULL)
		{
			CString errs = "Warovani: Volba v simple filtru je neplatna.\n\nSelect string:\n";
			errs += select;
			AfxMessageBox(errs);
		}
		else
		{
			//ProcessAllTransformations(node_to_transform, destination_parent);
			ret |= processor.ProcessFilteredOut(node_to_transform, order++, user1, user2);
		}
	}

	return ret;
}


#define FILTER_FILL_ELEMENT_ATTRIBUTES 54321

BOOL CAElTransform::ProcessFilteredOut(MSXML2::IXMLDOMNodePtr filtered_output_node, int node_order, LPARAM user1, LPARAM user2)
{
	if (user1 == FILTER_ALL_TRANSFORMATINOS)
	{
		ProcessAllTransformations(filtered_output_node,
			/*destination_parent*/ (MSXML2::IXMLDOMNodePtr) (MSXML2::IXMLDOMNode *) user2);

		return TRUE;
	}
	else if (user1 == FILTER_FILL_ELEMENT_ATTRIBUTES)
	{
		if (user2 /*index_of_filtered_out*/ == node_order)
		{
			FillElementAttributes(filtered_output_node);
			return TRUE;
		}

	}

	return FALSE;
}



//naplni atributy (<element_attributes>) v m_active_element podle index_of_filtered_out-teho uzlu z filtru
//vrati TRUE, pokud se atributy podarilo naplnit
BOOL CAElTransform::FillElementAttributes(int index_of_filtered_out)
{

	return ProcessSimpleFlter(* this, FILTER_FILL_ELEMENT_ATTRIBUTES, index_of_filtered_out);
}


//naplni atributy (<element_attributes>) v m_active_element podle uzlu output_node
void CAElTransform::FillElementAttributes(MSXML2::IXMLDOMNodePtr &output_node)
{
	CElementManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;

	MSXML2::IXMLDOMDocumentPtr attributes_DOM;
	attributes_DOM.CreateInstance(_T("Msxml2.DOMDocument"));
	attributes_DOM->async = VARIANT_FALSE;

	
	//provede tranformaci
	attributes_DOM->loadXML(
		//ladici
		//bs = output_node->transformNode(
		output_node->transformNode(
			m.getActiveElementInfo(
				m.IdentifyElement(m_active_element))->getFillElementAttributesTransformation()));

	if (attributes_DOM->parseError->errorCode != S_OK)
	{
		CString err_str;
		AfxFormatString2(err_str, IDS_ELEMENT_ATTRIBUTES_FAILED_LOAD, m_active_element->selectSingleNode("@id")->text, attributes_DOM->parseError->reason);
		AfxMessageBox(err_str);
		attributes_DOM.Release();
		return;
	}

	//ladici
	attributes_DOM->save("../XML/fill_element_attributes_example.xml");

/*********/	
	
	//ulozi atributy do elementu se stejnym id jako m_active_element (nutne kvuli klonovani pri generovani)
	CString query_str;
	query_str.Format("id(\"%s\")/attributes", (LPCTSTR) (_bstr_t) m_active_element->getAttribute("id"));

	MSXML2::IXMLDOMNodePtr attributes_node = m_active_element->selectSingleNode((LPCTSTR) query_str);
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
