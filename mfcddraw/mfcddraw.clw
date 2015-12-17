; CLW-Datei enthält Informationen für den MFC-Klassen-Assistenten

[General Info]
Version=1
LastClass=CMfcddrawDlg
LastTemplate=generic CWnd
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "mfcddraw.h"

ClassCount=4
Class1=CMfcddrawApp
Class2=CMfcddrawDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CDDrawWnd
Resource3=IDD_MFCDDRAW_DIALOG
Resource4=IDR_MENU1

[CLS:CMfcddrawApp]
Type=0
HeaderFile=mfcddraw.h
ImplementationFile=mfcddraw.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CMfcddrawApp

[CLS:CMfcddrawDlg]
Type=0
HeaderFile=mfcddrawDlg.h
ImplementationFile=mfcddrawDlg.cpp
Filter=D
LastObject=CMfcddrawDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=mfcddrawDlg.h
ImplementationFile=mfcddrawDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342308480
Control2=IDC_STATIC,static,1342308352
Control3=IDOK,button,1342373889
Control4=IDC_STATIC,static,1342308480

[DLG:IDD_MFCDDRAW_DIALOG]
Type=1
Class=CMfcddrawDlg
ControlCount=12
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,button,1342177287
Control3=IDC_NOREF,button,1342308361
Control4=IDC_OPENEND,button,1342177289
Control5=IDC_FIXEDEND,button,1342177289
Control6=IDC_STATIC,button,1342177287
Control7=IDC_SPEED,edit,1350631552
Control8=IDC_AMP,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_HZ,edit,1350631552
Control12=IDC_STATIC,static,1342308352

[CLS:CDDrawWnd]
Type=0
HeaderFile=DDrawWnd.h
ImplementationFile=DDrawWnd.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC
LastObject=CDDrawWnd

[MNU:IDR_MENU1]
Type=1
Class=?
Command1=ID_PROGRAMM_INFO
Command2=ID_PROGRAMM_EINSTELLUNGEN
Command3=ID_PROGRAMM_BEENDEN
CommandCount=3

