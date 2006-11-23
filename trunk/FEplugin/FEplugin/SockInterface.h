// version 1.0	14.3.2006	J. Kodym

/*
This header file is a part of LM - Report Assistent project.
It contains definition of important data types and CSockInterface structure, which create an interface between 
LM-Report Asistent kernell and each plugin.
This file should be included in each plugin of LM-Report Asistent

*/

#ifndef _SOCK_INTERFACE
#define _SOCK_INTERFACE

#include <wtypes.h>


/*
structure CSockInterface
------------------------
Structure creates an interface between LM-RA kernell and plugin. It contains a pointers to all functions of plugin, 
which offer a services to kernell:

  //typedef void* hSource_t   - handle on opened data source

1) queries about active elements
- evaluating query about all ocurences of active element with given ID (perform)
- obtaining the list of all active elements supported by FEplugin (getAPList)

 - BOOL perform (hSource_t hSource, const char* APName, BSTR* Result); 
		- gets handle on data source (hSource) and active element ID (APName)
		- stores (to Result) XML string with vsemiall occurences of given active element type from given source
		- return value: TRUE if success, FALSE if not success
	
	  -> hPerform

 - BSTR getAPList();
		- sructure of returned XML string:
		<LIST>
			<APID NAME="ID of active element 1"/>
			<APID NAME="ID of active element 2"/>
			...
		</LIST>

	  -> hGetAPList
 
2) operations with data sources
- creating and opening new data source (fNewSource)
- opening of existing data source (fOpenSource)
- closing of opened data source (fCloseSource)


 - hSource_t fNewSource (PersistID_t * pPerzistID);
		- usually opens a dialog for creating new data source (i.e. find file file, choose ODBC data source ... particular implementation depends just on plugin)
		- stores a perzist ID (i.e. connection string) of new source (i.e. connection string) to pPerzistID
		- opens the new source and returns handle or NULL (error)

	   -> hNewSource

 - hSource_t fOpenSource (PersistID_t PerzistID);
		- gets persist ID os existing (closed) data source (PerzistID)
		- opens the new source and returns handle or NULL (error)

       -> hOpenSource

 - BOOL fCloseSource (hSource_t hSource);
		- gets handle on opened data source (hSource)
		- closes the source and returns TRUE (success) or FALSE (error)

       -> hCloseSource

convention: particular implementation of functions in plugins - an suffix ("identifier" of plugin) is added to end 
of each function name
(i.e. fNewSource() is called fNewSourceLM() in LMplugin, fNewSourceFE() in FEplugin etc...)

/////////////////////////////////////////////////////
//////// initSock()

Each plugin MUST contain an initialization function 

  CSockInterface* initSock()

which creates and initializes an instance of CSockInterface structure. This function must be accessible for LM-RA kernell
(exported from DLL)
While start of LM-Report Asistent, kernell connects plugins by calling initSock() in each DLL found in "Plugin" directory.
If initSock() is not found, plugin is signed as invalid


*/


// ========== DATA TYPES =========


typedef void* hSource_t;	// handle to opened data source
typedef BSTR PersistID_t;	// perzist ID of data source

// TYPES pointers to particular functions of interface

// hPerform_t - type "pointer to perform() function"
typedef BOOL (* hPerform_t) (hSource_t, const char*, BSTR*);

// hGetAPList_t - type "pointer to getAPList() function"
typedef BSTR (* hGetAPList_t) ();

// hNewSource_t - type "pointer to fNewSource() function"
typedef hSource_t (* hNewSource_t) (PersistID_t *);

// hOpenSource_t - type "pointer to (fOpenSource) function"
typedef hSource_t (* hOpenSource_t) (PersistID_t);

// hCloseSource_t - type "pointer to fCloseSource() function"
typedef BOOL (* hCloseSource_t) (hSource_t);


//////////////////////////////////
//  definition of "interface" CSockInterface



