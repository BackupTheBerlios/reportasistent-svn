// DataSourceManager.cpp: implementation of the CDataSourceManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ReportAsistent.h"
#include "DataSourceManager.h"
#include "WaitDialog.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
// implementace metod

/////////////////////////////////////////////////////////////////
// --------- CPluginRec -----

// konstruktor
CPluginRec::CPluginRec(plugin_id_t Name): PluginName(Name)
{
	
	// inicializace a pripojeni zasuvky
	SockInterface = NULL;
	hLib = NULL;
}


// destruktor
CPluginRec::~CPluginRec()
{
	// odpojeni knihovny
	FreeLibrary(hLib);
}


// Valid()
BOOL CPluginRec::Valid()
{
	if(hLib!=NULL  &&  SockInterface!=NULL)
		return TRUE;

	return FALSE;
}



/////////////////////////////////////////////////////////////////
// --------- CSourceRec -----

// konstruktor
CSourceRec::CSourceRec()
{
	PerzistID = "";
	PluginID = "";
	PublicID = "";
	PluginIndex = -1;
	SourceHandle = NULL;
}


// Valid()
BOOL CSourceRec::Valid()
{
	if (PerzistID!=""  &&  PluginID!=""  &&  PublicID!=""  &&  PluginIndex!=-1)
		return TRUE;
	
	return FALSE;
}

/////////////////////////////////////////////////////////////////
// ----------- CDataSourcesManager -----

// konstruktor
CDataSourcesManager::CDataSourcesManager(CDirectoriesManager & m)
{
	// inicializace tabulky zasuvek a tabulky zdroju
	initPlugsTab(m.getPluginsDirectory());
	initSourcesTab(m.getSourcesConfigFilePath());
}

// destruktor
CDataSourcesManager::~CDataSourcesManager()
{
	// kody: zavreni vsech datovych zdroju (kvuli Ferdovi)
	// ***
	for (int i = 0;  i < SourcesTab.GetSize(); i++)
	{
		try
		{
			if(isSourceConnected(i))
				CloseSource(i);
		}
		catch(...) {}
	}

	// ***
	
	saveSourcesTab();
}



// ---- sprava zasuvek ----------------------

// initPlugsTab
int CDataSourcesManager::initPlugsTab(LPCTSTR plugins_dir_path)
{
	int i   = 0;
    BOOL Found;
	CFileFind FList;	// seznam nalezenych DLL
	
	// nalezeni vsech zasuvek a vyplneni jejich nazvu do pole PlugsTab

	//CString Path = _PLUGIN_DIR_PATH;
	//dedek:
	CString Path = plugins_dir_path;
	Path +=  "\\*.dll";
	Found = FList.FindFile(Path);
	
	while (Found)
	{
		Found = FList.FindNextFile();
		//printf("%s\n", FList.GetFileName());
		
		PlugsTab.Add(CPluginRec(FList.GetFileName()));
		i++;
	}

	// inicializace vsech zasuvek
	pSockIfaceFn_t pInitFn;
	CString LibName;
	for(int j=0; j<=PlugsTab.GetUpperBound(); j++)
	{
		pInitFn = NULL;	// ukazatel na inicializacni funkci zasuvky	
//		LibName = _PLUGIN_DIR_PATH + PlugsTab[j].PluginName;
//dedek:
		LibName.Format("%s\\%s", plugins_dir_path ,PlugsTab[j].PluginName);
		try
		{
			HMODULE m;
			PlugsTab[j].hLib = m = LoadLibrary(LibName);
/********
			if (m== NULL)
			{

				DWORD n;
				LPVOID lpMsgBuf;
				FormatMessage( 
					FORMAT_MESSAGE_ALLOCATE_BUFFER | 
					FORMAT_MESSAGE_FROM_SYSTEM | 
					FORMAT_MESSAGE_IGNORE_INSERTS,
					NULL,
					n = GetLastError(),
					MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
					(LPTSTR) &lpMsgBuf,
					0,
					NULL 
				);
				// Process any inserts in lpMsgBuf.
				// ...
				// Display the string.
				MessageBox( NULL, (LPCTSTR)lpMsgBuf, "Error", MB_OK | MB_ICONINFORMATION );
				// Free the buffer.
				LocalFree( lpMsgBuf );
			
			}
/******/
		}
		catch (...)
		{
			PlugsTab[j].hLib = NULL;		
		}

		if(PlugsTab[j].hLib != NULL)
		{
			// ziskani adresy rozhrani
			pInitFn = (pSockIfaceFn_t) GetProcAddress(PlugsTab[j].hLib, _SOCK_IFACE_FN_NAME);
			if(pInitFn != NULL)		// byla nalezena inicializacni funkce knihovny
			{
				// volani inicializacni funkce a nastaveni SockInterface
				try
				{
					PlugsTab[j].SockInterface = pInitFn();
				} 
				catch (...)
				{
					::MessageBox(NULL, "Varovani: pri nacitani zasuvky doslo k vyjimce.\n\nprikaz: PlugsTab[j].SockInterface = pInitFn();", PlugsTab[j].PluginName, MB_ICONWARNING);

				}
			}
		
		}
	}
	
	return i;
}




