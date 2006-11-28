// WordManager.cpp: implementation of the CWordManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ReportAsistent.h"
#include "WordManager.h"
#include "WaitDialog.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


void CStringTableImpl::Clear()
{
	for (int a=0; a<getCount(); a++)
	{
		delete data[a];
	}

//	data.RemoveAll();
	data.clear();
}


void CStringTableImpl::Add(LPCTSTR s)
{
	data.push_back(new CString(s));
//	int a = data.GetSize();
}

int CStringTableImpl::getCount()
{
	return data.size();
}

LPCTSTR CStringTableImpl::getItem(int index)
{
	ASSERT(index >= 0);
	ASSERT(index < getCount());
	
	return * data[index];
}

CStringTableImpl::~CStringTableImpl()
{
	Clear();
}



void CWordManager::LoadWordStylesThreadFunction(LPARAM template_name, LPARAM pWordManager)
{	
	CWordManager * m = (CWordManager *) pWordManager;

	m->LoadWordTemplates();
	m->LoadParagraphStyles((LPCTSTR) template_name);
	m->LoadCharacterStyles((LPCTSTR) template_name);
}


void CWordManager::LoadWordStylesAndTempates(LPCTSTR template_name)
{
	if (template_name == NULL)
	{
		template_name = "normal.dot";
	}

	if(! isInit()) 
		if (! InitWordLoader()) return;

	CWaitDialog d("Loading Word styles...");
	d.DoThreadFunction(LoadWordStylesThreadFunction,
						(LPARAM) template_name,
						(LPARAM) this);
}




void CWordManager::LoadWordTemplates()
{
	SAFEARRAY * ret_array = m_WordLoader->EnumTemplates();

	LoadSafeArrayToStringTable(ret_array, m_WordTemplates);
}


CWordManager::CWordManager(CDirectoriesManager & m)
: m_pEventHandler(NULL)
{
	//ladici:
	//LoadWordTemplates();
	//LoadWordStyles("normal.dot");
	
	BOOL res = FALSE;

	// kody
	try	{res = loadStylesFromXML(m.getWordStylesConfigFilePath());}
	catch(...)
	{
		res = FALSE;
	}
	if(!res)
		CReportAsistentApp::ReportError(IDS_STYLLISTLOAD_ERR);
}


CWordManager::~CWordManager()
{
	if (m_WordLoader != NULL) 
	{
		DisconnectWordEventHandler();
		m_WordLoader.Release();
	}

	// kody - ulozeni Wordovskejch stylu do XML
	CDirectoriesManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->DirectoriesManager;
	
	BOOL res = FALSE;
	
	try
	{
		res = saveStylesToXML((LPCTSTR) m.getWordStylesConfigFilePath());
	}
	catch(...)
	{
		res = FALSE;
	}

	if(!res)
		CReportAsistentApp::ReportError(IDS_STYLLISTSAVE_ERR);
}

BOOL CWordManager::InitWordLoader()
{
	if (CreateVBRAInstance(m_WordLoader))
	{

		FillActiveElements();
	
		return InitWordEventHandler();
	}

	return FALSE;
}

BOOL CWordManager::isInit()
{
	return m_WordLoader != NULL;
}



void CWordManager::LoadCharacterStyles(LPCTSTR template_name)
{
	SAFEARRAY * ret_array = m_WordLoader->EnumCharacterStyles(
		(long) (getWordTemplates().FindStringNoCase(template_name)+1));

	LoadSafeArrayToStringTable(ret_array, m_WordCharacterStyles);
}

void CWordManager::LoadParagraphStyles(LPCTSTR template_name)
{
	SAFEARRAY * ret_array = m_WordLoader->EnumParagraphStyles(
		(long) (getWordTemplates().FindStringNoCase(template_name)+1));

	LoadSafeArrayToStringTable(ret_array, m_WordParagraphStyles);
}

