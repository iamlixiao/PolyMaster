TEMPLATE = app
TARGET = pm
DEPENDPATH += . debug release
INCLUDEPATH += .
QT+=widgets
CONFIG+=c++11

SOURCES += \
    main.cpp \
    polycanvas.cpp \
    polygon2d.cpp \
    polygonkernel.cpp \
    mousedrawkernel.cpp

HEADERS += \
    polycanvas.h \
    polygon2d.h \
    polygonkernel.h \
    mousedrawkernel.h
