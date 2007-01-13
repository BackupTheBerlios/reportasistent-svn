// DataSourceManager.h: interface for the CDataSourceManager class.
//
//////////////////////////////////////////////////////////////////////
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
#if !defined(AFX_DATASOURCEMANAGER_H__976787EC_9D7F_4080_B685_F88419DA19FB__INCLUDED_)
#define AFX_DATASOURCEMANAGER_H__976787EC_9D7F_4080_B685_F88419DA19FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



// ================= INCLUDE ==================================
#include <afxtempl.h>
#include "../LMPlugin/SockInterface.h"
#include "DirectoriesManager.h"


/// ================= MAKRA ===================================

// --- jmena konfiguracnich souboru

// konf. XML soubor s datovymi zdroji
#define _CONF_FILE_SOURCES "sources.xml"

// --- rozhrani

// jmeno funkce, ktera vrati jadru ukazatel na rozhrani (strukturu CSockInterface)
#define _SOCK_IFACE_FN_NAME "initSock"



// ================= DATOVE TYPY =============================

// typ ukazatel na funkci _SOCK_IFACE_FN_NAME
/**
 * pSockIfaceFn_t:
 */
typedef CSockInterface* (* pSockIfaceFn_t) ();


// --- polozky tabulky zdroju

//retezec pouzivany v kostre u AP jako identifikator zdroje
	/**
	 * public_source_id_t:
	 */
	typedef CString public_source_id_t;

//perzistentni retezec (obshuje napr connection string, cestu k souboru)
	/**
 * persistent_id_t:
 */
typedef CString persistent_id_t;

//identifikuje zasuvku
//jmeno DLL souboru zasuvky v adresari Plugin
	/**
 * plugin_id_t:
 */
typedef CString plugin_id_t;

//index zasuvky v tabulce zasuvek
	/**
 * plugin_index_t:
 */
typedef int plugin_index_t;

//ukazatel na otevreny zdroj
	/**
 * source_handle_t:
 */
typedef void* source_handle_t;

// ================== TRIDY ==================================


/**
 * class APBuf: Class for buffering of output of one active element. Array of öbjects of this class for every active element supported by a given datasource is then in COutputBuffer class. There is one such class for every connected data source.
 * @author 
 */
class APBuf
{
public:
	CString ap_name;
	MSXML2::IXMLDOMDocumentPtr buffer;
	
	APBuf(CString name, BSTR buf);
	APBuf();
	~APBuf();

	/**
 * isBufferInitialized:
 *
 * @return BOOL 
 */
BOOL isBufferInitialized();


	/**
 * setBuffer:
 *
 * @param str 
 * @param xml 
 * @return static BOOL 
 */
static BOOL setBuffer(BSTR str, MSXML2::IXMLDOMDocumentPtr & xml);
};


/**
 * class COutputBuffer: Class that encapsulates buffers for each active element from one data source.
 *
 * @author 
 */
class COutputBuffer
{
	CArray<APBuf*,APBuf*> BufArray;	

public:
	/**
 * getBuffersCount: returns number of active elements which are buffered for the current data source
 *
 * @return int 
 */
int getBuffersCount();   
	/**
	 * getAPIndex:
	 *
	 * @param APName 
	 * @return int 
	 */
	int getAPIndex(CString APName);
	/**
	 * isAPBuffered:
	 *
	 * @param APName 
	 * @return BOOL 
	 */
	BOOL isAPBuffered(CString APName);
	/**
	 * getBuffer:
	 *
	 * @param APName 
	 * @param xml_dom 
	 * @return BOOL 
	 */
	BOOL getBuffer(CString APName, MSXML2::IXMLDOMDocument ** xml_dom); //returns buffer for given AP
	/**
	 * setBuffer:
	 *
	 * @param APName 
	 * @param Buffer 
	 * @return void 
	 */
	void setBuffer(CString APName, BSTR Buffer); // sets buffer -||-

