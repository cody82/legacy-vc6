; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPlayersDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "DPTest.h"

ClassCount=4
Class1=CDPTestApp
Class2=CDPTestDlg

ResourceCount=4
Resource2=IDD_DPTEST_DIALOG
Resource1=IDR_MAINFRAME
Class3=CSessionDlg
Resource3=IDD_SESSIONS
Class4=CPlayersDlg
Resource4=IDD_PLAYERS

[CLS:CDPTestApp]
Type=0
HeaderFile=DPTest.h
ImplementationFile=DPTest.cpp
Filter=N

[CLS:CDPTestDlg]
Type=0
HeaderFile=DPTestDlg.h
ImplementationFile=DPTestDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_LIST1



[DLG:IDD_DPTEST_DIALOG]
Type=1
Class=CDPTestDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST1,listbox,1352728833
Control4=IDC_SELECT,button,1342242816

[DLG:IDD_SESSIONS]
Type=1
Class=CSessionDlg
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST1,listbox,1352728833
Control4=IDC_CREATE,button,1342242816
Control5=IDC_JOIN,button,1342242816
Control6=IDC_UPDATE,button,1342242816

[CLS:CSessionDlg]
Type=0
HeaderFile=SessionDlg.h
ImplementationFile=SessionDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CSessionDlg

[DLG:IDD_PLAYERS]
Type=1
Class=CPlayersDlg
ControlCount=6
Control1=IDC_SEND,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST1,listbox,1352728833
Control4=IDC_UPDATE,button,1342242817
Control5=IDC_CREATE,button,1342242817
Control6=IDC_CHAT,edit,1350631552

[CLS:CPlayersDlg]
Type=0
HeaderFile=PlayersDlg.h
ImplementationFile=PlayersDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CPlayersDlg
VirtualFilter=dWC

