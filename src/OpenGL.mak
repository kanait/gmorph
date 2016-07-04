# Microsoft Developer Studio Generated NMAKE File, Based on OpenGL.dsp
!IF "$(CFG)" == ""
CFG=OpenGL - Win32 Debug
!MESSAGE 構成が指定されていません。ﾃﾞﾌｫﾙﾄの OpenGL - Win32 Debug を設定します。
!ENDIF 

!IF "$(CFG)" != "OpenGL - Win32 Release" && "$(CFG)" != "OpenGL - Win32 Debug"
!MESSAGE 指定された ﾋﾞﾙﾄﾞ ﾓｰﾄﾞ "$(CFG)" は正しくありません。
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "OpenGL.mak" CFG="OpenGL - Win32 Debug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "OpenGL - Win32 Release" ("Win32 (x86) Application" 用)
!MESSAGE "OpenGL - Win32 Debug" ("Win32 (x86) Application" 用)
!MESSAGE 
!ERROR 無効な構成が指定されています。
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "OpenGL - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\OpenGL.exe" "$(OUTDIR)\OpenGL.bsc"


CLEAN :
	-@erase "$(INTDIR)\CMDialog.obj"
	-@erase "$(INTDIR)\CMDialog.sbr"
	-@erase "$(INTDIR)\correspond.obj"
	-@erase "$(INTDIR)\correspond.sbr"
	-@erase "$(INTDIR)\CVDialog.obj"
	-@erase "$(INTDIR)\CVDialog.sbr"
	-@erase "$(INTDIR)\DCMDialog.obj"
	-@erase "$(INTDIR)\DCMDialog.sbr"
	-@erase "$(INTDIR)\dialog.obj"
	-@erase "$(INTDIR)\dialog.sbr"
	-@erase "$(INTDIR)\DistView.obj"
	-@erase "$(INTDIR)\DistView.sbr"
	-@erase "$(INTDIR)\DPFDialog.obj"
	-@erase "$(INTDIR)\DPFDialog.sbr"
	-@erase "$(INTDIR)\DPLDialog.obj"
	-@erase "$(INTDIR)\DPLDialog.sbr"
	-@erase "$(INTDIR)\draw.obj"
	-@erase "$(INTDIR)\draw.sbr"
	-@erase "$(INTDIR)\DSPDialog.obj"
	-@erase "$(INTDIR)\DSPDialog.sbr"
	-@erase "$(INTDIR)\dspr.obj"
	-@erase "$(INTDIR)\dspr.sbr"
	-@erase "$(INTDIR)\edit.obj"
	-@erase "$(INTDIR)\edit.sbr"
	-@erase "$(INTDIR)\file.obj"
	-@erase "$(INTDIR)\file.sbr"
	-@erase "$(INTDIR)\glppd.obj"
	-@erase "$(INTDIR)\glppd.sbr"
	-@erase "$(INTDIR)\gmorph.obj"
	-@erase "$(INTDIR)\gmorph.sbr"
	-@erase "$(INTDIR)\grouping.obj"
	-@erase "$(INTDIR)\grouping.sbr"
	-@erase "$(INTDIR)\harmonic.obj"
	-@erase "$(INTDIR)\harmonic.sbr"
	-@erase "$(INTDIR)\hged.obj"
	-@erase "$(INTDIR)\hged.sbr"
	-@erase "$(INTDIR)\hgppd.obj"
	-@erase "$(INTDIR)\hgppd.sbr"
	-@erase "$(INTDIR)\hppd.obj"
	-@erase "$(INTDIR)\hppd.sbr"
	-@erase "$(INTDIR)\linbcg.obj"
	-@erase "$(INTDIR)\linbcg.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\Material.obj"
	-@erase "$(INTDIR)\Material.sbr"
	-@erase "$(INTDIR)\matlib.obj"
	-@erase "$(INTDIR)\matlib.sbr"
	-@erase "$(INTDIR)\morphvec.obj"
	-@erase "$(INTDIR)\morphvec.sbr"
	-@erase "$(INTDIR)\MSPDialog.obj"
	-@erase "$(INTDIR)\MSPDialog.sbr"
	-@erase "$(INTDIR)\OpenGL.obj"
	-@erase "$(INTDIR)\OpenGL.pch"
	-@erase "$(INTDIR)\OpenGL.res"
	-@erase "$(INTDIR)\OpenGL.sbr"
	-@erase "$(INTDIR)\OpenGLDoc.obj"
	-@erase "$(INTDIR)\OpenGLDoc.sbr"
	-@erase "$(INTDIR)\OpenGLView.obj"
	-@erase "$(INTDIR)\OpenGLView.sbr"
	-@erase "$(INTDIR)\oppd.obj"
	-@erase "$(INTDIR)\oppd.sbr"
	-@erase "$(INTDIR)\PFDialog.obj"
	-@erase "$(INTDIR)\PFDialog.sbr"
	-@erase "$(INTDIR)\pick.obj"
	-@erase "$(INTDIR)\pick.sbr"
	-@erase "$(INTDIR)\PLDialog.obj"
	-@erase "$(INTDIR)\PLDialog.sbr"
	-@erase "$(INTDIR)\pov.obj"
	-@erase "$(INTDIR)\pov.sbr"
	-@erase "$(INTDIR)\ppd.obj"
	-@erase "$(INTDIR)\ppd.sbr"
	-@erase "$(INTDIR)\ppdedge.obj"
	-@erase "$(INTDIR)\ppdedge.sbr"
	-@erase "$(INTDIR)\ppdface.obj"
	-@erase "$(INTDIR)\ppdface.sbr"
	-@erase "$(INTDIR)\ppdlist.obj"
	-@erase "$(INTDIR)\ppdlist.sbr"
	-@erase "$(INTDIR)\ppdloop.obj"
	-@erase "$(INTDIR)\ppdloop.sbr"
	-@erase "$(INTDIR)\ppdnormal.obj"
	-@erase "$(INTDIR)\ppdnormal.sbr"
	-@erase "$(INTDIR)\ppdpart.obj"
	-@erase "$(INTDIR)\ppdpart.sbr"
	-@erase "$(INTDIR)\ppdsolid.obj"
	-@erase "$(INTDIR)\ppdsolid.sbr"
	-@erase "$(INTDIR)\ppdvertex.obj"
	-@erase "$(INTDIR)\ppdvertex.sbr"
	-@erase "$(INTDIR)\ps.obj"
	-@erase "$(INTDIR)\ps.sbr"
	-@erase "$(INTDIR)\quadtree.obj"
	-@erase "$(INTDIR)\quadtree.sbr"
	-@erase "$(INTDIR)\QuitDialog.obj"
	-@erase "$(INTDIR)\QuitDialog.sbr"
	-@erase "$(INTDIR)\screen.obj"
	-@erase "$(INTDIR)\screen.sbr"
	-@erase "$(INTDIR)\sellist.obj"
	-@erase "$(INTDIR)\sellist.sbr"
	-@erase "$(INTDIR)\SFIDialog.obj"
	-@erase "$(INTDIR)\SFIDialog.sbr"
	-@erase "$(INTDIR)\sgpaths.obj"
	-@erase "$(INTDIR)\sgpaths.sbr"
	-@erase "$(INTDIR)\sgprique.obj"
	-@erase "$(INTDIR)\sgprique.sbr"
	-@erase "$(INTDIR)\sgraph.obj"
	-@erase "$(INTDIR)\sgraph.sbr"
	-@erase "$(INTDIR)\sigproc.obj"
	-@erase "$(INTDIR)\sigproc.sbr"
	-@erase "$(INTDIR)\SIPDialog.obj"
	-@erase "$(INTDIR)\SIPDialog.sbr"
	-@erase "$(INTDIR)\smd.obj"
	-@erase "$(INTDIR)\smd.sbr"
	-@erase "$(INTDIR)\SPDialog.obj"
	-@erase "$(INTDIR)\SPDialog.sbr"
	-@erase "$(INTDIR)\SRDialog.obj"
	-@erase "$(INTDIR)\SRDialog.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\trisquare.obj"
	-@erase "$(INTDIR)\trisquare.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\veclib.obj"
	-@erase "$(INTDIR)\veclib.sbr"
	-@erase "$(OUTDIR)\OpenGL.bsc"
	-@erase "$(OUTDIR)\OpenGL.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\OpenGL.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
