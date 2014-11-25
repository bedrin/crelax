# Microsoft Developer Studio Project File - Name="LatticeRelaxation" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=LatticeRelaxation - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "LatticeRelaxation.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "LatticeRelaxation.mak" CFG="LatticeRelaxation - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LatticeRelaxation - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "LatticeRelaxation - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "LatticeRelaxation - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "LatticeRelaxation - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "LatticeRelaxation - Win32 Release"
# Name "LatticeRelaxation - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Atom.cpp
# End Source File
# Begin Source File

SOURCE=.\AtomDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\AtomPair.cpp
# End Source File
# Begin Source File

SOURCE=.\AtomType.cpp
# End Source File
# Begin Source File

SOURCE=.\AtomTypesDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorStatic.cpp
# End Source File
# Begin Source File

SOURCE=.\Direct3DView.cpp
# End Source File
# Begin Source File

SOURCE=.\Lattice.cpp
# End Source File
# Begin Source File

SOURCE=.\LatticeBuilder.cpp
# End Source File
# Begin Source File

SOURCE=.\LatticeElement.cpp
# End Source File
# Begin Source File

SOURCE=.\LatticeRelaxation.cpp
# End Source File
# Begin Source File

SOURCE=.\LatticeRelaxation.rc
# End Source File
# Begin Source File

SOURCE=.\LatticeRelaxationD3DView.cpp
# End Source File
# Begin Source File

SOURCE=.\LatticeRelaxationDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\LatticeRelaxationTableView.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MigrateAtomDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\MigrationResults.cpp
# End Source File
# Begin Source File

SOURCE=.\MigrationResultsDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\MigrationStepResults.cpp
# End Source File
# Begin Source File

SOURCE=.\Modeling.cpp
# End Source File
# Begin Source File

SOURCE=.\ModelingOptions.cpp
# End Source File
# Begin Source File

SOURCE=.\ModelingOptionsDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ModelingProject.cpp
# End Source File
# Begin Source File

SOURCE=.\NewLatticeDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\Potential.cpp
# End Source File
# Begin Source File

SOURCE=.\PotentialBuilder.cpp
# End Source File
# Begin Source File

SOURCE=.\PotentialDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\Relaxation.cpp
# End Source File
# Begin Source File

SOURCE=.\RelaxationResults.cpp
# End Source File
# Begin Source File

SOURCE=.\RelaxCorLatticeBuilder.cpp
# End Source File
# Begin Source File

SOURCE=.\RelaxPtPotentialBuilder.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TableSetFunction.cpp
# End Source File
# Begin Source File

SOURCE=.\Vacancy.cpp
# End Source File
# Begin Source File

SOURCE=.\Vector.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Atom.h
# End Source File
# Begin Source File

SOURCE=.\AtomDialog.h
# End Source File
# Begin Source File

SOURCE=.\AtomPair.h
# End Source File
# Begin Source File

SOURCE=.\AtomType.h
# End Source File
# Begin Source File

SOURCE=.\AtomTypesDialog.h
# End Source File
# Begin Source File

SOURCE=.\ColorStatic.h
# End Source File
# Begin Source File

SOURCE=.\Direct3DView.h
# End Source File
# Begin Source File

SOURCE=.\Lattice.h
# End Source File
# Begin Source File

SOURCE=.\LatticeBuilder.h
# End Source File
# Begin Source File

SOURCE=.\LatticeElement.h
# End Source File
# Begin Source File

SOURCE=.\LatticeRelaxation.h
# End Source File
# Begin Source File

SOURCE=.\LatticeRelaxationD3DView.h
# End Source File
# Begin Source File

SOURCE=.\LatticeRelaxationDoc.h
# End Source File
# Begin Source File

SOURCE=.\LatticeRelaxationTableView.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MigrateAtomDialog.h
# End Source File
# Begin Source File

SOURCE=.\MigrationResults.h
# End Source File
# Begin Source File

SOURCE=.\MigrationResultsDialog.h
# End Source File
# Begin Source File

SOURCE=.\MigrationStepResults.h
# End Source File
# Begin Source File

SOURCE=.\Modeling.h
# End Source File
# Begin Source File

SOURCE=.\ModelingOptions.h
# End Source File
# Begin Source File

SOURCE=.\ModelingOptionsDialog.h
# End Source File
# Begin Source File

SOURCE=.\ModelingProject.h
# End Source File
# Begin Source File

SOURCE=.\NewLatticeDialog.h
# End Source File
# Begin Source File

SOURCE=.\Potential.h
# End Source File
# Begin Source File

SOURCE=.\PotentialBuilder.h
# End Source File
# Begin Source File

SOURCE=.\PotentialDialog.h
# End Source File
# Begin Source File

SOURCE=.\Relaxation.h
# End Source File
# Begin Source File

SOURCE=.\RelaxationResults.h
# End Source File
# Begin Source File

SOURCE=.\RelaxCorLatticeBuilder.h
# End Source File
# Begin Source File

SOURCE=.\RelaxPtPotentialBuilder.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TableSetFunction.h
# End Source File
# Begin Source File

SOURCE=.\Vacancy.h
# End Source File
# Begin Source File

SOURCE=.\Vector.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\LatticeRelaxation.ico
# End Source File
# Begin Source File

SOURCE=.\res\LatticeRelaxation.rc2
# End Source File
# Begin Source File

SOURCE=.\res\LatticeRelaxationDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\LatticeRelaxation.reg
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
