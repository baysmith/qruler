TARGET = qruler
TEMPLATE = app

QT += widgets

SOURCES += main.cpp\
        qruler.cpp\
        aboutdialog.cpp

HEADERS  += qruler.h\
            aboutdialog.h

RESOURCES = qruler.qrc
ICON = qruler.icns

win32 {
    RC_FILE = qruler.rc
}
