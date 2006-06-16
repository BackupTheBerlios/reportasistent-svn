// Funkce pro vyrizeni pozadavku na AP v zasuvce pro Ferdu
// functions.h

#ifndef _FUNCTIONS_FE
#define _FUNCTIONS_FE

// ===== INCLUDE =======

#include <afx.h>

// ===== FUNKCE ========


// --- AP Kategorie

CString fFECategory(void* hSource);


// --- AP Hypotezy

CString fFE4fthyp(void* hSource);  // 4ft-hypoteza
CString fFEsd4fthyp(void* hSource);  // SD-4ft-hypoteza
CString fFEklhyp(void* hSource);  // KL-hypoteza
CString fFEsdklhyp(void* hSource);  // SD-KL-hypoteza
CString fFEcfhyp(void* hSource);  // CF-hypoteza
CString fFEsdcfhyp(void* hSource);  // SD-CF-hypoteza

// --- AP Atribut

CString fFEAttribute(void* hSource);

// --- AP Boolsky cedent

CString fFEBool_cedent(void* hSource);

// --- AP KL cedent

CString fFEKL_cedent(void* hSource);

// --- AP CF cedent

CString fFECF_cedent(void* hSource);

// --- AP Kvantifikator

CString fFEQuantifier(void* hSource);

// --- AP Task

CString fFETask(void* hSource);


#endif /* _FUNCTIONS*/