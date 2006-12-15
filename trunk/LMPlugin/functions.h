// Funkce pro vyrizeni pozadavku na AP v zasuvce pro LM
// functions.h
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

#ifndef _FUNCTIONS
#define _FUNCTIONS

#ifndef WINVER
#define WINVER 0x0400

#ifndef HYPOTHESIS_LIMIT
#define HYPOTHESIS_LIMIT 10000
#endif

#endif

// ===== INCLUDE =======

#include <afx.h>

// ===== FUNKCE ========

// ---AP Quantifier

/**
 * Finds all the LM quantifiers in the given data source.
 *
 * @param hSource Handle to the the source, from where the data are retrieved
 * @return XML string containing all the quantifiers in the given data source
 */
CString fLMQuantifier (void* hSource);

// ---AP Task

/**
 * Finds all the LM tasks in the given data source.
 *
 * @param hSource Handle to the the source, from where the data are retrieved
 * @return XML string containing all the task in the given data source
 */
CString fLMTask (void* hSource);

// ---AP KL cedent

/**
 * Finds all the LM KL cedents in the given data source.
 *
 * @param hSource Handle to the the source, from where the data are retrieved
 * @return XML string containing all the KL cedents in the given data source 
 */
CString fLMKLCedent (void* hSource);

// ---AP CF cedent

/**
 * Finds all the LM CF cedents in the given data source.
 *
 * @param hSource Handle to the the source, from where the data are retrieved
 * @return XML string containing all the CF cedents in the given data source 
 */
CString fLMCFCedent (void* hSource);

// ---AP bool cedent

/**
 * Finds all the LM bool cedents in the given data source.
 *
 * @param hSource Handle to the the source, from where the data are retrieved
 * @return XML string containing all the bool cedents in the given data source 
 */
CString fLMBoolCedent (void* hSource);

// ---AP attribute

/**
 * Finds all the LM attributes in the given data source.
 *
 * @param hSource Handle to the the source, from where the data are retrieved
 * @return XML string containing all the attributes in the given data source  
 */
CString fLMAttribute(void* hSource);

// --- AP category

/**
 * Finds all the LM categories in the given data source.
 *
 * @param hSource Handle to the the source, from where the data are retrieved
 * @return XML string containing all the categories in the given data source  
 */
CString fLMCategory(void* hSource);


// --- AP 4ft-hypothese

/**
 * Finds all the LM 4FT hypothesis in the given data source.
 *
 * @param hSource Handle to the the source, from where the data are retrieved
 * @return XML string containing all the 4FT hypothesis in the given data source  
 */
CString fLM4fthyp(void* hSource);

// --- AP CF-hypothese

/**
 * Finds all the LM CF hypothesis in the given data source.
 *
 * @param hSource Handle to the the source, from where the data are retrieved
 * @return XML string containing all the CF hypothesis in the given data source  
 */
CString fLMCFhyp(void* hSource);

// --- AP SD4FT-hypotese

/**
 * Finds all the LM SD4FT hypothesis in the given data source.
 *
 * @param hSource Handle to the the source, from where the data are retrieved
 * @return XML string containing all the SD4FT hypothesis in the given data source  
 */
CString fLMSD4fthyp(void * hSource);

// --- AP SDCF-hypothese

/**
 * Finds all the LM SDCF hypothesis in the given data source.
 *
 * @param hSource Handle to the the source, from where the data are retrieved
 * @return XML string containing all the SDCF hypothesis in the given data source  
 */
CString fLMSDCFhyp(void * hSource);

// --- AP KL-hypothese

/**
 * Finds all the LM KL hypothesis in the given data source.
 *
 * @param hSource Handle to the the source, from where the data are retrieved
 * @return XML string containing all the KL hypothesis in the given data source  
 */
CString fLMKLhyp(void * hSource);

// --- AP SDKL-hypothese

/**
 * Finds all the LM SDKL hypothesis in the given data source.
 *
 * @param hSource Handle to the the source, from where the data are retrieved
 * @return XML string containing all the SDKL hypothesis in the given data source  
 */
CString fLMSDKLhyp(void * hSource);

// --- AP 4FT hypothesis including AR2NL sentences

/**
 * Finds all the LM 4FT hypothesis including AR2NL sentences in the given data source.
 *
 * @param hSource Handle to the the source, from where the data are retrieved
 * @return XML string containing all the 4FT hypothesis including AR2NL sentences in the given data source  
 */
CString fLM4fthyp_ar2nl(void* hSource);

// --- AP Analyzed data matrix

/**
 * Finds the details about the analyzed data matrix in the given data source.
 *
 * @param hSource Handle to the the source, from where the data are retrieved
 * @return XML string containing all the details about the analyzed data matrix in the given data source  
 */
CString fLMdata_matrix (void* hSource);

/**
 * Finds all the columns of the analyzed data matrix in the given data source.
 *
 * @param hSource Handle to the the source, from where the data are retrieved
 * @return XML string containing all the columns of the analyzed data matrix in the given data source  
 */
CString fLMcolumn (void* hSource);

#endif /* _FUNCTIONS*/