// CSkeletonDoc.cpp : implementation of the CSkeletonDoc class
//

#include "stdafx.h"
#include "ReportAsistent.h"

#include "CSkeletonDoc.h"
//#include "SkeletonManager.h" - uz je v headeru
#include "SkeletonView.h"
#include "GenerateDialog.h"
#include "simplefilterdialog.h"
#include "APTransform.h"
#include "ElementTextDialog.h"
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
} 

BOOL CSkeletonDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	HRESULT hr;

	if (m_pXMLDom != NULL) m_pXMLDom.Release();

	hr= m_pXMLDom.CreateInstance(_T("Msxml2.DOMDocument"));
	if (FAILED(hr)) 
	{
		//mozna prepsat pomoci string table?
		AfxGetMainWnd()->MessageBox("Failed to instantiate an XML DOM.", "error", MB_ICONERROR);
		return FALSE;
	}

	m_pXMLDom->async = VARIANT_FALSE; // default - true,

	
	
	//vytvor prazny report
//	CGeneralManager * m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager;

	//by bylo fajn, ale pak tam neni DTD
	//pXMLDom->appendChild(m->ElementManager.CreateEmptyElement(elId_t_REPORT));

	//docasne reseni:
	CDirectoriesManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->DirectoriesManager;
	m_pXMLDom->load((LPCTSTR) (m.getXMLFilesDirectory() + "/prazdny.xml"));
	if (m_pXMLDom->parseError->errorCode != S_OK)
	{
			AfxMessageBox(m_pXMLDom->parseError->reason);
			return FALSE;
	}



	return TRUE;
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
	
	HRESULT hr;

	hr= m_pXMLDom.CreateInstance(_T("Msxml2.DOMDocument"));
	if (FAILED(hr)) 
	{
		//mozna prepsat pomoci string table?
		AfxGetMainWnd()->MessageBox("Failed to instantiate an XML DOM.", "error", MB_ICONERROR);
		return FALSE;
	}

	m_pXMLDom->async = VARIANT_FALSE; // default - true,

	if(m_pXMLDom->load((LPCTSTR) lpszPathName) != VARIANT_TRUE)
	{

		CString s;
		CString errstr( (BSTR) m_pXMLDom->parseError->Getreason());

		//mozna prepsat pomoci string table?
		s.Format("\nError in XML file reading.\n%s", lpszPathName);

		errstr += s;

		AfxGetMainWnd()->MessageBox(errstr, "error", MB_ICONERROR);

		return FALSE;
	}


	return TRUE;
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
//dedek: nova verze
/****/	
	if (pElement == NULL) return;

	HTREEITEM hTreeItem=NULL;
	CElementManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;

	CElementManager::elId_t el_id = m.IdentifyElement(pElement);
	
	hTreeItem = tree_control.InsertItem(m.CreateElementCaption(pElement), el_id, el_id, hParentItem, hInsertAfter);

	tree_control.SetItemData(hTreeItem, CreateItemData(pElement));

	
	//u kterych elementu nebude videt vnitrek
	if (m.isElementActive(el_id) || (el_id == ELID_ATTR_LINK_TABLE)) return;
	
	
	//rekurnetne projede deti;
	IXMLDOMNodeListPtr pChildren = pElement->childNodes;//ukazatel na potomky pElementu
	IXMLDOMNodePtr pChild = NULL;
	while ((pChild = pChildren->nextNode()) != NULL)
	{

		InsertNodeToTreeCtrl(pChild, hTreeItem, tree_control);
	}

	tree_control.Expand(hTreeItem, TVE_EXPAND);