	COutputBuffer();
	~COutputBuffer();
private:
	/**
	 * insertNewAP:
	 *
	 * @param APName 
	 * @param Buffer 
	 * @return int 
	 */
	int insertNewAP(CString APName, BSTR Buffer);

};



 
/**
 * class CPluginRec:The Class that encapsulates one item in table of reachable plugins LM-RA
 *
 * @author 
 */
class CPluginRec 
{
public:
	plugin_id_t   PluginName;	// jmeno dll knihovny zasuvky v adresari Plugin
	HMODULE       hLib;			// handle na otevrenou DLL
	CSockInterface* SockInterface;	// ukazatel na instanci CSockInterface (rozhrani zasuvky) ktera se v zasuvce
									// vytvori po pripojeni. Tuto polozku vrati fce initSock() v zasuvce
	/**
 * Valid:
 *
 * @return BOOL 
 */
BOOL Valid();						// priznak, zda je DLL platna (implementuje zasuvku) a byla vporadku pripojena

	// konstruktor a destruktor
	CPluginRec(plugin_id_t Name = "");
	~CPluginRec();
};

/**
 * class CSourceRec: One item of the table of data sources.
 *
 * @author 
 */
class CSourceRec
{
public:
	public_source_id_t PublicID;	// v kostre u AP jako identifikator zdroje
	persistent_id_t    PerzistID;	// connection string
	plugin_id_t	       PluginID;	// jedna z PluginName v tabulce zasuvek
	source_handle_t	   SourceHandle;// handle na otevreny zdroj
	COutputBuffer *	   Buffer;	// buffer vystupu AP zdroje

	
	int	PluginIndex;  // index zaznamu v tabulce zasuvek, jejiz PluginName se shoduje s PluginID teto instance
					  // == -1 pokut takovy neexistuje	
	
	
	/**
	 * Valid: Returns information whether is this record in order.
	 *
	 * @return BOOL 
	 */
	BOOL Valid();					// priznak, zda je tento zaznam v poradku


	// konstruktor a destruktor
	CSourceRec();
	~CSourceRec();
};


// ===========================================================

//je to udelany jako indexovany pole, ale poradi se muze behem zivota menit
//to jsem si kdysi neco dal na index 10 neznamena, ze to tam bude navzdy
//ale poradi se meni asi jen funkci RemoveSource
/**
 * class CDataSourcesManager: Class, that covers functions working with connected data sources. It encapsulated indexed array of connected data sources and functions working with them.
 *
 * @author 
 */
class CDataSourcesManager
{
private:
	public_source_id_t default_source;
//  DATA
	CArray<CPluginRec,CPluginRec> PlugsTab;		// tabulka zasuvek
	CArray<CSourceRec *, CSourceRec *> SourcesTab;	// tabulka zdroju

public:
	/**
	 * isElementSupportedByPlugin:
	 *
	 * @param plugin_index 
	 * @param element_name 
	 * @return BOOL 
	 */
	BOOL isElementSupportedByPlugin(int plugin_index, LPCTSTR element_name);
	/**
	 * isElementSupportedByPlugin:
	 *
	 * @param plugin_name 
	 * @param element_name 
	 * @return BOOL 
	 */
	BOOL isElementSupportedByPlugin(LPCTSTR plugin_name, LPCTSTR element_name);
	/**
	 * setDefaultSource:
	 *
	 * @param source 
	 * @return void 
	 */
	void setDefaultSource(public_source_id_t source);
	/**
	 * getDefaultSource:
	 *
	 * @return public_source_id_t 
	 */
	public_source_id_t getDefaultSource();
	/**
	 * isPluginValid:
	 *
	 * @param plugin_index 
	 * @return BOOL 
	 */
	BOOL isPluginValid(int plugin_index);
	/**
	 * isSourceValid:
	 *
	 * @param source_index 
	 * @return BOOL 
	 */
	BOOL isSourceValid(int source_index);

	

// METODY
	// konstruktor a destruktor
	CDataSourcesManager(CDirectoriesManager & m);
	~CDataSourcesManager();

