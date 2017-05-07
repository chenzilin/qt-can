# QT Modules
QT += qml quick

# Target
TARGET = tran
TEMPLATE = app

CONFIG += c++14
# Extra Configs
CONFIG(release, debug|release) {
    DEFINES += QT_NO_DEBUG_OUTPUT
}

# Sources and Headers
HEADERS += \
    ./tran.h \
    ../can/can.h

SOURCES += \
    main.cpp \
    ./tran.cpp \
    ../can/can.cpp

# Qml Files
OTHER_FILES += main.qml

# Resources
RESOURCES += qml.qrc
QMAKE_RESOURCE_FLAGS += -no-compress

# Objects Pathes
DESTDIR = bin
UI_DIR = build
MOC_DIR = build
RCC_DIR = build
OBJECTS_DIR = build



