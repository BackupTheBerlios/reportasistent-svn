// APTransform.h: interface for the CAPTransform class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_APTRANSFORM_H__3C627318_5510_492C_93AE_77F522093738__INCLUDED_)
#define AFX_APTRANSFORM_H__3C627318_5510_492C_93AE_77F522093738__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//zrusi varovani o prilis dlouhem identifikatoru
#pragma warning( disable : 4786 )


//honza:
//trida slouzici k vygenerovani jednoho aktivniho prvku
class CAPTransform  
{
private:
	CSkeletonManager & m_skel_manager;
	IXMLDOMElementPtr & m_active_element;
	IXMLDOMDocumentPtr m_plug_out;

protected:
	void ProcessSimpleFlter(IXMLDOMNodePtr & destination_parent);
	void ProcessAllTransformations(IXMLDOMNodePtr & target, IXMLDOMNodePtr & destination_parent);
	void ProcessSingleTransformation(IXMLDOMNodePtr & target,
			IXMLDOMNodePtr & destination_parent, IXMLDOMElementPtr & tr_definition_element);


public:
	IXMLDOMDocumentFragmentPtr DoAllTransnformations();
	
	CAPTransform(IXMLDOMElementPtr & node, CSkeletonManager & skel);
	~CAPTransform();	
};


#pragma warning( default : 4786 )

#endif // !defined(AFX_APTRANSFORM_H__3C627318_5510_492C_93AE_77F522093738__INCLUDED_)