/******
dedek: stara verze	
	
	
	//pridal honza
	if (pElement == NULL) return;
	
	
	
	MSXML2::IXMLDOMNodeListPtr pChildren = pElement->childNodes;//ukazatel na potomky pElementu
	MSXML2::IXMLDOMNodePtr pChild = NULL;
	CString csElementType; //typ prvku XMLstromu: text/chapter/report/...
	char sTextValue [256]; //text ktery se stane jmenem polozky v CtrlTree
	HTREEITEM hTreeItem=NULL;
	BOOL bChildrenYes=TRUE; //urcuje, mohu-li potomky tohoto prvku vlozit do kostry 
							//..napr. chapter - ano, 4fthypoteza- ne.

	
		
		csElementType=(LPCTSTR)(pElement->baseName);

		//pridam prvek do TreeCtrl..pro typ prvku REPORT
		if (0==strcmp("report",csElementType))
		{
			hTreeItem = tree_control.InsertItem((LPCTSTR) (_bstr_t) csElementType,//text prvku TreeCtrl
													IDB_REPORTICO-IDB_BMTREEFIRST-1,//nImage
													IDB_REPORTICO-IDB_BMTREEFIRST-1,//nSelectedImage
													hParentItem);
		}
		else
			//pridam prvek do TreeCtrl..pro typ prvku TEXT:
					//<text value="Vysledky."/> 
			if (0==strcmp("text",csElementType))
			{

/**		prepsal honza
				_variant_t & Value = pElement->getAttribute("value");

				if (Value.vt == VT_NULL) 
/****

				_bstr_t & Value = pElement->text;
				if ((BSTR) Value == NULL) 					
					sprintf(sTextValue,"Text - empty");
				else
				{
					sprintf(sTextValue,"%.*s...",LENGTH_TREE_ITEM_NAME-3,(LPCTSTR) (_bstr_t) Value);
				}

				hTreeItem = tree_control.InsertItem(sTextValue,//text prvku TreeCtrl
													IDB_TEXTICO-IDB_BMTREEFIRST-1,//nImage
													IDB_TEXTICO-IDB_BMTREEFIRST-1,//nSelectedImage
													hParentItem);
			}
			else 
				//pridam prvek do TreeCtrl ..pro typ prvku CHAPTER:
					//<chapter title = "Muzi">
				if (0==strcmp("chapter",csElementType))
				{
					_variant_t & Value = pElement->getAttribute("title");

					if (Value.vt == VT_NULL) 
						sprintf(sTextValue,"Title - missing");
					else
					{
						sprintf(sTextValue,"%.*s...",LENGTH_TREE_ITEM_NAME-3,(LPCTSTR) (_bstr_t) Value);
					}

					hTreeItem = tree_control.InsertItem(sTextValue,//text prvku TreeCtrl
														IDB_CHAPTERICO-IDB_BMTREEFIRST-1,//nImage
														IDB_CHAPTERICO-IDB_BMTREEFIRST-1,//nSelectedImage
														hParentItem);
				}
				//pridam prvek do TreeCtrl ..pro typ prvku PARAGRAPH
				else
					if (0==strcmp("paragraph",csElementType))
					{
						hTreeItem = tree_control.InsertItem((LPCTSTR) (_bstr_t) csElementType,//text prvku TreeCtrl
														IDB_PARAGRAPHICO-IDB_BMTREEFIRST-1,//nImage
														IDB_PARAGRAPHICO-IDB_BMTREEFIRST-1,//nSelectedImage
														hParentItem);
					}
					else
				//pridam prvek do TreeCtrl ..pro typ prvku ACTIVE_ELEMENT
						if (0==strcmp("active_element",csElementType))
						{
							_variant_t & vtTypeActElm = pElement->getAttribute("type");
							if (0==strcmp("hyp_4ft",(LPCTSTR) (_bstr_t) vtTypeActElm))
							//pridam prvek do TreeCtrl ..pro typ prvku 4FT-HYPOTEZA
								/****<active_element type="hyp_4ft" source="honzova_metabaze" id="hyp_4ft1">
									<params/>
								
									<filter type="simple">
										<selection id="hyp1"/>
										<selection id="hyp3"/>
									</filter>
								
									<output>
										<transformation file="../4ft_generuj1.xsl"/>
										<transformation file="../4ft_generuj1.xsl"/>
									</output>
								</active_element>/*****
							{
								_variant_t & vtId = pElement->getAttribute("id");

								if (vtId.vt == VT_NULL) 
									sprintf(sTextValue,"Id - missing");
								else
								{
									sprintf(sTextValue,"%s",(LPCTSTR) (_bstr_t) vtId);
								}

								hTreeItem = tree_control.InsertItem(sTextValue,//text prvku TreeCtrl
																	IDB_4FTHYPOTEZAICO-IDB_BMTREEFIRST-1,//nImage
																	IDB_4FTHYPOTEZAICO-IDB_BMTREEFIRST-1,//nSelectedImage
																	hParentItem);
								bChildrenYes=FALSE; // potomci nemaji byt prvky kostry, protoze jsou to zalezitosti pro dialog 4fthypotezy.

							}
							else
							//pridam aktivni prvek do TreeCtrl..pro jiny typ prvku nez vyse uvedeny
							hTreeItem = tree_control.InsertItem((LPCTSTR) (_bstr_t) csElementType,//text prvku TreeCtrl
														IDB_UNKNOWNICO-IDB_BMTREEFIRST-1,//nImage
														IDB_UNKNOWNICO-IDB_BMTREEFIRST-1,//nSelectedImage
													hParentItem);


						}
						//pridam prvek do TreeCtrl..pro jiny typ prvku nez vyse uvedeny
						else
							hTreeItem = tree_control.InsertItem((LPCTSTR) (_bstr_t) csElementType,//text prvku TreeCtrl
														IDB_UNKNOWNICO-IDB_BMTREEFIRST-1,//nImage
														IDB_UNKNOWNICO-IDB_BMTREEFIRST-1,//nSelectedImage
													hParentItem);


		pElement.AddRef();

		//ukazu TV_ITEM.lParam na odpovidajici uzel XML stromu

		
		tree_control.SetItemData(hTreeItem, CreateItemData(pElement));


	while (bChildrenYes && (pChild = pChildren->nextNode()) != NULL)
	{

		//rekurze
		InsetNodeToTreeCtrl(pChild, hTreeItem, tree_control);
	}

  /*****/

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

	
	
	IXMLDOMElementPtr edited_element = ElementFromItemData(tree.GetItemData(tree.GetSelectedItem()));

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

