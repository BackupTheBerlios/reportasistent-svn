// CSkeletonDoc.h : interface of the CSkeletonDoc class
//
/////////////////////////////////////////////////////////////////////////////
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
#if !defined(AFX_CSKELETONDOC_H__AF6E6924_ED51_4710_9D19_8B36BB8CCF94__INCLUDED_)
#define AFX_CSKELETONDOC_H__AF6E6924_ED51_4710_9D19_8B36BB8CCF94__INCLUDED_

class CSkeletonView;


//#define DONT_CLONE_REPORT_BEFORE_GENERATE


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/**
 * class CSkeletonDoc: The class of every document of LM-RA application.
 *
 * @author 
 */
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
	BOOL InsertNewElementAndUpdateTreeCtrl( BOOL bEdit,CElementManager::elId_t el_what_id, HTREEITEM hParentItem,HTREEITEM hInsertAfter); 
	void FillTreeControl(CTreeCtrl & tree_control);
	virtual ~CSkeletonDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
public:
	static MSXML2::IXMLDOMElement * ElementFromItemData(LPARAM item_data);
protected:
	CSkeletonView * GetFirstView();
	//{{AFX_MSG(CSkeletonDoc)
	afx_msg void OnElementEdit();
	afx_msg void OnMmgenrep();
	afx_msg void OnDelOrphans();
	//}}AFX_MSG
	afx_msg void OnMmnewelement(UINT nMessageID);
	DECLARE_MESSAGE_MAP()

public:
	static HTREEITEM InsertNodeToTreeCtrl(MSXML2::IXMLDOMElementPtr pElement, 
									HTREEITEM hParentItem, 
									CTreeCtrl  & tree_control, HTREEITEM hInsertAfter = TVI_LAST);
private:
	MSXML2::IXMLDOMDocumentPtr m_pXMLDom;

public:
	static BOOL EditActiveElement(MSXML2::IXMLDOMElementPtr &element);
	static LPARAM CreateItemData(MSXML2::IXMLDOMElementPtr & element);
protected:
	BOOL InitAndClearXmlDom();
	BOOL OpenSkeletonFile(LPCTSTR file_name);
	void TransformAttrLinks(MSXML2::IXMLDOMElementPtr & element);
	static CElementManager::elId_t ElementIdFromCommandId(UINT command);
	BOOL EditElement(MSXML2::IXMLDOMElementPtr & selected_element);
	MSXML2::IXMLDOMElementPtr InsertNewElement(CElementManager::elId_t elementID, MSXML2::IXMLDOMElementPtr & parent_element);
	MSXML2::IXMLDOMElementPtr InsertNewElement(LPCTSTR element_name, MSXML2::IXMLDOMElementPtr & parent_element);
	
	void GenerTransform1(MSXML2::IXMLDOMElementPtr & doc);
	void TransformActiveElements(MSXML2::IXMLDOMElementPtr & element); //rekurzivni

	
public:
	BOOL IsIDInTree (CString Id, MSXML2::IXMLDOMElementPtr pTree);
	CString CreateNewIDFromOld(CString old_ID);
	BOOL IsIDInTree(CString Id);
	BOOL IsDescendantOfElement(MSXML2::IXMLDOMElementPtr pDescendantXMLElm,MSXML2::IXMLDOMElementPtr pAncestorXMLElm);
	void ChangeIDsInTree(MSXML2::IXMLDOMElementPtr pXMLElm);
	void Generate(BOOL new_word);
	CString CreateNewID(CElementManager::elId_t element_type);
	static void DeleteItemData(LPARAM data);




public:
	afx_msg void OnShowXml();
public:
	// renames (to new_publicID) ID of data source in each active element, which has current value of source old_publicID
	BOOL updateAElSourcePublicID(LPCTSTR old_publicID, LPCTSTR new_publicID);
public:
	// makes a list of "orphans" active elements in skeleton to pOrpList paramter, returns a number of orphans found
	int findOrphans(MSXML2::IXMLDOMNodeListPtr & pOrpList);
public:
	// finds list of all "orphans active elements" in skeleton and if supported, changes their datasources to default source. Returns number of updated elements 
	int changeOrphansDataSourceToDefault(void);
public:
	BOOL SetReportSettings(LPCTSTR attribute, LPCTSTR value);
	CString GetReportSettings(LPCTSTR attribute);
	afx_msg void OnResetOrphans();
public:
	static CString StrToHtml(CString sText);
public:
	static CString HtmlToStr(CString sHtml);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSKELETONDOC_H__AF6E6924_ED51_4710_9D19_8B36BB8CCF94__INCLUDED_)
