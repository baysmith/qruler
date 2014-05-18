#-------------------------------------------------
#
# Project created by QtCreator 2009-08-25T21:09:01
#
#-------------------------------------------------

TARGET = QRule
TEMPLATE = app

SOURCES += src/main.cpp\
        src/qrule.cpp\
        src/aboutdialog.cpp

HEADERS  += src/qrule.h\
            src/aboutdialog.h

RESOURCES = qrule.qrc
ICON = qruler.icns

win32 {
    RC_FILE = qrule.rc
}
