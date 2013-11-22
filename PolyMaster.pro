TEMPLATE = app
TARGET = pm
DEPENDPATH += . debug release
INCLUDEPATH += .
QT+=widgets
CONFIG+=c++11

SOURCES += \
    main.cpp \
    polycanvas.cpp

HEADERS += \
    polycanvas.h
