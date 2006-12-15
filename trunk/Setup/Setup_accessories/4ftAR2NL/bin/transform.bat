@echo OFF

rem  spusteni: transform %lang %domain %expression %ruleID %relPath

set LANG=%1

set DOMAIN=%2

set EXPRESSION=%3

set RULE=%4

set REL_PATH=%5

set XML_CATALOG_FILES=%REL_PATH%dtd\catalog.xml


call %REL_PATH%bin\xsltproc -o %REL_PATH%param/params.xml --stringparam lang %LANG% --stringparam rule %RULE% --stringparam expression %EXPRESSION% --stringparam domain %DOMAIN% %REL_PATH%phase00.xsl %REL_PATH%rules/ar%RULE%.xml


call %REL_PATH%bin\xsltproc -o %REL_PATH%output/output01.xml --stringparam params param/params.xml %REL_PATH%phase01.xsl %REL_PATH%data/%LANG%/fp.xml

call %REL_PATH%bin\xsltproc -o %REL_PATH%output/output02.xml --stringparam params param/params.xml %REL_PATH%phase02.xsl %REL_PATH%output/output01.xml

call %REL_PATH%bin\xsltproc -o %REL_PATH%output/output02a.xml --stringparam params param/params.xml %REL_PATH%phase02.xsl %REL_PATH%output/output02.xml

call %REL_PATH%bin\xsltproc -o %REL_PATH%output/output03.xml --stringparam params param/params.xml %REL_PATH%phase03.xsl %REL_PATH%output/output02a.xml

call %REL_PATH%bin\xsltproc -o %REL_PATH%output/output04.xml --stringparam params param/params.xml %REL_PATH%phase04.xsl %REL_PATH%output/output03.xml

call %REL_PATH%bin\xsltproc -o %REL_PATH%output/output05.xml --stringparam params param/params.xml %REL_PATH%phase05.xsl %REL_PATH%output/output04.xml

call %REL_PATH%bin\xsltproc -o %REL_PATH%output/output06.xml --stringparam params param/params.xml %REL_PATH%phase06.xsl %REL_PATH%output/output05.xml

call %REL_PATH%bin\xsltproc -o %REL_PATH%output/output07.xml --stringparam params param/params.xml %REL_PATH%phase07.xsl %REL_PATH%output/output06.xml

call %REL_PATH%bin\xsltproc -o %REL_PATH%output/output08.xml --stringparam params param/params.xml %REL_PATH%phase08.xsl %REL_PATH%output/output07.xml

call %REL_PATH%bin\xsltproc -o %REL_PATH%output/output09.xml --stringparam params param/params.xml %REL_PATH%phase09.xsl %REL_PATH%output/output08.xml

call %REL_PATH%bin\xsltproc -o %REL_PATH%output/output10.xml --stringparam params param/params.xml %REL_PATH%phase10.xsl %REL_PATH%output/output09.xml

call %REL_PATH%bin\xsltproc -o %REL_PATH%output/output11.xml --stringparam params param/params.xml %REL_PATH%phase11.xsl %REL_PATH%output/output10.xml

call %REL_PATH%bin\xsltproc -o %REL_PATH%output/output12.xml --stringparam params param/params.xml %REL_PATH%phase12.xsl %REL_PATH%output/output11.xml

call %REL_PATH%bin\xsltproc -o %REL_PATH%randomness.xml %REL_PATH%set-random.xsl %REL_PATH%randomness.xml

call %REL_PATH%bin\xsltproc -o %REL_PATH%output/output.txt %REL_PATH%phase2txt.xsl %REL_PATH%output/output12.xml


@echo ON
