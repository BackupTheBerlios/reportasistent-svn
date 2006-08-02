// WordManager.cpp: implementation of the CWordManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ReportAsistent.h"
#include "WordManager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


void CStringTableImpl::Clear()
{
	for (int a=0; a<getCount(); a++)
	{
		delete data[a];
	}

	data.RemoveAll();
}


void CStringTableImpl::Add(LPCTSTR s)
{
	data.Add(new CString(s));
//	int a = data.GetSize();
}

int CStringTableImpl::getCount()
{
	return data.GetSize();
}

LPCTSTR CStringTableImpl::getItem(int index)
{
	ASSERT(index >= 0);
	ASSERT(index < getCount());
	
	return * data[index];
}

CStringTableImpl::~CStringTableImpl()
{
	Clear();
}

void CWordManager::LoadWordStyles(LPCTSTR template_name)
{
	if (! isInit()) 
	{
		if (! InitWordLoader()) return;
	}

	LoadWordTemplates();
	LoadParagraphStyles(template_name);
	LoadCharacterStyles(template_name);
}


void CWordManager::LoadWordTemplates()
{
	if (! isInit()) 
	{
		if (! InitWordLoader()) return;
	}

	SAFEARRAY * ret_array = m_WordLoader->EnumTemplates();


	LONG l_bound = 0;
	LONG u_bound = -1;

	SafeArrayGetLBound(ret_array, 1, & l_bound);
	SafeArrayGetUBound(ret_array, 1, & u_bound);

	m_WordTemplates.Clear();

	for (LONG a = l_bound; a <= u_bound; a++)
	{
		BSTR arg;
		SafeArrayGetElement(ret_array, &a, & arg);

		_bstr_t s;
		s.Assign(arg);

		m_WordTemplates.Add(s);
	}
	
	SafeArrayDestroy(ret_array);


/*		
	SAFEARRAY * enum_arr = word->EnumCharacterStyles("normal.dot");

	LONG l_bound = 0;
	LONG u_bound = 0;

	SafeArrayGetLBound(enum_arr, 1, & l_bound);
	SafeArrayGetUBound(enum_arr, 1, & u_bound);

	CString sl;
	sl.Format("%d - %d", l_bound, u_bound);
	AfxMessageBox(sl);

	for (LONG a = l_bound; a < u_bound; a++)
	{
		BSTR arg;
		SafeArrayGetElement(enum_arr, &a, & arg);

		_bstr_t s;
		s.Assign(arg);

		AfxMessageBox(s);
	}
	
	SafeArrayDestroy(enum_arr);
*/

}


CWordManager::CWordManager()
: m_pEventHandler(NULL)
{
	//ladici:
	//LoadWordTemplates();
	//LoadWordStyles("normal.dot");

}

CWordManager::~CWordManager()
{
	if (m_WordLoader != NULL) 
	{
		DisconnectWordEventHandler();
		m_WordLoader.Release();
	}
}

BOOL CWordManager::InitWordLoader()
{
	HRESULT hr;
	
	hr = m_WordLoader.CreateInstance("LMRA_WordLoader.LMRA_XML_WordLoader");

	if (S_OK != hr)
	{
				
		//dedek: pokusime se registrovat ActiveX objekt spustenim LMRA_WB_WordLoader s parametrem register
		STARTUPINFO si;
		ZeroMemory(& si, sizeof si);
		
		PROCESS_INFORMATION pi;
		ZeroMemory(& pi, sizeof pi);


		CDirectoriesManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->DirectoriesManager;

		BOOL ret = CreateProcess(m.getLMRA_WB_WordLoaderPath(), " register", NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, & si, & pi);
		if (! ret) 
		{
			CReportAsistentApp::ReportError(IDS_WB_WORD_LOADER_NOT_REGISTRED);
			return FALSE;
		}

		
		//pockame az spusteny process skonci
		DWORD wait_ret= WaitForSingleObject(pi.hProcess, 5000);
 		CloseHandle(pi.hProcess);

		if (wait_ret != WAIT_OBJECT_0)
		{
			CReportAsistentApp::ReportError(IDS_WB_WORD_LOADER_NOT_REGISTRED);
			return FALSE;
		}
	

		hr = m_WordLoader.CreateInstance("LMRA_WordLoader.LMRA_XML_WordLoader");
		if (S_OK != hr)
		{
			CReportAsistentApp::ReportError(IDS_WB_WORD_LOADER_NOT_REGISTRED);
			return FALSE;
		}
	}

	return InitWordEventHandler();
}

