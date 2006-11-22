// SkeletonView.h : interface of the CSkeletonView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKELETONVIEW_H__7EE68070_62BF_4C22_A2E1_57F1897D226D__INCLUDED_)
#define AFX_SKELETONVIEW_H__7EE68070_62BF_4C22_A2E1_57F1897D226D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//Iva: Definition of constants for OnUpdate(), its lHint parameter
#ifndef UT_DEL
	#define UT_DEL 1
#endif
#ifndef UT_INS
	#define UT_INS 2
#endif
#ifndef UT_EDIT
	#define UT_EDIT 3
#endif

//Iva: Definition of class for OnUpdate(), its pHint parameter
class CUT_Hint : public CObject
{
public:
	HTREEITEM pTreeItem;
	MSXML2::IXMLDOMElementPtr pElement;
	HTREEITEM pInsertAfter;

	CUT_Hint()
	{
		pTreeItem = NULL;
		pElement= NULL;
		pInsertAfter= TVI_LAST;
	}

	CUT_Hint(HTREEITEM a, MSXML2::IXMLDOMElementPtr b, HTREEITEM c )
	{
		pTreeItem = a;
		pElement= b;
		pInsertAfter= c;
	}
};



class CSkeletonView : public CTreeView
{
protected: // create from serialization only
	CSkeletonView();
	DECLARE_DYNCREATE(CSkeletonView)

// Attributes
public:
	CSkeletonDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkeletonView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL


// Implementation
public:
	void DeleteSelectedItem();
	CImageList m_ImageList;
	BOOL m_bDragging;
	CImageList* m_pimagelist;
	HTREEITEM m_hitemDrop;
	HTREEITEM m_hitemDrag;

	virtual ~CSkeletonView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSkeletonView)
	afx_msg void OnDeleteitem(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	afx_msg void OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnEditCut();
	afx_msg void OnMmdelete();
	afx_msg void OnCaptureChanged(CWnd *pWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void SignSingleOrphan(HTREEITEM item);
public:

	void SignOrphans(void);
public:
	afx_msg void OnSignOrphans();
};

#ifndef _DEBUG  // debug version in SkeletonView.cpp
inline CSkeletonDoc* CSkeletonView::GetDocument()
   { return (CSkeletonDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKELETONVIEW_H__7EE68070_62BF_4C22_A2E1_57F1897D226D__INCLUDED_)