IXMLDOMElement * CSkeletonDoc::ElementFromItemData(LPARAM item_data)
{
		return (MSXML2::IXMLDOMElement *) item_data;
}


//pokusi se vlozit novy element jako child parent_element uzlu, novy element vrati
//nenastuvuje ModifiedFlag, neprekresluje
IXMLDOMElementPtr CSkeletonDoc::InsertNewElement(CElementManager::elId_t elementID, IXMLDOMElementPtr & parent_element)
{
	CGeneralManager * m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager;

	
	IXMLDOMElementPtr new_example = m->ElementManager.CreateEmptyElement(elementID);

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
			//AfxMessageBox(e.ErrorMessage());
			AfxMessageBox(e.Description());
		}

	}
		
	
	AfxMessageBox(IDS_INSERT_NEW_ELEMENT_WRONG_LOCATION);	
	
	new_example.Release();
	
	return NULL;
}

//jen prelozi volani na metodu vyse
IXMLDOMElementPtr CSkeletonDoc::InsertNewElement(LPCTSTR element_name, IXMLDOMElementPtr & parent_element)
{

	CGeneralManager * pCGeneralManager = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager;

	return InsertNewElement(pCGeneralManager->ElementManager.ElementIdFromName(element_name), parent_element);

}

//vytvori novy id string pro eletment typu element_type
CString CSkeletonDoc::CreateNewID(CElementManager::elId_t element_type)
{
	
	LPCTSTR el_name = //priradi nazev elementu z ElementManageru
		((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager.getElementName(element_type);

	CString id;

	for (int a = 1; a < 0xFFFFFF; a++) //vygeneruje maximalne 0xFFFFFF=16777215 ruznych id :-)
	{
		id.Format("%s%d", el_name, a); //napr.: id = "hyp_4ft15"

		
		//podivame se jestli uz dane id v kostre existuje:
		//zkusime prvek s takovym id najit moci XPath funkce id()
		
		CString query; 
		query.Format("id(\"%s\")", (LPCTSTR) id); //napr.: query = 'id("hyp_4ft15")'

		IXMLDOMNodePtr select = m_pXMLDom->selectSingleNode((LPCTSTR) query);
		if (select == NULL) break; //kdyz to zadny uzel nenaslo tak id neni pouzite..
		else select.Release();
	}

	//pokud cyklus probehnul 16777215-krat, je to dost podezrele :-)
	ASSERT(a < 0xFFFFFF);

	return id;
}

//dedek: vrati TRUE pokud doslo ke zmene elementu
//nenastuvuje ModifiedFlag, neprekresluje
BOOL CSkeletonDoc::EditActiveElement(IXMLDOMElementPtr &element)
{
	CActiveElementDialog dlg(element, AfxGetMainWnd());


	return IDOK == dlg.DoModal();


//		ConfigureFilter(element);
}


//dedek: vrati TRUE pokud doslo ke zmene elementu
//nenastuvuje ModifiedFlag, neprekresluje
BOOL CSkeletonDoc::EditElement(IXMLDOMElementPtr selected_element)
{

	if (selected_element == NULL) return FALSE;

	//ziskej element
	//IXMLDOMElementPtr selected_element = ElementFromItemData(item_data);
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
			CElementTextDialog OElementTextDialog(AfxGetMainWnd());

			//Inicializuji promenne dialogu		
			OElementTextDialog.m_DialTextEditValue = (LPCTSTR) selected_element->text;

			//A dialog zobrazim
			UINT Res = OElementTextDialog.DoModal();
				
			if (Res == IDOK)
			{
				//Zmeny z dialogu soupnu do XMLDom stromu
				LPCTSTR sText= OElementTextDialog.m_DialTextEditValue; 
				selected_element->text=sText;
				return TRUE;
			}
			else
			{
				return FALSE;
			}
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
		AfxMessageBox(selected_element->xml);
		return FALSE;

	}

	
	
	//sem by to melo dojit
	ASSERT(FALSE);
	return FALSE;	
}

void CSkeletonDoc::ConfigureFilter(IXMLDOMElementPtr &active_element)
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
	IXMLDOMElement * np = (IXMLDOMElement *) data;

	if (np != NULL) np->Release();

}

