# Microsoft Visual C++ generated build script - Do not modify

PROJ = DDREC
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\C\REC\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC = REC.C       
FIRSTCPP =             
RC = rc
CFLAGS_D_WEXE = /nologo /G2 /W3 /Zi /AM /Od /D "_DEBUG" /GA /Fd"DDREC.PDB"
CFLAGS_R_WEXE = /nologo /W3 /AM /O1 /D "NDEBUG" /FR /GA 
LFLAGS_D_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE /CO  
LFLAGS_R_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE  
LIBS_D_WEXE = oldnames libw mlibcew msacm commdlg.lib mmsystem.lib olecli.lib olesvr.lib shell.lib 
LIBS_R_WEXE = oldnames libw mlibcew commdlg.lib olecli.lib olesvr.lib shell.lib 
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS = 
DEFFILE = REC.DEF
OBJS_EXT = 
LIBS_EXT = 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_WEXE)
LFLAGS = $(LFLAGS_D_WEXE)
LIBS = $(LIBS_D_WEXE)
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
!else
CFLAGS = $(CFLAGS_R_WEXE)
LFLAGS = $(LFLAGS_R_WEXE)
LIBS = $(LIBS_R_WEXE)
MAPFILE = nul
RCDEFINES = $(R_RCDEFINES)
!endif
!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS = REC.SBR \
		RECDLG.SBR \
		RECFILE.SBR \
		RECINIT.SBR \
		RECPAINT.SBR \
		RECPLAY.SBR \
		RECREC.SBR


REC_DEP = c:\c\rec\rec.h \
	c:\vfwdk\inc\mmreg.h \
	c:\vfwdk\inc\msacm.h \
	c:\c\rec\recinit.h \
	c:\c\rec\recfile.h \
	c:\c\rec\recdlg.h \
	c:\c\rec\recpaint.h \
	c:\c\rec\recrec.h \
	c:\c\rec\recplay.h


RECDLG_DEP = c:\c\rec\rec.h \
	c:\vfwdk\inc\mmreg.h \
	c:\vfwdk\inc\msacm.h \
	c:\c\rec\recdlg.h \
	c:\c\rec\recplay.h


RECFILE_DEP = c:\c\rec\rec.h \
	c:\vfwdk\inc\mmreg.h \
	c:\vfwdk\inc\msacm.h \
	c:\c\rec\recfile.h \
	c:\c\rec\recrec.h \
	c:\c\rec\recpaint.h \
	c:\c\rec\recdlg.h


RECINIT_DEP = c:\c\rec\rec.h \
	c:\vfwdk\inc\mmreg.h \
	c:\vfwdk\inc\msacm.h \
	c:\c\rec\recinit.h \
	c:\c\rec\recpaint.h \
	c:\c\rec\recfile.h


RECPAINT_DEP = c:\c\rec\rec.h \
	c:\vfwdk\inc\mmreg.h \
	c:\vfwdk\inc\msacm.h \
	c:\c\rec\recpaint.h


RECPLAY_DEP = c:\c\rec\rec.h \
	c:\vfwdk\inc\mmreg.h \
	c:\vfwdk\inc\msacm.h \
	c:\c\rec\recrec.h \
	c:\c\rec\recplay.h \
	c:\c\rec\recdlg.h \
	c:\c\rec\recpaint.h


RECREC_DEP = c:\c\rec\rec.h \
	c:\vfwdk\inc\mmreg.h \
	c:\vfwdk\inc\msacm.h \
	c:\c\rec\recrec.h \
	c:\c\rec\recdlg.h \
	c:\c\rec\recpaint.h


REC_RCDEP = c:\c\rec\rec.h \
	c:\vfwdk\inc\mmreg.h \
	c:\vfwdk\inc\msacm.h \
	c:\c\rec\rec.ico \
	c:\c\rec\rec1.ico \
	c:\c\rec\sqrlite1.bmp \
	c:\c\rec\sqrlite2.bmp \
	c:\c\rec\sqrlite3.bmp


all:	$(PROJ).EXE

REC.OBJ:	REC.C $(REC_DEP)
	$(CC) $(CFLAGS) $(CCREATEPCHFLAG) /c REC.C

RECDLG.OBJ:	RECDLG.C $(RECDLG_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c RECDLG.C

RECFILE.OBJ:	RECFILE.C $(RECFILE_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c RECFILE.C

RECINIT.OBJ:	RECINIT.C $(RECINIT_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c RECINIT.C

RECPAINT.OBJ:	RECPAINT.C $(RECPAINT_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c RECPAINT.C

RECPLAY.OBJ:	RECPLAY.C $(RECPLAY_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c RECPLAY.C

RECREC.OBJ:	RECREC.C $(RECREC_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c RECREC.C

REC.RES:	REC.RC $(REC_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r REC.RC


$(PROJ).EXE::	REC.RES

$(PROJ).EXE::	REC.OBJ RECDLG.OBJ RECFILE.OBJ RECINIT.OBJ RECPAINT.OBJ RECPLAY.OBJ \
	RECREC.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
REC.OBJ +
RECDLG.OBJ +
RECFILE.OBJ +
RECINIT.OBJ +
RECPAINT.OBJ +
RECPLAY.OBJ +
RECREC.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
c:\msvc\lib\+
c:\msvc\mfc\lib\+
c:\vfwdk\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) REC.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	REC.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) REC.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