// ---- sprava zdroju ----------------------

// InitSourcesTab
BOOL CDataSourcesManager::initSourcesTab(LPCTSTR config_file_path)
{
	CString FName;	// jmeno (cesta) ke konfig. souboru
//	FName = _CONF_DIR_PATH;
//	FName += _CONF_FILE_SOURCES;
	FName = config_file_path;
	BSTR FileName = FName.AllocSysString();

   // nacteni konfiguracniho souboru zdroju

	MSXML2::IXMLDOMDocumentPtr pXMLDom;  // koren XML stromu
	MSXML2::IXMLDOMElementPtr pNode;	// korenovy element
	MSXML2::IXMLDOMNodeListPtr pChildren;  // seznam podelementu korenoveho elementu
	MSXML2::IXMLDOMElementPtr pChild;	//  podelement korenoveho elementu

    int i = 0;	// indexova promenna
	_variant_t  Atr_val;	// textova hodnota atributu
	HRESULT hr;
     //COM init
    //CoInitialize(NULL);
	//dedek: uz je zavolano
	
      //Vytvori COM objekt (resp. instanci objektu)
    hr = pXMLDom.CreateInstance(_T("Msxml2.DOMDocument"));
    if (FAILED(hr)) 
       return FALSE;
    pXMLDom->async = VARIANT_FALSE;
   
       //nacti DOM ze souboru
    //if ( pXMLDom->load((_bstr_t)FileName) != VARIANT_TRUE)
	if ( pXMLDom->load((LPCTSTR) FName) == VARIANT_TRUE)
    {
		pNode = pXMLDom->GetdocumentElement();
		if (pNode != NULL)
		{
			if (pNode->baseName == (_bstr_t) "SOURCES_LIST") // spravny nazev korenoveho elementu
			{
				pChildren = pNode->childNodes;	// ziskani seznamu potomku
				pChild = NULL;
				while((pChild = pChildren->nextNode()) != NULL)  // zpracovavaji se potomci
				{
					if(pChild->baseName == (_bstr_t) "SOURCE")  // definice polozky v tabulce zdroju
					{
						// pridani prvku do tabulky zdroju
						SourcesTab.Add(CSourceRec());
							// PUBLIC_ID
						Atr_val = pChild->getAttribute("PUBLIC_ID");
						if(Atr_val.vt != VT_NULL)
							SourcesTab[i].PublicID = (BSTR) (_bstr_t) Atr_val;
							// PERZISTENT_ID
						Atr_val = pChild->getAttribute("PERZISTENT_ID");
						if(Atr_val.vt != VT_NULL)
							SourcesTab[i].PerzistID = (BSTR) (_bstr_t) Atr_val;

							// PLUGIN_ID
						Atr_val = pChild->getAttribute("PLUGIN_ID");
						if(Atr_val.vt != VT_NULL)
							SourcesTab[i].PluginID = (BSTR) (_bstr_t) Atr_val;

						i++;
					}
				}
			}


			//dedek: nacteni default source

			MSXML2::IXMLDOMElementPtr el_default_source = pNode->selectSingleNode("DEFAULT_SOURCE");
			if (el_default_source)
				setDefaultSource((public_source_id_t) (LPCTSTR) (_bstr_t) el_default_source->getAttribute("PUBLIC_ID"));



		}
	}

	SysFreeString(FileName);
	pXMLDom.Release();
	//pNode.Release();
	//pChildren.Release();
	//pChild.Release();

	// nastaveni odkazu na tabulku zasuvek prvkum z tabulky zdroju
	
	for(int j=0; j<= SourcesTab.GetUpperBound(); j++)	// pres polozky v tabulce zdroju
	{
		for(int k=0; k<=PlugsTab.GetUpperBound(); k++)
		{
			if(SourcesTab[j].PluginID == PlugsTab[k].PluginName)
			{
				SourcesTab[j].PluginIndex = k;	// nastaveni indexu v tabulce zasuvek
				break;
			}
		}
		
	}

	return TRUE;
}