RSC=rc.exe
RSC_PROJ=/l 0x411 /fo"$(INTDIR)\OpenGL.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\OpenGL.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\CMDialog.sbr" \
	"$(INTDIR)\correspond.sbr" \
	"$(INTDIR)\CVDialog.sbr" \
	"$(INTDIR)\DCMDialog.sbr" \
	"$(INTDIR)\dialog.sbr" \
	"$(INTDIR)\DistView.sbr" \
	"$(INTDIR)\DPFDialog.sbr" \
	"$(INTDIR)\DPLDialog.sbr" \
	"$(INTDIR)\draw.sbr" \
	"$(INTDIR)\DSPDialog.sbr" \
	"$(INTDIR)\dspr.sbr" \
	"$(INTDIR)\edit.sbr" \
	"$(INTDIR)\file.sbr" \
	"$(INTDIR)\glppd.sbr" \
	"$(INTDIR)\gmorph.sbr" \
	"$(INTDIR)\grouping.sbr" \
	"$(INTDIR)\harmonic.sbr" \
	"$(INTDIR)\hged.sbr" \
	"$(INTDIR)\hgppd.sbr" \
	"$(INTDIR)\hppd.sbr" \
	"$(INTDIR)\linbcg.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\Material.sbr" \
	"$(INTDIR)\matlib.sbr" \
	"$(INTDIR)\morphvec.sbr" \
	"$(INTDIR)\MSPDialog.sbr" \
	"$(INTDIR)\OpenGL.sbr" \
	"$(INTDIR)\OpenGLDoc.sbr" \
	"$(INTDIR)\OpenGLView.sbr" \
	"$(INTDIR)\oppd.sbr" \
	"$(INTDIR)\PFDialog.sbr" \
	"$(INTDIR)\pick.sbr" \
	"$(INTDIR)\PLDialog.sbr" \
	"$(INTDIR)\pov.sbr" \
	"$(INTDIR)\ppd.sbr" \
	"$(INTDIR)\ppdedge.sbr" \
	"$(INTDIR)\ppdface.sbr" \
	"$(INTDIR)\ppdlist.sbr" \
	"$(INTDIR)\ppdloop.sbr" \
	"$(INTDIR)\ppdnormal.sbr" \
	"$(INTDIR)\ppdpart.sbr" \
	"$(INTDIR)\ppdsolid.sbr" \
	"$(INTDIR)\ppdvertex.sbr" \
	"$(INTDIR)\ps.sbr" \
	"$(INTDIR)\quadtree.sbr" \
	"$(INTDIR)\QuitDialog.sbr" \
	"$(INTDIR)\screen.sbr" \
	"$(INTDIR)\sellist.sbr" \
	"$(INTDIR)\SFIDialog.sbr" \
	"$(INTDIR)\sgpaths.sbr" \
	"$(INTDIR)\sgprique.sbr" \
	"$(INTDIR)\sgraph.sbr" \
	"$(INTDIR)\sigproc.sbr" \
	"$(INTDIR)\SIPDialog.sbr" \
	"$(INTDIR)\smd.sbr" \
	"$(INTDIR)\SPDialog.sbr" \
	"$(INTDIR)\SRDialog.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\trisquare.sbr" \
	"$(INTDIR)\veclib.sbr"