int CStringTable::FindStringNoCase(LPCTSTR str)
{
	for (int a = 0; a < getCount(); a++)
	{
		if (((CString) getItem(a)).CompareNoCase(str) == 0) return a;
	}

	return -1;
}


int CStringTable::FindString(LPCTSTR str)
{
	for (int a = 0; a < getCount(); a++)
	{
		if (((CString) getItem(a)) == str) return a;
	}

	return -1;
}


void CWordManager::GenerateXMLStringToWordEditor(_bstr_t XML_str)
{
	if (! isInit()) 
	{
		if (! InitWordLoader()) return;
	}

	m_WordLoader->LoadFromStringToWordEditor(XML_str);

}


void CWordManager::GenerateXMLString(_bstr_t XML_str)
{
	
	if (! isInit()) 
	{
		if (! InitWordLoader()) return;
	}

	AfxMessageBox("is_init");
//	m_WordLoader->PutstrDefaultWordTemplate((LPCTSTR) "D:\\Documents and Settings\\Dedek\\Data aplikací\\Microsoft\\Šablony\\honza_template.dot");
		
	
	m_WordLoader->LoadFromString(XML_str);
}

BOOL CWordManager::InitWordEventHandler()
{
	m_pEventHandler = new CWordEventHandler();

	LPUNKNOWN p_unk = m_pEventHandler->GetIDispatch(FALSE);

	if (AfxConnectionAdvise(m_WordLoader.GetInterfacePtr(), 
			DIID___LMRA_XML_WordLoader, p_unk, FALSE, & m_dwEventHandlerCookie))
		return TRUE;
	else
		return FALSE;
}

void CWordManager::DisconnectWordEventHandler()
{
	try
	{
		LPUNKNOWN p_unk = m_pEventHandler->GetIDispatch(FALSE);
		AfxConnectionUnadvise(m_WordLoader.GetInterfacePtr(), 
			DIID___LMRA_XML_WordLoader, p_unk, FALSE, m_dwEventHandlerCookie);
	}
	catch (...)
	{

	}


	
	if(m_pEventHandler != NULL)
	{
		delete m_pEventHandler;
		m_pEventHandler = NULL;
	}
}


void CWordManager::SetWordEditorParentTaskName()
{
	ASSERT(isInit());

	CString wdCaption;
	AfxGetApp()->GetMainWnd()->GetWindowText(wdCaption);
	m_WordLoader->PutstrParentTaskName((LPCTSTR) wdCaption);
}

LPCTSTR CWordManager::getLastElementName()
{
	return m_pEventHandler->m_strLastElementName;
}

void CWordManager::OpenWordEditor()
{
	if (! isInit()) 
	{
		if (! InitWordLoader()) return;
	}

	WordEditHideMainWindow();


	SetWordEditorParentTaskName();

	try
	{
		m_WordLoader->OpenWordEditor();
	}
	catch (_com_error e)
	{
		//ladici
		AfxMessageBox(e.Description());
	}
}

void CWordManager::FillActiveElements()
{
	CElementManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;

	for (int a=0; a <= m.getLastElementId(); a++)
	{
		if (m.isElementActive(a))
		{
			CAElInfo * i = m.getActiveElementInfo(a);
			m_WordLoader->AddActiveElement(
				i->getElementName(),
				i->getElementLabel(),
				(LPCTSTR) i->getElementIconPath());
		}
	}
}