//dedek:
BOOL CDataSourcesManager::saveSourcesTab()
{
	BOOL ret = TRUE;
	
	MSXML2::IXMLDOMDocumentPtr pXMLDom;
    pXMLDom.CreateInstance(_T("Msxml2.DOMDocument"));

	
	MSXML2::IXMLDOMElementPtr root_el;	// korenovy element
	root_el = pXMLDom->createElement("SOURCES_LIST");
	pXMLDom->appendChild(root_el);


	MSXML2::IXMLDOMElementPtr source_el;	// source element
	source_el = pXMLDom->createElement("SOURCE");

	
	//atributy
	MSXML2::IXMLDOMAttributePtr attr;
	
	attr = pXMLDom->createAttribute("PUBLIC_ID");
	source_el->setAttributeNode(attr);
	attr.Release();

	attr = pXMLDom->createAttribute("PERZISTENT_ID");
	source_el->setAttributeNode(attr);
	attr.Release();

	attr = pXMLDom->createAttribute("PLUGIN_ID");
	source_el->setAttributeNode(attr);
	attr.Release();



	for (int a=0; a<getSourcesCount(); a++)
	{
		MSXML2::IXMLDOMElementPtr e = source_el->cloneNode(VARIANT_TRUE);

		e->setAttribute("PUBLIC_ID", (LPCTSTR) getSourcePublicID(a));
		e->setAttribute("PERZISTENT_ID", (LPCTSTR) getSourcePersistentID(a));
		e->setAttribute("PLUGIN_ID", (LPCTSTR) getSourcePlugin(a));

		root_el->appendChild(e);

		e.Release();

	}

	source_el.Release();



	//default zdroj:
	MSXML2::IXMLDOMElementPtr default_source;
	default_source = pXMLDom->createElement("DEFAULT_SOURCE");


	MSXML2::IXMLDOMAttributePtr src_attr;	
	src_attr = pXMLDom->createAttribute("PUBLIC_ID");
	src_attr->value = (LPCTSTR) getDefaultSource();
	default_source->setAttributeNode(src_attr);
	src_attr.Release();

	root_el->appendChild(default_source);

	default_source.Release();



	CDirectoriesManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->DirectoriesManager;

	ret = S_OK == pXMLDom->save((LPCTSTR) m.getSourcesConfigFilePath());
	root_el.Release();

	return ret;
}

// --- pristupove metody do tabulky zasuvek (PlugsTab) ----------------------

