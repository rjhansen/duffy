!include "MUI2.nsh"

Name "Sgt. Duffy"
OutFile "Sgt. Duffy 1.0-RC1.exe"

InstallDir "$PROGRAMFILES\Sgt. Duffy"
RequestExecutionLevel admin

; MUI Settings / Icons
!define MUI_ICON "${NSISDIR}\Contrib\Graphics\Icons\orange-install-nsis.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\orange-uninstall-nsis.ico"
 
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

Section "Sgt. Duffy 1.0-RC1" 
	SectionIn RO
	SetOutPath "$INSTDIR"
	File "Sgt. Duffy.exe"
	File "QtCore4.dll"
	File "QtGui4.dll"
	File "QtNetwork4.dll"
	File "QtSvg4.dll"
	File "duffy.nsi"
	File "License.rtf"
	WriteUninstaller "$INSTDIR\Uninstall.exe"
	CreateDirectory "$SMPROGRAMS\Sgt. Duffy"
	CreateShortCut "$SMPROGRAMS\Sgt. Duffy\Sgt. Duffy.lnk" "$INSTDIR\Sgt. Duffy.exe"
	CreateShortCut "$SMPROGRAMS\Sgt. Duffy\Uninstall.lnk" "$INSTDIR\Uninstall.exe"
SectionEnd

Section "Microsoft Visual C++ 2010 SP1 runtime"
    SetOutPath "$INSTDIR"
	File "vcredist_x86.exe"
	Exec "$INSTDIR\vcredist_x86.exe /q"
	Delete "$INSTDIR\vcredist_x86.exe"
SectionEnd

Section "Uninstall"
	Delete "$INSTDIR\*.*"
	RmDir "$INSTDIR"
	Delete "$SMPROGRAMS\Sgt. Duffy\Sgt. Duffy.lnk"
	Delete "$SMPROGRAMS\Sgt. Duffy\Uninstall.lnk"
	RmDir "$SMPROGRAMS\Sgt. Duffy"
SectionEnd