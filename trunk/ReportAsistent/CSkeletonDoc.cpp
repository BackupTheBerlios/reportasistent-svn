// CSkeletonDoc.cpp : implementation of the CSkeletonDoc class
//

#include "stdafx.h"
#include "ReportAsistent.h"

#include "CSkeletonDoc.h"
//#include "SkeletonManager.h" - uz je v headeru
#include "SkeletonView.h"
#include "GenerateDialog.h"
#include "simplefilterdialog.h"
#include "ElementTextDialog.h"
#include "ElementParagraphDialog.h"
#include "ElementChapterDialog.h"
#include "ElementReportDialog.h"
#include "ActiveElementDialog.h"
#include "AttributeLinkDialog.h"
#include "AttributeLinkTableDialog.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CSkeletonDoc

IMPLEMENT_DYNCREATE(CSkeletonDoc, CDocument)

BEGIN_MESSAGE_MAP(CSkeletonDoc, CDocument)
	//{{AFX_MSG_MAP(CSkeletonDoc)
	ON_COMMAND(ID_ELEMENT_EDIT, OnElementEdit)
	ON_COMMAND(ID_MMGENREP, OnMmgenrep)
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(ID_MMNEWSTATICFIRST, ID_MMNEWSTATICLAST, OnMmnewelement)
	ON_COMMAND_RANGE(ID_MMNEWACTIVEFIRST, ID_MMNEWACTIVELAST, OnMmnewelement)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkeletonDoc construction/destruction

CSkeletonDoc::CSkeletonDoc() /*: m_SkeletonManager(pXMLDom)*/
{
	// TODO: add one-time construction code here
//	srand( (unsigned)time( NULL ) );

}

CSkeletonDoc::~CSkeletonDoc()
{
	if (m_pXMLDom != NULL) m_pXMLDom.Release();
} 

BOOL CSkeletonDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	if (! InitAndClearXmlDom())
	{
		return FALSE;
	}

	return TRUE;
/*
	CDirectoriesManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->DirectoriesManager;

#ifdef _DEBUG
	return OpenSkeletonFile(m.getXMLFilesDirectory() + "/prazdny.xml");
#else	
	return OpenSkeletonFile(m.getXMLFilesDirectory() + "/reduk2.xml");
#endif
*/
}



/////////////////////////////////////////////////////////////////////////////
// CSkeletonDoc serialization

void CSkeletonDoc::Serialize(CArchive& ar)
{
	
	
	if (ar.IsStoring())
	{
		//honza: sem by se program nemel dostat - jinak prepisuje soubor po ulozeni
		ASSERT(FALSE);
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSkeletonDoc diagnostics

#ifdef _DEBUG
void CSkeletonDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSkeletonDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSkeletonDoc commands

BOOL CSkeletonDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	if (! InitAndClearXmlDom())
	{
		return FALSE;
	}
	
	return OpenSkeletonFile(lpszPathName);
}

void CSkeletonDoc::FillTreeControl(CTreeCtrl  & tree_control)
{
	MSXML2::IXMLDOMElementPtr pTopElement;

	tree_control.DeleteAllItems();

	// ukazu pTopElement na koren XMLDOM stromu  
	pTopElement = m_pXMLDom->GetdocumentElement();
	if (pTopElement == NULL)
	{
      AfxGetMainWnd()->MessageBox("Invalid top document node.","Invalid top document node.", MB_ICONERROR);
	  //(LPCSTR)pXMLDom->parseError->Getreason()); - popis chyby, TODO: nejlepe do logu chyb
	}
	//a naplnim TreeCtrl
	else
	{
		InsertNodeToTreeCtrl(pTopElement, TVI_ROOT, tree_control);
	}

	
}


void CSkeletonDoc::InsertNodeToTreeCtrl(MSXML2::IXMLDOMElementPtr pElement, 
									   HTREEITEM hParentItem, 
									   CTreeCtrl  & tree_control,
									   HTREEITEM hInsertAfter) //hInsertAfter = TVI_LAST
{
//dedek:

	if (pElement == NULL) return;

	HTREEITEM hTreeItem=NULL;
	CElementManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;

	CElementManager::elId_t el_id = m.IdentifyElement(pElement);
	
	hTreeItem = tree_control.InsertItem(m.CreateElementCaption(pElement), el_id, el_id, hParentItem, hInsertAfter);

	tree_control.SetItemData(hTreeItem, CreateItemData(pElement));

	
	//u kterych elementu nebude videt vnitrek
	if (m.isElementActive(el_id) || (el_id == ELID_ATTR_LINK_TABLE)) return;
	
	
	//rekurnetne projede deti;
	MSXML2::IXMLDOMNodeListPtr pChildren = pElement->childNodes;//ukazatel na potomky pElementu
	MSXML2::IXMLDOMNodePtr pChild = NULL;
	while ((pChild = pChildren->nextNode()) != NULL)
	{

		InsertNodeToTreeCtrl(pChild, hTreeItem, tree_control);
	}

	tree_control.Expand(hTreeItem, TVE_EXPAND);
}

//pridal honza
BOOL CSkeletonDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	m_pXMLDom->save(lpszPathName);

	SetModifiedFlag(FALSE);
	
	return TRUE;	//CDocument::OnSaveDocument(lpszPathName); - nepouzivat prepise nam soubor vyse
}


