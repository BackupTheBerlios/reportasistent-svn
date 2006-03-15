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
CDataSourceManager::public_source_id_t zdroje [] =
{
	"meatabaze1", "super_matabaze", "nic_moc_metabaze"
};

//honza: pracovni prijde nahradit tridou kodyho
int CDataSourceManager::getSourcesCount()
{
	return 3;
}

//honza: pracovni prijde nahradit tridou kodyho
CDataSourceManager::public_source_id_t CDataSourceManager::getSourcePublicID(int source_index)
{
	if ((source_index  >= 0) && (source_index < getSourcesCount()))
	{
		return zdroje[source_index];
	}

	return NULL;
}


//honza: tohle je univerzalni nemusi se nahrazovat
int CDataSourceManager::FindSourceByPublicID(CDataSourceManager::public_source_id_t id) //vrati index odpovidajiciho zdroje
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
