#include <wtypes.h>


//je to udelany jako indexovany pole, ale poradi se muze behem zivota menit
//to jsem si kdysi neco dal na index 10 neznamena, ze to tam bude navzdy
//ale poradi se meni asi jen funkci RemoveSource
class CDataSorcesManager
{
public:

	//handle na otevreny zdroj v zasuvce
	typedef unsigned int source_handle_t;

	//perzistentni retezec (obshuje napr connection string, cestu k souboru)
	//mozna bude vhodnejsi jiny string - ?char *, _bstr_t, CString? uvidime..
	typedef BSTR persistent_id_t;

	//retezec pouzivany v kostre u AP jako identifikator zdroje
	//mozna bude vhodnejsi jiny string - ?char *, _bstr_t, CString? uvidime..
	typedef BSTR public_source_id_t;

	//identifikuje zasuvku
	//odkaz na plugin managera
	//mozna bude lesi pouzit retezec jmeno dll knihovny - lze jednoznacne ulozit do XML
	typedef unsigned int plugin_id_t;

	//identifikator typu aktivniho prvku
	typedef _bstr_t ap_id_t;

	
	int getSourcesCount();
	
	public_source_id_t getSourcePublicID(int source_index);
	persistent_id_t getSourcePersistentID(int source_index);
	source_handle_t getSourceHandle(int source_index);	
	plugin_id_t getSourcePlugin(int source_index);

	BOOL setSourcePublicID(int source_index, public_source_id_t source_id); //prejmenovani zdroje
	
	BOOL isSourceConnected(int source_index);
	
	int ConnectNewSource(plugin_id_t plugin);	//pres zasuvku pripoji novy zdroj
												//vrati index noveho zdroje

	BOOL RemoveSource(int source_index);	//vyhodi zdroj z tabulky zdroju

	BOOL ConnectSource(int source_index);
	//pripoji jiz znamy zdroj pres zname persistnet_id na indexu source_index
	
	BOOL CloseSource(int source_index);

	int FindSourceByPublicID(public_source_id_t id); //vrati index odpovidajiciho zdroje


	//dal tady budou muset byt metody na reseni sirotku a pretahovani AP z koster,
	//ktere treba nebyly vytvoreny pomoci tohoto SourcesManageru - tedy se sem bude muset nejak
	//cast jejich source manageru pretahnout
	//predbezne:
	int AddSource(plugin_id_t plugin, persistent_id_t persistent_id, public_source_id_t public_id);


	//metody na ulozeni a nacteni SorcesManageru - potencialne ukladat primo do kostry..
	//ty se pouziji v konstruktoru/destruktoru
	//predbezne:
	BOOL LoadFromXML(BSTR xml_string);
	BSTR SaveToXML(); //vrati XML string

	
	//a tady nebo v plugin mamageru budou funkce pro zavaloni perform na danem zdroji
	//predbezne:
	BSTR CallPerformProc(int source_index, BSTR element_id); //vrati XML string
};

