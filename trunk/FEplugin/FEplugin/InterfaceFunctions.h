
//InterfaceFunctions.h: implementation(file)
//
//
// This file is part of LM Report Asistent. (http://reportasistent.berlios.de, reportasistent-list@lists.berlios.de)
//
// Authors: Jan Dedek, Jan Kodym, Martin Chrz, Iva Bartunkova 
//
// LM Report Asistent is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// LM Report Asistent is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with LM Report Asistent; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
/*
InterfaceFunctions.h
LM - Report Asistent

- implementation of FEplugin functions
- description of interface - see "SockInterface.h"
*/


#ifndef _INTERFACE_FUNCTIONS_FE
#define _INTERFACE_FUNCTIONS_FE

#include <afx.h>
#include "SockInterface.h"
#include <wtypes.h>




// =========== FUNCTIONS =============================

// functions, which creates an interface between FEplugin and "Data sources manager"
// (these functions are referenced from structure CSockInterface)

// ---------- performFE 

/**
*Evaluates all queries ok LM-RA kernell about all types of active elements. Returns a list (XML string) of
*all occurences of given active element in given data source (connected to FEplugin)
*@return TRUE - result XML string was stored to Result,  FALSE - an error occured (i.e. active element is not supported by FEplugin)
*@see CSockInterface 
*@param hSource  handle to opened data source
*@param APName   ID of active element
*@param Result   pointer to string, where function should save the result XML string (will be allocated in function)
*/
BOOL performFE (hSource_t hSource, const char* APName, BSTR* Result);


// ---------- getAPListFE
/**
*Returns a XML string (structure described in CString CFESock::getAPList())
*with IDs of all active elements supported by FEplugin
*@see CFESock::getAPList
*@retutn XML string with IDs of all active elements supported by FEplugin
*/
BSTR getAPListFE();



///// working with data sources functions


// --- fNewSourceFE
/**
*Creates a new data source of FEplugin:
*<ul>
*	<li>openes a dialod for creating new data source - user sets a path to file with Ferda project</li>
*	<li>saves a persistent ID (connection string) of new source to string pPerzistID</li>
*	<li>openes newly created source</li>
*</ul>
*@return handle on newly created data source or NULL (error)
*@parameter pPerzistID place to store a perzistent ID of new data source
*/
hSource_t fNewSourceFE (BSTR* pPerzistID);


// --- fOpenSourceFE
/**
*<ul>
*	<li>gets a (connection string) perzist ID of data source (PerzistID)</li>
*	<li>opens data source with given perzist ID</li>
*</ul>
*@return handle or opened source or NULL (error)
*/
hSource_t fOpenSourceFE (BSTR PerzistID);


// --- fCloseSourceFE
/**
*<ul>	
*	<li>gets handle on opened data source (hSource)</li>
*	<li>closes data source</li>
*</ul>
*@return TRUE (success) or FALSE (error)
*/
BOOL fCloseSourceFE (hSource_t hSource);




#endif    // _INTERFACE_FUNCTIONS_FE