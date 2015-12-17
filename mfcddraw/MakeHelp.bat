@echo off
REM -- Zuerst Zuordnungsdatei der mit Microsoft Visual C++ erzeugten resource.h erstellen
echo // Von MAKEHELP.BAT erzeugte Hilfe-Zuordnungsdatei. Wird verwendet von MFCDDRAW.HPJ. >"hlp\mfcddraw.hm"
echo. >>"hlp\mfcddraw.hm"
echo // Befehle (ID_* und IDM_*) >>"hlp\mfcddraw.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\mfcddraw.hm"
echo. >>"hlp\mfcddraw.hm"
echo // Eingabeaufforderungen (IDP_*) >>"hlp\mfcddraw.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\mfcddraw.hm"
echo. >>"hlp\mfcddraw.hm"
echo // Ressourcen (IDR_*) >>"hlp\mfcddraw.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\mfcddraw.hm"
echo. >>"hlp\mfcddraw.hm"
echo // Dialogfelder (IDD_*) >>"hlp\mfcddraw.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\mfcddraw.hm"
echo. >>"hlp\mfcddraw.hm"
echo // Rahmen-Steuerelemente (IDW_*) >>"hlp\mfcddraw.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\mfcddraw.hm"
REM -- Hilfe erstellen für Projekt MFCDDRAW


echo Erstelle Win32-Hilfedateien
start /wait hcw /C /E /M "hlp\mfcddraw.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\mfcddraw.hlp" goto :Error
if not exist "hlp\mfcddraw.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\mfcddraw.hlp" Debug
if exist Debug\nul copy "hlp\mfcddraw.cnt" Debug
if exist Release\nul copy "hlp\mfcddraw.hlp" Release
if exist Release\nul copy "hlp\mfcddraw.cnt" Release
echo.
goto :done

:Error
echo hlp\mfcddraw.hpj(1) : Fehler: Problem beim Erstellen der Hilfedatei festgestellt

:done
echo.
