# Microsoft Developer Studio Project File - Name="VIPLib_base" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=VIPLib_base - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VIPLib_base.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VIPLib_base.mak" CFG="VIPLib_base - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VIPLib_base - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "VIPLib_base - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "VIPLib_base - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../../tmp"
# PROP Intermediate_Dir "../../tmp"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x410 /d "NDEBUG"
# ADD RSC /l 0x410 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\VIPLib_base.lib"

!ELSEIF  "$(CFG)" == "VIPLib_base - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../../tmp"
# PROP Intermediate_Dir "../../tmp"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x410 /d "_DEBUG"
# ADD RSC /l 0x410 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\VIPLib_base.lib"

!ENDIF 

# Begin Target

# Name "VIPLib_base - Win32 Release"
# Name "VIPLib_base - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "buffers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\source\buffers\vipBufferArray.h
# End Source File
# Begin Source File

SOURCE=..\..\source\buffers\vipBufferLink.h
# End Source File
# End Group
# Begin Group "codecs"

# PROP Default_Filter ""
# Begin Group "external_BMP"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\source\codecs\external_BMP\MicrosoftBMP_RT.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\codecs\external_BMP\MicrosoftMonoBMP_RT.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\codecs\external_BMP\MicrosoftRCBMP_RT.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\source\codecs\vipCodec_BMP.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\codecs\vipCodec_RAW.cpp
# End Source File
# End Group
# Begin Group "filters"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\source\filters\vipDigitalFilter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\filters\vipFilterColor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\filters\vipFilterGeometric.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\filters\vipFilterNoiseChannel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\filters\vipMultiplexer.cpp
# End Source File
# End Group
# Begin Group "inputs"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\source\inputs\vipNoiseGenerator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\inputs\vipPlainFrameGenerator.cpp
# End Source File
# End Group
# Begin Group "outputs"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\source\outputs\vipDoctor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\outputs\vipOuputVoid.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\outputs\vipWindow32.cpp
# End Source File
# End Group
# Begin Group "vision"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\source\vision\vipMotionIlluminationInvariant.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\vision\vipMotionLame.cpp
# End Source File
# End Group
# Begin Group "math"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\source\math\vipDFMatrix.h
# End Source File
# Begin Source File

SOURCE=..\..\source\math\vipMatrix.h
# End Source File
# Begin Source File

SOURCE=..\..\source\math\vipStatistics.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\math\vipStatistics.h
# End Source File
# Begin Source File

SOURCE=..\..\source\math\vipVector.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\source\vipException.h
# End Source File
# Begin Source File

SOURCE=..\..\source\vipFilter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\vipFrameGrey.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\vipFrameHSV.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\vipFrameRGB24.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\vipFrameRGB96.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\vipFrameRGBA32.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\vipFrameYUV420.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\vipHist.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\vipInput.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\vipMath.h
# End Source File
# Begin Source File

SOURCE=..\..\source\vipObject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\vipProcess.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\vipThread.h
# End Source File
# Begin Source File

SOURCE=..\..\source\vipUtility.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\vipVision.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\include\VIPLib.h
# End Source File
# End Group
# Begin Group "CCVT"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\include\ccvt\ccvt.h
# End Source File
# End Group
# End Target
# End Project
