QT += serialbus widgets

TARGET = can
TEMPLATE = app

SOURCES += \
    bitratebox.cpp \
    connectdialog.cpp \
    main.cpp \
    mainwindow.cpp \

HEADERS += \
    bitratebox.h \
    connectdialog.h \
    mainwindow.h \

FORMS += \
    mainwindow.ui \
    connectdialog.ui

RESOURCES += can.qrc

# Objects Pathes
DESTDIR = bin
UI_DIR = build
MOC_DIR = build
RCC_DIR = build
OBJECTS_DIR = build