// getValidPlugsCount
int CDataSourcesManager::getValidPlugsCount()
{
	int Count = 0;
	for(int i=0; i<=PlugsTab.GetUpperBound(); i++)
	{
		if(PlugsTab[i].Valid())
			Count++;
	}
	return Count;
}


// getPlugsCount
int CDataSourcesManager::getPlugsCount()
{
	return (PlugsTab.GetUpperBound() + 1);
}


// getPluginID
plugin_id_t CDataSourcesManager::getPluginID(int plugin_index)
{
	plugin_id_t Ret = "";
	if(PlugsTab.GetUpperBound() >= plugin_index   &&  plugin_index >= 0)
		Ret = PlugsTab[plugin_index].PluginName;

	return Ret;
}


// FindPluginByPluginName
int CDataSourcesManager::FindPluginByPluginName(plugin_id_t name)
{
	int Result = -1;
	for(int i=0; i<=PlugsTab.GetUpperBound(); i++)
	{
		if(PlugsTab[i].PluginName == name)
		{
			Result = i;
			break;
		}
	}

	return Result;
}


// --- pristupove a konfiguracni metody do tabulky zdroju (SourcesTab) ----------------------


// getSourcesCount
int CDataSourcesManager::getSourcesCount()
{
	return (SourcesTab.GetUpperBound() + 1);
}


// getValidSourcesCount
int CDataSourcesManager::getValidSourcesCount()
{
	int Count = 0;
	for(int i=0; i<=SourcesTab.GetUpperBound(); i++)
	{
		if(SourcesTab[i].Valid())
			Count++;
	}
	
	return Count;
}

// getSourcePublicID
public_source_id_t CDataSourcesManager::getSourcePublicID(int source_index)
{
	public_source_id_t Ret = "";
	if(SourcesTab.GetUpperBound() >= source_index  &&  source_index>=0)
		Ret = SourcesTab[source_index].PublicID;

	return Ret;
}


// getSourcePersistentID
persistent_id_t CDataSourcesManager::getSourcePersistentID(int source_index)
{
	persistent_id_t Ret = "";
	if(SourcesTab.GetUpperBound() >= source_index  &&  source_index>=0)
		Ret = SourcesTab[source_index].PerzistID;

	return Ret;
}


// getSourcePlugin
plugin_id_t CDataSourcesManager::getSourcePlugin(int source_index)
{
	plugin_id_t Ret = "";
	if(SourcesTab.GetUpperBound() >= source_index  &&  source_index>=0)
		Ret = SourcesTab[source_index].PluginID;

	return Ret;
}

//dedek:
int CDataSourcesManager::getSourcePluginIndex(int source_index)
{
	int Ret = -1;
	if(SourcesTab.GetUpperBound() >= source_index  &&  source_index>=0)
		Ret = SourcesTab[source_index].PluginIndex;

	return Ret;
}


// getSourceHandle
source_handle_t CDataSourcesManager::getSourceHandle(int source_index) 
{
	source_handle_t Ret = NULL;
	if(SourcesTab.GetUpperBound() >= source_index  &&  source_index>=0)
		Ret = SourcesTab[source_index].SourceHandle;

	return Ret;
}


// setSourcePublicID
BOOL CDataSourcesManager::setSourcePublicID(int source_index, public_source_id_t source_id)
{
	if(SourcesTab.GetUpperBound() >= source_index  &&  source_index>=0)
	{
		SourcesTab[source_index].PublicID = source_id;
		return TRUE;
	}

	return FALSE;
}


// isSourceConnected
BOOL CDataSourcesManager::isSourceConnected(int source_index)
{
	if(SourcesTab.GetUpperBound() >= source_index  &&  source_index>=0)
	{
		if(SourcesTab[source_index].SourceHandle != NULL)
			return TRUE;
	}

	return FALSE;
}


