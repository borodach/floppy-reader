; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CFloppyReaderDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "FloppyReader.h"

ClassCount=3
Class1=CFloppyReaderApp
Class2=CFloppyReaderDlg
Class3=CAboutDlg

ResourceCount=6
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_FLOPPYREADER_DIALOG
Resource4=IDD_ABOUTBOX (English (U.S.))
Resource5=IDD_FLOPPYREADER_DIALOG (English (U.S.))
Resource6=IDC_MENU

[CLS:CFloppyReaderApp]
Type=0
HeaderFile=FloppyReader.h
ImplementationFile=FloppyReader.cpp
Filter=C
LastObject=CFloppyReaderApp

[CLS:CFloppyReaderDlg]
Type=0
HeaderFile=FloppyReaderDlg.h
ImplementationFile=FloppyReaderDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_EDIT1

[CLS:CAboutDlg]
Type=0
HeaderFile=FloppyReaderDlg.h
ImplementationFile=FloppyReaderDlg.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=3
Control1=IDC_STATIC,static,1342308480
Control2=IDC_STATIC,static,1342308352
Control3=IDOK,button,1342373889

[DLG:IDD_FLOPPYREADER_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CFloppyReaderDlg

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_FLOPPYREADER_DIALOG (English (U.S.))]
Type=1
Class=CFloppyReaderDlg
ControlCount=5
Control1=IDC_PROGRESS1,msctls_progress32,1350565888
Control2=IDC_SP1,static,1342308609
Control3=IDC_PROGRESS2,msctls_progress32,1350565888
Control4=IDC_SP2,static,1342308353
Control5=IDC_EDIT1,edit,1352730820

[MNU:IDC_MENU]
Type=1
Class=CFloppyReaderDlg
Command1=ID_N
Command2=ID_S
Command3=ID_ST
Command4=ID_L
Command5=ID_APP_EXIT
Command6=ID_STT
Command7=ID_CLR
Command8=ID_STOP
Command9=ID_HLP
CommandCount=9