"$(OUTDIR)\OpenGL.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=opengl32.lib glu32.lib glaux.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\OpenGL.pdb" /machine:I386 /out:"$(OUTDIR)\OpenGL.exe" 
LINK32_OBJS= \
	"$(INTDIR)\CMDialog.obj" \
	"$(INTDIR)\correspond.obj" \
	"$(INTDIR)\CVDialog.obj" \
	"$(INTDIR)\DCMDialog.obj" \
	"$(INTDIR)\dialog.obj" \
	"$(INTDIR)\DistView.obj" \
	"$(INTDIR)\DPFDialog.obj" \
	"$(INTDIR)\DPLDialog.obj" \
	"$(INTDIR)\draw.obj" \
	"$(INTDIR)\DSPDialog.obj" \
	"$(INTDIR)\dspr.obj" \
	"$(INTDIR)\edit.obj" \
	"$(INTDIR)\file.obj" \
	"$(INTDIR)\glppd.obj" \
	"$(INTDIR)\gmorph.obj" \
	"$(INTDIR)\grouping.obj" \
	"$(INTDIR)\harmonic.obj" \
	"$(INTDIR)\hged.obj" \
	"$(INTDIR)\hgppd.obj" \
	"$(INTDIR)\hppd.obj" \
	"$(INTDIR)\linbcg.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\Material.obj" \
	"$(INTDIR)\matlib.obj" \
	"$(INTDIR)\morphvec.obj" \
	"$(INTDIR)\MSPDialog.obj" \
	"$(INTDIR)\OpenGL.obj" \
	"$(INTDIR)\OpenGLDoc.obj" \
	"$(INTDIR)\OpenGLView.obj" \
	"$(INTDIR)\oppd.obj" \
	"$(INTDIR)\PFDialog.obj" \
	"$(INTDIR)\pick.obj" \
	"$(INTDIR)\PLDialog.obj" \
	"$(INTDIR)\pov.obj" \
	"$(INTDIR)\ppd.obj" \
	"$(INTDIR)\ppdedge.obj" \
	"$(INTDIR)\ppdface.obj" \
	"$(INTDIR)\ppdlist.obj" \
	"$(INTDIR)\ppdloop.obj" \
	"$(INTDIR)\ppdnormal.obj" \
	"$(INTDIR)\ppdpart.obj" \
	"$(INTDIR)\ppdsolid.obj" \
	"$(INTDIR)\ppdvertex.obj" \
	"$(INTDIR)\ps.obj" \
	"$(INTDIR)\quadtree.obj" \
	"$(INTDIR)\QuitDialog.obj" \
	"$(INTDIR)\screen.obj" \
	"$(INTDIR)\sellist.obj" \
	"$(INTDIR)\SFIDialog.obj" \
	"$(INTDIR)\sgpaths.obj" \
	"$(INTDIR)\sgprique.obj" \
	"$(INTDIR)\sgraph.obj" \
	"$(INTDIR)\sigproc.obj" \
	"$(INTDIR)\SIPDialog.obj" \
	"$(INTDIR)\smd.obj" \
	"$(INTDIR)\SPDialog.obj" \
	"$(INTDIR)\SRDialog.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\trisquare.obj" \
	"$(INTDIR)\veclib.obj" \
	"$(INTDIR)\OpenGL.res"

