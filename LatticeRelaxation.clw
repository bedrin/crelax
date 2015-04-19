; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=ModelingOptionsDialog
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "LatticeRelaxation.h"
LastPage=0

ClassCount=14
Class1=CLatticeRelaxationApp
Class2=CLatticeRelaxationDoc
Class3=CLatticeRelaxationTableView
Class4=CMainFrame

ResourceCount=18
Resource1=IDD_ABOUTBOX
Resource2=IDD_MIGRATION_RESULTS_DIALOG
Class5=CAboutDlg
Class6=CLatticeRelaxationD3DView
Class7=AtomTypesDialog
Resource3=IDR_MAINFRAME
Class8=AtomDialog
Resource4=IDD_ATOM_DIALOG
Class9=PotentialDialog
Class10=CColorStatic
Resource5=IDD_MIGRATE_ATOM_DIALOG
Class11=ModelingOptionsDialog
Resource6=IDD_ATOMTYPES_DIALOG
Class12=MigrateAtomDialog
Resource7=IDD_NEW_LATTICE_DIALOG
Class13=MigrationResultsDialog
Resource8=IDD_POTENTIAL_DIALOG
Resource9=IDD_POTENTIAL_DIALOG (English (U.S.))
Resource10=IDD_ATOM_DIALOG (English (U.S.))
Resource11=IDD_MIGRATION_RESULTS_DIALOG (English (U.S.))
Resource12=IDD_ATOMTYPES_DIALOG (English (U.S.))
Resource13=IDD_MODELING_OPTIONS_DIALOG (English (U.S.))
Resource14=IDR_MAINFRAME (English (U.S.))
Resource15=IDD_ABOUTBOX (English (U.S.))
Resource16=IDD_MODELING_OPTIONS_DIALOG
Class14=CNewLatticeDialog
Resource17=IDD_MIGRATE_ATOM_DIALOG (English (U.S.))
Resource18=IDD_NEW_LATTICE_DIALOG (English (U.K.))

[CLS:CLatticeRelaxationApp]
Type=0
HeaderFile=LatticeRelaxation.h
ImplementationFile=LatticeRelaxation.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC

[CLS:CLatticeRelaxationDoc]
Type=0
HeaderFile=LatticeRelaxationDoc.h
ImplementationFile=LatticeRelaxationDoc.cpp
Filter=W
BaseClass=CDocument
VirtualFilter=DC
LastObject=CLatticeRelaxationDoc

[CLS:CLatticeRelaxationTableView]
Type=0
HeaderFile=LatticeRelaxationTableView.h
ImplementationFile=LatticeRelaxationTableView.cpp
Filter=C
BaseClass=CListView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T




[CLS:CAboutDlg]
Type=0
HeaderFile=LatticeRelaxation.cpp
ImplementationFile=LatticeRelaxation.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1350565891
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_EXPORT_RESULTS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_VIEW_TOOLBAR
Command12=ID_VIEW_STATUS_BAR
Command13=ID_3DVIEW
Command14=ID_TABLEVIEW
Command15=ID_SELECT_POTENTIAL
Command16=ID_ATOM_TYPES
Command17=ID_ADD_ATOM_BUTTON
Command18=ID_DELETE_ATOM_BUTTON
Command19=ID_EDIT_BUTTON_ATOM
Command20=ID_START_RELAXATION
Command21=ID_PAUSE_RELAXATION
Command22=ID_STOP_RELAXATION
Command23=ID_CALCULATE_FORCES
Command24=ID_MODELING_OPTIONS
Command25=ID_MODELING_RESULTS
Command26=ID_APP_ABOUT
CommandCount=26

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_APP_ABOUT
Command6=ID_REFRESH
Command7=ID_TABLEVIEW
Command8=ID_3DVIEW
Command9=ID_START_RELAXATION
Command10=ID_PAUSE_RELAXATION
Command11=ID_STOP_RELAXATION
Command12=ID_ADD_ATOM_BUTTON
Command13=ID_DELETE_ATOM_BUTTON
Command14=ID_EDIT_BUTTON_ATOM
Command15=ID_MIGRATE_ATOM_BUTTON
CommandCount=15

