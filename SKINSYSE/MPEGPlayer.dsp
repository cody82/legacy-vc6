# Microsoft Developer Studio Project File - Name="MPEGPlayer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=MPEGPlayer - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MPEGPlayer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MPEGPlayer.mak" CFG="MPEGPlayer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MPEGPlayer - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MPEGPlayer - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath "Desktop"
# PROP WCE_FormatVersion ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MPEGPlayer - Win32 Release"

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
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x41f /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x41f /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 winmm.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "MPEGPlayer - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /YX"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x41f /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x41f /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 winmm.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "MPEGPlayer - Win32 Release"
# Name "MPEGPlayer - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\SkinSys\AnimatedLabel.cpp

!IF  "$(CFG)" == "MPEGPlayer - Win32 Release"

# ADD CPP /YX

!ELSEIF  "$(CFG)" == "MPEGPlayer - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Decoder\Audio.cpp

!IF  "$(CFG)" == "MPEGPlayer - Win32 Release"

# ADD CPP /YX

!ELSEIF  "$(CFG)" == "MPEGPlayer - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SkinSys\BitmapBtn.cpp

!IF  "$(CFG)" == "MPEGPlayer - Win32 Release"

# ADD CPP /YX"stdafx.h"

!ELSEIF  "$(CFG)" == "MPEGPlayer - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SkinSys\BitmapProgress.cpp

!IF  "$(CFG)" == "MPEGPlayer - Win32 Release"

# ADD CPP /YX"stdafx.h"

!ELSEIF  "$(CFG)" == "MPEGPlayer - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SkinSys\BitmapSlider.cpp

!IF  "$(CFG)" == "MPEGPlayer - Win32 Release"

# ADD CPP /YX"stdafx.h"

!ELSEIF  "$(CFG)" == "MPEGPlayer - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Decoder\Decoder.cpp

!IF  "$(CFG)" == "MPEGPlayer - Win32 Release"

# ADD CPP /YX"stdafx.h"

!ELSEIF  "$(CFG)" == "MPEGPlayer - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Decoder\Helper.cpp

!IF  "$(CFG)" == "MPEGPlayer - Win32 Release"

# ADD CPP /YX"stdafx.h"

!ELSEIF  "$(CFG)" == "MPEGPlayer - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SkinSys\Inifile.Cpp

!IF  "$(CFG)" == "MPEGPlayer - Win32 Release"

# ADD CPP /YX"stdafx.h"

!ELSEIF  "$(CFG)" == "MPEGPlayer - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MPEGPlayer.cpp

!IF  "$(CFG)" == "MPEGPlayer - Win32 Release"

# ADD CPP /YX"stdafx.h"

!ELSEIF  "$(CFG)" == "MPEGPlayer - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MPEGPlayer.rc
# End Source File
# Begin Source File

SOURCE=.\MPEGPlayerDlg.cpp

!IF  "$(CFG)" == "MPEGPlayer - Win32 Release"

# ADD CPP /YX"stdafx.h"

!ELSEIF  "$(CFG)" == "MPEGPlayer - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Decoder\Player.cpp

!IF  "$(CFG)" == "MPEGPlayer - Win32 Release"

# ADD CPP /YX"stdafx.h"

!ELSEIF  "$(CFG)" == "MPEGPlayer - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SkinSys\SkinButton.cpp

!IF  "$(CFG)" == "MPEGPlayer - Win32 Release"

# ADD CPP /YX"stdafx.h"

!ELSEIF  "$(CFG)" == "MPEGPlayer - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SkinSys\SkinDialog.cpp

!IF  "$(CFG)" == "MPEGPlayer - Win32 Release"

# ADD CPP /YX"stdafx.h"

!ELSEIF  "$(CFG)" == "MPEGPlayer - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SkinSys\SkinLabel.cpp

!IF  "$(CFG)" == "MPEGPlayer - Win32 Release"

# ADD CPP /YX"stdafx.h"

!ELSEIF  "$(CFG)" == "MPEGPlayer - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SkinSys\SkinProgress.cpp

!IF  "$(CFG)" == "MPEGPlayer - Win32 Release"

# ADD CPP /YX"stdafx.h"

!ELSEIF  "$(CFG)" == "MPEGPlayer - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SkinSys\SkinSlider.cpp

!IF  "$(CFG)" == "MPEGPlayer - Win32 Release"

# ADD CPP /YX"stdafx.h"

!ELSEIF  "$(CFG)" == "MPEGPlayer - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Decoder\stream.cpp

!IF  "$(CFG)" == "MPEGPlayer - Win32 Release"

# ADD CPP /YX"stdafx.h"

!ELSEIF  "$(CFG)" == "MPEGPlayer - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Decoder\tabinit.cpp

!IF  "$(CFG)" == "MPEGPlayer - Win32 Release"

# ADD CPP /YX"stdafx.h"

!ELSEIF  "$(CFG)" == "MPEGPlayer - Win32 Debug"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\SkinSys\AnimatedLabel.h
# End Source File
# Begin Source File

SOURCE=.\Decoder\Args.h
# End Source File
# Begin Source File

SOURCE=.\Decoder\Audio.h
# End Source File
# Begin Source File

SOURCE=.\SkinSys\BitmapBtn.h
# End Source File
# Begin Source File

SOURCE=.\SkinSys\BitmapProgress.h
# End Source File
# Begin Source File

SOURCE=.\SkinSys\BitmapSlider.h
# End Source File
# Begin Source File

SOURCE=.\Decoder\Common.h
# End Source File
# Begin Source File

SOURCE=.\Decoder\Decoder.h
# End Source File
# Begin Source File

SOURCE=.\Decoder\Elsound.h
# End Source File
# Begin Source File

SOURCE=.\Decoder\Helper.h
# End Source File
# Begin Source File

SOURCE=.\Decoder\Huffman.h
# End Source File
# Begin Source File

SOURCE=.\SkinSys\IniFile.H
# End Source File
# Begin Source File

SOURCE=.\MPEGPlayer.h
# End Source File
# Begin Source File

SOURCE=.\MPEGPlayerDlg.h
# End Source File
# Begin Source File

SOURCE=.\Decoder\player.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SkinSys\SkinButton.h
# End Source File
# Begin Source File

SOURCE=.\SkinSys\SkinDialog.h
# End Source File
# Begin Source File

SOURCE=.\SkinSys\SkinLabel.h
# End Source File
# Begin Source File

SOURCE=.\SkinSys\SkinProgress.h
# End Source File
# Begin Source File

SOURCE=.\SkinSys\SkinSlider.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Decoder\stream.h
# End Source File
# Begin Source File

SOURCE=.\Decoder\Tables.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\MPEGPlayer.ico
# End Source File
# Begin Source File

SOURCE=.\res\MPEGPlayer.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
