// APTransform.h: interface for the CAPTransform class.
//
//////////////////////////////////////////////////////////////////////
/*
This file is part of LM Report Asistent.

Authors: Jan Dedek, Jan Kodym, Martin Chrz, Iva Bartunkova

LM Report Asistent is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

LM Report Asistent is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with LM Report Asistent; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#if !defined(AFX_APTRANSFORM_H__3C627318_5510_492C_93AE_77F522093738__INCLUDED_)
#define AFX_APTRANSFORM_H__3C627318_5510_492C_93AE_77F522093738__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER >  1000

//zrusi varovani o prilis dlouhem identifikatoru
#pragma warning( disable : 4786 )


//slouzi jako call back interface pro volani fitrovacich funkci - napr: ProcessSimpleFlter
/**
 * class CFilterProcessor:
 *
 * @author 
 */
class CFilterProcessor
{
public:
	//vrati TRUE pokud funkce uspela
	/**
 * ProcessFilteredOut:
 *
 * @param filtered_output_node 
 * @param node_order 
 * @param user1 
 * @param user2 
 * @return virtual BOOL 
 */
virtual BOOL ProcessFilteredOut(
		MSXML2::IXMLDOMNodePtr filtered_output_node,	//XML uzel ktery z plugin output prosel fitrem
		int node_order,							//poradi filtered_output_node uzlu mezi temi ktere prosly
		LPARAM user1,							//uzivatelsky parametr, ktery byl predan filtrovaci funkci
		LPARAM user2							//uzivatelsky parametr, ktery byl predan filtrovaci funkci
		) = 0;

};


//honza:
//trida slouzici k vygenerovani jednoho aktivniho prvku
/**
 * class CAElTransform:
 *
 * @author 
 */
class CAElTransform: public CFilterProcessor
{
private:
//	CSkeletonDoc & m_skel_document;
	MSXML2::IXMLDOMElementPtr & m_active_element;
	MSXML2::IXMLDOMDocumentPtr m_plug_out;

void static ApplyFixedValueFilter(MSXML2::IXMLDOMElementPtr & filter_dom, LPCTSTR attr_name, BOOL num_compare, LPCTSTR fixed_value);
void static ApplyTopNFilter(MSXML2::IXMLDOMElementPtr & filter_dom, LPCTSTR attr_name, BOOL numeric_sort, BOOL descending_sort, int top_n);
void static ApplyTresholdFilter(MSXML2::IXMLDOMElementPtr & filter_dom, LPCTSTR attr_name, BOOL numeric_sort, BOOL descending_sort, LPCTSTR treshold);



public:
	BOOL LoadFilterDOM(public_source_id_t sId, MSXML2::IXMLDOMElementPtr & filter_DOM);
	void TransformCmplexFilterToSimple();

	void ApplyAllFilters(MSXML2::IXMLDOMElementPtr & filter_dom);
	void ApplyAllAttributeFilters(MSXML2::IXMLDOMElementPtr & filter_dom);
	void static ApplySingleAttributeFilter(MSXML2::IXMLDOMElementPtr & filter_dom, MSXML2::IXMLDOMElementPtr attribute_filter);

protected:
	void FillElementAttributes(MSXML2::IXMLDOMNodePtr & output_node);
	virtual BOOL ProcessFilteredOut(MSXML2::IXMLDOMNodePtr filtered_output_node, int node_order, LPARAM user1, LPARAM user2);

	void ProcessSimpleFlter(MSXML2::IXMLDOMNodePtr & destination_parent);
	void ProcessAllTransformations(MSXML2::IXMLDOMNodePtr & target, MSXML2::IXMLDOMNodePtr & destination_parent);
	void ProcessSingleTransformation(
						MSXML2::IXMLDOMNodePtr & target,
						MSXML2::IXMLDOMNodePtr & destination_parent,
						MSXML2::IXMLDOMNodePtr & transformation_node);

	void static CAElTransform::SetTransformationOptions(MSXML2::IXMLDOMNodePtr & el_transformation, MSXML2::IXMLDOMNodePtr & values_node);



public:
	BOOL ProcessSimpleFlter(CFilterProcessor & processor, LPARAM user1 = 0, LPARAM user2 = 0);
	BOOL FillElementAttributes(int index_of_filtered_out);
	MSXML2::IXMLDOMDocumentFragmentPtr DoAllTransnformations();
	
	CAElTransform(MSXML2::IXMLDOMElementPtr & active_element);
	CAElTransform(MSXML2::IXMLDOMElementPtr & active_element, MSXML2::IXMLDOMNodePtr & plugin_output);
	~CAElTransform();	
};


#pragma warning( default : 4786 )

#endif // !defined(AFX_APTRANSFORM_H__3C627318_5510_492C_93AE_77F522093738__INCLUDED_)
