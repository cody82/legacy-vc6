@echo off
REM -- Zuerst Zuordnungsdatei der mit Microsoft Visual C++ erzeugten resource.h erstellen
echo // Von MAKEHELP.BAT erzeugte Hilfe-Zuordnungsdatei. Wird verwendet von MFCDIRECTSHOW.HPJ. >"hlp\mfcdirectshow.hm"
echo. >>"hlp\mfcdirectshow.hm"
echo // Befehle (ID_* und IDM_*) >>"hlp\mfcdirectshow.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\mfcdirectshow.hm"
echo. >>"hlp\mfcdirectshow.hm"
echo // Eingabeaufforderungen (IDP_*) >>"hlp\mfcdirectshow.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\mfcdirectshow.hm"
echo. >>"hlp\mfcdirectshow.hm"
echo // Ressourcen (IDR_*) >>"hlp\mfcdirectshow.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\mfcdirectshow.hm"
echo. >>"hlp\mfcdirectshow.hm"
echo // Dialogfelder (IDD_*) >>"hlp\mfcdirectshow.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\mfcdirectshow.hm"
echo. >>"hlp\mfcdirectshow.hm"
echo // Rahmen-Steuerelemente (IDW_*) >>"hlp\mfcdirectshow.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\mfcdirectshow.hm"
REM -- Hilfe erstellen für Projekt MFCDIRECTSHOW


echo Erstelle Win32-Hilfedateien
start /wait hcw /C /E /M "hlp\mfcdirectshow.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\mfcdirectshow.hlp" goto :Error
if not exist "hlp\mfcdirectshow.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\mfcdirectshow.hlp" Debug
if exist Debug\nul copy "hlp\mfcdirectshow.cnt" Debug
if exist Release\nul copy "hlp\mfcdirectshow.hlp" Release
if exist Release\nul copy "hlp\mfcdirectshow.cnt" Release
echo.
goto :done

:Error
echo hlp\mfcdirectshow.hpj(1) : Fehler: Problem beim Erstellen der Hilfedatei festgestellt

:done
echo.