BOOL CDataSourcesManager::isSourceValid(int source_index)
{
	if(SourcesTab.GetUpperBound() >= source_index  &&  source_index>=0)
	{
		return SourcesTab[source_index].Valid();
	}

	return FALSE;
}

BOOL CDataSourcesManager::isPluginValid(int plugin_index)
{
	if(PlugsTab.GetUpperBound() >= plugin_index  &&  plugin_index>=0)
	{
		return PlugsTab[plugin_index].Valid();
	}

	return FALSE;

}





// ConnectNewSource

void CDataSourcesManager::ConnectNewSourceThreadFunction(LPARAM hNewSourceFn, LPARAM NewSourcePerzistID, LPARAM h_hSource)
{
	* ((hSource_t *) h_hSource) = ((hNewSource_t) hNewSourceFn)  ((PersistID_t *) NewSourcePerzistID);
	
	return;
}

int CDataSourcesManager::ConnectNewSource(plugin_id_t plugin)   //pres zasuvku pripoji novy zdroj
{
	// nalezeni prislusne zasuvky - polozky v tabulce zasuvek s PluginName = plugin
	int i = FindPluginByPluginName(plugin);  // index zasuvky v poli zasuvek
	
	if(i == -1)	// zasuvka neni v tabulce zasuvek
		return -1;

	// test, jestli je zasuvka validni
	if(PlugsTab[i].Valid() == FALSE)
		return -1;

	// zavolani funkce zasuvky pro vytvoreni noveho zdroje
	PersistID_t NewSourcePerzistID = NULL;	// vrati zasuvka - perzistentni ID noveho zdroje
	hSource_t   NewSourceHandler;		// handler na novy zdroj
		// zavolani funkce zasuvky v novem vlakne
	CWaitDialog d("Connecting new data source");
	d.DoThreadFunction(  ConnectNewSourceThreadFunction,
						(LPARAM) PlugsTab[i].SockInterface->hNewSource,
						(LPARAM) & NewSourcePerzistID,
						(LPARAM) & NewSourceHandler);
	
	
	//NewSourceHandler = PlugsTab[i].SockInterface->hNewSource (&NewSourcePerzistID);
	if(NewSourceHandler == NULL)  // chyba v zasuvce
	{
		SysFreeString(NewSourcePerzistID);
		return -1;
	}

	// vytvoreninove polozky v tabulce zdroju a nastaveni jejich polozek
	int j = SourcesTab.Add(CSourceRec()); // index nove pridavaneho zaznamu do tabulky zdroju
	SourcesTab[j].PerzistID = NewSourcePerzistID;
	SourcesTab[j].SourceHandle = NewSourceHandler;
	SourcesTab[j].PluginID = PlugsTab[i].PluginName;
	SourcesTab[j].PluginIndex = i;
	
	//pridal dedek
	CString public_id;
	public_id.Format("new_%s_source_%d", (LPCTSTR) PlugsTab[i].PluginName, getSourcesCount());
	SourcesTab[j].PublicID = public_id;
	
	SysFreeString(NewSourcePerzistID);
	return j;	
}



// RemoveSource
BOOL CDataSourcesManager::RemoveSource(int source_index)	//vyhodi zdroj z tabulky zdroju
// pokud je zdroj pripojen, bude odpojen
{
	
	if(SourcesTab.GetUpperBound() < source_index  ||  source_index<0)
		return FALSE;	// mozna TRUE, kdyz se vlastne nic nestalo?
	
	// odpojeni zrdoje, je-li pripojen
	int PlIndex;	// index zasuvky
	if(SourcesTab[source_index].SourceHandle != NULL)
	{
		PlIndex = SourcesTab[source_index].PluginIndex;
		if(PlugsTab[PlIndex].Valid())	// zasuvka je platna
			// odpojeni zasuvky
			PlugsTab[PlIndex].SockInterface->hCloseSource(SourcesTab[source_index].SourceHandle);
	}

	// zruseni zaznamu v tabulce zdroju
	SourcesTab.RemoveAt(source_index);

	return TRUE;
}