/**
*<p>
*Structure creates an interface between LM-RA kernell and plugin. It contains a pointers to all functions of plugin, 
*which offer a services to kernell:
*</p>
*
*  <pre>//typedef void* hSource_t   - handle on opened data source</pre>
*
*<ol>
*  <li>
*<b>queries about active elements</b><br>
*  <ul>
*	<li>evaluating queries about all ocurences of active element with given ID (perform)</li>
*	<li>obtaining the list of all active elements supported by FEplugin (getAPList)</li>
*  </ul>
*  <pre>
* - BOOL perform (hSource_t hSource, const char* APName, BSTR* Result);
*		<br>
*		- gets handle on data source (hSource) and active element ID (APName)
*		- stores (to Result) XML string with vsemiall occurences of given active element type from given source
*		- return value: TRUE if success, FALSE if not success
*		<br>
*      -> hPerform
*  </pre>
*  <pre>
* - BSTR getAPList();
*		<br>
*		- sructure of returned XML string:
*		<br>
*		&lt;LIST&gt;
*			&lt;APID NAME="ID of active element 1"/&gt;
*			&lt;APID NAME="ID of active element 2"/&gt;
*			...
*		&lt;/LIST&gt;
*		<br>
*	  -> hGetAPList
*  </pre>
*  </li>
*  <li> 
*<b>operations with data sources</b><br>
* <ul>
*	<li>creating and opening new data source (fNewSource)</li>
*	<li>opening of existing data source (fOpenSource)</li>
*	<li>closing of opened data source (fCloseSource)</li>
* </ul>
*
* <pre>
* - hSource_t fNewSource (PersistID_t * pPerzistID);
*		<br>
*		- usually opens a dialog for creating new data source (i.e. find file file, choose ODBC data source ... particular implementation depends just on plugin)
*		- stores a perzist ID (i.e. connection string) of new source (i.e. connection string) to pPerzistID
*		- opens the new source and returns handle or NULL (error)
*		<br>
*      -> hNewSource
* 
* - hSource_t fOpenSource (PersistID_t PerzistID);
*		<br>
*		- gets persist ID os existing (closed) data source (PerzistID)
*		- opens the new source and returns handle or NULL (error)
*		<br>
*      -> hOpenSource
*
* - BOOL fCloseSource (hSource_t hSource);
*		<br>
*		- gets handle on opened data source (hSource)
*		- closes the source and returns TRUE (success) or FALSE (error)
*		<br>
*      -> hCloseSource
* </pre>
*   </li>
*</ol>
*<p>
*<b>convention:</b> particular implementation of functions in plugins - an suffix ("identifier" of plugin) is added to end 
*of each function name <br>
*(i.e. fNewSource() is called fNewSourceLM() in LMplugin, fNewSourceFE() in FEplugin etc...)
*</p>
*@see <a href="(FEplugin__globals).html#initSock()">initSock()</a>
*@see <a href="(FEplugin__globals).html#performFE(hSource_t,constchar*,BSTR*)">performFE()</a>
*/
struct CSockInterface {
	// pointers to functions

	hPerform_t	 hPerform;  /// pointer to the "perform()" function of plugin
	hGetAPList_t hGetAPList; /// pointer to function, which returns list of IDs of active elements supported by plugin
	hNewSource_t hNewSource; /// pointer to function, which creates a new data source
	hOpenSource_t hOpenSource; /// pointer to function, which openes an existing (closed) data source
	hCloseSource_t hCloseSource; /// pointer to function, which closes an opened data source
};



/*
 =========================================
*====== initSock()
*
*Each plugin MUST contain an initialization function 
*
*  CSockInterface* initSock()
*
*which creates and initializes an instance of CSockInterface structure. This function must be accessible for LM-RA kernell
*(exported from DLL)
*While start of LM-Report Asistent, kernell connects plugins by calling initSock() in each DLL found in "Plugin" directory.
*If initSock() is not found, plugin is signed as invalid
*/

#endif  // _SOCK_INTERFACE