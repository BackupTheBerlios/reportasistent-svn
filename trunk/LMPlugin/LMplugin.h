//LMplugin.h
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
#ifndef _LMplugin
#define _LMplugin


#ifndef WINVER
#define WINVER 0x0400
#endif
#include <afx.h>
#include <afxdisp.h>
#include "SockInterface.h"
#include "functions.h"

// number of supported active elements
#define _LM_AP_COUNT 16


// =========== TYPES ===============================

/**
 * pointer to the function, which resolve the kernel query of the certain type
 */
typedef CString (* pFn_t) (void*);



// =========== CLASSES ==============================

// ------------ class CLMSock

/**
 * Creates and manages the table of the supported active elements and the functions,
 * which evaluates the queries for this active elements.
 *
 * @author Jan Kodym
 */
class CLMSock {

// TYPY

  /**
 * the item of the table of supported active elements and associated functions
 *
 * @author Jan Kodym
 */
typedef struct Item_t {
	  CString AP_ID;	/// ID of the active element
	  pFn_t   pFn;		/// pointer to the function for this active element
  };

// DATA

  int APCount;	/// number of active elements supported by the socket

  Item_t APTable[_LM_AP_COUNT];	/// table of active elements and functions

// METODY

  pFn_t getFnAddress(CString APName);	/// returns the address of the function associated to the active element with the id AP_ID=APName or NULL (if it doesn't exists)

public:
  
  CLMSock();	/// constructor
  
  CString getAPList();	/// return the list of all the IDs of the supported active elements

// STATIC
  /**
 * Displays the error message on the screen.
 *
 * @param nErrorID ID of the error
 * @param FormatString Error message (formated as e.g. C++ printf function)
 * @param ... Additional error messages
 * @return 0, if there is not enough memory to display the message
 */
static int ReportError(UINT nErrorID, const char* FormatString, ...);


// FRIENDS

  friend BOOL performLM (void* hSource, const char* APName, BSTR* Result); // funkce perform zasuvky pro LM
};


// =========== GLOBAL VARIABLES ==================


extern CLMSock LMSock;
extern CSockInterface SockInterfaceLM;  // rozhrani zasuvky





/////////////////////////////////////////
/////// initSock
// initializes the global instantion of SockInterface and returns its pointer to the object which called this method (kernel)

CSockInterface* initSock();



#endif	// _LMplugin