// ConnectSource

// 
void CDataSourcesManager::ConnectSourceThreadFunction(LPARAM hOpenSourceFn, LPARAM PID, LPARAM h_hSource)
{
	* ((hSource_t *) h_hSource) = ((hOpenSource_t) hOpenSourceFn) (* ((PersistID_t *) PID));
	
	return;
}

BOOL CDataSourcesManager::ConnectSource(int source_index)
{
	int SI = source_index;	// kratsi nazev :-)
	
	// kontrola indexu
	if(SourcesTab.GetUpperBound() < SI  ||  SI<0) 
		return FALSE;
		

	// kontrola, zda je zdroj pripojen k validni zasuvce
	if(SourcesTab[SI].PluginIndex == -1)
		return FALSE;
	if(PlugsTab[SourcesTab[SI].PluginIndex].Valid() == FALSE)
		return FALSE;
	// kontrola, zda uz zdroj neni pripojen
	if(isSourceConnected(SI))
		return TRUE;

	int i = SourcesTab[SI].PluginIndex;	// index zasuvky v tabulce zasuvek

	// zavolani funkce zasuvky, ktera pripoji zdroj
	PersistID_t PID = (SourcesTab[SI].PerzistID).AllocSysString();
			// zavolani funkce zasuvky v novem vlakne
	hSource_t SourceH;
	CWaitDialog d("Connecting data source");
	d.DoThreadFunction(  ConnectSourceThreadFunction,
						(LPARAM) PlugsTab[i].SockInterface->hOpenSource,
						(LPARAM) & PID,
						(LPARAM) & SourceH);
	//hSource_t SourceH = PlugsTab[i].SockInterface->hOpenSource(PID);
	
	// vyplneni handleru na zdroj v polozce tabulky
	SourcesTab[SI].SourceHandle = SourceH;

	SysFreeString(PID);
	if(SourceH == NULL)
		return FALSE;

	return TRUE;
}


// CloseSource
BOOL CDataSourcesManager::CloseSource(int source_index)
{
	if(SourcesTab.GetUpperBound() < source_index  ||  source_index<0)
		return FALSE;	// mozna TRUE, kdyz se vlastne nic nestalo?
	
	// odpojeni zrdoje
	int PlIndex;	// index zasuvky
	if(SourcesTab[source_index].SourceHandle != NULL)
	{
		PlIndex = SourcesTab[source_index].PluginIndex;
		if(PlugsTab[PlIndex].Valid())	// zasuvka je platna
			// odpojeni zasuvky
			PlugsTab[PlIndex].SockInterface->hCloseSource(SourcesTab[source_index].SourceHandle);
	}

	SourcesTab[source_index].SourceHandle = NULL;
	return TRUE;
}


// FindSourceByPublicID
int CDataSourcesManager::FindSourceByPublicID(public_source_id_t id) //vrati index odpovidajiciho zdroje
{
	int Index = -1;	// index zdroje
	for(int i=0; i<=SourcesTab.GetUpperBound(); i++)
	{
		if(SourcesTab[i].PublicID == id)
		{
			Index = i;
			break;
		}
	}

	return Index;
}
/* honzova verze - nejak jsem to sem chtel dat :)
int CDataSourcesManager::FindSourceByPublicID(public_source_id_t id) //vrati index odpovidajiciho zdroje
{
	CString sid = id;
	for (int a=0; a<getSourcesCount(); a++)
	{
		if (sid == getSourcePublicID(a)) return a;
	}

	return -1;
}
*/