LPARAM CSkeletonDoc::CreateItemData(IXMLDOMElementPtr & element)
{
	IXMLDOMElement * np = element;

	np->AddRef();

	return (LPARAM) np;
}








void CSkeletonDoc::Generate()
{
	IXMLDOMElementPtr doc_element;
	

#ifdef DONT_CLONE_REPORT_BEFORE_GENERATE
	doc_element = m_skeleton->documentElement;
#else
	//klonuje cely dokumnet
	doc_element = m_pXMLDom->documentElement->cloneNode(VARIANT_TRUE);
#endif
	
	//provede transformace
	GenerTransform1(doc_element);

	

//	doc_element->save("../out.xml");

	
	
/*****///generovani do Wordu	

	HRESULT hr;
	
	LMRA_WordLoader::_LMRA_XML_WordLoaderPtr word;
	hr = word.CreateInstance(CLSID_LMRA_XML_WordLoader);

	if (S_OK != hr)
	{
		AfxMessageBox(IDS_WB_WORD_LOADER_NOT_REGISTRED);

		
		
		//dedek: pokusime se registrovat ActiveX objekt spustenim LMRA_WB_WordLoader s parametrem register
		STARTUPINFO si;
		ZeroMemory(& si, sizeof si);
		
		PROCESS_INFORMATION pi;
		ZeroMemory(& pi, sizeof pi);


		CDirectoriesManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->DirectoriesManager;

		BOOL ret = CreateProcess(m.getLMRA_WB_WordLoaderPath(), " register", NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, & si, & pi);
		if (! ret) 
		{
			return;
		}

		
		//pockame az spusteny process skonci
		DWORD wait_ret= WaitForSingleObject(pi.hProcess, 5000);
 		CloseHandle(pi.hProcess);

		if (wait_ret != WAIT_OBJECT_0) return;
	

		
		
		hr = word.CreateInstance(CLSID_LMRA_XML_WordLoader);
		if (S_OK != hr) return;
	}

	try
	{	
		word->LoadFromString(doc_element->xml);
	}
	catch (_com_error & e)
	{
		CString err = "Chyba pri generovani.\n\nposledni zpracovavane id:   ";
		err += word->GetstrLastProcessedId();
		err += "\n\n";
		err += word->GetstrLastError();
		err += "\n";
		err += e.Description();
		err += "\n";
		err += e.ErrorMessage();
		AfxMessageBox(err);
	}

	word.Release();
/******/

}


//tahle metoda asi prijde zrusit
void CSkeletonDoc::GenerTransform1(IXMLDOMElementPtr & doc)
{
	TransformActiveElements(doc);
	AfxMessageBox(doc->xml);
	
	TransformAttrLinks(doc);
	AfxMessageBox(doc->xml);
}



//rekurzivni
void CSkeletonDoc::TransformActiveElements(IXMLDOMElementPtr & element)
{
	if (element == NULL) return;

	CElementManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;


	if (m.isElementActive(m.IdentifyElement(element)))
	{
		TransformActiveElement(element);
	}
	else
	{
		IXMLDOMNodeListPtr iChildren = element->childNodes;

		IXMLDOMElementPtr iChild = NULL;

		while ((iChild = iChildren->nextNode()) != NULL)
		{
			
			//rekurze
			TransformActiveElements(iChild);
		}
	}
	
}

