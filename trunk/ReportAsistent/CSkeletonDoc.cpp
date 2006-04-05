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
	ON_COMMAND(ID_MMDELETE, OnMmdelete)
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(ID_MMNEWSTATICFIRST, ID_MMNEWSTATICLAST, OnMmnewelement)
	ON_COMMAND_RANGE(ID_MMNEWACTIVEFIRST, ID_MMNEWACTIVELAST, OnMmnewelement)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkeletonDoc construction/destruction

CSkeletonDoc::CSkeletonDoc() /*: m_SkeletonManager(pXMLDom)*/
{
	// TODO: add one-time construction code here
	srand( (unsigned)time( NULL ) );

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
		InsetNodeToTreeCtrl(pTopElement, TVI_ROOT, tree_control);
	}

	
}


void CSkeletonDoc::InsetNodeToTreeCtrl(MSXML2::IXMLDOMElementPtr pElement, 
									   HTREEITEM hParentItem, 
									   CTreeCtrl  & tree_control)
{
//dedek: nova verze
/****/	
	if (pElement == NULL) return;

	HTREEITEM hTreeItem=NULL;
	CElementManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;

	CElementManager::elId_t el_id = m.IdentifyElement(pElement);
	
	hTreeItem = tree_control.InsertItem(m.CreateElementCaption(pElement), el_id, el_id, hParentItem);

	tree_control.SetItemData(hTreeItem, CreateItemData(pElement));

	
	//u kterych elementu nebude videt vnitrek
	if (m.isElementActive(el_id) || (el_id == ELID_ATTR_LINK_TABLE)) return;
	
	
	//rekurnetne projede deti;
	IXMLDOMNodeListPtr pChildren = pElement->childNodes;//ukazatel na potomky pElementu
	IXMLDOMNodePtr pChild = NULL;
	while ((pChild = pChildren->nextNode()) != NULL)
	{

		InsetNodeToTreeCtrl(pChild, hTreeItem, tree_control);
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
	
	
	IXMLDOMElementPtr edited_element = ElementFromItemData(tree.GetItemData(tree.GetSelectedItem()));

	EditElement(edited_element);

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

	id.Format("%s%d", el_name, rand());


	return id;
}

void CSkeletonDoc::EditActiveElement(IXMLDOMElementPtr &element)
{
	CActiveElementDialog dlg(element, AfxGetMainWnd());


	dlg.DoModal();	


//		ConfigureFilter(element);
}


//dedek: docasne - sem prijde volani spravnych edit dialogu
void CSkeletonDoc::EditElement(IXMLDOMElementPtr selected_element)
{

	if (selected_element == NULL) return;

	//ziskej element
	//IXMLDOMElementPtr selected_element = ElementFromItemData(item_data);
	//ziskej manager
	CElementManager & OElementManager = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;
	//ziskej typ elementu
	CElementManager::elId_t selected_elementTypeId = OElementManager.IdentifyElement(selected_element);

	

	
	//jedna se o aktivni prvek?
	if (OElementManager.isElementActive(selected_elementTypeId))
	{
		EditActiveElement(selected_element);
	}	
	// Iva: jedna se o prvek text?
	else if (selected_elementTypeId == ELID_TEXT)
	{
		
		//AfxMessageBox(selected_element->text);

		//Vytvorim instanci dialogu pro Prvek Text
			CElementTextDialog OElementTextDialog;

			//Inicializuji promenne dialogu		
			OElementTextDialog.m_DialTextEditValue = (LPCTSTR) selected_element->text;

			//A dialog zobrazim
			UINT Res = OElementTextDialog.DoModal();
			
			if (Res == IDOK)
			{
				//Zmeny z dialogu soupnu do XMLDom stromu
				LPCTSTR sText= OElementTextDialog.m_DialTextEditValue; 
				selected_element->text=sText;
				//Update TreeCtrl
				SetModifiedFlag();		
				UpdateAllViews(NULL, 0);
			}

	}
	else
	{	//ostatni prvky
		AfxMessageBox(selected_element->xml);
	}

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

		STARTUPINFO si;
		ZeroMemory(& si, sizeof si);
		
		PROCESS_INFORMATION pi;
		ZeroMemory(& pi, sizeof pi);


		CDirectoriesManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->DirectoriesManager;

		BOOL ret = CreateProcess(m.getLMRA_WB_WordLoaderPath(), NULL, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, & si, & pi);
		if (! ret) 
		{
			return;
		}
	
//dedek: chtelo by to jestetu aplikaci ukoncit :)
//		PostThreadMessage(pi.dwThreadId, WM_DESTROY, 0, 0);

		
		CloseHandle(pi.hProcess);
		
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
	Transform1Element(doc);
}



//rekurzivni
void CSkeletonDoc::Transform1Element(IXMLDOMElementPtr & element)
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
			Transform1Element(iChild);
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

void CSkeletonDoc::OnMmdelete() 
{
	CTreeCtrl & hTreeCtrl = GetFirstView()->GetTreeCtrl();
	
	HTREEITEM hSelTreeItem = hTreeCtrl.GetSelectedItem();

	IXMLDOMElementPtr selected_element = ElementFromItemData(hTreeCtrl.GetItemData( hSelTreeItem ));
	
	IXMLDOMElementPtr parent_element= selected_element->parentNode;


	parent_element->removeChild(selected_element);

	if (0 == hTreeCtrl.DeleteItem(hSelTreeItem))
	{
		AfxMessageBox("Smazani prvku z TreeCtrl se nepovedlo.",0,0);
		return;
	}
	

	SetModifiedFlag();		
	UpdateAllViews(NULL);
}

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
	/***/

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
			UpdateAllViews(NULL, (LPARAM) (IXMLDOMElement *) new_element);
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