// AddSource
int CDataSourcesManager::AddSource(plugin_id_t plugin, persistent_id_t persistent_id, public_source_id_t public_id)
{
	int i = SourcesTab.Add(CSourceRec()); // pridani noveho prvku, ziskani indexu
	// vyplneni polozek noveho prvku
	SourcesTab[i].PerzistID = persistent_id;
	SourcesTab[i].PluginID = plugin;
	SourcesTab[i].PublicID = public_id;
	
	// nalezeni zasuvky a vyplneni indexu zasuvky
	 SourcesTab[i].PluginIndex = FindPluginByPluginName(plugin);
	
	return i;
}



// --- volani funkce Perform ----------------------

// CallPerformProc
// Kody - upravil jsem typ u parametru  element_id z BSTR na char*, tak to chce jadro
//      - kdyztak to Dedo predelej, jestli potrebujes, zpatky a pridej konverzi
// Kody - co se ma vratit, kdyz fce perform vrati chybu?
// pro Dedu - alternativa ... viz niz a vyber si jednu z nich. Totez v headru
BSTR CDataSourcesManager::CallPerformProc(int source_index, LPCTSTR element_id) //vrati XML string
{
	BSTR Result = NULL;	// bude vysledek
	int SI = source_index;
	
	if(SourcesTab.GetUpperBound() < SI)   // kontrola indexu a odkazu na zasuvku
		return Result;

	int j = SourcesTab[SI].PluginIndex;  // nalezeni indexu zasuvky

	if((j != -1) && (PlugsTab[j].Valid()) && (SourcesTab[SI].SourceHandle != NULL)) // zasuvka je platna a zdroj otevreny
	{
		// zavolani  fce Perform zasuvky
		//BOOL PerfRes = PlugsTab[j].SockInterface->hPerform(SourcesTab[SI].SourceHandle, element_id, &Result);
		// kody: vytvoreni WaitDialogu a volani jeho DoThreadFunction()
		CWaitDialog d("Loading data from source");
		d.DoThreadFunction(PerformThreadFunction,
							(LPARAM) PlugsTab[j].SockInterface->hPerform,
						    (LPARAM) SourcesTab[SI].SourceHandle,
							(LPARAM) element_id,
							(LPARAM) &Result);
	}

	return Result;
}

// 
void CDataSourcesManager::PerformThreadFunction(LPARAM hPreformFn, LPARAM hSource, LPARAM element_id, LPARAM pResult)
{
	 ((hPerform_t) hPreformFn) ((void*) hSource, (LPCTSTR) element_id, (BSTR*) pResult);
	
	return;
}

//dedek
BSTR CDataSourcesManager::GetPluginOutput(public_source_id_t source, LPCTSTR ap_name)
{
	int src_index = FindSourceByPublicID(source);
	if (! isSourceConnected(src_index)) 
	{
		if (! ConnectSource(src_index)) return NULL;
	}

	return CallPerformProc(src_index, ap_name);
}



/*
//alternativa:

BOOL CDataSourcesManager::CallPerformProc(int source_index, char* element_id, BSTR* Result)
{
	int SI = source_index;
	BOOL Ret = FALSE;  // navrat
	
	if(SourcesTab.GetUpperBound() < SI)   // kontrola indexu a odkazu na zasuvku
		return Ret;
	
	int j = SourcesTab[SI].PluginIndex;  // nalezeni indexu zasuvky

	if((j != -1) && (PlugsTab[j].Valid()) && (SourcesTab[SI].SourceHandle != NULL)) // zasuvka je platna a zdroj otevreny
		Ret = PlugsTab[j].SockInterface->hPerform(SourcesTab[SI].SourceHandle, element_id, Result);

	return Ret;
}
*/


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
/////////////////////POMOCNA CAST - SMAZAT////////////////////////