"$(OUTDIR)\OpenGL.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "OpenGL - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\OpenGL.exe" "$(OUTDIR)\OpenGL.bsc"


CLEAN :
	-@erase "$(INTDIR)\CMDialog.obj"
	-@erase "$(INTDIR)\CMDialog.sbr"
	-@erase "$(INTDIR)\correspond.obj"
	-@erase "$(INTDIR)\correspond.sbr"
	-@erase "$(INTDIR)\CVDialog.obj"
	-@erase "$(INTDIR)\CVDialog.sbr"
	-@erase "$(INTDIR)\DCMDialog.obj"
	-@erase "$(INTDIR)\DCMDialog.sbr"
	-@erase "$(INTDIR)\dialog.obj"
	-@erase "$(INTDIR)\dialog.sbr"
	-@erase "$(INTDIR)\DistView.obj"
	-@erase "$(INTDIR)\DistView.sbr"
	-@erase "$(INTDIR)\DPFDialog.obj"
	-@erase "$(INTDIR)\DPFDialog.sbr"
	-@erase "$(INTDIR)\DPLDialog.obj"
	-@erase "$(INTDIR)\DPLDialog.sbr"
	-@erase "$(INTDIR)\draw.obj"
	-@erase "$(INTDIR)\draw.sbr"
	-@erase "$(INTDIR)\DSPDialog.obj"
	-@erase "$(INTDIR)\DSPDialog.sbr"
	-@erase "$(INTDIR)\dspr.obj"
	-@erase "$(INTDIR)\dspr.sbr"
	-@erase "$(INTDIR)\edit.obj"
	-@erase "$(INTDIR)\edit.sbr"
	-@erase "$(INTDIR)\file.obj"
	-@erase "$(INTDIR)\file.sbr"
	-@erase "$(INTDIR)\glppd.obj"
	-@erase "$(INTDIR)\glppd.sbr"
	-@erase "$(INTDIR)\gmorph.obj"
	-@erase "$(INTDIR)\gmorph.sbr"
	-@erase "$(INTDIR)\grouping.obj"
	-@erase "$(INTDIR)\grouping.sbr"
	-@erase "$(INTDIR)\harmonic.obj"
	-@erase "$(INTDIR)\harmonic.sbr"
	-@erase "$(INTDIR)\hged.obj"
	-@erase "$(INTDIR)\hged.sbr"
	-@erase "$(INTDIR)\hgppd.obj"
	-@erase "$(INTDIR)\hgppd.sbr"
	-@erase "$(INTDIR)\hppd.obj"
	-@erase "$(INTDIR)\hppd.sbr"
	-@erase "$(INTDIR)\linbcg.obj"
	-@erase "$(INTDIR)\linbcg.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\Material.obj"
	-@erase "$(INTDIR)\Material.sbr"
	-@erase "$(INTDIR)\matlib.obj"
	-@erase "$(INTDIR)\matlib.sbr"
	-@erase "$(INTDIR)\morphvec.obj"
	-@erase "$(INTDIR)\morphvec.sbr"
	-@erase "$(INTDIR)\MSPDialog.obj"
	-@erase "$(INTDIR)\MSPDialog.sbr"
	-@erase "$(INTDIR)\OpenGL.obj"
	-@erase "$(INTDIR)\OpenGL.pch"
	-@erase "$(INTDIR)\OpenGL.res"
	-@erase "$(INTDIR)\OpenGL.sbr"
	-@erase "$(INTDIR)\OpenGLDoc.obj"
	-@erase "$(INTDIR)\OpenGLDoc.sbr"
	-@erase "$(INTDIR)\OpenGLView.obj"
	-@erase "$(INTDIR)\OpenGLView.sbr"
	-@erase "$(INTDIR)\oppd.obj"
	-@erase "$(INTDIR)\oppd.sbr"
	-@erase "$(INTDIR)\PFDialog.obj"
	-@erase "$(INTDIR)\PFDialog.sbr"
	-@erase "$(INTDIR)\pick.obj"
	-@erase "$(INTDIR)\pick.sbr"
	-@erase "$(INTDIR)\PLDialog.obj"
	-@erase "$(INTDIR)\PLDialog.sbr"
	-@erase "$(INTDIR)\pov.obj"
	-@erase "$(INTDIR)\pov.sbr"
	-@erase "$(INTDIR)\ppd.obj"
	-@erase "$(INTDIR)\ppd.sbr"
	-@erase "$(INTDIR)\ppdedge.obj"
	-@erase "$(INTDIR)\ppdedge.sbr"
	-@erase "$(INTDIR)\ppdface.obj"
	-@erase "$(INTDIR)\ppdface.sbr"
	-@erase "$(INTDIR)\ppdlist.obj"
	-@erase "$(INTDIR)\ppdlist.sbr"
	-@erase "$(INTDIR)\ppdloop.obj"
	-@erase "$(INTDIR)\ppdloop.sbr"
	-@erase "$(INTDIR)\ppdnormal.obj"
	-@erase "$(INTDIR)\ppdnormal.sbr"
	-@erase "$(INTDIR)\ppdpart.obj"
	-@erase "$(INTDIR)\ppdpart.sbr"
	-@erase "$(INTDIR)\ppdsolid.obj"
	-@erase "$(INTDIR)\ppdsolid.sbr"
	-@erase "$(INTDIR)\ppdvertex.obj"
	-@erase "$(INTDIR)\ppdvertex.sbr"
	-@erase "$(INTDIR)\ps.obj"
	-@erase "$(INTDIR)\ps.sbr"
	-@erase "$(INTDIR)\quadtree.obj"
	-@erase "$(INTDIR)\quadtree.sbr"
	-@erase "$(INTDIR)\QuitDialog.obj"
	-@erase "$(INTDIR)\QuitDialog.sbr"
	-@erase "$(INTDIR)\screen.obj"
	-@erase "$(INTDIR)\screen.sbr"
	-@erase "$(INTDIR)\sellist.obj"
	-@erase "$(INTDIR)\sellist.sbr"
	-@erase "$(INTDIR)\SFIDialog.obj"
	-@erase "$(INTDIR)\SFIDialog.sbr"
	-@erase "$(INTDIR)\sgpaths.obj"
	-@erase "$(INTDIR)\sgpaths.sbr"
	-@erase "$(INTDIR)\sgprique.obj"
	-@erase "$(INTDIR)\sgprique.sbr"
	-@erase "$(INTDIR)\sgraph.obj"
	-@erase "$(INTDIR)\sgraph.sbr"
	-@erase "$(INTDIR)\sigproc.obj"
	-@erase "$(INTDIR)\sigproc.sbr"
	-@erase "$(INTDIR)\SIPDialog.obj"
	-@erase "$(INTDIR)\SIPDialog.sbr"
	-@erase "$(INTDIR)\smd.obj"
	-@erase "$(INTDIR)\smd.sbr"
	-@erase "$(INTDIR)\SPDialog.obj"
	-@erase "$(INTDIR)\SPDialog.sbr"
	-@erase "$(INTDIR)\SRDialog.obj"
	-@erase "$(INTDIR)\SRDialog.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\trisquare.obj"
	-@erase "$(INTDIR)\trisquare.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\veclib.obj"
	-@erase "$(INTDIR)\veclib.sbr"
	-@erase "$(OUTDIR)\OpenGL.bsc"
	-@erase "$(OUTDIR)\OpenGL.exe"
	-@erase "$(OUTDIR)\OpenGL.ilk"
	-@erase "$(OUTDIR)\OpenGL.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\OpenGL.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
