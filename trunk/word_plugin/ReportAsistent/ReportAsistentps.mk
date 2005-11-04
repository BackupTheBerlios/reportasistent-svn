
ReportAsistentps.dll: dlldata.obj ReportAsistent_p.obj ReportAsistent_i.obj
	link /dll /out:ReportAsistentps.dll /def:ReportAsistentps.def /entry:DllMain dlldata.obj ReportAsistent_p.obj ReportAsistent_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del ReportAsistentps.dll
	@del ReportAsistentps.lib
	@del ReportAsistentps.exp
	@del dlldata.obj
	@del ReportAsistent_p.obj
	@del ReportAsistent_i.obj
