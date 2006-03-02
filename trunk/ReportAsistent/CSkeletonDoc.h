// CSkeletonDoc.h : interface of the CSkeletonDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CSKELETONDOC_H__AF6E6924_ED51_4710_9D19_8B36BB8CCF94__INCLUDED_)
#define AFX_CSKELETONDOC_H__AF6E6924_ED51_4710_9D19_8B36BB8CCF94__INCLUDED_

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
	//}}AFX_VIRTUAL

// Implementation
public:
	void FillTreeControl(CTreeCtrl & tree_control);
	virtual ~CSkeletonDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSkeletonDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	static void InsetNodeToTreeCtrl(MSXML2::IXMLDOMNodePtr iNode, HTREEITEM hParentItem, CTreeCtrl  & tree_control);
	MSXML2::IXMLDOMDocumentPtr m_XMLDOMDoc;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSKELETONDOC_H__AF6E6924_ED51_4710_9D19_8B36BB8CCF94__INCLUDED_)