//pridal honza - vrati prvni view ve kterem je zobrazovan tento dokument
CSkeletonView * CSkeletonDoc::GetFirstView()
{
	POSITION pos = GetFirstViewPosition();
	return (CSkeletonView *) GetNextView( pos );
}

void CSkeletonDoc::OnElementEdit() 
{
	CTreeCtrl & tree = GetFirstView()->GetTreeCtrl();

	//dedek:
	if (tree.GetSelectedItem() == NULL) return;

	
	
	MSXML2::IXMLDOMElementPtr edited_element = ElementFromItemData(tree.GetItemData(tree.GetSelectedItem()));

	if (EditElement(edited_element))
	{
		SetModifiedFlag();
		UpdateAllViews(NULL);
	}

}

void CSkeletonDoc::OnMmgenrep() 
{
	CGenerateDialog dlg(* this, AfxGetMainWnd());
	
	//pozor vlastni kod generovani je ve CSkeletonManager::Generate()
	dlg.DoModal();


//zobrazi vysledek transformaci v kostre
#ifdef DONT_CLONE_REPORT_BEFORE_GENERATE
	UpdateAllViews(NULL);
#endif
}

MSXML2::IXMLDOMElement * CSkeletonDoc::ElementFromItemData(LPARAM item_data)
{
		return (MSXML2::IXMLDOMElement *) item_data;
}


//pokusi se vlozit novy element jako child parent_element uzlu, novy element vrati
//nenastuvuje ModifiedFlag, neprekresluje
MSXML2::IXMLDOMElementPtr CSkeletonDoc::InsertNewElement(CElementManager::elId_t elementID, MSXML2::IXMLDOMElementPtr & parent_element)
{
	CGeneralManager * m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager;

	
	MSXML2::IXMLDOMElementPtr new_example = m->ElementManager.CreateEmptyElement(elementID);

	if (m->ElementManager.CanInsertChildHere(new_example, parent_element))
	{
		//ladici
		//AfxMessageBox(new_example->xml);	
		//AfxMessageBox(parent_element->xml);	
		
		
		//a tohle je sranda nejvetsi :-) hazi to chyby jak na bezicim pasu
		//kontroluje to tozi DTD dokumentu tak bacha, nejde vsecko vsude vlozit
		//az bude funkcni CanInsertChildHere tak by uz chyby nemely nastat
		try
		{
			parent_element->appendChild(new_example);
			return new_example;

		}
		catch (_com_error &e)
		{
			//ladici
			AfxMessageBox(e.Description());
		}

	}
		
	
	CReportAsistentApp::ReportError(IDS_INSERT_NEW_ELEMENT_WRONG_LOCATION);	
	
	new_example.Release();
	
	return NULL;
}

//jen prelozi volani na metodu vyse
MSXML2::IXMLDOMElementPtr CSkeletonDoc::InsertNewElement(LPCTSTR element_name, MSXML2::IXMLDOMElementPtr & parent_element)
{

	CGeneralManager * pCGeneralManager = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager;

	return InsertNewElement(pCGeneralManager->ElementManager.ElementIdFromName(element_name), parent_element);

}

