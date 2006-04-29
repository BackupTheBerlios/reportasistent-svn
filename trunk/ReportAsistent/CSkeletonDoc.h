// CSkeletonDoc.h : interface of the CSkeletonDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CSKELETONDOC_H__AF6E6924_ED51_4710_9D19_8B36BB8CCF94__INCLUDED_)
#define AFX_CSKELETONDOC_H__AF6E6924_ED51_4710_9D19_8B36BB8CCF94__INCLUDED_

//#include "SkeletonManager.h"	// Added by ClassView
//#include "SkeletonView.h"		// nepridavat znamena cyklicky include -honza
class CSkeletonView;



#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSkeletonDoc : public CDocument
{
protected: // create from serialization only
	CSkeletonDoc();
	DECLARE_DYNCREATE(CSkeletonDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkeletonDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
//	CSkeletonManager m_SkeletonManager;

	void FillTreeControl(CTreeCtrl & tree_control);
	virtual ~CSkeletonDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
public:
	IXMLDOMElement * ElementFromItemData(LPARAM item_data);
protected:
	CSkeletonView * GetFirstView();
	//{{AFX_MSG(CSkeletonDoc)
	afx_msg void OnElementEdit();
	afx_msg void OnMmgenrep();
	//}}AFX_MSG
	afx_msg void OnMmnewelement(UINT nMessageID);
	DECLARE_MESSAGE_MAP()

public:
	static void InsertNodeToTreeCtrl(MSXML2::IXMLDOMElementPtr pElement, 
									HTREEITEM hParentItem, 
									CTreeCtrl  & tree_control, HTREEITEM hInsertAfter = TVI_LAST);
private:
	MSXML2::IXMLDOMDocumentPtr m_pXMLDom;

protected:
	static CElementManager::elId_t ElementIdFromCommandId(UINT command);
	static LPARAM CreateItemData(IXMLDOMElementPtr & element);
	void ConfigureFilter(IXMLDOMElementPtr & active_element);
	BOOL EditElement(IXMLDOMElementPtr selected_element);
	BOOL EditActiveElement(IXMLDOMElementPtr &element);
	IXMLDOMElementPtr InsertNewElement(CElementManager::elId_t elementID, IXMLDOMElementPtr & parent_element);
	IXMLDOMElementPtr InsertNewElement(LPCTSTR element_name, IXMLDOMElementPtr & parent_element);
	
	void GenerTransform1(IXMLDOMElementPtr & doc);
	void Transform1Element(IXMLDOMElementPtr & element); //rekurzivni
	void TransformActiveElement(IXMLDOMElementPtr & element);

	
public:
	BOOL IsDescendantOfElement(IXMLDOMElementPtr pDescendantXMLElm,IXMLDOMElementPtr pAncestorXMLElm);
	void ChangeIDsInTree(IXMLDOMElementPtr pXMLElm);
	void Generate();
	CString CreateNewID(CElementManager::elId_t element_type);
	static void DeleteItemData(LPARAM data);




};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSKELETONDOC_H__AF6E6924_ED51_4710_9D19_8B36BB8CCF94__INCLUDED_)
