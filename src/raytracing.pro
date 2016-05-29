TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11


QMAKE_CXXFLAGS += -O3 -fopenmp
QMAKE_LFLAGS += -fopenmp


HEADERS += \
    Scene.h \
    Drawable.h \
    Vector.h \
    Sphere.h \
    Color.h \
    Ray.h \
    Light.h \
    Camera.h \
    Render.h \
    ARender.h \
    Image.h \
    PaintDevice.h \
    Debug.h \
    Utils.h

SOURCES += \
    main.cpp \
    Scene.cpp \
    Drawable.cpp \
    Sphere.cpp