BOOL CWordManager::CreateVBRAInstance(_LMRA_XML_WordLoaderPtr & refLMRAInterface)
{
	HRESULT hr;
	
	hr = refLMRAInterface.CreateInstance("LMRA_WordLoader.LMRA_XML_WordLoader");

/*
	if (hr == CO_E_NOTINITIALIZED)
	{
		CoInitializeEx()
	}
*/
	if (S_OK != hr)
	{
				
		//dedek: pokusime se registrovat ActiveX objekt spustenim LMRA_WB_WordLoader s parametrem register
		STARTUPINFO si;
		ZeroMemory(& si, sizeof si);
		
		PROCESS_INFORMATION pi;
		ZeroMemory(& pi, sizeof pi);


		CDirectoriesManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->DirectoriesManager;

		BOOL ret = CreateProcess(m.getLMRA_WB_WordLoaderPath(), " register", NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, & si, & pi);
		if (! ret) 
		{
			CReportAsistentApp::ReportError(IDS_WB_WORD_LOADER_NOT_REGISTRED, "LMRA_WordLoader execution failed.");
			return FALSE;
		}

		//pockame az spusteny process skonci
		DWORD wait_ret= WaitForSingleObject(pi.hProcess, 5000);
 		CloseHandle(pi.hProcess);

		if (wait_ret != WAIT_OBJECT_0)
		{
			CReportAsistentApp::ReportError(IDS_WB_WORD_LOADER_NOT_REGISTRED, "LMRA_WordLoader execution exceeded timeout.");
			return FALSE;
		}
	
		hr = refLMRAInterface.CreateInstance("LMRA_WordLoader.LMRA_XML_WordLoader");
		if (S_OK != hr)
		{
//			DWORD n;
			LPVOID lpMsgBuf;
			FormatMessage( 
				FORMAT_MESSAGE_ALLOCATE_BUFFER | 
				FORMAT_MESSAGE_FROM_SYSTEM | 
				FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL,
//					n = GetLastError(),
				hr,
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
				(LPTSTR) &lpMsgBuf,
				0,
				NULL 
			);
			// Process any inserts in lpMsgBuf.
			// ...
			// Display the string.			
			CReportAsistentApp::ReportError(IDS_WB_WORD_LOADER_NOT_REGISTRED, (LPCTSTR) lpMsgBuf);

			// Free the buffer.
			LocalFree( lpMsgBuf );

			return FALSE;
		}
	}

	return TRUE;
}

//vrati pocet zkopirovanych stringu
int CWordManager::LoadSafeArrayToStringTable(SAFEARRAY *sarray, CStringTableImpl &str_table)
{
	LONG l_bound = 0;
	LONG u_bound = -1;

	SafeArrayGetLBound(sarray, 1, & l_bound);
	SafeArrayGetUBound(sarray, 1, & u_bound);

	str_table.Clear();


	for (LONG a = l_bound; a <= u_bound; a++)
	{
		BSTR arg;
		SafeArrayGetElement(sarray, &a, & arg);

		_bstr_t s;
		s.Assign(arg);

		str_table.Add(s);
	}
	
	SafeArrayDestroy(sarray);

	return u_bound - l_bound +1;
}

BOOL CWordManager::isWordEditorActive()
{
	if (! isInit()) return FALSE;
	return m_WordLoader->GetisWordEditorActive() == VARIANT_TRUE;
}



void CWordManager::WordEditHideMainWindow()
{
	if (! isWordEditorActive())
	{
	
		ZeroMemory(& m_origWINDOWPLACEMENT, sizeof m_origWINDOWPLACEMENT);
		m_origWINDOWPLACEMENT.length = sizeof m_origWINDOWPLACEMENT;
		
		AfxGetApp()->GetMainWnd()->GetWindowPlacement(& m_origWINDOWPLACEMENT);
	}

	WINDOWPLACEMENT newpl;
	ZeroMemory(& newpl, sizeof newpl);
	newpl.length = sizeof newpl;

	newpl.flags = WPF_SETMINPOSITION;
	newpl.showCmd = SW_MINIMIZE; //SW_SHOWMINIMIZED

	AfxGetApp()->GetMainWnd()->SetWindowPlacement(& newpl);
//	AfxGetApp()->GetMainWnd()->EnableWindow(FALSE);

	

	if (isInit())
	{
		m_WordLoader->ActivateWordEditor();
	}
	
	AfxGetApp()->GetMainWnd()->ShowWindow(SW_HIDE);
}