/*
void vypisZasuvku(int i, CDataSourcesManager* SM)
{
	printf("zasuvka c. %d  PluginName: %s  Valid %d\n",i,SM->PlugsTab[i].PluginName,SM->PlugsTab[i].Valid());
}

void vypisZdroj(int i, CDataSourcesManager* SM)
{
	printf("zdroj c. %d  PerzistID: %s  PluginID: %s  PublicID: %s, PluginIndex: %d\n",i,SM->SourcesTab[i].PerzistID,SM->SourcesTab[i].PluginID,SM->SourcesTab[i].PublicID,SM->SourcesTab[i].PluginIndex);
}



int main(int argc, char** argv)
{
	// zkouska funkcnosti pripojovani zasuvek
	CDataSourcesManager SM;
	
	int i;
	printf("bylo pripojeno %d zasuvek:\n", SM.getPlugsCount());
	printf("z nich %d platnych\n", SM.getValidPlugsCount());
	CString Platnost;
	for (i=0; i<SM.getPlugsCount(); i++)
	{
		if(SM.PlugsTab[i].Valid())
			Platnost = "platna";
		else
			Platnost = "neplatna";
		printf("%d)   %s   %s\n", i, SM.PlugsTab[i].PluginName, Platnost);
	}


	// zkouseni novych funkci
	CString publ_id = "prvni zdroj";
	int cislo = SM.FindSourceByPublicID(publ_id);
	
	CString str = SM.getSourcePublicID(-1);
	str = SM.getSourcePersistentID(5);
	str = SM.getSourcePlugin(-1);

	BOOL bul;
	
	int q = SM.FindPluginByPluginName("LMplugin.dll");
	int nzindex = SM.ConnectNewSource("LMplugin.dll");
	bul = SM.isSourceConnected(nzindex);
	bul = SM.isSourceConnected(0);
	bul = SM.CloseSource(nzindex);
	bul = SM.CloseSource(0);
	bul = SM.isSourceConnected(nzindex);
	bul = SM.ConnectSource(nzindex);
	bul = SM.setSourcePublicID(nzindex, "slananynkadozeli");
	bul = SM.setSourcePublicID(-200, "slananynkadozeli");
	bul = SM.isSourceConnected(nzindex);
	
	// zkouska PERFORM
	BSTR result = SM.CallPerformProc(nzindex,"4fthyp");
	CString cres = result;


	printf("\n\n");
	printf("Zasuvky\n-------\n");
	for(i=0; i<=SM.PlugsTab.GetUpperBound(); i++)
		vypisZasuvku(i, &SM);
	printf("\nZdroje\n-------\n");
	for(i=0; i<=SM.SourcesTab.GetUpperBound(); i++)
		vypisZdroj(i, &SM);

	void* pt = SM.getSourceHandle(-1);
	return 0;
}
*/


//dedek:
public_source_id_t CDataSourcesManager::getDefaultSource()
{
	int src_index = FindSourceByPublicID(default_source);
	
	
	
	if (src_index != -1) return default_source;


	
	
	if (getSourcesCount() == 0) return "";



	
	
	default_source = getSourcePublicID(0);
	return default_source;



}

//dedek:
void CDataSourcesManager::setDefaultSource(public_source_id_t source)
{
	default_source = source;
}

//dedek:
BOOL CDataSourcesManager::isElementSupportedByPlugin(int plugin_index, LPCTSTR element_name)
{
	ASSERT(plugin_index >= 0);
	ASSERT(plugin_index < PlugsTab.GetSize());
	
//	ASSERT(isPluginValid(plugin_index));
	if (! isPluginValid(plugin_index)) return FALSE;
	
	MSXML2::IXMLDOMDocumentPtr ael_list;
	ael_list.CreateInstance(_T("Msxml2.DOMDocument"));
	ael_list->async = VARIANT_FALSE; // default - true,

	ael_list->loadXML(
		PlugsTab[plugin_index].SockInterface->hGetAPList());

	if (ael_list->parseError->errorCode == S_OK)
	{
		CString query_str;
		query_str.Format("/LIST/APID[@NAME = \"%s\"]", element_name);

		if (NULL != ael_list->selectSingleNode((LPCTSTR) query_str)) return TRUE;
	}


	

	ael_list.Release();
	return FALSE;
}
