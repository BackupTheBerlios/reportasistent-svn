// WordManager.cpp: implementation of the CWordManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ReportAsistent.h"
#include "WordManager.h"
#include "WaitDialog.h"

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

//	data.RemoveAll();
	data.clear();
}


void CStringTableImpl::Add(LPCTSTR s)
{
	data.push_back(new CString(s));
//	int a = data.GetSize();
}

int CStringTableImpl::getCount()
{
	return data.size();
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



void CWordManager::LoadWordStylesThreadFunction(LPARAM template_name, LPARAM pWordManager)
{
	//dedek:	COM objekt nelze pouzit v jinem vlakne nez v tom, ktere ho vytvorilo.
	//			Proto zde musim vytvorit novy COM objekt.
	
	CWordManager * m = (CWordManager *) pWordManager;

	_LMRA_XML_WordLoaderPtr WordLoader;
	
	if (m->CreateVBRAInstance(WordLoader))
	{
		m->LoadWordTemplates(WordLoader);
		m->LoadParagraphStyles(WordLoader, (LPCTSTR) template_name);
		m->LoadCharacterStyles(WordLoader, (LPCTSTR) template_name);

		WordLoader.Release();
	}	
}


void CWordManager::LoadWordStyles(LPCTSTR template_name)
{
	CWaitDialog d("Loading Word styles...");
	d.DoThreadFunction(LoadWordStylesThreadFunction,
						(LPARAM) template_name,
						(LPARAM) this);
}




void CWordManager::LoadWordTemplates(_LMRA_XML_WordLoaderPtr & WordLoader)
{
	SAFEARRAY * ret_array = WordLoader->EnumTemplates();

	LoadSafeArrayToStringTable(ret_array, m_WordTemplates);
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
	if (CreateVBRAInstance(m_WordLoader))
	{

		FillActiveElements();
	
		return InitWordEventHandler();
	}

	return FALSE;
}

BOOL CWordManager::isInit()
{
	return m_WordLoader != NULL;
}



void CWordManager::LoadCharacterStyles(_LMRA_XML_WordLoaderPtr & WordLoader, LPCTSTR template_name)
{
	SAFEARRAY * ret_array = WordLoader->EnumCharacterStyles(
		(long) (getWordTemplates().FindStringNoCase(template_name)+1));

	LoadSafeArrayToStringTable(ret_array, m_WordCharacterStyles);
}

void CWordManager::LoadParagraphStyles(_LMRA_XML_WordLoaderPtr & WordLoader, LPCTSTR template_name)
{
	SAFEARRAY * ret_array = WordLoader->EnumParagraphStyles(
		(long) (getWordTemplates().FindStringNoCase(template_name)+1));


	LoadSafeArrayToStringTable(ret_array, m_WordParagraphStyles);
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

void CWordManager::GenerateXMLStringToWordEditor(_bstr_t XML_str)
{
	if (! isInit()) 
	{
		if (! InitWordLoader()) return;
	}

	m_WordLoader->LoadFromStringToWordEditor(XML_str);

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


void CWordManager::SetWordEditorParentTaskName()
{
	ASSERT(isInit());

	CString wdCaption;
	AfxGetApp()->GetMainWnd()->GetWindowText(wdCaption);
	m_WordLoader->PutstrParentTaskName((LPCTSTR) wdCaption);
}

void CWordManager::OpenWordEditor()
{
	if (! isInit()) 
	{
		if (! InitWordLoader()) return;
	}

	WordEditHideMainWindow();


	SetWordEditorParentTaskName();

	try
	{
		m_WordLoader->OpenWordEditor();
	}
	catch (_com_error e)
	{
		//ladici
		AfxMessageBox(e.Description());
	}
}

void CWordManager::FillActiveElements()
{
	CElementManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;

	for (int a=0; a <= m.getLastElementId(); a++)
	{
		if (m.isElementActive(a))
		{
			CAElInfo * i = m.getActiveElementInfo(a);
			m_WordLoader->AddActiveElement(
				i->getElementName(),
				i->getElementLabel(),
				(LPCTSTR) i->getElementIconPath());
		}
	}
}

BOOL CWordManager::CreateVBRAInstance(_LMRA_XML_WordLoaderPtr & refLMRAInterface)
{
	HRESULT hr;
	
	hr = refLMRAInterface.CreateInstance("LMRA_WordLoader.LMRA_XML_WordLoader");

	if (S_OK != hr)
	{
				
		//dedek: pokusime se registrovat ActiveX objekt spustenim LMRA_WB_WordLoader s parametrem register
		STARTUPINFO si;
		ZeroMemory(& si, sizeof si);
		
		PROCESS_INFORMATION pi;
		ZeroMemory(& pi, sizeof pi);


		CDirectoriesManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->DirectoriesManager;

		// kody - smaz
		//AfxMessageBox(m.getLMRA_WB_WordLoaderPath());

		BOOL ret = CreateProcess(m.getLMRA_WB_WordLoaderPath(), " register", NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, & si, & pi);
		if (! ret) 
		{
			CReportAsistentApp::ReportError(IDS_WB_WORD_LOADER_NOT_REGISTRED);
			return FALSE;
		}

		// kody - smaz
		//AfxMessageBox("registracni proces spusten");
		
		//pockame az spusteny process skonci
		DWORD wait_ret= WaitForSingleObject(pi.hProcess, 5000);
 		CloseHandle(pi.hProcess);

		if (wait_ret != WAIT_OBJECT_0)
		{
			CReportAsistentApp::ReportError(IDS_WB_WORD_LOADER_NOT_REGISTRED);
			return FALSE;
		}
	
		// kody - smaz
		//AfxMessageBox("registracni proces skoncil uspesne");

		hr = refLMRAInterface.CreateInstance("LMRA_WordLoader.LMRA_XML_WordLoader");
		if (S_OK != hr)
		{
			CReportAsistentApp::ReportError(IDS_WB_WORD_LOADER_NOT_REGISTRED);
			return FALSE;
		}
	}
	// kody - smaz
	//AfxMessageBox("Netreba registrovat ActiveX");

	return TRUE;
}

//vrati pocet zkopirovanych stringu
int CWordManager::LoadSafeArrayToStringTable(SAFEARRAY *sarray, CStringTableImpl &str_table)
{
	LONG l_bound = 0;
	LONG u_bound = -1;

	SafeArrayGetLBound(sarray, 1, & l_bound);
	SafeArrayGetUBound(sarray, 1, & u_bound);

	str_table.Clear();


	for (LONG a = l_bound; a <= u_bound; a++)
	{
		BSTR arg;
		SafeArrayGetElement(sarray, &a, & arg);

		_bstr_t s;
		s.Assign(arg);

		str_table.Add(s);
	}
	
	SafeArrayDestroy(sarray);

	return u_bound - l_bound +1;
}


void CWordManager::WordEditHideMainWindow()
{
	if (m_WordLoader->GetisWordEditorActive() == VARIANT_FALSE)
	{
	
		ZeroMemory(& m_origWINDOWPLACEMENT, sizeof m_origWINDOWPLACEMENT);
		m_origWINDOWPLACEMENT.length = sizeof m_origWINDOWPLACEMENT;
		
		AfxGetApp()->GetMainWnd()->GetWindowPlacement(& m_origWINDOWPLACEMENT);
	}

	WINDOWPLACEMENT newpl;
	ZeroMemory(& newpl, sizeof newpl);
	newpl.length = sizeof newpl;

	newpl.flags = WPF_SETMINPOSITION;
	newpl.showCmd = SW_MINIMIZE; //SW_SHOWMINIMIZED

	AfxGetApp()->GetMainWnd()->SetWindowPlacement(& newpl);
//	AfxGetApp()->GetMainWnd()->EnableWindow(FALSE);

}

void CWordManager::WordEditShowMainWindow()
{
	m_origWINDOWPLACEMENT.showCmd = SW_RESTORE;
	AfxGetApp()->GetMainWnd()->SetWindowPlacement(& m_origWINDOWPLACEMENT);
}

bool CStringTableImpl::num_sort_desc(CString * s1,  CString * s2)
{
	_variant_t v;
	double d1, d2;

	BOOL b1 = TRUE;

	try
	{
		v = * s1;
		d1 = v;
	}
	catch (...)
	{
		b1 = FALSE;
	}
	
	try
	{
		v = * s2;
		d2 = v;
	}
	catch (...)
	{
		if (b1) return true;
		else return *s1 > *s2;
	}

	if (b1) return d1 > d2;
	else return false;
}

bool CStringTableImpl::num_sort_asc(CString * s1,  CString * s2)
{
	_variant_t v;
	double d1, d2;

	BOOL b1 = TRUE;

	try
	{
		v = * s1;
		d1 = v;
	}
	catch (...)
	{
		b1 = FALSE;
	}
	
	try
	{
		v = * s2;
		d2 = v;
	}
	catch (...)
	{
		if (b1) return true;
		else return *s1 < *s2;
	}

	if (b1) return d1 < d2;
	else return false;
}

bool CStringTableImpl::str_sort_asc(CString * s1,  CString * s2)
{
	return *s1 < *s2;
}

bool CStringTableImpl::str_sort_desc(CString * s1,  CString * s2)
{
	return *s1 > *s2;
}

void CStringTableImpl::SortNumeric(BOOL ascending)
{
	if (ascending)
		std::sort(data.begin(), data.end(), num_sort_asc);
	else
		std::sort(data.begin(), data.end(), num_sort_desc);
}

void CStringTableImpl::Sort(BOOL ascending)
{
	if (ascending)
		std::sort(data.begin(), data.end(), str_sort_asc);
	else
		std::sort(data.begin(), data.end(), str_sort_desc);
}

CString CWordManager::getLastProcessedId(void)
{
  return (CString) (LPCTSTR) m_WordLoader->GetstrLastProcessedId();
}

CString CWordManager::getLastError(void)
{
  return (CString) (LPCTSTR) m_WordLoader->GetstrLastError();
}
