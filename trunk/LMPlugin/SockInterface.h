//SockInterface.h
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

/////////////////////////////////////////////////////
//////// initSock()

Kazda zasuvka musi obsahovat funkci 

  CSockInterface* initSock()

ktera vytvori a inicializuje strukturu CSockInterface a vrati jadru ukazatel na ni. 
Jadro pripojuje zasuvky tak, ze zavola funkci initSock()


*/


// ========== DATOVE TYPY =========


/**
 * handle to the open data source
 */
typedef void* hSource_t;	// handler na otevreny zdroj
/**
 * persist ID of the data source
 */
typedef BSTR PersistID_t;	// perzistentni ID zdroje

// typy ukazatele na jednotlive funkce rozhranni

// hPerform_t - typ "ukazatel na funkci perform()"
/**
 * pointer to the perform() function
 */
typedef BOOL (* hPerform_t) (hSource_t, const char*, BSTR*);

// hGetAPList_t - typ "ukazatel na funkci getAPList()"
/**
 * pointer to the getAPList() function
 */
typedef BSTR (* hGetAPList_t) ();

// hNewSource_t - typ "ukazatel na funkci fNewSource()"
/**
 * pointer to the fNewSource() function
 */
typedef hSource_t (* hNewSource_t) (PersistID_t *);

// hOpenSource_t - typ "ukazatel na funkci (fOpenSource)"
/**
 * pointer to the fOpenSource() function
 */
typedef hSource_t (* hOpenSource_t) (PersistID_t);

// hCloseSource_t - typ "ukazatel na funkci fCloseSource()"
/**
 * pointer to the fCloseSource() function
 */
typedef BOOL (* hCloseSource_t) (hSource_t);


//////////////////////////////////
//  definice rozhrani CSockInterface

/**
 * The structure creates the interface between the socket and the kernel.
 * It contains the pointers to all of the funcions in the socket, which supply the services
 * to the kernel. These services are queries and manipulation with the data sources.
 *
 * @author Jan Kodym
 */
struct CSockInterface {
	// ukazatele na funkce

	hPerform_t	 hPerform;/// pointer to the perform() function
	hGetAPList_t hGetAPList;/// pointer to the getAPList() function
	hNewSource_t hNewSource;/// pointer to the fNewSource() function
	hOpenSource_t hOpenSource;/// pointer to the fOpenSource() function
	hCloseSource_t hCloseSource;/// pointer to the fCloseSource() function
};





#endif  // _SOCK_INTERFACE