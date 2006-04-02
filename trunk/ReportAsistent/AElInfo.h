// AElInfo.h: interface for the CAElInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AELINFO_H__0974EB59_93DF_4180_9E7B_8B12A39E63F5__INCLUDED_)
#define AFX_AELINFO_H__0974EB59_93DF_4180_9E7B_8B12A39E63F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAElInfo  
{
public:
	IXMLDOMNode * getSimpleFilterTransformation();
	BOOL LoadFromDir(LPCTSTR dir_path);
	LPCTSTR getElementName();
	CAElInfo();
	virtual ~CAElInfo();

private:
	IXMLDOMDocumentPtr pSimpleFilterDOM;
	IXMLDOMDocumentPtr pElementDefinitionDOM;
	CString el_name;
};

#endif // !defined(AFX_AELINFO_H__0974EB59_93DF_4180_9E7B_8B12A39E63F5__INCLUDED_)