RSC=rc.exe
RSC_PROJ=/l 0x411 /fo"$(INTDIR)\OpenGL.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\OpenGL.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\CMDialog.sbr" \
	"$(INTDIR)\correspond.sbr" \
	"$(INTDIR)\CVDialog.sbr" \
	"$(INTDIR)\DCMDialog.sbr" \
	"$(INTDIR)\dialog.sbr" \
	"$(INTDIR)\DistView.sbr" \
	"$(INTDIR)\DPFDialog.sbr" \
	"$(INTDIR)\DPLDialog.sbr" \
	"$(INTDIR)\draw.sbr" \
	"$(INTDIR)\DSPDialog.sbr" \
	"$(INTDIR)\dspr.sbr" \
	"$(INTDIR)\edit.sbr" \
	"$(INTDIR)\file.sbr" \
	"$(INTDIR)\glppd.sbr" \
	"$(INTDIR)\gmorph.sbr" \
	"$(INTDIR)\grouping.sbr" \
	"$(INTDIR)\harmonic.sbr" \
	"$(INTDIR)\hged.sbr" \
	"$(INTDIR)\hgppd.sbr" \
	"$(INTDIR)\hppd.sbr" \
	"$(INTDIR)\linbcg.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\Material.sbr" \
	"$(INTDIR)\matlib.sbr" \
	"$(INTDIR)\morphvec.sbr" \
	"$(INTDIR)\MSPDialog.sbr" \
	"$(INTDIR)\OpenGL.sbr" \
	"$(INTDIR)\OpenGLDoc.sbr" \
	"$(INTDIR)\OpenGLView.sbr" \
	"$(INTDIR)\oppd.sbr" \
	"$(INTDIR)\PFDialog.sbr" \
	"$(INTDIR)\pick.sbr" \
	"$(INTDIR)\PLDialog.sbr" \
	"$(INTDIR)\pov.sbr" \
	"$(INTDIR)\ppd.sbr" \
	"$(INTDIR)\ppdedge.sbr" \
	"$(INTDIR)\ppdface.sbr" \
	"$(INTDIR)\ppdlist.sbr" \
	"$(INTDIR)\ppdloop.sbr" \
	"$(INTDIR)\ppdnormal.sbr" \
	"$(INTDIR)\ppdpart.sbr" \
	"$(INTDIR)\ppdsolid.sbr" \
	"$(INTDIR)\ppdvertex.sbr" \
	"$(INTDIR)\ps.sbr" \
	"$(INTDIR)\quadtree.sbr" \
	"$(INTDIR)\QuitDialog.sbr" \
	"$(INTDIR)\screen.sbr" \
	"$(INTDIR)\sellist.sbr" \
	"$(INTDIR)\SFIDialog.sbr" \
	"$(INTDIR)\sgpaths.sbr" \
	"$(INTDIR)\sgprique.sbr" \
	"$(INTDIR)\sgraph.sbr" \
	"$(INTDIR)\sigproc.sbr" \
	"$(INTDIR)\SIPDialog.sbr" \
	"$(INTDIR)\smd.sbr" \
	"$(INTDIR)\SPDialog.sbr" \
	"$(INTDIR)\SRDialog.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\trisquare.sbr" \
	"$(INTDIR)\veclib.sbr"

