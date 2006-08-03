DEDEK:

zacinam s pluginem do Wordu

vsichni uz muzete testovat - budu moc rad 

dejte vedet kdyz to nebude chodit

spousti se: v RA klavesova zkratka Ctrl + W



momentalne to umi:
zobrazi toolbar AP, vklada AP






------------------------------------------------------------------------------------------
Kody to deda:
- tak u Raucha ten FE plugin nefunguje, je invalidni :-/ Ma Win XP SP1. Musime z toho nejak dostat ty knihovny...
dedek: hmmm to bude asi narocny ladeni, ale zkusime to nejak logovat nebo hlaskovat, at aspon vime cim to je..

- BUG: pri generovani se generujou pouze aktivni prvky v prvni kapitole, AP v dalsich kapitolach to ignoruje
dedek: opraveno, problem byl v chybe v souboru reduk2.xml

- nefunguje mi Copy/Paste, hazi to posloupnost hlasek vcetne jedny bez jakyhokoliv textu :-)
dedek: pouze release verze ?!!!, taky mi to nefunguje - prace pro Ivu..

- Rauch trva na tom, aby byl LM_RA "dvojjazycnej" (cesky, anglicky). Nastesti ne na urovni programu (ovladaci prvky atd)
ale na urovni jazyka generovany analyticky zpravy. 
-> ve vsech XSL transformacich bude definovana promenna <xsl:variable name="lng"> nabyvajici hodnot "cz" nebo "en". 
Chtelo by to mit v LM-RA nejakej Options dialog, kde se bude tohle nastavovat a pak pred provedenim transformace
tu promennou pripadne prenastavit. (Lepsi reseni me nenapadlo).
dedek: ok dohodnuto zapracuje kody s moji pomoci

- Rauch chce listu s nabidkou aktivnich prvku
dedek: prace pro Ivu





------------------------------------------------------------------------------------------
Ivina poznamka - to vsichni:
Zmenila jsem DTD - element chapter:
puvodne: subkapitoly smi byt jen na konci nadrazene kapitoly
Nove: subkapitoly smi byt kdekoliv v nadrazene kapitole


to Deda: problemy s copy/paste jsou uz vyreseny, tvuj napad s variaci stareho ID jsem pouzila. :-)



------------------------------------------------------------------------------------------
dedek:
Vytvoril jsem novou statickou metodu CReportAsistentApp::ReportError,
pres kterou by se mely vypisovat vsecky chybove hlasky, funguje jako printf



------------------------------------------------------------------------------------------
Pro Ivu:

Dalsi bug:
id nesmi obsahovat ? * . a kdovi co jeste vsecko..
asi to bude chtit kontrolovat primo pokusem o zmenu id prvku v kostre a odchytavat vyjimky



------------------------------------------------------------------------------------------
pro vsechny ale havne pro Martina a Ivu:

!!!Piste strukturovane a objektove!!!

To uz si z prvaku nepamatujete jak se programuje?
Proc kod jedne metody copy/paste prenasite do vsech objektu, chyba nebo zmena v tom kodu
se pak musi prepisovat v kazdem zvlast a to se mi za vas uz nejak nechce :-)
(jednou bych to jeste zvladnul :) ale trikrat az 7-krat ne)








------------------------------------------------------------------------------------------
taky uz to umi Word styly - viz dialog pro attr_link







------------------------------------------------------------------------------------------
honzovy poznamky:


!!!!!!! uz by to melo jit prelozit ve VS 2005 !!!!!!



------------------------------------------------------------------------------------------
ve tride App je promenna m_pGeneralManager pro instance globalnich manageru

pro pouziti techto manageru:

