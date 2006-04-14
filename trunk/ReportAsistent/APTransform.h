// APTransform.h: interface for the CAPTransform class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_APTRANSFORM_H__3C627318_5510_492C_93AE_77F522093738__INCLUDED_)
#define AFX_APTRANSFORM_H__3C627318_5510_492C_93AE_77F522093738__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER >  1000

//zrusi varovani o prilis dlouhem identifikatoru
#pragma warning( disable : 4786 )


//slouzi jako call back interface pro volani fitrovacich funkci - napr: ProcessSimpleFlter
class CFilterProcessor
{
public:
	//vrati TRUE pokud funkce uspela
	virtual BOOL ProcessFilteredOut(
		IXMLDOMNodePtr filtered_output_node,	//XML uzel ktery z plugin output prosel fitrem
		int node_order,							//poradi filtered_output_node uzlu mezi temi ktere prosly
		LPARAM user1,							//uzivatelsky parametr, ktery byl predan filtrovaci funkci
		LPARAM user2							//uzivatelsky parametr, ktery byl predan filtrovaci funkci
		) = 0;
};


//honza:
//trida slouzici k vygenerovani jednoho aktivniho prvku
class CAElTransform: public CFilterProcessor
{
private:
//	CSkeletonDoc & m_skel_document;
	IXMLDOMElementPtr & m_active_element;
	IXMLDOMDocumentPtr m_plug_out;

protected:
	void FillElementAttributes(IXMLDOMNodePtr & output_node);
	virtual BOOL ProcessFilteredOut(IXMLDOMNodePtr filtered_output_node, int node_order, LPARAM user1, LPARAM user2);

	void ProcessSimpleFlter(IXMLDOMNodePtr & destination_parent);
	void ProcessAllTransformations(IXMLDOMNodePtr & target, IXMLDOMNodePtr & destination_parent);
	void ProcessSingleTransformation(IXMLDOMNodePtr & target,
			IXMLDOMNodePtr & destination_parent, IXMLDOMElementPtr & tr_definition_element);


public:
	BOOL ProcessSimpleFlter(CFilterProcessor & processor, LPARAM user1 = 0, LPARAM user2 = 0);
	BOOL FillElementAttributes(int index_of_filtered_out);
	IXMLDOMDocumentFragmentPtr DoAllTransnformations();
	
	CAElTransform(IXMLDOMElementPtr & active_element);
	CAElTransform(IXMLDOMElementPtr & active_element, IXMLDOMNodePtr & plugin_output);
	~CAElTransform();	
};


#pragma warning( default : 4786 )

#endif // !defined(AFX_APTRANSFORM_H__3C627318_5510_492C_93AE_77F522093738__INCLUDED_)