"$(OUTDIR)\OpenGL.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=opengl32.lib glu32.lib glaux.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\OpenGL.pdb" /debug /machine:I386 /out:"$(OUTDIR)\OpenGL.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\CMDialog.obj" \
	"$(INTDIR)\correspond.obj" \
	"$(INTDIR)\CVDialog.obj" \
	"$(INTDIR)\DCMDialog.obj" \
	"$(INTDIR)\dialog.obj" \
	"$(INTDIR)\DistView.obj" \
	"$(INTDIR)\DPFDialog.obj" \
	"$(INTDIR)\DPLDialog.obj" \
	"$(INTDIR)\draw.obj" \
	"$(INTDIR)\DSPDialog.obj" \
	"$(INTDIR)\dspr.obj" \
	"$(INTDIR)\edit.obj" \
	"$(INTDIR)\file.obj" \
	"$(INTDIR)\glppd.obj" \
	"$(INTDIR)\gmorph.obj" \
	"$(INTDIR)\grouping.obj" \
	"$(INTDIR)\harmonic.obj" \
	"$(INTDIR)\hged.obj" \
	"$(INTDIR)\hgppd.obj" \
	"$(INTDIR)\hppd.obj" \
	"$(INTDIR)\linbcg.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\Material.obj" \
	"$(INTDIR)\matlib.obj" \
	"$(INTDIR)\morphvec.obj" \
	"$(INTDIR)\MSPDialog.obj" \
	"$(INTDIR)\OpenGL.obj" \
	"$(INTDIR)\OpenGLDoc.obj" \
	"$(INTDIR)\OpenGLView.obj" \
	"$(INTDIR)\oppd.obj" \
	"$(INTDIR)\PFDialog.obj" \
	"$(INTDIR)\pick.obj" \
	"$(INTDIR)\PLDialog.obj" \
	"$(INTDIR)\pov.obj" \
	"$(INTDIR)\ppd.obj" \
	"$(INTDIR)\ppdedge.obj" \
	"$(INTDIR)\ppdface.obj" \
	"$(INTDIR)\ppdlist.obj" \
	"$(INTDIR)\ppdloop.obj" \
	"$(INTDIR)\ppdnormal.obj" \
	"$(INTDIR)\ppdpart.obj" \
	"$(INTDIR)\ppdsolid.obj" \
	"$(INTDIR)\ppdvertex.obj" \
	"$(INTDIR)\ps.obj" \
	"$(INTDIR)\quadtree.obj" \
	"$(INTDIR)\QuitDialog.obj" \
	"$(INTDIR)\screen.obj" \
	"$(INTDIR)\sellist.obj" \
	"$(INTDIR)\SFIDialog.obj" \
	"$(INTDIR)\sgpaths.obj" \
	"$(INTDIR)\sgprique.obj" \
	"$(INTDIR)\sgraph.obj" \
	"$(INTDIR)\sigproc.obj" \
	"$(INTDIR)\SIPDialog.obj" \
	"$(INTDIR)\smd.obj" \
	"$(INTDIR)\SPDialog.obj" \
	"$(INTDIR)\SRDialog.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\trisquare.obj" \
	"$(INTDIR)\veclib.obj" \
	"$(INTDIR)\OpenGL.res"