BOOL CWordManager::isInit()
{
	return m_WordLoader != NULL;
}



void CWordManager::LoadCharacterStyles(LPCTSTR template_name)
{
	ASSERT(isInit());


	SAFEARRAY * ret_array = m_WordLoader->EnumCharacterStyles(
		(long) (getWordTemplates().FindStringNoCase(template_name)+1));


	LONG l_bound = 0;
	LONG u_bound = -1;

	SafeArrayGetLBound(ret_array, 1, & l_bound);
	SafeArrayGetUBound(ret_array, 1, & u_bound);

	m_WordCharacterStyles.Clear();


	for (LONG a = l_bound; a <= u_bound; a++)
	{
		BSTR arg;
		SafeArrayGetElement(ret_array, &a, & arg);

		_bstr_t s;
		s.Assign(arg);

		m_WordCharacterStyles.Add(s);
	}
	
	SafeArrayDestroy(ret_array);
}

void CWordManager::LoadParagraphStyles(LPCTSTR template_name)
{
	ASSERT(isInit());


	SAFEARRAY * ret_array = m_WordLoader->EnumParagraphStyles(
		(long) (getWordTemplates().FindStringNoCase(template_name)+1));


	LONG l_bound = 0;
	LONG u_bound = -1;

	SafeArrayGetLBound(ret_array, 1, & l_bound);
	SafeArrayGetUBound(ret_array, 1, & u_bound);

	m_WordParagraphStyles.Clear();


	for (LONG a = l_bound; a <= u_bound; a++)
	{
		BSTR arg;
		SafeArrayGetElement(ret_array, &a, & arg);

		_bstr_t s;
		s.Assign(arg);

		m_WordParagraphStyles.Add(s);
	}
	
	SafeArrayDestroy(ret_array);
}

int CStringTable::FindStringNoCase(LPCTSTR str)
{
	for (int a = 0; a < getCount(); a++)
	{
		if (((CString) getItem(a)).CompareNoCase(str) == 0) return a;
	}

	return -1;
}


int CStringTable::FindString(LPCTSTR str)
{
	for (int a = 0; a < getCount(); a++)
	{
		if (((CString) getItem(a)) == str) return a;
	}

	return -1;
}

void CWordManager::GenerateXMLString(_bstr_t XML_str)
{
	if (! isInit()) 
	{
		if (! InitWordLoader()) return;
	}

	m_WordLoader->LoadFromString(XML_str);
}

BOOL CWordManager::InitWordEventHandler()
{
	m_pEventHandler = new CWordEventHandler();

	LPUNKNOWN p_unk = m_pEventHandler->GetIDispatch(FALSE);

	if (AfxConnectionAdvise(m_WordLoader.GetInterfacePtr(), 
			DIID___LMRA_XML_WordLoader, p_unk, FALSE, & m_dwEventHandlerCookie))
		return TRUE;
	else
		return FALSE;
}

void CWordManager::DisconnectWordEventHandler()
{
	LPUNKNOWN p_unk = m_pEventHandler->GetIDispatch(FALSE);

	AfxConnectionUnadvise(m_WordLoader.GetInterfacePtr(), 
			DIID___LMRA_XML_WordLoader, p_unk, FALSE, m_dwEventHandlerCookie);

	
	if(m_pEventHandler != NULL)
	{
		delete m_pEventHandler;
		m_pEventHandler = NULL;
	}
}
