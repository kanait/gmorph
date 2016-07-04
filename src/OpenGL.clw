; CLW ÉtÉ@ÉCÉãÇÕ MFC ClassWizard ÇÃèÓïÒÇä‹ÇÒÇ≈Ç¢Ç‹Ç∑ÅB

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "OpenGL.h"
LastPage=0

ClassCount=20
Class1=COpenGLApp
Class2=COpenGLDoc
Class3=COpenGLView
Class4=CMainFrame

ResourceCount=18
Resource1=IDD_CREATE_SPATH_MANU
Class5=CAboutDlg
Resource2=IDR_MAINFRAME (âpåÍ (±“ÿ∂))
Class6=CDistView
Resource3=IDD_RECORD_POV_DIALOG (âpåÍ (±“ÿ∂))
Class7=CQuitDialog
Resource4=IDD_ABOUTBOX
Resource5=IDD_DELETE_SPATH
Class8=CMSPDialog
Class9=CCVDialog
Resource6=IDD_CREATE_PPDFACE
Class10=CPLDialog
Resource7=IDD_CREATE_PPDLOOP
Class11=CCMDialog
Resource8=IDD_INTERP_PARAMS
Class12=CPFDialog
Resource9=IDD_CREATE_SPATH
Class13=CDPLDialog
Resource10=IDD_DELETE_PPDLOOP
Class14=CDCMDialog
Resource11=IDD_FAIR_COE
Class15=CDPFDialog
Resource12=IDD_QUIT_DIALOG
Class16=CSPDialog
Resource13=IDD_DELETE_CMESH
Resource14=IDD_DELETE_PPDFACE
Class17=CDSPDialog
Resource15=IDD_CREATE_CV
Class18=CSIPDialog
Resource16=IDR_MAINFRAME
Class19=CSFIDialog
Resource17=IDD_CREATE_CMESH
Class20=CSRDialog
Resource18=IDD_SET_RADIUS

[CLS:COpenGLApp]
Type=0
HeaderFile=OpenGL.h
ImplementationFile=OpenGL.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=COpenGLApp

[CLS:COpenGLDoc]
Type=0
HeaderFile=OpenGLDoc.h
ImplementationFile=OpenGLDoc.cpp
Filter=N
LastObject=COpenGLDoc

[CLS:COpenGLView]
Type=0
HeaderFile=OpenGLView.h
ImplementationFile=OpenGLView.cpp
Filter=C
LastObject=COpenGLView
BaseClass=CView
VirtualFilter=VWC

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_MORPH_SPATH_CREATE
BaseClass=CFrameWnd
VirtualFilter=fWC



[CLS:CAboutDlg]
Type=0
HeaderFile=OpenGL.cpp
ImplementationFile=OpenGL.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308491
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_OPEN_DIST
Command2=ID_EDIT_COPY
Command3=ID_FILE_OPEN_GMH
Command4=ID_FILE_NEW
Command5=ID_FILE_OPEN
Command6=ID_FILE_PRINT
Command7=ID_APP_EXIT
Command8=ID_FILE_SAVE
Command9=ID_EDIT_PASTE
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
Command14=ID_EDIT_COPY
Command15=ID_EDIT_PASTE
Command16=ID_EDIT_CUT
Command17=ID_EDIT_UNDO
CommandCount=17

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[CLS:CDistView]
Type=0
HeaderFile=DistView.h
ImplementationFile=DistView.cpp
BaseClass=CView
Filter=C
LastObject=CDistView
VirtualFilter=VWC

[DLG:IDD_QUIT_DIALOG]
Type=1
Class=CQuitDialog
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

[CLS:CQuitDialog]
Type=0
HeaderFile=QuitDialog.h
ImplementationFile=QuitDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CQuitDialog

