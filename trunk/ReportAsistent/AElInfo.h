// AElInfo.h: interface for the CAElInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AELINFO_H__0974EB59_93DF_4180_9E7B_8B12A39E63F5__INCLUDED_)
#define AFX_AELINFO_H__0974EB59_93DF_4180_9E7B_8B12A39E63F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER >   1000

/**
 * class CAElInfo:
 *
 * @author 
 */
class CAElInfo  
{
public:
	CString getElementIconPath();
	int FindTransformationByName(LPCTSTR tr_name);
	MSXML2::IXMLDOMElementPtr CreateEmptyElement();
	BOOL LoadElementIcon(CBitmap &icon);
	MSXML2::IXMLDOMNodePtr getComplexFilterTransformation();
	MSXML2::IXMLDOMNodePtr getFillElementAttributesTransformation();
	BOOL LoadFromDir(LPCTSTR dir_path);
	LPCTSTR getElementName();
	LPCTSTR getElementLabel();
	CAElInfo();
	virtual ~CAElInfo();

	int getTranformationsCount();
	CString getTranformationName(int tr_index);
	MSXML2::IXMLDOMNodePtr getTranformationNode(int tr_index);
	MSXML2::IXMLDOMNodePtr getTranformationOptionsDoc(int tr_index);
	


private:
	struct s_transformation
	{
		CString name;
		MSXML2::IXMLDOMDocumentPtr doc;
		MSXML2::IXMLDOMDocumentPtr options;
	};

	CString src_dir_path;
	MSXML2::IXMLDOMDocumentPtr pComplexFilterDOM;
	MSXML2::IXMLDOMDocumentPtr pFillElementAttributesDOM;
	MSXML2::IXMLDOMDocumentPtr pElementDefinitionDOM;
	CString el_name;
	CString el_label;	// kody: label AP

	void LoadTransformations(LPCTSTR dir_path);

	CArray<s_transformation *,s_transformation*> m_transformations;

	
	// kody: nastaveni jazyka transformace (hodnoty promenne "lng")
	BOOL setLanguageInTransformation(MSXML2::IXMLDOMNodePtr pTransf);

};

#endif // !defined(AFX_AELINFO_H__0974EB59_93DF_4180_9E7B_8B12A39E63F5__INCLUDED_)