"$(OUTDIR)\OpenGL.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("OpenGL.dep")
!INCLUDE "OpenGL.dep"
!ELSE 
!MESSAGE Warning: cannot find "OpenGL.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "OpenGL - Win32 Release" || "$(CFG)" == "OpenGL - Win32 Debug"
SOURCE=.\CMDialog.cpp

"$(INTDIR)\CMDialog.obj"	"$(INTDIR)\CMDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\correspond.cpp

"$(INTDIR)\correspond.obj"	"$(INTDIR)\correspond.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\CVDialog.cpp

"$(INTDIR)\CVDialog.obj"	"$(INTDIR)\CVDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\DCMDialog.cpp

"$(INTDIR)\DCMDialog.obj"	"$(INTDIR)\DCMDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\dialog.cpp

"$(INTDIR)\dialog.obj"	"$(INTDIR)\dialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\DistView.cpp

"$(INTDIR)\DistView.obj"	"$(INTDIR)\DistView.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\DPFDialog.cpp

"$(INTDIR)\DPFDialog.obj"	"$(INTDIR)\DPFDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\DPLDialog.cpp

"$(INTDIR)\DPLDialog.obj"	"$(INTDIR)\DPLDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\draw.cpp

"$(INTDIR)\draw.obj"	"$(INTDIR)\draw.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\DSPDialog.cpp

"$(INTDIR)\DSPDialog.obj"	"$(INTDIR)\DSPDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\dspr.cpp

"$(INTDIR)\dspr.obj"	"$(INTDIR)\dspr.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\edit.cpp

"$(INTDIR)\edit.obj"	"$(INTDIR)\edit.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\file.cpp

"$(INTDIR)\file.obj"	"$(INTDIR)\file.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\glppd.cpp

"$(INTDIR)\glppd.obj"	"$(INTDIR)\glppd.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\gmorph.cpp

"$(INTDIR)\gmorph.obj"	"$(INTDIR)\gmorph.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\grouping.cpp

"$(INTDIR)\grouping.obj"	"$(INTDIR)\grouping.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\harmonic.cpp

"$(INTDIR)\harmonic.obj"	"$(INTDIR)\harmonic.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\hged.cpp

"$(INTDIR)\hged.obj"	"$(INTDIR)\hged.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\hgppd.cpp

"$(INTDIR)\hgppd.obj"	"$(INTDIR)\hgppd.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\hppd.cpp

"$(INTDIR)\hppd.obj"	"$(INTDIR)\hppd.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\linbcg.cpp

"$(INTDIR)\linbcg.obj"	"$(INTDIR)\linbcg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\MainFrm.cpp

