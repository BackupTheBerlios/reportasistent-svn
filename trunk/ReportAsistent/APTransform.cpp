// APTransform.cpp: implementation of the CAPTransform class.
//
//////////////////////////////////////////////////////////////////////
/*
This file is part of LM Report Asistent.

Authors: Jan Dedek, Jan Kodym, Martin Chrz, Iva Bartunkova

LM Report Asistent is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

Foobar is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Foobar; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
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
	
	//m_plug_out.CreateInstance(_T("Msxml2.DOMDocument"));
	//m_plug_out->async = VARIANT_FALSE; // default - true,
	

	CDataSourcesManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->DataSourcesManager;

	
	m.GetPluginOutput(
		(LPCTSTR) (_bstr_t) m_active_element->getAttribute("source"),
		(_bstr_t) m_active_element->getAttribute("type"),
		& m_plug_out);

}
 


CAElTransform::~CAElTransform()
{
	if (m_plug_out != NULL) m_plug_out.Release();
}

MSXML2::IXMLDOMDocumentFragmentPtr CAElTransform::DoAllTransnformations()
{
	//document fragment kam se budou ukladat jednotlive transformace
	MSXML2::IXMLDOMDocumentFragmentPtr parent_frag =
		m_active_element->ownerDocument->createDocumentFragment();
	
	if (m_plug_out != NULL)
	{
		TransformCmplexFilterToSimple();

		//provede tranformace na kazdou polozku vybranou v simple filter
		ProcessSimpleFlter( (MSXML2::IXMLDOMNodePtr) parent_frag );
	}

	FillElementAttributes(0);


/*****
	//pokud ma aktivni prvek rodice, nahradime ho vysledkem transformaci
	if (m_active_element->parentNode != NULL)
	{
		m_active_element->parentNode->replaceChild(parent_frag, m_active_element);
	}
/*****/
	
	//vysledek vsech transformaci ulozime na misto vtrku output elementu
	MSXML2::IXMLDOMNodePtr out = m_active_element->selectSingleNode("output");

	((MSXML2::IXMLDOMSelectionPtr) out->selectNodes("*"))->removeAll();
	
	out->appendChild(parent_frag->cloneNode(VARIANT_TRUE));

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
			CString errs = "Varování: Volba v simple filtru je neplatná.\n\nSelect string:\n";
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



		if (transformation_type_str == "attr_link_table")
		{
			FillElementAttributes(target);

			MSXML2::IXMLDOMDocumentPtr tr_table = m.TransformAttrLinkTableNoReplaceSource(
					(MSXML2::IXMLDOMElementPtr) el_transformation->selectSingleNode("attr_link_table"));

			if (tr_table != NULL)
			{
				destination_parent->appendChild(tr_table->documentElement);
				tr_table.Release();
			}
		}
		else
		{
			int tr_index = el_info->FindTransformationByName(
				(_bstr_t) el_transformation->getAttribute("name"));

			if (tr_index == -1)
			{
				CReportAsistentApp::ReportError(IDS_WRONG_ELEMENT_TRANSFORMATION,
					(LPCTSTR) (_bstr_t) el_transformation->getAttribute("name"),
					(LPCTSTR) (_bstr_t) m_active_element->getAttribute("type"),
					(LPCTSTR) (_bstr_t) m_active_element->getAttribute("id"));
				el_transformation.Release();
				return;
			}


			
			
			MSXML2::IXMLDOMNodePtr & transformation_node = el_info->getTranformationNode(tr_index);

			if (transformation_type_str == "simple")
			{
				ProcessSingleTransformation(target, destination_parent, transformation_node);		
			}
			else if (transformation_type_str == "with_options")
			{
				SetTransformationOptions(transformation_node, el_transformation->selectSingleNode("visualization_values"));
				ProcessSingleTransformation(target, destination_parent, transformation_node);		
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

class CFilterSortItem
{
private:
	LPCTSTR static attr_name;
	CString static treshold_value;

	static bool (* compare_function) (CString *, CString *);



	//jedina datova polozka
	MSXML2::IXMLDOMElementPtr data;

public:
	CFilterSortItem(MSXML2::IXMLDOMElementPtr d): data(d) {};
	//	~CFilterSortItem() {};
	MSXML2::IXMLDOMElementPtr GetData() {return data; };
	void static PrepareRemoveIf(LPCTSTR _treshold_value) {treshold_value = _treshold_value;} ;

	void static PrepareSort(LPCTSTR _attr_name, BOOL _numeric_sort, BOOL _descending_sort)
	{
		attr_name = _attr_name;

		if (_numeric_sort)
		{
			if (_descending_sort) compare_function = CStrCompare::num_sort_desc;
			else compare_function = CStrCompare::num_sort_asc;
		}
		else
		{
			if (_descending_sort) compare_function = CStrCompare::str_sort_desc;
			else compare_function = CStrCompare::str_sort_asc;
		}
	};

	bool operator < (CFilterSortItem s)
	{
		CString a = (LPCTSTR) (_bstr_t) data->getAttribute(attr_name);
		CString b = (LPCTSTR) (_bstr_t) s.data->getAttribute(attr_name);

		return compare_function(& a, & b);
	};

	bool static TresholdCompare(CFilterSortItem s)
	{
		CString a = (LPCTSTR) (_bstr_t) s.data->getAttribute(attr_name);

		return compare_function(& treshold_value, & a);
	};
};

LPCTSTR CFilterSortItem::attr_name;
CString CFilterSortItem::treshold_value;
bool (* CFilterSortItem::compare_function) (CString *, CString *);



void CAElTransform::ApplyTresholdFilter(MSXML2::IXMLDOMElementPtr & filter_dom, LPCTSTR attr_name, BOOL numeric_sort, BOOL descending_sort, LPCTSTR treshold)
{
	MSXML2::IXMLDOMNodePtr parent = filter_dom->selectSingleNode("/dialog_data/values");
	MSXML2::IXMLDOMNodeListPtr values_list = filter_dom->selectNodes("/dialog_data/values/value");

	std::vector<CFilterSortItem> sort_helper;
	std::vector<CFilterSortItem>::iterator treshold_end;

	int a;
	for (a = 0; a < values_list->length; a++)
	{
		sort_helper.push_back(CFilterSortItem(parent->removeChild(values_list->item[a])));		
	}

	CFilterSortItem::PrepareSort(attr_name, numeric_sort, descending_sort);
	CFilterSortItem::PrepareRemoveIf(treshold);

	treshold_end = std::remove_if(sort_helper.begin(), sort_helper.end(), CFilterSortItem::TresholdCompare);
	sort_helper.erase(treshold_end, sort_helper.end());

	std::sort(sort_helper.begin(), sort_helper.end());

	for (a = 0; a < (int) sort_helper.size(); a++)
	{		
		parent->appendChild(sort_helper[a].GetData() );		
	}
}

void CAElTransform::ApplyTopNFilter(MSXML2::IXMLDOMElementPtr & filter_dom, LPCTSTR attr_name, BOOL numeric_sort, BOOL descending_sort, int top_n)
{
	MSXML2::IXMLDOMNodePtr parent = filter_dom->selectSingleNode("/dialog_data/values");
	MSXML2::IXMLDOMNodeListPtr values_list = filter_dom->selectNodes("/dialog_data/values/value");

	std::vector<CFilterSortItem> sort_helper;

	int a;
	for (a = 0; a < values_list->length; a++)
	{
		sort_helper.push_back(CFilterSortItem(parent->removeChild(values_list->item[a])));		
	}

	CFilterSortItem::PrepareSort(attr_name, numeric_sort, descending_sort);
	
	if (values_list->length <= top_n)
	{
		std::sort(sort_helper.begin(), sort_helper.end());
	}
	else
	{
		std::partial_sort(sort_helper.begin(), sort_helper.begin() + top_n, sort_helper.end());
	}

	for (a = 0; a < top_n; a++)
	{
		if (a >= (int) sort_helper.size()) break;
		
		parent->appendChild(sort_helper[a].GetData() );		
	}

}

void CAElTransform::ApplyFixedValueFilter(MSXML2::IXMLDOMElementPtr & filter_dom, LPCTSTR attr_name, BOOL num_compare, LPCTSTR fixed_value)
{
	MSXML2::IXMLDOMNodePtr parent = filter_dom->selectSingleNode("/dialog_data/values");
	MSXML2::IXMLDOMNodeListPtr values_list = filter_dom->selectNodes("/dialog_data/values/value");

	CString s_fixed_value = fixed_value;

	CString q;
	q.Format("@%s", attr_name);

	for (int a = 0; a < values_list->length; a++)
	{
		CString current_value;

		try
		{
			current_value = (LPCTSTR) values_list->item[a]->selectSingleNode((LPCTSTR) q)->text;
		}
		catch (...)
		{
			continue;
		}
		
		
		// zachovej hodnotu pokud !(a < b) && !(b < a)			...=> a == b
		if (
			(num_compare && (! CStrCompare::num_sort_desc(& s_fixed_value, & current_value) &&
							 ! CStrCompare::num_sort_desc(& current_value, & s_fixed_value))) 
				||
			(! num_compare && (! CStrCompare::str_sort_desc(& s_fixed_value, & current_value) &&
							 ! CStrCompare::str_sort_desc(& current_value, & s_fixed_value))))
		{
			continue;
		}

		parent->removeChild(values_list->item[a]);
	}
}

BOOL CAElTransform::LoadFilterDOM(public_source_id_t sId, MSXML2::IXMLDOMElementPtr & filter_DOM)
{
	CGeneralManager * m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager;

    CAElInfo * element_info = m->ElementManager.getActiveElementInfo(
								m->ElementManager.IdentifyElement(m_active_element));

   	
    MSXML2::IXMLDOMDocumentPtr plugout_doc;

	//nacte data z plugin output
	if (! m->DataSourcesManager.GetPluginOutput(sId, element_info->getElementName(), & plugout_doc))
	{
		CReportAsistentApp::ReportError(IDS_SIMPLE_FILTER_FAILED_SOURCE_LOAD, "Plugin output is empty.");
		return FALSE;	
	}

    try
	{
		plugout_doc->save((LPCTSTR) (m->DirectoriesManager.getXMLFilesDirectory() + "/plug_out_example.xml"));
	}
	catch (...) {}

	
    //ulozi element atributy
//	CAElTransform tr(m_active_element, (MSXML2::IXMLDOMNodePtr) plugout_doc);
//	FillElementAttributes(0);


    //transformace plugout na filter dom
    MSXML2::IXMLDOMDocumentPtr filter_doc;
    filter_doc.CreateInstance(_T("Msxml2.DOMDocument"));
	filter_doc->async = VARIANT_FALSE; // default - true,
	
	filter_doc->loadXML(
		plugout_doc->transformNode(element_info->getComplexFilterTransformation()));

    plugout_doc.Release();

	if (filter_doc->parseError->errorCode != S_OK)
	{
   		CReportAsistentApp::ReportError(IDS_COMPLEX_FILTER_OUTPUT_INVALID, 
			element_info->getElementLabel(), (LPCTSTR) filter_doc->parseError->reason);
		return FALSE;
	}

	CString err;
	if (! m->ElementManager.ValidateComplexFilter(filter_doc, err))
	{
   		CReportAsistentApp::ReportError(IDS_COMPLEX_FILTER_OUTPUT_INVALID, 
			element_info->getElementLabel(), (LPCTSTR) err);
		return FALSE;
	}
	
	
	if (filter_doc->documentElement == NULL)
	{
   		CReportAsistentApp::ReportError(IDS_SIMPLE_FILTER_FAILED_SOURCE_LOAD, "Document element of \"complex_filter.xsl\" transformation result is empty.");
		return FALSE;
	}

   	try
	{
		filter_doc->save((LPCTSTR) (m->DirectoriesManager.getXMLFilesDirectory() + "/complex_filter_example.xml"));
	}
	catch (...) {}
    
	filter_DOM = filter_doc->documentElement;
	filter_doc.Release();
	return TRUE;
}

void CAElTransform::TransformCmplexFilterToSimple()
{
	int a;

	MSXML2::IXMLDOMNodePtr simple_filter = m_active_element->selectSingleNode("filter[@type='simple']");
	MSXML2::IXMLDOMNodePtr complex_filter = m_active_element->selectSingleNode("filter[@type='complex']");

	if (simple_filter == NULL)
	{
		//vytvori prazdny simple filter
		MSXML2::IXMLDOMAttributePtr atr = m_active_element->ownerDocument->createAttribute("type");
		atr->text = "simple";
		MSXML2::IXMLDOMElementPtr el = m_active_element->ownerDocument->createAttribute("filter");
		el->setAttributeNode(atr);
		m_active_element->insertBefore(el, (MSXML2::IXMLDOMNode *) complex_filter);
		simple_filter = el;
	}

	//pokud je simple fiter neprazdny tak nic
	if (simple_filter->firstChild != NULL) return;

	if ((complex_filter == NULL) || (complex_filter->firstChild == NULL)) return;

	MSXML2::IXMLDOMElementPtr filter_dom;
	if (! LoadFilterDOM(
			(LPCTSTR) (_bstr_t) m_active_element->getAttribute("source"),
			filter_dom))
	{
		return;
	}

	ApplyAllAttributeFilters(filter_dom);

	//vymaz vnitrek filtru
/*
	MSXML2::IXMLDOMNodePtr filter_node = m_active_element->selectSingleNode("filter");
	while (filter_node->firstChild != NULL)
	{
		filter_node->removeChild(filter_node->firstChild);
	}
//	AfxMessageBox(filter_node->xml);
*/
	
	//vloz obsah simple fitru
	MSXML2::IXMLDOMElementPtr selection_el = m_active_element->ownerDocument->createElement("selection");
	MSXML2::IXMLDOMAttributePtr id_attr = m_active_element->ownerDocument->createAttribute("id");
	selection_el->setAttributeNode(id_attr);
	id_attr.Release();

	MSXML2::IXMLDOMNodeListPtr value_ids = filter_dom->selectNodes("/dialog_data/values/value/@id");
	for (a = 0; a < value_ids->length; a++)
	{
		selection_el->setAttribute("id", value_ids->item[a]->text);
		simple_filter->appendChild(selection_el->cloneNode(VARIANT_TRUE));
	}
}

void CAElTransform::ApplyAllFilters(MSXML2::IXMLDOMElementPtr & filter_dom)
{
	MSXML2::IXMLDOMNodePtr simple_filter_clone = 
		m_active_element->selectSingleNode("filter[@type='simple']")->cloneNode(VARIANT_TRUE);

	TransformCmplexFilterToSimple();

	MSXML2::IXMLDOMNodePtr values_node = filter_dom->selectSingleNode("/dialog_data/values");
	MSXML2::IXMLDOMNodePtr simple_filter = m_active_element->selectSingleNode("filter[@type='simple']");
	MSXML2::IXMLDOMNodeListPtr simple_filter_ids = simple_filter->selectNodes("selection/@id");


//	AfxMessageBox(simple_filter->xml);

	for (int val = values_node->childNodes->length-1; val >= 0; val--)
	{
		BOOL remove_val = TRUE;
		for (int id = 0; id < simple_filter_ids->length; id++)
		{
			MSXML2::IXMLDOMNodePtr id_attr = values_node->childNodes->item[val]->selectSingleNode("@id");
			if (id_attr == NULL) continue;
			if (id_attr->text 
					== 
				simple_filter_ids->item[id]->text)
			{
				remove_val = FALSE;
				break;
			}			
		}

		if (remove_val) values_node->removeChild(values_node->childNodes->item[val]);
	}

	

	m_active_element->replaceChild(simple_filter_clone, simple_filter);

}

void CAElTransform::ApplyAllAttributeFilters(MSXML2::IXMLDOMElementPtr & filter_dom)
{
	MSXML2::IXMLDOMNodeListPtr attr_filer_list = 
		m_active_element->selectNodes("filter/attribute_filter");

	for (int a = 0; a < attr_filer_list->length; a++)
	{
		ApplySingleAttributeFilter(filter_dom, attr_filer_list->item[a]);
	}

}

void CAElTransform::ApplySingleAttributeFilter(MSXML2::IXMLDOMElementPtr & filter_dom, MSXML2::IXMLDOMElementPtr attribute_filter)
{
	CString attr_name = (LPCTSTR) (_bstr_t) attribute_filter->getAttribute("attr_name");
	CString filter_type = (LPCTSTR) (_bstr_t) attribute_filter->getAttribute("filter_type");
	CString compare_value = (LPCTSTR) (_bstr_t) attribute_filter->getAttribute("filter_data");
	BOOL numeric_sort = ((_bstr_t) attribute_filter->getAttribute("numeric_sort") == (_bstr_t) "true");
	BOOL descending_sort = ((_bstr_t) attribute_filter->getAttribute("sort_direction") == (_bstr_t) "descending");
	
	if (filter_type == "treshold")
	{
		ApplyTresholdFilter(filter_dom, attr_name, numeric_sort, descending_sort, compare_value);
	}
	else
	if (filter_type == "fixed")
	{
		ApplyFixedValueFilter(filter_dom, attr_name, numeric_sort, compare_value);
	}
	else
	if (filter_type == "top-n")
	{
		ApplyTopNFilter(filter_dom, attr_name, numeric_sort, descending_sort, 
			(long) attribute_filter->getAttribute("filter_data"));
	}

	attribute_filter->getAttribute("filter_data");	
}

//varati TRUE pokud processor.ProcessFilteredOut alespon jednou uspela, pokud je filter prazdy vrati FALSE
BOOL CAElTransform::ProcessSimpleFlter(CFilterProcessor & processor, LPARAM user1, LPARAM user2)
{
	ASSERT(m_plug_out != NULL);
	
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

#ifdef _DEBUG
			CString errs = "Varování: Volba v simple filtru je neplatná.\n\nSelect string:\n";
			errs += select;
			AfxMessageBox(errs);
#endif

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
	if (m_plug_out == NULL)
	{
		return FALSE;
	}

	//transformace complex fitru na obyc
	MSXML2::IXMLDOMNodePtr filter_backup;
	try
	{
		filter_backup =  m_active_element->selectSingleNode("filter[type='simple']")->cloneNode(VARIANT_TRUE);
	}
	catch (...)
	{
		filter_backup = NULL;
	}
	
	TransformCmplexFilterToSimple();
	BOOL ret = ProcessSimpleFlter(* this, FILTER_FILL_ELEMENT_ATTRIBUTES, index_of_filtered_out);
	
	if (filter_backup != NULL)
	{
		m_active_element->replaceChild(filter_backup, m_active_element->selectSingleNode("filter[type='simple']"));
	}

	return ret;
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
		CReportAsistentApp::ReportError(IDS_ELEMENT_ATTRIBUTES_FAILED_LOAD,
			(LPCTSTR) m_active_element->selectSingleNode("@id")->text,
			(LPCTSTR) attributes_DOM->parseError->reason);
		attributes_DOM.Release();
		return;
	}

	CDirectoriesManager & dm = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->DirectoriesManager;
	try
	{
		attributes_DOM->save((LPCTSTR) (dm.getXMLFilesDirectory() + "/fill_element_attributes_example.xml"));
	}
	catch (...) {}

	CString err;
	if (! m.ValidateFillElementAttributes(attributes_DOM, err))
	{
		CReportAsistentApp::ReportError(IDS_ELEMENT_ATTRIBUTES_FAILED_LOAD,
			(LPCTSTR) m_active_element->selectSingleNode("@id")->text,
			(LPCTSTR) err);
		attributes_DOM.Release();
		return;
	}


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
