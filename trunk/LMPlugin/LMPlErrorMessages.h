//LMPlErrorMessages.h
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
/*
All the error messages (formated) for LMplugin are in this file
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

//LMP004 - Can not create temporary ODBC for AR2NL
#define LMERR_CANNOT_CREATE_ODBC "The application couldn't create temporary ODBC source for AR2NL."

//LMP005 - Can not remove temporary ODBC for AR2NL
#define LMERR_CANNOT_REMOVE_ODBC "The application couldn't delete temporary ODBC source for AR2NL."

//LMP006 - Can not find the AR2NL application path
#define LMERR_CANNOT_FIND_AR2NL_EXE_PATH "The application didn't find the directory for AR2NL: %s"

//LMP007 - The application couldn't launch AR2NL
#define LMERR_AR2NL_EXE_FAIL "The application couldn't launch AR2NL from location %s."

//LMP008 - The application couldn't determine AR2NL exit code
#define LMERR_AR2NL_EXIT_FAIL "The application couldn't determine AR2NL exit code."

//LMP009 - The application couldn't read AR2NL output
#define LMERR_CANNOT_READ_AR2NL_OUTPUT "The application couldn't read AR2NL output."

//LMP010 - The application couldn't read AR2NL output
#define LMERR_AR2NL_ERR "Error occurred while processing the AR2NL task."

//LMP011 - This version of metabase is not supported by LMRA
#define LMERR_BAD_MDB_VERSION "This version of metabase is not supported by LM Report Asistent.\nYou have probably the old version of LM metabase. Use the new one."

//LMP012 - The application couldn't read the file containing DTD
#define LMERR_DTD_ERROR "The application couldn't read the DTD file for active elements."
// ==============================================================

#endif