	// inicializuje tabulku zasuvek, vrati pocet zasuvek
	/**
	 * initPlugsTab:
	 *
	 * @param plugins_dir_path 
	 * @return int 
	 */
	int initPlugsTab(LPCTSTR plugins_dir_path);

	// inicializuje tabulku zdroju z konfiguracniho XML souboru
	/**
	 * initSourcesTab:
	 *
	 * @param config_file_path 
	 * @return BOOL 
	 */
	BOOL initSourcesTab(LPCTSTR config_file_path);
	// ulozi tabulku zdroju do konfiguracniho XML souboru
	/**
	 * saveSourcesTab:
	 *
	 * @return BOOL 
	 */
	BOOL saveSourcesTab();



	// --- pristupove metody do tabulky zasuvek (PlugsTab)
	
	// pocet pripojenych zasuvek (prvku PlugsTab) / pocet pripojenych platnych zasuvek
	/**
	 * getPlugsCount:
	 *
	 * @return int 
	 */
	int getPlugsCount();			
	/**
	 * getValidPlugsCount:
	 *
	 * @return int 
	 */
	int getValidPlugsCount();

	// vrati PluginName zasuvky na dane pozici
	/**
	 * getPluginID:
	 *
	 * @param plugin_index 
	 * @return plugin_id_t 
	 */
	plugin_id_t getPluginID(int plugin_index);

	//  vrati index v PlugsTab, kdr je zasuvka s PluginName name nebo -1 (nenalezeno)
	/**
	 * FindPluginByPluginName:
	 *
	 * @param name 
	 * @return int 
	 */
	int FindPluginByPluginName(plugin_id_t name);



	// --- pristupove a konfiguracni metody do tabulky zdroju (SourcesTab)

	// vrati pocet zdroju (prvku v tabulce SourcesTab)
	/**
	 * getSourcesCount:
	 *
	 * @return int 
	 */
	int getSourcesCount();
	/**
	 * getValidSourcesCount:
	 *
	 * @return int 
	 */
	int getValidSourcesCount();

	// vrati PublicID prvku na pozici source_index v tabulce zdroju
	/**
	 * getSourcePublicID:
	 *
	 * @param source_index 
	 * @return public_source_id_t 
	 */
	public_source_id_t getSourcePublicID(int source_index);

	// vrati PerzistentID prvku na pozici source_index v tabulce zdroju
	/**
	 * getSourcePersistentID:
	 *
	 * @param source_index 
	 * @return persistent_id_t 
	 */
	persistent_id_t getSourcePersistentID(int source_index);

	// vrati Plugin index (do tabulky zasuvek) prvku na pozici source_index v tabulce zdroju
	/**
	 * getSourcePluginIndex:
	 *
	 * @param source_index 
	 * @return int 
	 */
	int getSourcePluginIndex(int source_index);

	// vrati PluginID prvku na pozici source_index v tabulce zdroju
	/**
	 * getSourcePlugin:
	 *
	 * @param source_index 
	 * @return plugin_id_t 
	 */
	plugin_id_t getSourcePlugin(int source_index);	
	
	// vrati handle na otevreny zdroj
	/**
	 * getSourceHandle:
	 *
	 * @param source_index 
	 * @return source_handle_t 
	 */
	source_handle_t getSourceHandle(int source_index);	
	

	// prejmenovani zdroje
	/**
	 * setSourcePublicID:
	 *
	 * @param source_index 
	 * @param source_id 
	 * @return BOOL 
	 */
	BOOL setSourcePublicID(int source_index, public_source_id_t source_id); 