void CWordManager::PrepareParentTaskActivation()
{
	((CReportAsistentApp *) AfxGetApp())->m_bWordPluginMode = FALSE;

	AfxGetApp()->GetMainWnd()->ShowWindow(SW_SHOW);
	SetWordEditorParentTaskName();
}


void CWordManager::WordEditShowMainWindow()
{
	m_origWINDOWPLACEMENT.showCmd = SW_RESTORE;
	AfxGetApp()->GetMainWnd()->SetWindowPlacement(& m_origWINDOWPLACEMENT);
}

bool CStrCompare::num_sort_desc(CString * s1,  CString * s2)
{
	_variant_t v;
	double d1, d2;

	BOOL b1 = TRUE;

	try
	{
		v = * s1;
		d1 = v;
	}
	catch (...)
	{
		b1 = FALSE;
	}
	
	try
	{
		v = * s2;
		d2 = v;
	}
	catch (...)
	{
		if (b1) return true;
		else return *s1 > *s2;
	}

	if (b1) return d1 > d2;
	else return false;
}

bool CStrCompare::num_sort_asc(CString * s1,  CString * s2)
{
	_variant_t v;
	double d1, d2;

	BOOL b1 = TRUE;

	try
	{
		v = * s1;
		d1 = v;
	}
	catch (...)
	{
		b1 = FALSE;
	}
	
	try
	{
		v = * s2;
		d2 = v;
	}
	catch (...)
	{
		if (b1) return true;
		else return *s1 < *s2;
	}

	if (b1) return d1 < d2;
	else return false;
}

bool CStrCompare::str_sort_asc(CString * s1,  CString * s2)
{
	return *s1 < *s2;
}

bool CStrCompare::str_sort_desc(CString * s1,  CString * s2)
{
	return *s1 > *s2;
}

void CStringTableImpl::SortNumeric(BOOL ascending)
{
	if (ascending)
		std::sort(data.begin(), data.end(), CStrCompare::num_sort_asc);
	else
		std::sort(data.begin(), data.end(), CStrCompare::num_sort_desc);
}

void CStringTableImpl::Sort(BOOL ascending)
{
	if (ascending)
		std::sort(data.begin(), data.end(), CStrCompare::str_sort_asc);
	else
		std::sort(data.begin(), data.end(), CStrCompare::str_sort_desc);
}

// loads items (values) from XML DOM Node - elements with type <item value="(new item)">
BOOL CStringTableImpl::loadItemsFromXML(MSXML2::IXMLDOMNodeListPtr & pNodeList)
{
	Clear();  // smazani puvodniho obsahu
	
	MSXML2::IXMLDOMElementPtr pChild = NULL;
	_variant_t  Atr_val;	// textova hodnota atributu

	while((pChild = pNodeList->nextNode()) != NULL)
	{
		if(pChild->baseName == (_bstr_t) "item")  // definice jedne polozky
		{
			Atr_val = pChild->getAttribute("value");
			if(Atr_val.vt != VT_NULL)
			{
				CString new_item = (LPCTSTR) (_bstr_t) Atr_val;
				Add(new_item);
			}
		}
	}

	return TRUE;
}


CString CWordManager::getLastProcessedId(void)
{
  return (CString) (LPCTSTR) m_WordLoader->GetstrLastProcessedId();
}

// returns a xml string with all items : <item value="(item)"/>
CString CStringTableImpl::getItemsInXML(void)
{
	CString result = "";
	for(int i=0; i<getCount(); i++)
	{
		result += "<item value=\"";
		result += getItem(i);
		result += "\" />";
	}
	return result;
}


CString CWordManager::getLastError(void)
{
  return (CString) (LPCTSTR) m_WordLoader->GetstrLastError();
}

