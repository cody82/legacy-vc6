# Microsoft Developer Studio Project File - Name="Facharbeit2" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Facharbeit2 - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "Facharbeit2.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "Facharbeit2.mak" CFG="Facharbeit2 - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "Facharbeit2 - Win32 Release" (basierend auf  "Win32 (x86) Application")
!MESSAGE "Facharbeit2 - Win32 Debug" (basierend auf  "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Facharbeit2 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 d3dx.lib gaudio1x.lib dxguid.lib ddraw.lib dsound.lib dinput.lib winmm.lib vfw32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Facharbeit2 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 d3dx.lib gaudio1x.lib dxguid.lib ddraw.lib dsound.lib dinput.lib winmm.lib vfw32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Facharbeit2 - Win32 Release"
# Name "Facharbeit2 - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Facharbeit2.cpp
# End Source File
# Begin Source File

SOURCE=.\MechanicWave.cpp
# End Source File
# Begin Source File

SOURCE=.\MechWaveDlg.cpp
# End Source File
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\MechanicWave.h
# End Source File
# Begin Source File

SOURCE=.\MechWaveDlg.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# End Group
# Begin Group "Ressourcendateien"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\resource.rc
# End Source File
# End Group
# Begin Group "Lib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Libraries\Include\UniversalLib\BitBool.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Libraries\Include\UniversalLib\CmdMsgTarget.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Libraries\Include\DirectXLib\D3DXDeviceDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Libraries\Include\DirectXLib\D3DXEngine.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Libraries\Include\DirectXLib\D3DXTexList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Libraries\Include\DirectXLib\D3DXUtil.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Libraries\Include\DirectXLib\DI7Engine.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Libraries\Include\UniversalLib\Dib.c
# End Source File
# Begin Source File

SOURCE=..\..\Libraries\Include\UniversalLib\Dibapi.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Libraries\Include\UniversalLib\dll.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Libraries\Include\DirectXLib\DSEngine.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Libraries\Include\DirectXLib\Dsutil3d.c
# End Source File
# Begin Source File

SOURCE=..\..\Libraries\Include\GameLib\DXAviWindow.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Libraries\Include\GameLib\DXCursor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Libraries\Include\GameLib\DXFont.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Libraries\Include\GameLib\DXObject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Libraries\Include\GameLib\DXPath.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Libraries\Include\GameLib\DXSprite.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Libraries\Include\GameLib\DXSpriteControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Libraries\Include\GameLib\DXTile.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Libraries\Include\GameLib\DXWindow.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Libraries\Include\GameLib\Effects.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Libraries\Include\GameLib\GameEngine.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Libraries\Include\DirectXLib\GAudioPlayer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Libraries\Include\UniversalLib\IUnknownList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Libraries\Include\UniversalLib\List.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Libraries\Include\UniversalLib\MathLib.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Libraries\Include\UniversalLib\profiles.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Libraries\Include\UniversalLib\RuntimeClassInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Libraries\Include\DirectXLib\SpeedTest.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Libraries\Include\UniversalLib\StringX.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Libraries\Include\UniversalLib\Universal.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Libraries\Include\UniversalLib\Window.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