((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager

CGeneralManager * m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager;
	CDataSourcesManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->DataSourcesManager;
	CDirectoriesManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->DirectoriesManager;
	CElementManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;
	CWordManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->WordManager;








------------------------------------------------------------------------------------------
dedek TODO:

otestovat zabijeni vlaken a hlavne resume application v jednotlivych situacich

coz takhle nejak inteligentne usporadat AP?

zdokumentovat chybovou hlasku o neplatne volbe simple filtru pri generovani

otestovat: co kdyz se transformace jmenuje stejne jako * attrlink table *

mazat captions_list pri zmene targetu v attr_link_table
-hotovo

doladit ukladani int hodnoty property editoru - ve stringu to mozna muze vratit desetinne cislo 
-hotovo nemuze

zavirat normal.dot - jinak ji to odmita menit v jinych spustenych wordech
-hotovo normal.dot se zavira COM Word ne

?styly textu: combobox editovatelny a nove styly se vytvori v novem do dokumentu?
-asi ne, je to blbost

pridat refresh atributu aktivniho prvku na OnOK dialogu aktivniho prvku
-ted se atributy aktualizuji asi jen pri otevreni dialogu aktivniho prvku

chtelo by to nejak upozornovat na to, ze aplikace pracuje, napr. menit kurzor na presypaci hodiny
-pri nacitani ze zdroje
-pri nacitani word stylu
-pri generovani
-pri ???




DacourcesManager - 	pridat funci co zjisti podporovane prvky
-hotovo
-nemelo by se prejmenovat APID?




------------------------------------------------------------------------------------------
hotovo:
chybka v copy/paste:
kdyz dam copy na cely odstavec, ktery obsahuje dalsi prvky,
tak potom nefunguje paste - prvkum uvnitr toho okopirovaneho odstavce se nezmeni id 
- problem je v tom, ze kontrola id probiha pouze v ramci zobrazovaneho dokumentu 
	a nikoliv v ramci vkladanych dat
potom se muze stat (stava se) ze to vsem nove vlozenym elementum stejneho typu 
	vyrobi stejne id
-navic by mozna bylo fajn, kdyz by to existujici id nenahrazovalo uplne novymi 
	ale jen je to trochu modifikovalo


predelal jsem svou uzasnou nahodnou funkci na generovani ID CSkeletonDoc::CreateNewID
je tam videt jak snadno se da zjistit, jestli je dane id uz pouzite..
(koukal jsem ze uz jsi k tomu editovani id neco psala..)



















hotovo:

mazat combobox stylu pri refresh tlacitku (attr_link)
-hotovo

pouzivat default source!
-hotovo

generovani attr_link_* atributu
-hotovo

pouzivat CWordManager pri generovani
-hotovo

otestovat destruktor ~CStringTableImpl()
-jestli se nevola z ~CStringTable() proste kdyz se pouzije nektra z funkci getWordParagraphStyles
-hotovo nevola se

pridat attr_link_table mezi vizualizace
-hotovo


v void CAElTransform::ProcessAllTransformations(IXMLDOMNodePtr & target, IXMLDOMNodePtr & destination_parent)
pridat transformaci attr_link_table
-hotovo


opravit ukoncovani wordu uvnitr BV-WL
-pokud se zavola jen init tak pri ukocovani spadne asi
-hotovo


attr_link_table

predelat na detekci chyb / navratovou hodnotu uvnitr call backu CAElTransform::ProcessSimpleFlter

zavedeni default source

reletivni adresace metabaze v perzist ID - predelano - uklada se tam absolutni cesta .mdb souboru metabaze, 
ale funguje i s relativni cestou viz zdroj "testovaci metabaze"
 - relativni cesta s v open predelava na absolutni viz fOpenSourceLM







========================================================================
       MICROSOFT FOUNDATION CLASS LIBRARY : ReportAsistent
========================================================================


AppWizard has created this ReportAsistent application for you.  This application
not only demonstrates the basics of using the Microsoft Foundation classes
but is also a starting point for writing your application.

This file contains a summary of what you will find in each of the files that
make up your ReportAsistent application.

ReportAsistent.dsp
    This file (the project file) contains information at the project level and
    is used to build a single project or subproject. Other users can share the
    project (.dsp) file, but they should export the makefiles locally.

ReportAsistent.h
    This is the main header file for the application.  It includes other
    project specific headers (including Resource.h) and declares the
    CReportAsistentApp application class.

ReportAsistent.cpp
    This is the main application source file that contains the application
    class CReportAsistentApp.

ReportAsistent.rc
    This is a listing of all of the Microsoft Windows resources that the
    program uses.  It includes the icons, bitmaps, and cursors that are stored
    in the RES subdirectory.  This file can be directly edited in Microsoft
	Visual C++.

ReportAsistent.clw
    This file contains information used by ClassWizard to edit existing
    classes or add new classes.  ClassWizard also uses this file to store
    information needed to create and edit message maps and dialog data
    maps and to create prototype member functions.

res\ReportAsistent.ico
    This is an icon file, which is used as the application's icon.  This
    icon is included by the main resource file ReportAsistent.rc.

res\ReportAsistent.rc2
    This file contains resources that are not edited by Microsoft 
	Visual C++.  You should place all resources not editable by
	the resource editor in this file.

ReportAsistent.reg
    This is an example .REG file that shows you the kind of registration
    settings the framework will set for you.  You can use this as a .REG
    file to go along with your application or just delete it and rely
    on the default RegisterShellFileTypes registration.



/////////////////////////////////////////////////////////////////////////////

For the main frame window:

MainFrm.h, MainFrm.cpp
    These files contain the frame class CMainFrame, which is derived from
    CFrameWnd and controls all SDI frame features.

res\Toolbar.bmp
    This bitmap file is used to create tiled images for the toolbar.
    The initial toolbar and status bar are constructed in the CMainFrame
    class. Edit this toolbar bitmap using the resource editor, and
    update the IDR_MAINFRAME TOOLBAR array in ReportAsistent.rc to add
    toolbar buttons.
/////////////////////////////////////////////////////////////////////////////

AppWizard creates one document type and one view:

CSkeletonDoc.h, CSkeletonDoc.cpp - the document
    These files contain your CSkeletonDoc class.  Edit these files to
    add your special document data and to implement file saving and loading
    (via CSkeletonDoc::Serialize).

SkeletonView.h, SkeletonView.cpp - the view of the document
    These files contain your CSkeletonView class.
    CSkeletonView objects are used to view CSkeletonDoc objects.



/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named ReportAsistent.pch and a precompiled types file named StdAfx.obj.

Resource.h
    This is the standard header file, which defines new resource IDs.
    Microsoft Visual C++ reads and updates this file.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" to indicate parts of the source code you
should add to or customize.

If your application uses MFC in a shared DLL, and your application is 
in a language other than the operating system's current language, you
will need to copy the corresponding localized resources MFC42XXX.DLL
from the Microsoft Visual C++ CD-ROM onto the system or system32 directory,
and rename it to be MFCLOC.DLL.  ("XXX" stands for the language abbreviation.
For example, MFC42DEU.DLL contains resources translated to German.)  If you
don't do this, some of the UI elements of your application will remain in the
language of the operating system.

/////////////////////////////////////////////////////////////////////////////