// loads lists of Word styles from configuration XML file
BOOL CWordManager::loadStylesFromXML(LPCTSTR XMLFilePath)
{
	CString FName;	// jmeno (cesta) ke konfig. souboru
	FName = XMLFilePath;

	MSXML2::IXMLDOMDocumentPtr pXMLDom;  // koren XML stromu
	MSXML2::IXMLDOMElementPtr pNode;	// korenovy element
	MSXML2::IXMLDOMNodeListPtr pChildren;  // seznam podelementu korenoveho elementu
	MSXML2::IXMLDOMNodeListPtr pChildrenItems;  // seznam podelementu elementu - vstupuje do funkce pro nacitani StringTable
	MSXML2::IXMLDOMElementPtr pChild;	//  podelement korenoveho elementu

	int i = 0;	// indexova promenna
	_variant_t  Atr_val;	// textova hodnota atributu
	HRESULT hr;
    
      //Vytvori COM objekt (resp. instanci objektu)
    hr = pXMLDom.CreateInstance(_T("Msxml2.DOMDocument"));
    if (FAILED(hr)) 
       return FALSE;
    pXMLDom->async = VARIANT_FALSE;
   
       //nacti DOM ze souboru
    if ( pXMLDom->load((LPCTSTR) FName) == VARIANT_TRUE)
	{
		pNode = pXMLDom->GetdocumentElement();
		if (pNode != NULL)
		{
			if (pNode->baseName == (_bstr_t) "word_styles") // spravny nazev korenoveho elementu
			{
				pChildren = pNode->childNodes;	// ziskani seznamu potomku
				pChild = NULL;
				while((pChild = pChildren->nextNode()) != NULL)  // zpracovavaji se potomci
				{
					pChildrenItems = pChild->childNodes;
					if (pChild->baseName == (_bstr_t) "templates")
						m_WordTemplates.loadItemsFromXML(pChildrenItems);

					else if (pChild->baseName == (_bstr_t) "paragraph_styles")
						m_WordParagraphStyles.loadItemsFromXML(pChildrenItems);

					else if (pChild->baseName == (_bstr_t) "character_styles")
						m_WordCharacterStyles.loadItemsFromXML(pChildrenItems);
					
				}
			}
		}
	}

	pXMLDom.Release();

	return TRUE;
}



// saves a list of Word styles to configutation XML file
BOOL CWordManager::saveStylesToXML(LPCTSTR file_path)
{
	CString XMLString = "";
	XMLString += "<word_styles>";
		XMLString += "<templates>";
			XMLString += m_WordTemplates.getItemsInXML();
		XMLString += "</templates>";

		XMLString += "<paragraph_styles>";
			XMLString += m_WordParagraphStyles.getItemsInXML();
		XMLString += "</paragraph_styles>";

		XMLString += "<character_styles>";
			XMLString += m_WordCharacterStyles.getItemsInXML();
		XMLString += "</character_styles>";
	XMLString += "</word_styles>";

	CString FName;	// jmeno (cesta) ke konfig. souboru
	FName = file_path;

	MSXML2::IXMLDOMDocumentPtr pXMLDom;  // koren XML stromu
	HRESULT hr;
    
      //Vytvori COM objekt (resp. instanci objektu)
    hr = pXMLDom.CreateInstance(_T("Msxml2.DOMDocument"));
    if (FAILED(hr)) 
       return FALSE;
    pXMLDom->async = VARIANT_FALSE;
   
       //nacti DOM ze stringu
    if ( pXMLDom->loadXML((_bstr_t) XMLString) != VARIANT_TRUE)
	{
		pXMLDom.Release();
		return FALSE;
	}
	
	BOOL ret = FALSE;

	try
	{
		ret = S_OK == pXMLDom->save((LPCTSTR) FName);
	}
	catch(...)
	{
		ret = FALSE;
	}
	
	pXMLDom.Release();

	return ret;
}

void CWordManager::ActivateWordEditor()
{
	ASSERT(isInit());

	m_WordLoader->ActivateWordEditor();
}
