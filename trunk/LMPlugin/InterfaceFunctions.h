/*
InterfaceFunctions.h
LM - Report Asistent
- implementace funkci zasuvky pro LM
- popis rozhrani - viz "SockInterface.h"
*/
/*
This file is part of LM Report Asistent.

Authors: Jan Dedek, Jan Kodym, Martin Chrz, Iva Bartunkova

LM Report Asistent is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

Foobar is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Foobar; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/


#ifndef _INTERFACE_FUNCTIONS
#define _INTERFACE_FUNCTIONS

#ifndef WINVER
#define WINVER 0x0400
#endif

#include <afx.h>
#include "SockInterface.h"
#include <wtypes.h>
#include <sqltypes.h>



// =========== FUNKCE =============================

/////// funkce, ktere tvori rozhrani mezi zasuvkou a "spravcem zasuvek a zdroju"
/////// (odkaz na ne ze struktury CSockInterface)

// ---------- performLM 
/*
hlavni rozhrani mezi jadrem a LM zasuvkou - vyrizuje vsechny pozadavky jadra na poskytnuti vsech 
AP urciteho typu z nektereho zdroje  pripojeneho k teto zasuvce

parametry:  hSource - otevreny handle na zdroj
			APName  - ID aktivniho prvku, jehoz vsechny vyskyty ze zdroje hSource chci ziskat
			Result  - ukazatel na retezec, kam se ulozi vystup (musi se ale naalokovat)
navratova hodnota:	TRUE - do Result ulozen vystup,  FALSE - chyba (zasuvka nepodporuje tentu AP)
*/

/**
 * The main interface between the kernel and the LM socket. It handles all the queries,
 * asked by the kernel, to retrieve all the active elements of the certain type from some
 * source which is connected to this socket.
 *
 * @param hSource Opened data source.
 * @param APName The ID of the active element, which occurences are retrieved from the given data source.
 * @param Result The pointer to the string containing the output.
 * @return Returns FALSE if some error occured during the processing or TRUE, if the
 * function was successfuly evaluated.
 */
BOOL performLM (hSource_t hSource, const char* APName, BSTR* Result);


// ---------- getAPListLM
/*
funkce vrati volajicimu XML string (stejny format jako CString CLMSock::getAPList())
s identifikatory vsech AP, ktere tato zasuvka podporuje
*/

/**
 *
 * @return Returns the XML string containing the identifiers of the all active elements supported
 * by the socket.
 */
BSTR getAPListLM();



///// funkce rozhrani pro praci se zdroji

// --- fNewSourceLM
/*
otevre dialog pro vyber noveho zdroje
po navratu z dialogu do retezce pPerzistID ulozi connection string noveho zdroje
novy zdroj otevre a vrati na nej handler nebo NULL (chyba)
*/

/**
 * Opens the dialog to choose the new data source and openes the created data source.
 *
 * @param pPerzistID Contains the connection string of the new data source.
 * @return Handle to the new data source or NULL if unsuccessful.
 */
hSource_t fNewSourceLM (BSTR* pPerzistID);


// --- fOpenSourceLM
/*
dostane connection string (PerzistID)
otevre zdroj a vrati na nej handle nebo NULL (chyba)
*/
/**
 * Opens the data source.
 *
 * @param PerzistID The connection string of the data source to be opened.
 * @return Handle to the opened data source or NULL if unsucessfull.
 */
hSource_t fOpenSourceLM (BSTR PerzistID);


// --- fCloseSourceLM
/*
dostane otevreny handler na zdroj (hSource)
uzavre handler a vrati TRUE (uspech) nebo FALSE (chyba)
*/

/**
 * Closes the opened data source.
 *
 * @param hSource Handle to the opened data source.
 * @return TRUE if successful, else false.
 */
BOOL fCloseSourceLM (hSource_t hSource);


























#endif    // _INTERFACE_FUNCTIONS