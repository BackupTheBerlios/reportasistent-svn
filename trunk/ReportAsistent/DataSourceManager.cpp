// DataSourceManager.cpp: implementation of the CDataSourceManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ReportAsistent.h"
#include "DataSourceManager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


//honza: pracovni prijde nahradit tridou kodyho
public_source_id_t zdroje [] =
{
	"meatabaze1", "super_matabaze", "nic_moc_metabaze"
};

CDataSourcesManager::CDataSourcesManager()
{
}
	
CDataSourcesManager::~CDataSourcesManager()
{
}


//honza: pracovni prijde nahradit tridou kodyho
int CDataSourcesManager::getSourcesCount()
{
	return 3;
}

//honza: pracovni prijde nahradit tridou kodyho
public_source_id_t CDataSourcesManager::getSourcePublicID(int source_index)
{
	if ((source_index  >= 0) && (source_index < getSourcesCount()))
	{
		return zdroje[source_index];
	}

	return "";
}


//honza: tohle je univerzalni nemusi se nahrazovat
int CDataSourcesManager::FindSourceByPublicID(public_source_id_t id) //vrati index odpovidajiciho zdroje
{
	CString sid = id;
	for (int a=0; a<getSourcesCount(); a++)
	{
		if (sid == getSourcePublicID(a)) return a;
	}

	return -1;
}


/*
CDataSourceManager::CDataSourceManager()
{

}

CDataSourceManager::~CDataSourceManager()
{

}
*/
