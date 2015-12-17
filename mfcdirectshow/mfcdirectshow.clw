; CLW-Datei enthält Informationen für den MFC-Klassen-Assistenten

[General Info]
Version=1
LastClass=CMfcdirectshowDlg
LastTemplate=generic CWnd
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "mfcdirectshow.h"

ClassCount=4
Class1=CMfcdirectshowApp
Class2=CMfcdirectshowDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CDirectShowWnd
Resource3=IDD_MFCDIRECTSHOW_DIALOG

[CLS:CMfcdirectshowApp]
Type=0
HeaderFile=mfcdirectshow.h
ImplementationFile=mfcdirectshow.cpp
Filter=N

[CLS:CMfcdirectshowDlg]
Type=0
HeaderFile=mfcdirectshowDlg.h
ImplementationFile=mfcdirectshowDlg.cpp
Filter=D
LastObject=CMfcdirectshowDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=mfcdirectshowDlg.h
ImplementationFile=mfcdirectshowDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_MFCDIRECTSHOW_DIALOG]
Type=1
Class=CMfcdirectshowDlg
ControlCount=4
Control1=IDC_FULLSCREEN,button,1342242817
Control2=IDC_PLAY,button,1342242816
Control3=ID_HELP,button,1342242816
Control4=IDC_FILE,edit,1350631552

[CLS:CDirectShowWnd]
Type=0
HeaderFile=DirectShowWnd.h
ImplementationFile=DirectShowWnd.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC
LastObject=CDirectShowWnd

