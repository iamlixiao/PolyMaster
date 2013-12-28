TEMPLATE = app
TARGET = pm
DEPENDPATH += . debug release
INCLUDEPATH += .
QT+=core widgets
CONFIG+=c++11

SOURCES += \
    main.cpp \
    polycanvas.cpp \
    polygon3d.cpp \
    scene3d.cpp \
    polygon2d.cpp \
    rasterizer.cpp

HEADERS += \
    polycanvas.h \
    polygon3d.h \
    scene3d.h \
    polygon2d.h \
    rasterizer.h
