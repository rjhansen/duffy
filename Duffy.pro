#-------------------------------------------------
#
# Project created by QtCreator 2012-07-05T02:10:58
#
#-------------------------------------------------

QT        += core gui network svg
TEMPLATE   = app
SOURCES   += main.cpp mainwindow.cpp
HEADERS   += mainwindow.h
FORMS     += mainwindow.ui
RESOURCES += Resources.qrc


win32 {
TARGET = duffy
OTHER_FILES += Duffy.ico icon.rc
RC_FILE = icon.rc
}

macx {
CONFIG   += app_bundle
ICON = duffy_osx.icns
TARGET = duffy

QMAKE_CFLAGS += -gdwarf-2
QMAKE_CXXFLAGS += -gdwarf-2

QMAKE_INFO_PLIST = duffy.plist

QMAKE_CFLAGS_RELEASE = $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
QMAKE_CXXFLAGS_RELEASE = $$QMAKE_CXXFLAGS_RELEASE_WITH_DEBUGINFO
QMAKE_OBJECTIVE_CFLAGS_RELEASE =  $$QMAKE_OBJECTIVE_CFLAGS_RELEASE_WITH_DEBUGINFO
QMAKE_LFLAGS_RELEASE = $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO

OTHER_FILES += duffy.plist

codesign.depends  += pristine all
codesign.commands += macdeployqt duffy.app;
codesign.commands += dsymutil duffy.app/Contents/MacOS/duffy -o duffy.app.dSYM;

# Sign frameworks and plug-ins (uncomment and change to suit your application)
codesign.commands += codesign -s \"Robert J. Hansen\" -i \"com.secret-alchemy.Duffy\" duffy.app/Contents/Frameworks/QtCore.framework/Versions/4/QtCore;
codesign.commands += codesign -s \"Robert J. Hansen\" -i \"com.secret-alchemy.Duffy\" duffy.app/Contents/Frameworks/QtNetwork.framework/Versions/4/QtNetwork;
codesign.commands += codesign -s \"Robert J. Hansen\" -i \"com.secret-alchemy.Duffy\" duffy.app/Contents/Frameworks/QtXml.framework/Versions/4/QtXml;
codesign.commands += codesign -s \"Robert J. Hansen\" -i \"com.secret-alchemy.Duffy\" duffy.app/Contents/Frameworks/QtGui.framework/Versions/4/QtGui;
codesign.commands += codesign -s \"Robert J. Hansen\" -i \"com.secret-alchemy.Duffy\" duffy.app/Contents/Frameworks/QtSvg.framework/Versions/4/QtSvg;
codesign.commands += codesign -s \"Robert J. Hansen\" -i \"com.secret-alchemy.Duffy\" duffy.app/Contents/PlugIns/accessible/libqtaccessiblewidgets.dylib;
codesign.commands += codesign -s \"Robert J. Hansen\" -i \"com.secret-alchemy.Duffy\" duffy.app/Contents/PlugIns/bearer/libqcorewlanbearer.dylib;
codesign.commands += codesign -s \"Robert J. Hansen\" -i \"com.secret-alchemy.Duffy\" duffy.app/Contents/PlugIns/bearer/libqgenericbearer.dylib;
codesign.commands += codesign -s \"Robert J. Hansen\" -i \"com.secret-alchemy.Duffy\" duffy.app/Contents/PlugIns/codecs/libqcncodecs.dylib;
codesign.commands += codesign -s \"Robert J. Hansen\" -i \"com.secret-alchemy.Duffy\" duffy.app/Contents/PlugIns/codecs/libqjpcodecs.dylib;
codesign.commands += codesign -s \"Robert J. Hansen\" -i \"com.secret-alchemy.Duffy\" duffy.app/Contents/PlugIns/codecs/libqkrcodecs.dylib;
codesign.commands += codesign -s \"Robert J. Hansen\" -i \"com.secret-alchemy.Duffy\" duffy.app/Contents/PlugIns/codecs/libqtwcodecs.dylib;
codesign.commands += codesign -s \"Robert J. Hansen\" -i \"com.secret-alchemy.Duffy\" duffy.app/Contents/PlugIns/iconengines/libqsvgicon.dylib;
codesign.commands += codesign -s \"Robert J. Hansen\" -i \"com.secret-alchemy.Duffy\" duffy.app/Contents/PlugIns/imageformats/libqgif.dylib;
codesign.commands += codesign -s \"Robert J. Hansen\" -i \"com.secret-alchemy.Duffy\" duffy.app/Contents/PlugIns/imageformats/libqico.dylib;
codesign.commands += codesign -s \"Robert J. Hansen\" -i \"com.secret-alchemy.Duffy\" duffy.app/Contents/PlugIns/imageformats/libqjpeg.dylib;
codesign.commands += codesign -s \"Robert J. Hansen\" -i \"com.secret-alchemy.Duffy\" duffy.app/Contents/PlugIns/imageformats/libqmng.dylib;
codesign.commands += codesign -s \"Robert J. Hansen\" -i \"com.secret-alchemy.Duffy\" duffy.app/Contents/PlugIns/imageformats/libqsvg.dylib;
codesign.commands += codesign -s \"Robert J. Hansen\" -i \"com.secret-alchemy.Duffy\" duffy.app/Contents/PlugIns/imageformats/libqtga.dylib;
codesign.commands += codesign -s \"Robert J. Hansen\" -i \"com.secret-alchemy.Duffy\" duffy.app/Contents/PlugIns/imageformats/libqtiff.dylib;

# Sign the application bundle, using the provided entitlements
codesign.commands += codesign -f -s \"Robert J. Hansen\" -i \"com.secret-alchemy.Duffy\" -v duffy.app;

product.depends += codesign
product.commands += productbuild --component duffy.app /Applications --sign \"Robert J. Hansen\" duffy.pkg

dmg.depends += codesign
dmg.commands += hdiutil create -fs HFS+ -volname \"Duffy 1.0 RC2\" -srcfolder duffy.app \"Duffy 1.0 RC2.dmg\"

pristine.depends += clean
pristine.commands += rm -rf *.app *.dmg *.dSYM *.pkg;

QMAKE_EXTRA_TARGETS += codesign product copyfiles dmg pristine
}

unix:!macx {
TARGET       = duffy
target.path  = /usr/bin
INSTALLS    += target
}
