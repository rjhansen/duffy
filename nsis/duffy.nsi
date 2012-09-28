!include "MUI2.nsh"

Name "Duffy"
OutFile "Duffy 1.0-RC2.exe"

InstallDir "$PROGRAMFILES\Duffy"
RequestExecutionLevel admin

; MUI Settings / Icons
!define MUI_ICON "${NSISDIR}\Contrib\Graphics\Icons\orange-install-nsis.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\orange-uninstall-nsis.ico"
 
 
!define MUI_COMPONENTSPAGE_SMALLDESC

; MUI Settings / Header
!define MUI_HEADERIMAGE
!define MUI_HEADERIMAGE_RIGHT
!define MUI_HEADERIMAGE_BITMAP "${NSISDIR}\Contrib\Graphics\Header\orange-r-nsis.bmp"
!define MUI_HEADERIMAGE_UNBITMAP "${NSISDIR}\Contrib\Graphics\Header\orange-uninstall-r-nsis.bmp"
 
; MUI Settings / Wizard
!define MUI_WELCOMEFINISHPAGE_BITMAP "${NSISDIR}\Contrib\Graphics\Wizard\orange-nsis.bmp"
!define MUI_UNWELCOMEFINISHPAGE_BITMAP "${NSISDIR}\Contrib\Graphics\Wizard\orange-uninstall-nsis.bmp"

!define MUI_ABORTWARNING_CANCEL_DEFAULT

!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE "License.rtf"
!insertmacro MUI_PAGE_COMPONENTS
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_UNPAGE_WELCOME
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES
!insertmacro MUI_UNPAGE_FINISH

!insertmacro MUI_LANGUAGE "English"

Section "Duffy 1.0-RC2" Duffy
	SectionIn RO
	SetOutPath "$INSTDIR"
	File "duffy.exe"
	File "QtCore4.dll"
	File "QtGui4.dll"
	File "QtNetwork4.dll"
	File "QtSvg4.dll"
	File "duffy.nsi"
	File "License.rtf"
	WriteUninstaller "$INSTDIR\Uninstall.exe"
	CreateDirectory "$SMPROGRAMS\Duffy"
	CreateShortCut "$SMPROGRAMS\Duffy\Duffy.lnk" "$INSTDIR\duffy.exe"
	CreateShortCut "$SMPROGRAMS\Duffy\Uninstall.lnk" "$INSTDIR\Uninstall.exe"
SectionEnd

Section "Microsoft Visual C++ 2010 SP1 runtime" MSVCRT
    SetOutPath "$INSTDIR"
	File "vcredist_x86.exe"
	ExecWait "$INSTDIR\vcredist_x86.exe"
	Delete "$INSTDIR\vcredist_x86.exe"
SectionEnd

Section "Uninstall"
	Delete "$INSTDIR\*.*"
	RmDir "$INSTDIR"
	Delete "$SMPROGRAMS\Duffy\Duffy.lnk"
	Delete "$SMPROGRAMS\Duffy\Uninstall.lnk"
	RmDir "$SMPROGRAMS\Duffy"
SectionEnd

LangString DescDuffy ${LANG_ENGLISH} "The core files required by Duffy."
LangString DescMSVCRT ${LANG_ENGLISH} "The Microsoft Visual C++ 2010 Runtime, Service Pack 1."
!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
!insertmacro MUI_DESCRIPTION_TEXT ${Duffy} $(DescDuffy)
!insertmacro MUI_DESCRIPTION_TEXT ${MSVCRT} $(DescMSVCRT)
!insertmacro MUI_FUNCTION_DESCRIPTION_END
