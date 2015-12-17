# Microsoft Developer Studio Generated NMAKE File, Based on Enhanced2D.dsp
!IF "$(CFG)" == ""
CFG=Enhanced2D - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Enhanced2D - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Enhanced2D - Win32 Release" && "$(CFG)" !=\
 "Enhanced2D - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Enhanced2D.mak" CFG="Enhanced2D - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Enhanced2D - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Enhanced2D - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Enhanced2D - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\Enhanced2D.exe"

!ELSE 

ALL : "$(OUTDIR)\Enhanced2D.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\ddutil.obj"
	-@erase "$(INTDIR)\enhanced2d.obj"
	-@erase "$(INTDIR)\sprite3d.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\winmain.obj"
	-@erase "$(INTDIR)\winmain.res"
	-@erase "$(OUTDIR)\Enhanced2D.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\Enhanced2D.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x407 /fo"$(INTDIR)\winmain.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Enhanced2D.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=ddraw.lib winmm.lib dxguid.lib d3dim.lib\
 c:\mssdk\samples\multimedia\d3dim\src\d3dframe\release\d3dframe.lib\
 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib\
 shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo\
 /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\Enhanced2D.pdb"\
 /machine:I386 /out:"$(OUTDIR)\Enhanced2D.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ddutil.obj" \
	"$(INTDIR)\enhanced2d.obj" \
	"$(INTDIR)\sprite3d.obj" \
	"$(INTDIR)\winmain.obj" \
	"$(INTDIR)\winmain.res"

"$(OUTDIR)\Enhanced2D.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Enhanced2D - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\Enhanced2D.exe"

!ELSE 

ALL : "$(OUTDIR)\Enhanced2D.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\ddutil.obj"
	-@erase "$(INTDIR)\enhanced2d.obj"
	-@erase "$(INTDIR)\sprite3d.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(INTDIR)\winmain.obj"
	-@erase "$(INTDIR)\winmain.res"
	-@erase "$(OUTDIR)\Enhanced2D.exe"
	-@erase "$(OUTDIR)\Enhanced2D.ilk"
	-@erase "$(OUTDIR)\Enhanced2D.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /w /W0 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)\Enhanced2D.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x407 /fo"$(INTDIR)\winmain.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Enhanced2D.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=ddraw.lib winmm.lib dxguid.lib d3dim.lib d3dxof.lib\
 Lib\d3dframe.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)\Enhanced2D.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)\Enhanced2D.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\ddutil.obj" \
	"$(INTDIR)\enhanced2d.obj" \
	"$(INTDIR)\sprite3d.obj" \
	"$(INTDIR)\winmain.obj" \
	"$(INTDIR)\winmain.res"

"$(OUTDIR)\Enhanced2D.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

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


!IF "$(CFG)" == "Enhanced2D - Win32 Release" || "$(CFG)" ==\
 "Enhanced2D - Win32 Debug"
SOURCE=.\ddutil.cpp
DEP_CPP_DDUTI=\
	"c:\mssdk\samples\multimedia\ddraw\include\ddutil.h"\
	

"$(INTDIR)\ddutil.obj" : $(SOURCE) $(DEP_CPP_DDUTI) "$(INTDIR)"


SOURCE=.\enhanced2d.cpp

!IF  "$(CFG)" == "Enhanced2D - Win32 Release"

DEP_CPP_ENHAN=\
	".\ccklib.h"\
	".\sprite3d.h"\
	"c:\mssdk\include\d3dvec.inl"\
	"c:\mssdk\samples\multimedia\d3dim\include\d3dframe.h"\
	"c:\mssdk\samples\multimedia\d3dim\include\d3dtextr.h"\
	"c:\mssdk\samples\multimedia\d3dim\include\d3dutil.h"\
	"c:\mssdk\samples\multimedia\ddraw\include\ddutil.h"\
	

"$(INTDIR)\enhanced2d.obj" : $(SOURCE) $(DEP_CPP_ENHAN) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Enhanced2D - Win32 Debug"

DEP_CPP_ENHAN=\
	".\ccklib.h"\
	".\sprite3d.h"\
	"c:\mssdk\include\d3dvec.inl"\
	"c:\mssdk\samples\multimedia\d3dim\include\d3dframe.h"\
	"c:\mssdk\samples\multimedia\d3dim\include\d3dtextr.h"\
	"c:\mssdk\samples\multimedia\d3dim\include\d3dutil.h"\
	"c:\mssdk\samples\multimedia\ddraw\include\ddutil.h"\
	

"$(INTDIR)\enhanced2d.obj" : $(SOURCE) $(DEP_CPP_ENHAN) "$(INTDIR)"


!ENDIF 

SOURCE=.\sprite3d.cpp

!IF  "$(CFG)" == "Enhanced2D - Win32 Release"

DEP_CPP_SPRIT=\
	".\sprite3d.h"\
	"c:\mssdk\include\d3dvec.inl"\
	"c:\mssdk\samples\multimedia\d3dim\include\d3dframe.h"\
	"c:\mssdk\samples\multimedia\d3dim\include\d3dtextr.h"\
	

"$(INTDIR)\sprite3d.obj" : $(SOURCE) $(DEP_CPP_SPRIT) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Enhanced2D - Win32 Debug"

DEP_CPP_SPRIT=\
	".\sprite3d.h"\
	"c:\mssdk\include\d3dvec.inl"\
	"c:\mssdk\samples\multimedia\d3dim\include\d3dframe.h"\
	"c:\mssdk\samples\multimedia\d3dim\include\d3dtextr.h"\
	

"$(INTDIR)\sprite3d.obj" : $(SOURCE) $(DEP_CPP_SPRIT) "$(INTDIR)"


!ENDIF 

SOURCE=.\winmain.cpp

!IF  "$(CFG)" == "Enhanced2D - Win32 Release"

DEP_CPP_WINMA=\
	"c:\mssdk\samples\multimedia\d3dim\include\d3denum.h"\
	"c:\mssdk\samples\multimedia\d3dim\include\d3dframe.h"\
	"c:\mssdk\samples\multimedia\d3dim\include\d3dutil.h"\
	

"$(INTDIR)\winmain.obj" : $(SOURCE) $(DEP_CPP_WINMA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Enhanced2D - Win32 Debug"

DEP_CPP_WINMA=\
	"c:\mssdk\samples\multimedia\d3dim\include\d3denum.h"\
	"c:\mssdk\samples\multimedia\d3dim\include\d3dframe.h"\
	"c:\mssdk\samples\multimedia\d3dim\include\d3dutil.h"\
	

"$(INTDIR)\winmain.obj" : $(SOURCE) $(DEP_CPP_WINMA) "$(INTDIR)"


!ENDIF 

SOURCE=.\winmain.rc
DEP_RSC_WINMAI=\
	".\directx.ico"\
	

"$(INTDIR)\winmain.res" : $(SOURCE) $(DEP_RSC_WINMAI) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