void CSkeletonDoc::TransformActiveElement(IXMLDOMElementPtr & element)
{

	CAElTransform tr(element);
	tr.DoAllTransnformations();


//honza: ladici - lze pouzit pro generovani preview
/***
	IXMLDOMElementPtr klon = element->cloneNode(VARIANT_TRUE);

	CAPTransform tr(klon, * this);

	AfxMessageBox(tr.DoAllTransnformations()->xml);

	klon.Release();

/***/
}

//DEL void CSkeletonDoc::OnMmdelete() 
//DEL {
//DEL 	CTreeCtrl & hTreeCtrl = GetFirstView()->GetTreeCtrl();
//DEL 	
//DEL 	HTREEITEM hSelTreeItem = hTreeCtrl.GetSelectedItem();
//DEL 
//DEL 	IXMLDOMElementPtr selected_element = ElementFromItemData(hTreeCtrl.GetItemData( hSelTreeItem ));
//DEL 	
//DEL 	IXMLDOMElementPtr parent_element= selected_element->parentNode;
//DEL 
//DEL 
//DEL 	parent_element->removeChild(selected_element);
//DEL 
//DEL 	if (0 == hTreeCtrl.DeleteItem(hSelTreeItem))
//DEL 	{
//DEL 		AfxMessageBox("Smazani prvku z TreeCtrl se nepovedlo.",0,0);
//DEL 		return;
//DEL 	}
//DEL 	
//DEL 
//DEL 	SetModifiedFlag();		
//DEL 	UpdateAllViews(NULL);
//DEL }


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

	IXMLDOMElementPtr selected_element = ElementFromItemData(hTreeCtrl.GetItemData( hSelTreeItem ));	

	CElementManager::elId_t el_id = ElementIdFromCommandId(nMessageID);
	if (el_id == ELID_UNKNOWN) return;

	
	
	IXMLDOMElementPtr new_element = InsertNewElement(el_id, selected_element);
	if (new_element != NULL) //tj. pridani se zdarilo
	{
		if (EditElement(new_element))
		{
			SetModifiedFlag();
			UpdateAllViews(NULL);
		}
		else
		{
			//pokud uspene neprobhla editace, element se z kostry smaze
			new_element->parentNode->removeChild(new_element);
		}

		new_element.Release();
	}

	
	selected_element.Release();
}

/*
void CSkeletonDoc::OnMmnewelement(UINT nMessageID) 
{
	CTreeCtrl & hTreeCtrl = GetFirstView()->GetTreeCtrl();
	
	HTREEITEM hSelTreeItem = hTreeCtrl.GetSelectedItem();

	IXMLDOMElementPtr selected_element = ElementFromItemData(hTreeCtrl.GetItemData( hSelTreeItem ));	
	
	CElementManager & OElementManager = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;

	IXMLDOMElementPtr new_element = NULL;

	//zobrazi zpravu s typem vybraneho elementu
	//honza: ladici klidne zakomentujte
	/****
	CElementManager::elId_t id = OElementManager.IdentifyElement(selected_element);
	AfxMessageBox(OElementManager->getElementName(id));
	/***//*

	if (nMessageID < ID_MMNEWSTATICFIRST)
	{	//CHYBA!!
		AfxMessageBox(IDS_WRONG_TYPEELEMENTID,0,0);
	}
		
	//pridavany prvek je STATIC
	if ((nMessageID >= ID_MMNEWSTATICFIRST) && (nMessageID <= ID_MMNEWSTATICLAST))
	{
		new_element = InsertNewElement(
			OElementManager.getElementName(nMessageID - ID_MMNEWSTATICFIRST+ OElementManager.getFirstStaticElementID()),
			selected_element);
		if (new_element != NULL) //tj. pridani se zdarilo
		{
			EditElement(new_element); 
			
			SetModifiedFlag();		
			
			//dedek: v medode EditElement se tez vola UpdateAllViews, tedy jesm tohle zakomentoval
			//UpdateAllViews(NULL, (LPARAM) (IXMLDOMElement *) new_element);
		}
	}
	//pridavany prvek je ACTIVE
	if (nMessageID >= ID_MMNEWACTIVEFIRST)
	{
		new_element = InsertNewElement(
			OElementManager.getElementName(nMessageID - ID_MMNEWACTIVEFIRST+ OElementManager.getFirstActiveElementID()),
			selected_element);
		if (new_element != NULL) //tj. pridani se zdarilo
		{
			EditActiveElement(new_element); 
			
			SetModifiedFlag();		
			UpdateAllViews(NULL, (LPARAM) (IXMLDOMElement *) new_element);
		}

	}

	if (nMessageID >= ID_MMNEWACTIVELAST)
	{	//CHYBA!!
		AfxMessageBox(IDS_WRONG_TYPEELEMENTID,0,0);
	}	
}
*/

