// DataSourceManager.h: interface for the CDataSourceManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATASOURCEMANAGER_H__976787EC_9D7F_4080_B685_F88419DA19FB__INCLUDED_)
#define AFX_DATASOURCEMANAGER_H__976787EC_9D7F_4080_B685_F88419DA19FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



// ================= INCLUDE ==================================
#include <afxtempl.h>
#include "../LMPlugin/SockInterface.h"



/// ================= MAKRA ===================================

// --- cesty k adresarum

// cesta do adresare Plugin k souborum typu .dll
#define _PLUGIN_DIR_PATH "Plugin\\"

// cesta do adresare Config ke konfiguracnim souborum (spravce zdroju atd.)
#define _CONF_DIR_PATH "Config\\"


// --- jmena konfiguracnich souboru

// konf. XML soubor s datovymi zdroji
#define _CONF_FILE_SOURCES "sources.xml"

// --- rozhrani

// jmeno funkce, ktera vrati jadru ukazatel na rozhrani (strukturu CSockInterface)
#define _SOCK_IFACE_FN_NAME "initSock"



// ================= DATOVE TYPY =============================

// typ ukazatel na funkci _SOCK_IFACE_FN_NAME
typedef CSockInterface* (* pSockIfaceFn_t) ();


// --- polozky tabulky zdroju

//retezec pouzivany v kostre u AP jako identifikator zdroje
	typedef CString public_source_id_t;

//perzistentni retezec (obshuje napr connection string, cestu k souboru)
	typedef CString persistent_id_t;

//identifikuje zasuvku
//jmeno DLL souboru zasuvky v adresari Plugin
	typedef CString plugin_id_t;

//index zasuvky v tabulce zasuvek
	typedef int plugin_index_t;

//ukazatel na otevreny zdroj
	typedef void* source_handle_t;

// ================== TRIDY ==================================


// --------- CPluginRec - polozka tabulky zasuvek
class CPluginRec 
{
public:
	plugin_id_t   PluginName;	// jmeno dll knihovny zasuvky v adresari Plugin
	HMODULE       hLib;			// handle na otevrenou DLL
	CSockInterface* SockInterface;	// ukazatel na instanci CSockInterface (rozhrani zasuvky) ktera se v zasuvce
									// vytvori po pripojeni. Tuto polozku vrati fce initSock() v zasuvce
	BOOL Valid();						// priznak, zda je DLL platna (implementuje zasuvku) a byla vporadku pripojena

	// konstruktor a destruktor
	CPluginRec(plugin_id_t Name = "");
	~CPluginRec();
};

// --------- CSourceRec - polozka tabulky zdroju
class CSourceRec
{
public:
	public_source_id_t PublicID;	// v kostre u AP jako identifikator zdroje
	persistent_id_t    PerzistID;	// connection string
	plugin_id_t	       PluginID;	// jedna z PluginName v tabulce zasuvek
	source_handle_t	   SourceHandle;// handle na otevreny zdroj

	
	int	PluginIndex;  // index zaznamu v tabulce zasuvek, jejiz PluginName se shoduje s PluginID teto instance
					  // == -1 pokut takovy neexistuje

	BOOL Valid();					// priznak, zda je tento zaznam v poradku


	// konstruktor
	CSourceRec();
};

// ===========================================================

//je to udelany jako indexovany pole, ale poradi se muze behem zivota menit
//to jsem si kdysi neco dal na index 10 neznamena, ze to tam bude navzdy
//ale poradi se meni asi jen funkci RemoveSource
class CDataSourcesManager
{
private:
	public_source_id_t default_source;
//  DATA
	CArray<CPluginRec,CPluginRec> PlugsTab;		// tabulka zasuvek
	CArray<CSourceRec,CSourceRec> SourcesTab;	// tabulka zdroju

public:
	void setDefaultSource(public_source_id_t source);
	public_source_id_t getDefaultSource();
	BOOL isPluginValid(int plugin_index);
	BOOL isSourceValid(int source_index);

	

// METODY
	// konstruktor a destruktor
	CDataSourcesManager();
	~CDataSourcesManager();

