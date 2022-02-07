# Microsoft Developer Studio Generated NMAKE File, Based on FloppyReader.dsp
!IF "$(CFG)" == ""
CFG=FloppyReader - Win32 Debug
!MESSAGE No configuration specified. Defaulting to FloppyReader - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "FloppyReader - Win32 Release" && "$(CFG)" !=\
 "FloppyReader - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "FloppyReader.mak" CFG="FloppyReader - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "FloppyReader - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "FloppyReader - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "FloppyReader - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\FloppyReader.exe" "$(OUTDIR)\FloppyReader.pch"

!ELSE 

ALL : "$(OUTDIR)\FloppyReader.exe" "$(OUTDIR)\FloppyReader.pch"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\FloppyReader.obj"
	-@erase "$(INTDIR)\FloppyReader.pch"
	-@erase "$(INTDIR)\FloppyReader.res"
	-@erase "$(INTDIR)\FloppyReaderDlg.obj"
	-@erase "$(INTDIR)\IOKernel.obj"
	-@erase "$(INTDIR)\OpenDir.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\FloppyReader.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /Ob2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /Fp"$(INTDIR)\FloppyReader.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC=rc.exe
RSC_PROJ=/l 0x419 /fo"$(INTDIR)\FloppyReader.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\FloppyReader.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\FloppyReader.pdb" /machine:I386\
 /out:"$(OUTDIR)\FloppyReader.exe" 
LINK32_OBJS= \
	"$(INTDIR)\FloppyReader.obj" \
	"$(INTDIR)\FloppyReader.res" \
	"$(INTDIR)\FloppyReaderDlg.obj" \
	"$(INTDIR)\IOKernel.obj" \
	"$(INTDIR)\OpenDir.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\FloppyReader.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "FloppyReader - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\FloppyReader.exe" "$(OUTDIR)\FloppyReader.pch"

!ELSE 

ALL : "$(OUTDIR)\FloppyReader.exe" "$(OUTDIR)\FloppyReader.pch"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\FloppyReader.obj"
	-@erase "$(INTDIR)\FloppyReader.pch"
	-@erase "$(INTDIR)\FloppyReader.res"
	-@erase "$(INTDIR)\FloppyReaderDlg.obj"
	-@erase "$(INTDIR)\IOKernel.obj"
	-@erase "$(INTDIR)\OpenDir.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\FloppyReader.exe"
	-@erase "$(OUTDIR)\FloppyReader.ilk"
	-@erase "$(OUTDIR)\FloppyReader.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /GX /Zi /Od /Gf /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /Fp"$(INTDIR)\FloppyReader.pch" /YX /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC=rc.exe
RSC_PROJ=/l 0x419 /fo"$(INTDIR)\FloppyReader.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\FloppyReader.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)\FloppyReader.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)\FloppyReader.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\FloppyReader.obj" \
	"$(INTDIR)\FloppyReader.res" \
	"$(INTDIR)\FloppyReaderDlg.obj" \
	"$(INTDIR)\IOKernel.obj" \
	"$(INTDIR)\OpenDir.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\FloppyReader.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "FloppyReader - Win32 Release" || "$(CFG)" ==\
 "FloppyReader - Win32 Debug"
SOURCE=.\FloppyReader.cpp

!IF  "$(CFG)" == "FloppyReader - Win32 Release"

DEP_CPP_FLOPP=\
	".\FloppyReader.h"\
	".\FloppyReaderDlg.h"\
	".\IOKernel.h"\
	".\OpenDir.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\FloppyReader.obj" : $(SOURCE) $(DEP_CPP_FLOPP) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "FloppyReader - Win32 Debug"

DEP_CPP_FLOPP=\
	".\FloppyReader.h"\
	".\FloppyReaderDlg.h"\
	".\IOKernel.h"\
	".\OpenDir.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\FloppyReader.obj" : $(SOURCE) $(DEP_CPP_FLOPP) "$(INTDIR)"


!ENDIF 

SOURCE=.\FloppyReader.rc
DEP_RSC_FLOPPY=\
	".\res\FloppyReader.ico"\
	".\res\FloppyReader.rc2"\
	

"$(INTDIR)\FloppyReader.res" : $(SOURCE) $(DEP_RSC_FLOPPY) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\FloppyReaderDlg.cpp

!IF  "$(CFG)" == "FloppyReader - Win32 Release"

DEP_CPP_FLOPPYR=\
	".\FloppyReader.h"\
	".\FloppyReaderDlg.h"\
	".\IOKernel.h"\
	".\OpenDir.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\FloppyReaderDlg.obj" : $(SOURCE) $(DEP_CPP_FLOPPYR) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "FloppyReader - Win32 Debug"

DEP_CPP_FLOPPYR=\
	".\FloppyReader.h"\
	".\FloppyReaderDlg.h"\
	".\IOKernel.h"\
	".\OpenDir.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\FloppyReaderDlg.obj" : $(SOURCE) $(DEP_CPP_FLOPPYR) "$(INTDIR)"


!ENDIF 

SOURCE=.\IOKernel.cpp

!IF  "$(CFG)" == "FloppyReader - Win32 Release"

DEP_CPP_IOKER=\
	".\FloppyReader.h"\
	".\FloppyReaderDlg.h"\
	".\IOKernel.h"\
	".\OpenDir.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\IOKernel.obj" : $(SOURCE) $(DEP_CPP_IOKER) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "FloppyReader - Win32 Debug"

DEP_CPP_IOKER=\
	".\FloppyReader.h"\
	".\FloppyReaderDlg.h"\
	".\IOKernel.h"\
	".\OpenDir.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\IOKernel.obj" : $(SOURCE) $(DEP_CPP_IOKER) "$(INTDIR)"


!ENDIF 

SOURCE=.\OpenDir.cpp
DEP_CPP_OPEND=\
	".\StdAfx.h"\
	

"$(INTDIR)\OpenDir.obj" : $(SOURCE) $(DEP_CPP_OPEND) "$(INTDIR)"


SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "FloppyReader - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /Ob2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /Fp"$(INTDIR)\FloppyReader.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\FloppyReader.pch" : $(SOURCE)\
 $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "FloppyReader - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /GX /Zi /Od /Gf /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /Fp"$(INTDIR)\FloppyReader.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\FloppyReader.pch" : $(SOURCE)\
 $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

