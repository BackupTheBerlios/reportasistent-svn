/*
V tomto souboru jsou jako makra vsechny chybove zpravy (formatovaci retezce) pro LMplugin
*/

#ifndef _LM_PLUGIN_ERR_MSG

#define _LM_PLUGIN_ERR_MSG

// ==============================================================

// LMP001 - Microsoft Access driver not found
#define LMERR_ACCESSDRV_NFOUND "Required ODBC Microsoft Access driver (*.mdb) not found on this computer.\nNew data source can not be created."

// LMP002 - Data source can not be created for another reason
#define LMERR_CANNOT_CREATE_SOURCE "Data source with persist ID \"%s\" can't be created. Reason: %s"

// LMP003 - Data source can not be opened for another reason
#define LMERR_CANNOT_OPEN_SOURCE "Data source with persist ID \"%s\" can't be opened. Reason: %s"



// ==============================================================

#endif