void CSkeletonDoc::ChangeIDsInTree(IXMLDOMElementPtr pElm)
{
	if (pElm == NULL) return;

	CElementManager & OElementManager = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;	
	IXMLDOMNodeListPtr pChildren = pElm->childNodes;//ukazatel na potomky pElm
	IXMLDOMNodePtr pChild = NULL;

	

	while ((pChild = pChildren->nextNode()) != NULL)
	{

		ChangeIDsInTree(pChild);
	}
//zjistim soucasnou hodnotu atributu id. Pokud prvek takovy atribut nema, skoncim.
	_variant_t varAtr = pElm->getAttribute("id");
	if (VT_NULL == varAtr.vt) return;

//zjistim id typu prvku a zmenim id prvku.
	CElementManager::elId_t idTypeElm = OElementManager.IdentifyElement(pElm);
	pElm->setAttribute("id",(LPCTSTR)CreateNewID(idTypeElm));	
	return;
}



BOOL CSkeletonDoc::IsDescendantOfElement(IXMLDOMElementPtr pDescendantXMLElm, IXMLDOMElementPtr pAncestorXMLElm)
{
	BOOL bDescInAnc=FALSE;
	IXMLDOMElementPtr pTop=m_pXMLDom->GetdocumentElement();

	while ((pTop!=pDescendantXMLElm)&& !(bDescInAnc= (pDescendantXMLElm==pAncestorXMLElm)))
		pDescendantXMLElm = pDescendantXMLElm->GetparentNode();

	return (bDescInAnc);

}

void CSkeletonDoc::TransformAttrLink(IXMLDOMElementPtr &element)
{
	CElementManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;

	IXMLDOMElementPtr txt_elem = m.CreateEmptyElement(ELID_TEXT);
	
	//nastav style
	_variant_t vt_style = element->getAttribute("style");
	if (vt_style.vt != VT_NULL)
	{
		IXMLDOMAttributePtr style_attr = element->ownerDocument->createAttribute("style");
		style_attr->text = (_bstr_t) vt_style;
		txt_elem->setAttributeNode(style_attr);
		style_attr.Release();
	}

	
	//ziskej hodnotu attribut
	CString query;
	query.Format("id(\"%s\")/attributes/element_attributes/attribute[@name = \"%s\"]/@value",
		(LPCTSTR) (_bstr_t) element->getAttribute("target"),
		(LPCTSTR) (_bstr_t) element->getAttribute("attr_name"));

	IXMLDOMNodePtr value_node = element->ownerDocument->selectSingleNode((LPCTSTR) query);

	AfxMessageBox(value_node->xml);

	if (value_node != NULL)
	{
		txt_elem->text = value_node->text;
		value_node.Release();
	}

	element->parentNode->replaceChild(txt_elem, element);
}

void CSkeletonDoc::TransformAttrLinkTable(IXMLDOMElementPtr &element)
{

}

//rekurzivni
void CSkeletonDoc::TransformAttrLinks(IXMLDOMElementPtr &element)
{
	if (element == NULL) return;

	CElementManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;

	CElementManager::elId_t el_id = m.IdentifyElement(element);

	switch (el_id)
	{
	case ELID_ATTR_LINK:
		TransformAttrLink(element);
		break;

	case ELID_ATTR_LINK_TABLE:
		TransformAttrLinkTable(element);
		break;

	default:
		IXMLDOMNodeListPtr iChildren = element->childNodes;
		IXMLDOMElementPtr iChild = NULL;

		while ((iChild = iChildren->nextNode()) != NULL)
		{
			//rekurze
			TransformAttrLinks(iChild);
		}
	}

}
