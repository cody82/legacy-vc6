# Microsoft Developer Studio Project File - Name="start_new" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=start_new - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "start_new.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "start_new.mak" CFG="start_new - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "start_new - Win32 Release" (basierend auf  "Win32 (x86) Application")
!MESSAGE "start_new - Win32 Debug" (basierend auf  "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "start_new - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 vfw32.lib msimg32.lib winmm.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "start_new - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 vfw32.lib msimg32.lib winmm.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "start_new - Win32 Release"
# Name "start_new - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Asteroids.cpp
# End Source File
# Begin Source File

SOURCE=..\Include\bmputil.cpp
# End Source File
# Begin Source File

SOURCE=..\Include\cpakfile.cpp
# End Source File
# Begin Source File

SOURCE=..\Include\DDRotate.CPP
# End Source File
# Begin Source File

SOURCE=..\Include\Ddutil.cpp
# End Source File
# Begin Source File

SOURCE=..\Include\Dib.c
# End Source File
# Begin Source File

SOURCE=..\Include\Dibapi.cpp
# End Source File
# Begin Source File

SOURCE=..\Include\int2str.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionPages.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionsSheet.cpp
# End Source File
# Begin Source File

SOURCE=..\Include\packfile.cpp
# End Source File
# Begin Source File

SOURCE=.\PlayersDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ShipSelectDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SoundPage.cpp
# End Source File
# Begin Source File

SOURCE=.\start_new.cpp
# End Source File
# Begin Source File

SOURCE=.\start_new.rc
# End Source File
# Begin Source File

SOURCE=.\start_newDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Asteroids.h
# End Source File
# Begin Source File

SOURCE=..\Include\bmputil.h
# End Source File
# Begin Source File

SOURCE=..\Include\cpakfile.h
# End Source File
# Begin Source File

SOURCE=..\Include\DDRotate.h
# End Source File
# Begin Source File

SOURCE=..\Include\Dib.h
# End Source File
# Begin Source File

SOURCE=..\Include\int2str.h
# End Source File
# Begin Source File

SOURCE=.\OptionPages.h
# End Source File
# Begin Source File

SOURCE=.\OptionsSheet.h
# End Source File
# Begin Source File

SOURCE=..\Include\packfile.h
# End Source File
# Begin Source File

SOURCE=.\PlayersDialog.h
# End Source File
# Begin Source File

SOURCE=..\Include\profiles.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ShipSelectDlg.h
# End Source File
# Begin Source File

SOURCE=.\SoundPage.h
# End Source File
# Begin Source File

SOURCE=.\start_new.h
# End Source File
# Begin Source File

SOURCE=.\start_newDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon2.ico
# End Source File
# Begin Source File

SOURCE=..\Include\profiles.cpp
# End Source File
# Begin Source File

SOURCE=.\res\start_new.ico
# End Source File
# Begin Source File

SOURCE=.\res\start_new.rc2
# End Source File
# Begin Source File

SOURCE=.\tie1.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
