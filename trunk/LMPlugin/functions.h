// Funkce pro vyrizeni pozadavku na AP v zasuvce pro LM
// functions.h

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

CString fLMQuantifier (void* hSource);

// ---AP Task

CString fLMTask (void* hSource);

// ---AP KL cedent

CString fLMKLCedent (void* hSource);

// ---AP CF cedent

CString fLMCFCedent (void* hSource);

// ---AP bool cedent

CString fLMBoolCedent (void* hSource);

// ---AP attribute

CString fLMAttribute(void* hSource);

// --- AP category

CString fLMCategory(void* hSource);


// --- AP 4ft-hypothese

CString fLM4fthyp(void* hSource);

// --- AP CF-hypothese

CString fLMCFhyp(void* hSource);

// --- AP SD4FT-hypotese

CString fLMSD4fthyp(void * hSource);

// --- AP SDCF-hypothese

CString fLMSDCFhyp(void * hSource);

// --- AP KL-hypothese

CString fLMKLhyp(void * hSource);

// --- AP SDKL-hypothese

CString fLMSDKLhyp(void * hSource);

CString fLM4fthyp_ar2nl(void* hSource);

#endif /* _FUNCTIONS*/