[MNU:IDR_MAINFRAME (âpåÍ (±“ÿ∂))]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN_GMH
Command3=ID_FILE_OPEN
Command4=ID_FILE_OPEN_DIST
Command5=ID_FILE_SAVE
Command6=ID_FILE_SAVE_AS
Command7=ID_APP_EXIT
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_VIEW_TOOLBAR
Command13=ID_VIEW_STATUS_BAR
Command14=ID_MENU_SCREEN_VERT
Command15=ID_MENU_SCREEN_WIREFRAME
Command16=ID_MENU_SCREEN_SHADING
Command17=ID_MENU_SCREEN_CV
Command18=ID_MENU_SCREEN_PCM
Command19=ID_MENU_SCREEN_LOOP
Command20=ID_MENU_SCREEN_GROUP
Command21=ID_MENU_SCREEN_SPATH
Command22=ID_MENU_SCREEN_HMAP
Command23=ID_MENU_SCREEN_COAXIS
Command24=ID_APP_ABOUT
CommandCount=24

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN_GMH
Command3=ID_FILE_OPEN
Command4=ID_FILE_OPEN_DIST
Command5=ID_FILE_OPEN_GPPD
Command6=ID_FILE_SAVE_GMH
Command7=ID_FILE_SAVE_SRC
Command8=ID_FILE_SAVE_DIST
Command9=ID_FILE_SAVE_GPPD
Command10=ID_FILE_SAVE_POV
Command11=ID_FILE_RECORD_PPD
Command12=ID_FILE_RECORD_BMP
Command13=ID_FILE_RECORD_POV
Command14=ID_APP_EXIT
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=ID_MENU_SCREEN_VERT
Command18=ID_MENU_SCREEN_WIREFRAME
Command19=ID_MENU_SCREEN_SHADING
Command20=ID_MENU_SCREEN_CV
Command21=ID_MENU_SCREEN_PCM
Command22=ID_MENU_SCREEN_LOOP
Command23=ID_MENU_SCREEN_GROUP
Command24=ID_MENU_SCREEN_SPATH
Command25=ID_MENU_SCREEN_HMAP
Command26=ID_MENU_SCREEN_COAXIS
Command27=ID_MENU_SCREEN_ENHANCED
Command28=ID_MENU_SCREEN_SMOOTH
Command29=ID_MENU_SCREEN_INTERP
Command30=ID_MENU_SCREEN_RADIUS
Command31=ID_MORPH_SPATH_CREATE
Command32=ID_MORPH_SPATH_CLEAR
Command33=ID_MORPH_CREATE_GPPD
Command34=ID_MORPH_DELETE_GPPD
Command35=ID_MORPH_START
Command36=ID_MORPH_RESET
Command37=ID_MORPH_SET_DIV
Command38=ID_MENU_GENER_INTERP
Command39=ID_MENU_SET_CONST
Command40=ID_MENU_FAIR_SP
Command41=ID_MENU_FAIR_WW
Command42=ID_APP_ABOUT
CommandCount=42

[DLG:IDD_CREATE_CV]
Type=1
Class=CCVDialog
ControlCount=6
Control1=IDC_EDIT_CCV_SRC,edit,1350633600
Control2=IDC_EDIT_CCV_DIST,edit,1350633600
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816
Control5=IDC_STATIC,static,1342373899
Control6=IDC_STATIC,static,1342373900

[DLG:IDD_RECORD_POV_DIALOG (âpåÍ (±“ÿ∂))]
Type=1
Class=?
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT2,edit,1350631552
Control4=IDC_EDIT3,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,button,1342177287
Control8=IDC_STATIC,button,1342177287
Control9=IDC_EDIT5,edit,1350631552
Control10=IDC_BUTTON1,button,1342242816

[CLS:CCVDialog]
Type=0
HeaderFile=CVDialog.h
ImplementationFile=CVDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CCVDialog
VirtualFilter=dWC

[DLG:IDD_CREATE_PPDLOOP]
Type=1
Class=CPLDialog
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_CPL_VT,edit,1350633600
Control4=IDC_STATIC,static,1342308352
Control5=IDC_CPL_SC,edit,1350633600
Control6=IDC_STATIC,static,1342308352