[CLS:CLatticeRelaxationD3DView]
Type=0
HeaderFile=LatticeRelaxationD3DView.h
ImplementationFile=LatticeRelaxationD3DView.cpp
BaseClass=CScrollView
Filter=M
VirtualFilter=VWC
LastObject=CLatticeRelaxationD3DView

[DLG:IDD_ATOMTYPES_DIALOG]
Type=1
Class=AtomTypesDialog
ControlCount=11
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST1,listbox,1352728833
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT1,edit,1350631552
Control7=IDC_EDIT2,edit,1484849280
Control8=IDC_ADD_ATOM_TYPE_BUTTON,button,1342242816
Control9=IDC_ATOMTYPE_COLOR_STATIC,static,1342308352
Control10=IDC_CHANGE_ATOM_TYPE_COLOR_BUTTON,button,1342242816
Control11=IDC_EMBEDDING_ENERGY_BUTTON,button,1342242816

[CLS:AtomTypesDialog]
Type=0
HeaderFile=AtomTypesDialog.h
ImplementationFile=AtomTypesDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=AtomTypesDialog
VirtualFilter=dWC

[DLG:IDD_ATOM_DIALOG]
Type=1
Class=AtomDialog
ControlCount=20
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT_POSITION_X,edit,1350631552
Control6=IDC_EDIT_FORCE_X,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_EDIT_POSITION_Y,edit,1350631552
Control10=IDC_STATIC,static,1342308352
Control11=IDC_EDIT_POSITION_Z,edit,1350631552
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_EDIT_FORCE_Y,edit,1350631552
Control15=IDC_STATIC,static,1342308352
Control16=IDC_EDIT_FORCE_Z,edit,1350631552
Control17=IDC_CHECK_MOVEABLE,button,1342242819
Control18=IDC_CHECK_VISIBLE,button,1342242819
Control19=IDC_ATOMTYPE_COMBO,combobox,1344339971
Control20=IDC_STATIC,static,1342308352

[CLS:AtomDialog]
Type=0
HeaderFile=AtomDialog.h
ImplementationFile=AtomDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=AtomDialog

[DLG:IDD_POTENTIAL_DIALOG]
Type=1
Class=PotentialDialog
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_POTENTIAL_LIST,SysListView32,1350631437
Control4=IDC_LOAD_POTENTIAL_BUTTON,button,1342242816
Control5=IDC_LOAD_ELECTRONIC_DISTRIBUTION_BUTTON,button,1342242816

[CLS:PotentialDialog]
Type=0
HeaderFile=PotentialDialog.h
ImplementationFile=PotentialDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_LOAD_POTENTIAL_BUTTON
VirtualFilter=dWC

[CLS:CColorStatic]
Type=0
HeaderFile=ColorStatic.h
ImplementationFile=ColorStatic.cpp
BaseClass=CStatic
Filter=W
VirtualFilter=WC
LastObject=IDC_EDIT1

[DLG:IDD_MODELING_OPTIONS_DIALOG]
Type=1
Class=ModelingOptionsDialog
ControlCount=28
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_EDIT_MAXIMUM_NUMBER_OF_STEPS,edit,1350631552
Control13=IDC_EDIT_MAXIMUM_NUMBER_OF_DEMPHINGS,edit,1350631552
Control14=IDC_EDIT_MAXIMUM_INTERACTION_DISTANCE,edit,1350631552
Control15=IDC_EDIT_MIMIMUM_KINETIC_ENERGY,edit,1350631552
Control16=IDC_EDIT_START_TIME_DELTA,edit,1350631552
Control17=IDC_EDIT_TIME_DELTA_INCREMENT,edit,1350631552
Control18=IDC_EDIT_MAXIMUM_TIME_DELTA,edit,1350631552
Control19=IDC_EDIT_DIFFERENTIAL_STEP,edit,1350631552
Control20=IDC_CHECK_USE_EMBEDDED_ATOM_METHOD,button,1342242819
Control21=IDC_CHECK_USE_DILATATION_VOLUME_CORRECTION,button,1342242819
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_EDIT_BULK_MODULUS,edit,1350631552
Control25=IDC_STATIC,static,1342308352
Control26=IDC_EDIT_ELASTIC_CORRECTIONS_AMMOUNT,edit,1350631552
Control27=IDC_CHECK_DAMPING_ENABLED,button,1342242819
Control28=IDC_STATIC,static,1342308352

