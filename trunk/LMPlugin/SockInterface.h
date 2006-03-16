// verze 1.0	14.3.2006	J. Kodym

#ifndef _SOCK_INTERFACE
#define _SOCK_INTERFACE

#include <wtypes.h>


/*
struktura CSockInterface
------------------------
struktura tvori interface mezi zasuvkou a jadrem. Obsahuje ukazatele na vsechny 
funkce zasuvky, ktere poskytuji sluzby jadru. Jsou to:

  //typedef void* hSource_t   - handler na otevreny zdroj

1) dotazy
- provedeni dotazu na aktivni prvek (perform)
- ziskani seznamu vsech AP podporovanych v zasuvce (getAPList)

 - BOOL perform (hSource_t hSource, const char* APName, BSTR* Result); 
		- dostane handle na zdroj (hSource) a ID Akt. prvku (APName)
		- vrati (do Result) XML string se vsemi AP tohoto typu z tohoto zdroje
		- navratova hodnota: FALSE pri neuspechu
	
	  -> hPerform

 - BSTR getAPList();
		- format vraceneho stringu:

	  -> hGetAPList
 
2) manipulace se zdroji
- vytvoreni a otevreni noveho zdroje (fNewSource)
- otevreni znameho zdroje (fOpenSource)
- zavreni otevreneho zdroje (fCloseSource)


 - hSource_t fNewSource (PersistID_t * pPerzistID);
		- otevre dialog pro vyber noveho zdroje
		- po navratu z dialogu do retezce pPerzistID ulozi connection string noveho zdroje
		- novy zdroj otevre a vrati na nej handler nebo NULL (chyba)

	   -> hNewSource

 - hSource_t fOpenSource (PersistID_t PerzistID);
		- dostane connection string (PerzistID)
		- otevre zdroj a vrati na nej handle nebo NULL (chyba)

       -> hOpenSource

 - BOOL fCloseSource (hSource_t hSource);
		- dostane otevreny handler na zdroj (hSource)
		- uzavre handler a vrati TRUE (uspech) nebo FALSE (chyba)

       -> hCloseSource

konvence: konkretni implementace funkci v zasuvkach - na konec nazvu fce se prida
"identifikator zasuvky"
(tj. fNewSource() se bude v zasuvce pro LM jmenovat fNewSourceLM() atd...)

*/


// ========== DATOVE TYPY =========


typedef void* hSource_t;	// handler na otevreny zdroj
typedef BSTR PersistID_t;	// perzistentni ID zdroje

// typy ukazatele na jednotlive funkce rozhranni

// hPerform_t - typ "ukazatel na funkci perform()"
typedef BOOL (* hPerform_t) (hSource_t, const char*, BSTR*);

// hGetAPList_t - typ "ukazatel na funkci getAPList()"
typedef BSTR (* hGetAPList_t) ();

// hNewSource_t - typ "ukazatel na funkci fNewSource()"
typedef hSource_t (* hNewSource_t) (PersistID_t *);

// hOpenSource_t - typ "ukazatel na funkci (fOpenSource)"
typedef hSource_t (* hOpenSource_t) (PersistID_t);

// hCloseSource_t - typ "ukazatel na funkci fCloseSource()"
typedef BOOL (* hCloseSource_t) (hSource_t);


//////////////////////////////////
//  definice rozhrani CSockInterface

struct CSockInterface {
	// ukazatele na funkce

	hPerform_t	 hPerform;
	hGetAPList_t hGetAPList;
	hNewSource_t hNewSource;
	hOpenSource_t hOpenSource;
	hCloseSource_t hCloseSource;	 
};


#endif  // _SOCK_INTERFACE