	// inicializuje tabulku zasuvek, vrati pocet zasuvek
	int initPlugsTab();

	// inicializuje tabulku zdroju z konfiguracniho XML souboru
	BOOL initSourcesTab();
	// ulozi tabulku zdroju do konfiguracniho XML souboru
	BOOL saveSourcesTab();



	// --- pristupove metody do tabulky zasuvek (PlugsTab)
	
	// pocet pripojenych zasuvek (prvku PlugsTab) / pocet pripojenych platnych zasuvek
	int getPlugsCount();			
	int getValidPlugsCount();

	// vrati PluginName zasuvky na dane pozici
	plugin_id_t getPluginID(int plugin_index);

	//  vrati index v PlugsTab, kdr je zasuvka s PluginName name nebo -1 (nenalezeno)
	int FindPluginByPluginName(plugin_id_t name);



	// --- pristupove a konfiguracni metody do tabulky zdroju (SourcesTab)

	// vrati pocet zdroju (prvku v tabulce SourcesTab)
	int getSourcesCount();
	int getValidSourcesCount();

	// vrati PublicID prvku na pozici source_index v tabulce zdroju
	public_source_id_t getSourcePublicID(int source_index);

	// vrati PerzistentID prvku na pozici source_index v tabulce zdroju
	persistent_id_t getSourcePersistentID(int source_index);

	// vrati PluginID prvku na pozici source_index v tabulce zdroju
	plugin_id_t getSourcePlugin(int source_index);	
	
	// vrati handle na otevreny zdroj
	source_handle_t getSourceHandle(int source_index);	
	

	// prejmenovani zdroje
	BOOL setSourcePublicID(int source_index, public_source_id_t source_id); 
	
	// je zdroj pripojen?
	BOOL isSourceConnected(int source_index);
	
	//pres zasuvku pripoji novy zdroj
	int ConnectNewSource(plugin_id_t plugin);	//vrati index noveho zdroje, (-1 = chyba)
												
	//vyhodi zdroj z tabulky zdroju
	BOOL RemoveSource(int source_index);	

	//pripoji jiz znamy zdroj pres zname persistnet_id na indexu source_index
	BOOL ConnectSource(int source_index);
	
	// uzavre zdroj
	BOOL CloseSource(int source_index);

	// najde zdroj podle PublicID a vrati jeho index v tabulce
	int FindSourceByPublicID(public_source_id_t id); //vrati index odpovidajiciho zdroje


	//dal tady budou muset byt metody na reseni sirotku a pretahovani AP z koster,
	//ktere treba nebyly vytvoreny pomoci tohoto SourcesManageru - tedy se sem bude muset nejak
	//cast jejich source manageru pretahnout
	//predbezne:
	int AddSource(plugin_id_t plugin, persistent_id_t persistent_id, public_source_id_t public_id);
	// vrati index pridaneho prvku v tabulce zdroju


	//metody na ulozeni a nacteni SorcesManageru - potencialne ukladat primo do kostry..
	//ty se pouziji v konstruktoru/destruktoru
	//predbezne:
/* kody - tohle asi stejne nebudes pouzivat, ne? To uz delaj jiny funkce

	BOOL LoadFromXML(BSTR xml_string);
	BSTR SaveToXML(); //vrati XML string

*/	
	//a tady nebo v plugin mamageru budou funkce pro zavaloni perform na danem zdroji
	//predbezne:
	BSTR CallPerformProc(int source_index, LPCTSTR element_id); //vrati XML string
	BSTR GetPluginOutput(public_source_id_t source, LPCTSTR ap_name); //zavola CallPerformProc


/* kody - pro Dedu
  // alternativa
	BOOL CallPerformProc(int source_index, char* element_id, BSTR* Result);
*/
};



#endif // !defined(AFX_DATASOURCEMANAGER_H__976787EC_9D7F_4080_B685_F88419DA19FB__INCLUDED_)