[CLS:ModelingOptionsDialog]
Type=0
HeaderFile=ModelingOptionsDialog.h
ImplementationFile=ModelingOptionsDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=ID_3DVIEW

[DLG:IDD_MIGRATE_ATOM_DIALOG]
Type=1
Class=MigrateAtomDialog
ControlCount=11
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT_X,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EDIT_Y,edit,1350631552
Control8=IDC_STATIC,static,1342308352
Control9=IDC_EDIT_Z,edit,1350631552
Control10=IDC_STATIC,static,1342308352
Control11=IDC_EDIT_MIGRATION_STEPS,edit,1350631552

[CLS:MigrateAtomDialog]
Type=0
HeaderFile=MigrateAtomDialog.h
ImplementationFile=MigrateAtomDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=ID_3DVIEW

[DLG:IDD_MIGRATION_RESULTS_DIALOG]
Type=1
Class=MigrationResultsDialog
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_NUMBER_OF_MIGRATION_STEPS_EDIT,edit,1350633600
Control5=IDC_ENERGY_OF_MIGRATION_EDIT,edit,1350633600
Control6=IDC_STATIC,button,1342177287
Control7=IDC_MIGRATION_STEPS_LIST,SysListView32,1350631429

[CLS:MigrationResultsDialog]
Type=0
HeaderFile=MigrationResultsDialog.h
ImplementationFile=MigrationResultsDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=ID_3DVIEW

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1350565891
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_ATOM_DIALOG (English (U.S.))]
Type=1
Class=AtomDialog
ControlCount=20
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT_POSITION_X,edit,1350631552
Control6=IDC_EDIT_FORCE_X,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_EDIT_POSITION_Y,edit,1350631552
Control10=IDC_STATIC,static,1342308352
Control11=IDC_EDIT_POSITION_Z,edit,1350631552
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_EDIT_FORCE_Y,edit,1350631552
Control15=IDC_STATIC,static,1342308352
Control16=IDC_EDIT_FORCE_Z,edit,1350631552
Control17=IDC_CHECK_MOVEABLE,button,1342242819
Control18=IDC_CHECK_VISIBLE,button,1342242819
Control19=IDC_ATOMTYPE_COMBO,combobox,1344339971
Control20=IDC_STATIC,static,1342308352

[DLG:IDD_MODELING_OPTIONS_DIALOG (English (U.S.))]
Type=1
Class=ModelingOptionsDialog
ControlCount=28
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_EDIT_MAXIMUM_NUMBER_OF_STEPS,edit,1350631552
Control13=IDC_EDIT_MAXIMUM_NUMBER_OF_DEMPHINGS,edit,1350631552
Control14=IDC_EDIT_MAXIMUM_INTERACTION_DISTANCE,edit,1350631552
Control15=IDC_EDIT_MIMIMUM_KINETIC_ENERGY,edit,1350631552
Control16=IDC_EDIT_START_TIME_DELTA,edit,1350631552
Control17=IDC_EDIT_TIME_DELTA_INCREMENT,edit,1350631552
Control18=IDC_EDIT_MAXIMUM_TIME_DELTA,edit,1350631552
Control19=IDC_EDIT_DIFFERENTIAL_STEP,edit,1350631552
Control20=IDC_CHECK_USE_EMBEDDED_ATOM_METHOD,button,1342242819
Control21=IDC_CHECK_USE_DILATATION_VOLUME_CORRECTION,button,1342242819
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_EDIT_BULK_MODULUS,edit,1350631552
Control25=IDC_STATIC,static,1342308352
Control26=IDC_EDIT_ELASTIC_CORRECTIONS_AMMOUNT,edit,1350631552
Control27=IDC_CHECK_DAMPING_ENABLED,button,1342242819
Control28=IDC_STATIC,static,1342308352

