// SkeletonView.h : interface of the CSkeletonView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKELETONVIEW_H__7EE68070_62BF_4C22_A2E1_57F1897D226D__INCLUDED_)
#define AFX_SKELETONVIEW_H__7EE68070_62BF_4C22_A2E1_57F1897D226D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//Kody:  definition of constants for ResolveOrphans() and ResolveSingleOrphan(), its mode parameter
	// delete orphans
#ifndef ORP_DELETE
	#define ORP_DELETE 1
#endif
	// sign orphans
#ifndef ORP_SIGN
	#define ORP_SIGN 2
#endif

// sign orphans
#ifndef ORP_UNSIGN
	#define ORP_UNSIGN 3
#endif

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
#ifndef UT_SETTINGS
	#define UT_SETTINGS 4
#endif
#ifndef UT_SOURCES
	#define UT_SOURCES 5
#endif


//Iva: Definition of class for OnUpdate(), its pHint parameter
/**
 * class CUT_Hint:
 *
 * @author 
 */
class CUT_Hint : public CObject
{
public:
	int iMarkOrphans;
	BOOL bNewItemTexts;
	HTREEITEM pTreeItem;
	MSXML2::IXMLDOMElementPtr pElement;
	HTREEITEM pInsertAfter;

	/**
	 * CUT_Hint:
	 *
	 * @return  
	 */
	CUT_Hint()
	{
		bNewItemTexts=false;
		iMarkOrphans = 0; // 0:no change, 2:mark orphans, 3:unmark orphans
		pTreeItem = NULL;
		pElement= NULL;
		pInsertAfter= TVI_LAST;
	}

	/**
	 * CUT_Hint:
	 *
	 * @param a 
	 * @param b 
	 * @param c 
	 * @return  
	 */
	CUT_Hint(HTREEITEM a, MSXML2::IXMLDOMElementPtr b, HTREEITEM c )
	{
		pTreeItem = a;
		pElement= b;
		pInsertAfter= c;
	}
};



/**
 * class CSkeletonView:
 *
 * @author 
 */
class CSkeletonView : public CTreeView
{
protected: // create from serialization only
	CSkeletonView();
	DECLARE_DYNCREATE(CSkeletonView)

// Attributes
public:
	/**
	 * GetDocument:
	 *
	 * @return CSkeletonDoc* 
	 */
	CSkeletonDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkeletonView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL


// Implementation
	
protected:
	/**
	 * DeleteItem:
	 *
	 * @param hSelTreeItem 
	 * @return void 
	 */
	void DeleteItem(HTREEITEM hSelTreeItem);

public:
	/**
	 * DeleteSelectedItem:
	 *
	 * @return void 
	 */
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
	/**
	 * UpdateAllItemTexts:
	 *
	 * @param pItem 
	 * @return void 
	 */
	void UpdateAllItemTexts(HTREEITEM pItem);
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

	void ResolveSingleOrphan(HTREEITEM item, LPARAM mode);
public:

	void ResolveOrphans(LPARAM mode);
public:
	afx_msg void OnSignOrphans();
public:
	afx_msg void OnDeleteOrphans();
};

#ifndef _DEBUG  // debug version in SkeletonView.cpp
inline CSkeletonDoc* CSkeletonView::GetDocument()
   { return (CSkeletonDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKELETONVIEW_H__7EE68070_62BF_4C22_A2E1_57F1897D226D__INCLUDED_)