"$(INTDIR)\MainFrm.obj"	"$(INTDIR)\MainFrm.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\Material.cpp

"$(INTDIR)\Material.obj"	"$(INTDIR)\Material.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\matlib.cpp

"$(INTDIR)\matlib.obj"	"$(INTDIR)\matlib.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\morphvec.cpp

"$(INTDIR)\morphvec.obj"	"$(INTDIR)\morphvec.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\MSPDialog.cpp

"$(INTDIR)\MSPDialog.obj"	"$(INTDIR)\MSPDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\OpenGL.cpp

"$(INTDIR)\OpenGL.obj"	"$(INTDIR)\OpenGL.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\OpenGL.rc

"$(INTDIR)\OpenGL.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\OpenGLDoc.cpp

"$(INTDIR)\OpenGLDoc.obj"	"$(INTDIR)\OpenGLDoc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\OpenGLView.cpp

"$(INTDIR)\OpenGLView.obj"	"$(INTDIR)\OpenGLView.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\oppd.cpp

"$(INTDIR)\oppd.obj"	"$(INTDIR)\oppd.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\PFDialog.cpp

"$(INTDIR)\PFDialog.obj"	"$(INTDIR)\PFDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\pick.cpp

"$(INTDIR)\pick.obj"	"$(INTDIR)\pick.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\PLDialog.cpp

"$(INTDIR)\PLDialog.obj"	"$(INTDIR)\PLDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\pov.cpp

"$(INTDIR)\pov.obj"	"$(INTDIR)\pov.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\ppd.cpp

"$(INTDIR)\ppd.obj"	"$(INTDIR)\ppd.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\ppdedge.cpp

"$(INTDIR)\ppdedge.obj"	"$(INTDIR)\ppdedge.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\ppdface.cpp

"$(INTDIR)\ppdface.obj"	"$(INTDIR)\ppdface.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\ppdlist.cpp

"$(INTDIR)\ppdlist.obj"	"$(INTDIR)\ppdlist.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\ppdloop.cpp

"$(INTDIR)\ppdloop.obj"	"$(INTDIR)\ppdloop.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\ppdnormal.cpp

"$(INTDIR)\ppdnormal.obj"	"$(INTDIR)\ppdnormal.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\ppdpart.cpp

"$(INTDIR)\ppdpart.obj"	"$(INTDIR)\ppdpart.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\ppdsolid.cpp

"$(INTDIR)\ppdsolid.obj"	"$(INTDIR)\ppdsolid.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\ppdvertex.cpp

"$(INTDIR)\ppdvertex.obj"	"$(INTDIR)\ppdvertex.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\ps.cpp

"$(INTDIR)\ps.obj"	"$(INTDIR)\ps.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\quadtree.cpp

"$(INTDIR)\quadtree.obj"	"$(INTDIR)\quadtree.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\QuitDialog.cpp

"$(INTDIR)\QuitDialog.obj"	"$(INTDIR)\QuitDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\screen.cpp

"$(INTDIR)\screen.obj"	"$(INTDIR)\screen.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\sellist.cpp

"$(INTDIR)\sellist.obj"	"$(INTDIR)\sellist.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\SFIDialog.cpp

"$(INTDIR)\SFIDialog.obj"	"$(INTDIR)\SFIDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\sgpaths.cpp

"$(INTDIR)\sgpaths.obj"	"$(INTDIR)\sgpaths.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\sgprique.cpp

"$(INTDIR)\sgprique.obj"	"$(INTDIR)\sgprique.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\sgraph.cpp

"$(INTDIR)\sgraph.obj"	"$(INTDIR)\sgraph.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\sigproc.cpp

"$(INTDIR)\sigproc.obj"	"$(INTDIR)\sigproc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\SIPDialog.cpp

"$(INTDIR)\SIPDialog.obj"	"$(INTDIR)\SIPDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\smd.cpp

"$(INTDIR)\smd.obj"	"$(INTDIR)\smd.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\SPDialog.cpp

"$(INTDIR)\SPDialog.obj"	"$(INTDIR)\SPDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\SRDialog.cpp

"$(INTDIR)\SRDialog.obj"	"$(INTDIR)\SRDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "OpenGL - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\OpenGL.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\OpenGL.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "OpenGL - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\OpenGL.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\OpenGL.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\trisquare.cpp

"$(INTDIR)\trisquare.obj"	"$(INTDIR)\trisquare.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"


SOURCE=.\veclib.cpp

"$(INTDIR)\veclib.obj"	"$(INTDIR)\veclib.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL.pch"



!ENDIF 

