# Microsoft Developer Studio Project File - Name="Include" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Include - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "Include.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "Include.mak" CFG="Include - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "Include - Win32 Release" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "Include - Win32 Debug" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Include - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "Include - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Debug\Include_d.lib"

!ENDIF 

# Begin Target

# Name "Include - Win32 Release"
# Name "Include - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AviItem.cpp
# End Source File
# Begin Source File

SOURCE=.\BitBool.cpp
# End Source File
# Begin Source File

SOURCE=.\BitmapItem.cpp
# End Source File
# Begin Source File

SOURCE=.\bmputil.cpp
# End Source File
# Begin Source File

SOURCE=.\ButtonItem.cpp
# End Source File
# Begin Source File

SOURCE=.\CAVIPlayTest.cpp
# End Source File
# Begin Source File

SOURCE=.\CDPlayer.cpp
# End Source File
# Begin Source File

SOURCE=.\cmdlineitem.cpp
# End Source File
# Begin Source File

SOURCE=.\cpakfile.cpp
# End Source File
# Begin Source File

SOURCE=.\Ddutil.cpp
# End Source File
# Begin Source File

SOURCE=.\Dib.c
# End Source File
# Begin Source File

SOURCE=.\Dibapi.cpp
# End Source File
# Begin Source File

SOURCE=.\DIClass.cpp
# End Source File
# Begin Source File

SOURCE=.\dsplayer.cpp
# End Source File
# Begin Source File

SOURCE=.\Dsutil3d.c
# End Source File
# Begin Source File

SOURCE=.\engine.cpp
# End Source File
# Begin Source File

SOURCE=.\event.cpp
# End Source File
# Begin Source File

SOURCE=.\int2str.cpp
# End Source File
# Begin Source File

SOURCE=.\joystick.cpp
# End Source File
# Begin Source File

SOURCE=.\packfile.cpp
# End Source File
# Begin Source File

SOURCE=.\profiles.cpp
# End Source File
# Begin Source File

SOURCE=.\sprite.cpp
# End Source File
# Begin Source File

SOURCE=.\WndItem.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AviItem.h
# End Source File
# Begin Source File

SOURCE=.\BitBool.h
# End Source File
# Begin Source File

SOURCE=.\BitmapItem.h
# End Source File
# Begin Source File

SOURCE=.\bmputil.h
# End Source File
# Begin Source File

SOURCE=.\ButtonItem.h
# End Source File
# Begin Source File

SOURCE=.\CDPlayer.h
# End Source File
# Begin Source File

SOURCE=.\cmdlineitem.h
# End Source File
# Begin Source File

SOURCE=.\cpakfile.h
# End Source File
# Begin Source File

SOURCE=.\Ddutil.h
# End Source File
# Begin Source File

SOURCE=.\Dib.h
# End Source File
# Begin Source File

SOURCE=.\Dibapi.h
# End Source File
# Begin Source File

SOURCE=.\DIClass.h
# End Source File
# Begin Source File

SOURCE=.\dsplayer.h
# End Source File
# Begin Source File

SOURCE=.\Dsutil3d.h
# End Source File
# Begin Source File

SOURCE=.\Engine.h
# End Source File
# Begin Source File

SOURCE=.\event.h
# End Source File
# Begin Source File

SOURCE=.\gaudio.h
# End Source File
# Begin Source File

SOURCE=.\include.h
# End Source File
# Begin Source File

SOURCE=.\int2str.h
# End Source File
# Begin Source File

SOURCE=.\joystick.h
# End Source File
# Begin Source File

SOURCE=.\packfile.h
# End Source File
# Begin Source File

SOURCE=.\profiles.h
# End Source File
# Begin Source File

SOURCE=.\Sprite.h
# End Source File
# Begin Source File

SOURCE=.\WndItem.h
# End Source File
# End Group
# End Target
# End Project