	// test na duplicity v Public ID zdroju v SourcesTab (TRUE=bez duplicit)
	/**
	 * checkSourcePublicIDdupl:
	 *
	 * @param source_index 
	 * @param source_id 
	 * @return BOOL 
	 */
	BOOL checkSourcePublicIDdupl(int source_index, public_source_id_t source_id);
	
	// je zdroj pripojen?
	/**
	 * isSourceConnected:
	 *
	 * @param source_index 
	 * @return BOOL 
	 */
	BOOL isSourceConnected(int source_index);
	
	//pres zasuvku pripoji novy zdroj
	/**
	 * ConnectNewSource:
	 *
	 * @param plugin 
	 * @return int 
	 */
	int ConnectNewSource(plugin_id_t plugin);	//vrati index noveho zdroje, (-1 = chyba)
	/**
	 * ConnectNewSourceThreadFunction:
	 *
	 * @param hNewSourceFn 
	 * @param NewSourcePerzistID 
	 * @param h_hSource 
	 * @return void static 
	 */
	void static ConnectNewSourceThreadFunction(LPARAM hNewSourceFn, LPARAM NewSourcePerzistID, LPARAM h_hSource);
												
	//vyhodi zdroj z tabulky zdroju
	/**
	 * RemoveSource:
	 *
	 * @param source_index 
	 * @return BOOL 
	 */
	BOOL RemoveSource(int source_index);	

	//pripoji jiz znamy zdroj pres zname persistnet_id na indexu source_index
	/**
	 * ConnectSource:
	 *
	 * @param source_index 
	 * @return BOOL 
	 */
	BOOL ConnectSource(int source_index);
	/**
	 * ConnectSourceThreadFunction:
	 *
	 * @param hOpenSourceFn 
	 * @param PID 
	 * @param h_hSource 
	 * @return void static 
	 */
	void static ConnectSourceThreadFunction(LPARAM hOpenSourceFn, LPARAM PID, LPARAM h_hSource);
	
	// uzavre zdroj
	/**
	 * CloseSource:
	 *
	 * @param source_index 
	 * @return BOOL 
	 */
	BOOL CloseSource(int source_index);

	// najde zdroj podle PublicID a vrati jeho index v tabulce
	/**
	 * FindSourceByPublicID:
	 *
	 * @param id 
	 * @return int 
	 */
	int FindSourceByPublicID(public_source_id_t id); //vrati index odpovidajiciho zdroje


	/**
	 * AddSource:
	 *
	 * @param plugin 
	 * @param persistent_id 
	 * @param public_id 
	 * @return int 
	 */
	int AddSource(plugin_id_t plugin, persistent_id_t persistent_id, public_source_id_t public_id);
	// vrati index pridaneho prvku v tabulce zdroju


	//funkce pro zavaloni perform na danem zdroji
	/**
	 * CallPerformProc:
	 *
	 * @param source_index 
	 * @param element_id 
	 * @return void 
	 */
	void CallPerformProc(int source_index, LPCTSTR element_id); //vrati XML string
	/**
	 * GetPluginOutput:
	 *
	 * @param source 
	 * @param ap_name 
	 * @param xml_dom 
	 * @return BOOL 
	 */
	BOOL GetPluginOutput(public_source_id_t source, LPCTSTR ap_name, MSXML2::IXMLDOMDocument ** xml_dom); //zavola CallPerformProc
	/**
	 * PerformThreadFunction:
	 *
	 * @param hPreformFn 
	 * @param hSource 
	 * @param element_id 
	 * @param pOutputBuffer 
	 * @return void static 
	 */
	void static PerformThreadFunction(LPARAM hPreformFn, LPARAM hSource, LPARAM element_id, LPARAM pOutputBuffer);

public:
	/**
	 * defaultSourceDefined:
	 *
	 * @param  
	 * @return BOOL 
	 */
	BOOL defaultSourceDefined(void);
};



#endif // !defined(AFX_DATASOURCEMANAGER_H__976787EC_9D7F_4080_B685_F88419DA19FB__INCLUDED_)
