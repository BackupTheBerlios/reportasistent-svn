// SkeletonManager.h: interface for the CSkeletonManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKELETONMANAGER_H__170040CF_0F1F_44A9_BF89_B4468A97ACDD__INCLUDED_)
#define AFX_SKELETONMANAGER_H__170040CF_0F1F_44A9_BF89_B4468A97ACDD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DataSourceManager.h"
#include "ElementManager.h"

class CSkeletonManager  
{
public:
	void EditActiveElement(IXMLDOMElementPtr & element);
	CString CreateNewID(CElementManager::elId element_type);
	IXMLDOMElementPtr InsertNewElement(LPCTSTR element_name, IXMLDOMElementPtr & parent_element);
	IXMLDOMElementPtr InsertNewElement(CElementManager::elId elementID, IXMLDOMElementPtr & parent_element);
	IXMLDOMElement * ElementFromItemData(LPARAM item_data);
	static LPARAM CreateItemData(IXMLDOMElementPtr &);
	CSkeletonManager(IXMLDOMDocumentPtr & skeleton);

	void Generate();
	void EditElenemt(LPARAM item_data);
	void AddElement();
	void DeleteItemData(LPARAM data);
	void FillTreeCtrl(CTreeCtrl & tree_ctrl);
	virtual ~CSkeletonManager();
	static _bstr_t GetPluginOutput(CDataSorcesManager::public_source_id_t source, CDataSorcesManager::ap_id_t ap);

private:
	MSXML2::IXMLDOMDocumentPtr & m_skeleton;

	static void CSkeletonManager::RecurentTreeFill(CTreeCtrl &tree_ctrl, MSXML2::IXMLDOMNodePtr & iNode, HTREEITEM hParentItem);


protected:
	void TransformActiveElement(IXMLDOMElementPtr & element);
	void Transform1Node(IXMLDOMElementPtr & element);
	void GenerTransform1(IXMLDOMElementPtr & element);
	void ConfigureFilter(IXMLDOMElementPtr & active_element);
};

#endif // !defined(AFX_SKELETONMANAGER_H__170040CF_0F1F_44A9_BF89_B4468A97ACDD__INCLUDED_)
