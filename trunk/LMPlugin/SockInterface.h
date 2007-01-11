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
The structure creates the interface between the socket and the kernel.
It contains the pointers to all the socket functions, which provides the services
to the kernell. The servicess are following:

  //typedef void* hSource_t   - handle of the opened data source

1) queries
- performs the query to the active element (perform)
- gets the list of all supported active elements in this socket (getAPList)

 - BOOL perform (hSource_t hSource, const char* APName, BSTR* Result); 
		- takes the handle to the source (hSource) and the active element (AE) ID (APName)
		- returns (in Result) the XML string with all AEs of this type in this source
		- return value: FALSE if unsuccessful
	
	  -> hPerform

 - BSTR getAPList();
		- the formate of the returned string:

	  -> hGetAPList
 
2) sources manipulation
- creates and openes the new source (fNewSource)
- openes the new source (fOpenSource)
- closes the source (fCloseSource)


 - hSource_t fNewSource (PersistID_t * pPerzistID);
		- opens the dialog to select the new source
		- the connection string of the new source is stored to PerzistID variable
		- opens the new source and returns its handle or NULL (error)

	   -> hNewSource

 - hSource_t fOpenSource (PersistID_t PerzistID);
		- gets the connection string (PerzistID)
		- opens the new source and returns its handle or NULL (error)

       -> hOpenSource

 - BOOL fCloseSource (hSource_t hSource);
		- gets the opened handle to the source (hSource)
		- closes the handle and returns TRUE (success) or FALSE (error)

       -> hCloseSource

convention: the implementation of the functions in the sockets - the socket identifier
is added to the end of the name
(ie. fNewSource() will have the name fNewSourceLM() in the LM socket)

/////////////////////////////////////////////////////
//////// initSock()

every socket must contain the function

  CSockInterface* initSock()

which creates and initializes the structure CSockInterface and returns it pointer to the kernel. 
The kernel connects the sockets by calling the initSock() function.


*/


// ========== DATA TYPES =========


/**
 * handle to the open data source
 */
typedef void* hSource_t;	// handler na otevreny zdroj
/**
 * persist ID of the data source
 */
typedef BSTR PersistID_t;	// perzist ID of the source

// types: pointers to the functions of the interface

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
//  definition of the interface CSockInterface

/**
 * The structure creates the interface between the socket and the kernel.
 * It contains the pointers to all of the funcions in the socket, which supply the services
 * to the kernel. These services are queries and manipulation with the data sources.
 *
 * @author Jan Kodym
 */
struct CSockInterface {
	//pointers to the functions

	hPerform_t	 hPerform;/// pointer to the perform() function
	hGetAPList_t hGetAPList;/// pointer to the getAPList() function
	hNewSource_t hNewSource;/// pointer to the fNewSource() function
	hOpenSource_t hOpenSource;/// pointer to the fOpenSource() function
	hCloseSource_t hCloseSource;/// pointer to the fCloseSource() function
};





#endif  // _SOCK_INTERFACE