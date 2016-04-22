TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    src/shapes/shape.cpp \
    src/shapes/sphere.cpp \
    src/cameras/camera.cpp \
    src/cameras/ortographic.cpp \
    src/cameras/perspective.cpp \
    src/core/eqsolver.cpp \
    src/core/film.cpp \
    src/core/utils.cpp \
    src/core/matrix4x4.cpp \
    src/core/ray.cpp \
    src/core/tester.cpp \
    src/core/vector3d.cpp \
    src/main.cpp \
    src/core/bitmap.cpp \

HEADERS += \
    src/shapes/shape.h \
    src/shapes/sphere.h \
    src/cameras/camera.h \
    src/cameras/ortographic.h \
    src/cameras/perspective.h \
    src/core/eqsolver.h \
    src/core/utils.h \
    src/core/film.h \
    src/core/matrix4x4.h \
    src/core/ray.h \
    src/core/tester.h \
    src/core/vector3d.h \
    src/core/bitmap.h
