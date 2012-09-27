#-------------------------------------------------
#
# Project created by QtCreator 2012-07-05T02:10:58
#
#-------------------------------------------------

QT        += core gui network svg
CONFIG    += release warn_on
TARGET     = "Sgt. Duffy"
TEMPLATE   = app
SOURCES   += main.cpp mainwindow.cpp
HEADERS   += mainwindow.h
FORMS     += mainwindow.ui
RESOURCES += Resources.qrc


win32 {
OTHER_FILES += Duffy.ico icon.rc
RC_FILE = icon.rc
}

macx {
CONFIG   += app_bundle
ICON = duffy_osx.icns
}