//vytvori novy id string pro element typu element_type
CString CSkeletonDoc::CreateNewID(CElementManager::elId_t element_type)
{
	
	LPCTSTR el_name = //priradi nazev elementu z ElementManageru
		((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager.getElementName(element_type);

	CString id;

	int a;
    for (a = 1; a < 0xFFFFFF; a++) //vygeneruje maximalne 0xFFFFFF=16777215 ruznych id :-)
	{
		id.Format("%s%d", el_name, a); //napr.: id = "hyp_4ft15"

		
		if ( ! IsIDInTree(id)) break;
	}

	//pokud cyklus probehnul 16777215-krat, je to dost podezrele :-)
	ASSERT(a < 0xFFFFFF);

	return id;
}

//dedek: vrati TRUE pokud doslo ke zmene elementu
//nenastuvuje ModifiedFlag, neprekresluje
BOOL CSkeletonDoc::EditActiveElement(MSXML2::IXMLDOMElementPtr &element)
{
	CActiveElementDialog dlg(element, AfxGetMainWnd());


	return IDOK == dlg.DoModal();


//		ConfigureFilter(element);
}


//dedek: vrati TRUE pokud doslo ke zmene elementu
//nenastuvuje ModifiedFlag, neprekresluje
BOOL CSkeletonDoc::EditElement(MSXML2::IXMLDOMElementPtr selected_element)
{

	if (selected_element == NULL) return FALSE;

	//ziskej element
	//MSXML2::IXMLDOMElementPtr selected_element = ElementFromItemData(item_data);
	//ziskej manager
	CElementManager & OElementManager = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;
	//ziskej typ elementu
	CElementManager::elId_t selected_elementTypeId = OElementManager.IdentifyElement(selected_element);

	

	
	//jedna se o aktivni prvek?
	if (OElementManager.isElementActive(selected_elementTypeId))
	{
		return EditActiveElement(selected_element);
	}


	//dedek:
	switch(selected_elementTypeId)
	{
	case  ELID_TEXT:
		{
			//Vytvorim instanci dialogu pro Prvek Text
			CElementTextDialog OElementTextDialog(selected_element,AfxGetMainWnd());
			UINT Res= OElementTextDialog.DoModal() ;
			if (Res == IDOK)
			{
			//Zmeny z dialogu soupnu do XMLDom stromu
				//Id:
				selected_element->setAttribute("id",(LPCTSTR) OElementTextDialog.m_DialTextIDEditValue);		
				//Title:
				selected_element->text=(LPCTSTR) OElementTextDialog.m_DialTextEditValue;
			}
			//dedek: ma vratit TRUE pokud doslo ke zmene elementu, tedy spravne je to takhle:
			return Res == IDOK;
			//return Res;

		}

	case  ELID_PARAGRAPH:
		{
			//Vytvorim instanci dialogu pro Prvek Chapter
			CElementParagraphDialog OElementParagraphDialog(selected_element,AfxGetMainWnd());
			UINT Res= OElementParagraphDialog.DoModal() ;
			if (Res == IDOK)
			{
			//Zmeny z dialogu soupnu do XMLDom stromu
				//Id:
				selected_element->setAttribute("id",(LPCTSTR) OElementParagraphDialog.m_DialParagraphIDEditValue);		
			}
			return Res == IDOK;
			//return Res;


		}
	
	case  ELID_CHAPTER:
		{
			//Vytvorim instanci dialogu pro Prvek Chapter
			CElementChapterDialog OElementChapterDialog(selected_element,AfxGetMainWnd());
			UINT Res= OElementChapterDialog.DoModal() ;
			if (Res == IDOK)
			{
			//Zmeny z dialogu soupnu do XMLDom stromu
				//Id:
				selected_element->setAttribute("id",(LPCTSTR) OElementChapterDialog.m_DialChapterIDEditValue);		
				//Title:
				selected_element->setAttribute("title",(LPCTSTR) OElementChapterDialog.m_DialChapterTitleEditValue);
			}
			return Res == IDOK;
			//return Res;

		}
	case  ELID_REPORT:
		{
			//Vytvorim instanci dialogu pro Prvek Report
			CElementReportDialog OElementReportDialog(selected_element,AfxGetMainWnd());
			UINT Res= OElementReportDialog.DoModal() ;
			if (Res == IDOK)
			{
			//Zmeny z dialogu soupnu do XMLDom stromu
				//Id:
				selected_element->setAttribute("id",(LPCTSTR) OElementReportDialog.m_DialReportIDEditValue);		
				//Title:
				selected_element->setAttribute("title",(LPCTSTR) OElementReportDialog.m_DialReportTitleEditValue);
				//Subtitle:
				selected_element->setAttribute("subtitle",(LPCTSTR) OElementReportDialog.m_DialReportSubtitleEditValue);
				//Author:
				selected_element->setAttribute("author",(LPCTSTR) OElementReportDialog.m_DialReportAuthorEditValue);
			}
			return Res == IDOK;
			//return Res;

		}
	
	case ELID_ATTR_LINK:
		{
			CAttributeLinkDialog dlg(selected_element, AfxGetMainWnd());
			return dlg.DoModal() == IDOK;
		}

	case ELID_ATTR_LINK_TABLE:
		{
			CAttributeLinkTableDialog dlg(selected_element, AfxGetMainWnd());
			return dlg.DoModal() == IDOK;
		}

	default:
		//ostatni prvky
		return IDOK == AfxMessageBox(selected_element->xml, MB_OKCANCEL);		

	}

	
	
	//sem by to melo dojit
	ASSERT(FALSE);
	return FALSE;	
}

void CSkeletonDoc::ConfigureFilter(MSXML2::IXMLDOMElementPtr &active_element)
{
	//sem prijdou i jiny fitry
	
	//dialog prepise active_element podle uzivatelovy volby
	CSimpleFilterDialog dlg(active_element, /*
		GetPluginOutput((_bstr_t) active_element->getAttribute("source"),
						(_bstr_t) active_element->getAttribute("type")),*/
		AfxGetMainWnd());

	int nResponse = dlg.DoModal();	

}

void CSkeletonDoc::DeleteItemData(LPARAM data)
{
	MSXML2::IXMLDOMElement * np = (MSXML2::IXMLDOMElement *) data;

	if (np != NULL) np->Release();

}

LPARAM CSkeletonDoc::CreateItemData(MSXML2::IXMLDOMElementPtr & element)
{
	MSXML2::IXMLDOMElement * np = element;

	np->AddRef();

	return (LPARAM) np;
}


void CSkeletonDoc::Generate()
{
	MSXML2::IXMLDOMElementPtr doc_element;
	

#ifdef DONT_CLONE_REPORT_BEFORE_GENERATE
	doc_element = m_pXMLDom->documentElement;
#else
	//klonuje cely dokumnet
	doc_element = m_pXMLDom->documentElement->cloneNode(VARIANT_TRUE);
#endif
	
	//provede transformace
	GenerTransform1(doc_element);

	

//	doc_element->save("../out.xml");

	
//generovani do Wordu

	CWordManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->WordManager;
	m.GenerateXMLString(doc_element->xml);
}


//tahle metoda asi prijde zrusit
void CSkeletonDoc::GenerTransform1(MSXML2::IXMLDOMElementPtr & doc)
{
	TransformActiveElements(doc);
//	AfxMessageBox(doc->xml);
	
	TransformAttrLinks(doc);
//	AfxMessageBox(doc->xml);
}



//rekurzivni
void CSkeletonDoc::TransformActiveElements(MSXML2::IXMLDOMElementPtr & element)
{
	if (element == NULL) return;

	CElementManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;


	if (m.isElementActive(m.IdentifyElement(element)))
	{
		m.TransformActiveElement(element);
	}
	else
	{
		MSXML2::IXMLDOMNodeListPtr iChildren = element->childNodes;

		MSXML2::IXMLDOMElementPtr iChild = NULL;

		while ((iChild = iChildren->nextNode()) != NULL)
		{
			
			//rekurze
			TransformActiveElements(iChild);
		}
	}
	
}


//dedek:
CElementManager::elId_t CSkeletonDoc::ElementIdFromCommandId(UINT nMessageID)
{
	CElementManager & OElementManager = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;

	if ((nMessageID >= ID_MMNEWSTATICFIRST) && (nMessageID <= ID_MMNEWSTATICLAST))
		return nMessageID - ID_MMNEWSTATICFIRST + OElementManager.getFirstStaticElementID();

	if (nMessageID >= ID_MMNEWACTIVEFIRST)
		return nMessageID - ID_MMNEWACTIVEFIRST + OElementManager.getFirstActiveElementID();


	return ELID_UNKNOWN;
}


//dedek: prislo mi to neprehledny a navic divne funkcni/nefunkcni (nektere elemnty se obevovaly jinde jine zas vubec)
//stara verze nize
void CSkeletonDoc::OnMmnewelement(UINT nMessageID) 
{
	CTreeCtrl & hTreeCtrl = GetFirstView()->GetTreeCtrl();
	HTREEITEM hSelTreeItem = hTreeCtrl.GetSelectedItem();
	if (hSelTreeItem == NULL) return;

	MSXML2::IXMLDOMElementPtr selected_element = ElementFromItemData(hTreeCtrl.GetItemData( hSelTreeItem ));	

	CElementManager::elId_t el_id = ElementIdFromCommandId(nMessageID);
	if (el_id == ELID_UNKNOWN) return;

	
	
	MSXML2::IXMLDOMElementPtr new_element = InsertNewElement(el_id, selected_element);
	if (new_element != NULL) //tj. pridani se zdarilo
	{
		if (EditElement(new_element))
		{
			SetModifiedFlag();
			UpdateAllViews(NULL);
		}
		else
		{
			//pokud editace neprobehla uspene, element se z kostry smaze
			new_element->parentNode->removeChild(new_element);
		}

		new_element.Release();
	}

	
	selected_element.Release();
}

void CSkeletonDoc::ChangeIDsInTree(MSXML2::IXMLDOMElementPtr pElm)
{
	if (pElm == NULL) return;

	CElementManager & OElementManager = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;	
	MSXML2::IXMLDOMNodeListPtr pChildren = pElm->childNodes;//ukazatel na potomky pElm
	MSXML2::IXMLDOMNodePtr pChild = NULL;

	

	while ((pChild = pChildren->nextNode()) != NULL)
	{

		ChangeIDsInTree(pChild);
	}
//zjistim soucasnou hodnotu atributu id. Pokud prvek takovy atribut nema, skoncim.
	_variant_t varAtr = pElm->getAttribute("id");
	if (VT_NULL == varAtr.vt) return;

//zjistim id typu prvku a zmenim id prvku.
	CElementManager::elId_t idTypeElm = OElementManager.IdentifyElement(pElm);
	CString new_ID=(LPCTSTR)CreateNewIDFromOld((LPCTSTR) (_bstr_t)varAtr);
	//nyni by jeste mohla byt kontrola, neni-li new_ID nekde ve vkladanem podstromu...
	//...to se ale diky tvorbe novych ID ze starych (ktera duplicitni urcite nebyla) nemuze stat.
	pElm->setAttribute("id",(LPCTSTR) new_ID);	
	return;
}



BOOL CSkeletonDoc::IsDescendantOfElement(MSXML2::IXMLDOMElementPtr pDescendantXMLElm, MSXML2::IXMLDOMElementPtr pAncestorXMLElm)
{
	BOOL bDescInAnc=FALSE;
	MSXML2::IXMLDOMElementPtr pTop=m_pXMLDom->GetdocumentElement();

	while ((pTop!=pDescendantXMLElm)&& !(bDescInAnc= (pDescendantXMLElm==pAncestorXMLElm)))
		pDescendantXMLElm = pDescendantXMLElm->GetparentNode();

	return (bDescInAnc);

}

//rekurzivni
void CSkeletonDoc::TransformAttrLinks(MSXML2::IXMLDOMElementPtr &element)
{
	if (element == NULL) return;

	CElementManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;

	CElementManager::elId_t el_id = m.IdentifyElement(element);

	//linky uvnitr aktivnich elementu se netransformuji
	if (m.isElementActive(el_id)) return;

	switch (el_id)
	{
	case ELID_ATTR_LINK:
		m.TransformAttrLink(element);
		break;

	case ELID_ATTR_LINK_TABLE:
		m.TransformAttrLinkTable(element);
		break;

	default:
		MSXML2::IXMLDOMNodeListPtr iChildren = element->childNodes;
		MSXML2::IXMLDOMElementPtr iChild = NULL;

		while ((iChild = iChildren->nextNode()) != NULL)
		{
			//rekurze
			TransformAttrLinks(iChild);
		}
	}

}



BOOL CSkeletonDoc::OpenSkeletonFile(LPCTSTR file_name)
{
	ASSERT (m_pXMLDom != NULL);
	ASSERT (m_pXMLDom->documentElement != NULL);

	BOOL ret = FALSE;

	MSXML2::IXMLDOMDocumentPtr open_doc;
	open_doc.CreateInstance(_T("Msxml2.DOMDocument"));
	open_doc->async = VARIANT_FALSE;

	if (VARIANT_TRUE == open_doc->load(file_name))
	{
		m_pXMLDom->replaceChild(open_doc->documentElement, m_pXMLDom->documentElement);

		MSXML2::IXMLDOMDocument2Ptr validator = m_pXMLDom;
		MSXML2::IXMLDOMParseErrorPtr err = validator->validate();

		if (err->errorCode == S_OK)
		{
			ret = TRUE;
		}
		else
		{
			CReportAsistentApp::ReportError(IDS_OPEN_FILE_FAILED, file_name, (LPCTSTR) err->reason);
		}

		err.Release();
		validator.Release();

	}
	else
	{
		CReportAsistentApp::ReportError(IDS_OPEN_FILE_FAILED, file_name, (LPCTSTR) open_doc->parseError->reason);
	}

	open_doc.Release();
	return ret;
}

BOOL CSkeletonDoc::InitAndClearXmlDom()
{
	HRESULT hr;

	if (m_pXMLDom != NULL) m_pXMLDom.Release();

	hr= m_pXMLDom.CreateInstance(_T("Msxml2.DOMDocument"));
	if (FAILED(hr)) 
	{
		CReportAsistentApp::ReportError(IDS_FAILED_CREATE_XML_DOM_INSTANCE);
		return FALSE;
	}

	m_pXMLDom->async = VARIANT_FALSE; // default - true,


	
	//nacti DTD
	
/***
	CDirectoriesManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->DirectoriesManager;
	m_pXMLDom->load((LPCTSTR) (m.getXMLFilesDirectory() + "/skeleton_DTD.xml"));
	if (m_pXMLDom->parseError->errorCode != S_OK)
	{
		CReportAsistentApp::ReportError(IDS_CREATE_NEW_FILE_FAILED, (LPCTSTR) m_pXMLDom->parseError->reason);
		return FALSE;
	}
/***/
	CElementManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;
	m.LoadSkeletonDTD(m_pXMLDom);


	
	return TRUE;
}

CString CSkeletonDoc::CreateNewIDFromOld(CString old_ID)
{
	CString id;

	int a;
    for (a = 1; a < 0xFFFFFF; a++) //vygeneruje maximalne 0xFFFFFF=16777215 ruznych id :-)
	{
		id.Format("%s%d", old_ID, a); //napr.: old_ID= "mojeID" a id = "mojeID15"

		
		if ( ! IsIDInTree(id)) break;
	}

	//pokud cyklus probehnul 16777215-krat, je to dost podezrele :-)
	ASSERT(a < 0xFFFFFF);

	return id;

}

BOOL CSkeletonDoc::IsIDInTree(CString Id)
{

	return IsIDInTree(Id, m_pXMLDom->documentElement);
		//podivame se jestli uz dane id v kostre existuje:
		//zkusime prvek s takovym id najit moci XPath funkce id()
/*		
		CString query; 
		query.Format("id(\"%s\")", (LPCTSTR) Id); //napr.: query = 'id("hyp_4ft15")'
		MSXML2::IXMLDOMNodePtr select = m_pXMLDom->selectSingleNode((LPCTSTR) query);
		if (select == NULL) return FALSE; //kdyz to zadny uzel nenaslo tak id neni pouzite..
		else //Iva:Id is used in the tree
		{
			select.Release();
			return TRUE;
		}
*/
}

BOOL CSkeletonDoc::IsIDInTree(CString Id, MSXML2::IXMLDOMElementPtr pTree)
{
		//podivame se jestli uz dane id v kostre existuje:
		//zkusime prvek s takovym id najit moci XPath funkce id()
		
		if (pTree==NULL) return FALSE;	

		CString query; 
		query.Format("//*[@id=\"%s\"]", (LPCTSTR) Id); //napr.: query = '//*[@id="hyp_4ft15"]'
		MSXML2::IXMLDOMNodePtr select = pTree->selectSingleNode((LPCTSTR) query);
		if (select == NULL) return FALSE; //kdyz to zadny uzel nenaslo tak id neni pouzite..
		else //Iva:Id is used in the tree
		{
			select.Release();
			return TRUE;
		}

}