[DLG:IDD_MIGRATE_ATOM_DIALOG (English (U.S.))]
Type=1
Class=MigrateAtomDialog
ControlCount=11
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT_X,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EDIT_Y,edit,1350631552
Control8=IDC_STATIC,static,1342308352
Control9=IDC_EDIT_Z,edit,1350631552
Control10=IDC_STATIC,static,1342308352
Control11=IDC_EDIT_MIGRATION_STEPS,edit,1350631552

[DLG:IDD_MIGRATION_RESULTS_DIALOG (English (U.S.))]
Type=1
Class=MigrationResultsDialog
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_NUMBER_OF_MIGRATION_STEPS_EDIT,edit,1350633600
Control5=IDC_ENERGY_OF_MIGRATION_EDIT,edit,1350633600
Control6=IDC_STATIC,button,1342177287
Control7=IDC_MIGRATION_STEPS_LIST,SysListView32,1350631429

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_EXPORT_RESULTS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_VIEW_TOOLBAR
Command12=ID_VIEW_STATUS_BAR
Command13=ID_3DVIEW
Command14=ID_TABLEVIEW
Command15=ID_SELECT_POTENTIAL
Command16=ID_ATOM_TYPES
Command17=ID_ADD_ATOM_BUTTON
Command18=ID_DELETE_ATOM_BUTTON
Command19=ID_EDIT_BUTTON_ATOM
Command20=ID_START_RELAXATION
Command21=ID_PAUSE_RELAXATION
Command22=ID_STOP_RELAXATION
Command23=ID_CALCULATE_FORCES
Command24=ID_MODELING_OPTIONS
Command25=ID_MODELING_RESULTS
Command26=ID_APP_ABOUT
CommandCount=26

[DLG:IDD_ATOMTYPES_DIALOG (English (U.S.))]
Type=1
Class=AtomTypesDialog
ControlCount=11
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST1,listbox,1352728833
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT1,edit,1350631552
Control7=IDC_EDIT2,edit,1484849280
Control8=IDC_ADD_ATOM_TYPE_BUTTON,button,1342242816
Control9=IDC_ATOMTYPE_COLOR_STATIC,static,1342308352
Control10=IDC_CHANGE_ATOM_TYPE_COLOR_BUTTON,button,1342242816
Control11=IDC_EMBEDDING_ENERGY_BUTTON,button,1342242816

[DLG:IDD_POTENTIAL_DIALOG (English (U.S.))]
Type=1
Class=PotentialDialog
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_POTENTIAL_LIST,SysListView32,1350631437
Control4=IDC_LOAD_POTENTIAL_BUTTON,button,1342242816
Control5=IDC_LOAD_ELECTRONIC_DISTRIBUTION_BUTTON,button,1342242816

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_APP_ABOUT
Command6=ID_REFRESH
Command7=ID_TABLEVIEW
Command8=ID_3DVIEW
Command9=ID_START_RELAXATION
Command10=ID_PAUSE_RELAXATION
Command11=ID_STOP_RELAXATION
Command12=ID_ADD_ATOM_BUTTON
Command13=ID_DELETE_ATOM_BUTTON
Command14=ID_EDIT_BUTTON_ATOM
Command15=ID_MIGRATE_ATOM_BUTTON
CommandCount=15

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_NEW_LATTICE_DIALOG (English (U.K.))]
Type=1
Class=CNewLatticeDialog
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_RADIO_BCC,button,1342177289
Control4=IDC_RADIO_FCC,button,1342177289
Control5=IDC_EDIT_MOVEABLE_RADIUS,edit,1350639744
Control6=IDC_EDIT_TOTAL_RADIUS,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352

[CLS:CNewLatticeDialog]
Type=0
HeaderFile=NewLatticeDialog.h
ImplementationFile=NewLatticeDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT_MOVEABLE_RADIUS
VirtualFilter=dWC

[DLG:IDD_NEW_LATTICE_DIALOG]
Type=1
Class=CNewLatticeDialog
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_RADIO_BCC,button,1342177289
Control4=IDC_RADIO_FCC,button,1342177289
Control5=IDC_EDIT_MOVEABLE_RADIUS,edit,1350639744
Control6=IDC_EDIT_TOTAL_RADIUS,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352