[CLS:CPLDialog]
Type=0
HeaderFile=PLDialog.h
ImplementationFile=PLDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CPLDialog

[DLG:IDD_CREATE_CMESH]
Type=1
Class=CCMDialog
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_CCM_CV_LIST,listbox,1352728835

[CLS:CCMDialog]
Type=0
HeaderFile=CMDialog.h
ImplementationFile=CMDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CCMDialog
VirtualFilter=dWC

[DLG:IDD_CREATE_PPDFACE]
Type=1
Class=CPFDialog
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_CPF_PV_LIST,listbox,1352728835

[CLS:CPFDialog]
Type=0
HeaderFile=PFDialog.h
ImplementationFile=PFDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CPFDialog

[DLG:IDD_DELETE_PPDLOOP]
Type=1
Class=CDPLDialog
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_DPL_PL,edit,1350633600
Control4=IDC_STATIC,static,1342308352

[CLS:CDPLDialog]
Type=0
HeaderFile=DPLDialog.h
ImplementationFile=DPLDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_DPL_PL
VirtualFilter=dWC

[DLG:IDD_DELETE_CMESH]
Type=1
Class=CDCMDialog
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_DCM_CM,edit,1350633600
Control4=IDC_STATIC,static,1342308352

[CLS:CDCMDialog]
Type=0
HeaderFile=DCMDialog.h
ImplementationFile=DCMDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDCMDialog

[DLG:IDD_DELETE_PPDFACE]
Type=1
Class=CDPFDialog
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_DPF_PF,edit,1350633600

[CLS:CDPFDialog]
Type=0
HeaderFile=DPFDialog.h
ImplementationFile=DPFDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDPFDialog

[DLG:IDD_CREATE_SPATH]
Type=1
Class=CSPDialog
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_CSP_SRC,edit,1350633600
Control6=IDC_CSP_DIST,edit,1350633600

[CLS:CSPDialog]
Type=0
HeaderFile=SPDialog.h
ImplementationFile=SPDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CSPDialog
VirtualFilter=dWC

[DLG:IDD_DELETE_SPATH]
Type=1
Class=CDSPDialog
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_DSP_SP,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_DSP_SC,edit,1350631552

[CLS:CDSPDialog]
Type=0
HeaderFile=DSPDialog.h
ImplementationFile=DSPDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDSPDialog

[DLG:IDD_CREATE_SPATH_MANU]
Type=1
Class=CMSPDialog
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_MSP_PV,listbox,1352728835

[CLS:CMSPDialog]
Type=0
HeaderFile=MSPDialog.h
ImplementationFile=MSPDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CMSPDialog

[DLG:IDD_INTERP_PARAMS]
Type=1
Class=CSIPDialog
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_SIP_PRM,edit,1350631552

[CLS:CSIPDialog]
Type=0
HeaderFile=SIPDialog.h
ImplementationFile=SIPDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CSIPDialog

[DLG:IDD_FAIR_COE]
Type=1
Class=CSFIDialog
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_SFI_LMD,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_SFI_KPB,edit,1350631552
Control7=IDC_STATIC,button,1342177287
Control8=IDC_STATIC,button,1342177287
Control9=IDC_STATIC,static,1342308352
Control10=IDC_SFI_NUM,edit,1350631552

[CLS:CSFIDialog]
Type=0
HeaderFile=SFIDialog.h
ImplementationFile=SFIDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_SFI_KPB
VirtualFilter=dWC

[DLG:IDD_SET_RADIUS]
Type=1
Class=CSRDialog
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=ID_STATIC,static,1342308352
Control4=ID_STATIC2,static,1342308352
Control5=IDC_RADIUS_SPH,edit,1350631552
Control6=IDC_RADIUS_CYL,edit,1350631552

[CLS:CSRDialog]
Type=0
HeaderFile=SRDialog.h
ImplementationFile=SRDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=ID_STATIC

