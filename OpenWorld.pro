#-------------------------------------------------
#
# Project created by QtCreator 2014-05-16T13:10:18
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenWorld
TEMPLATE = app


# Dit --------------------------------------------
DESTDIR = ../Win32/Debug
CONFIG += debug console
DEFINES += QT_LARGEFILE_SUPPORT QT_DLL QT_OPENGL_LIB
INCLUDEPATH += . \
    ./GeneratedFiles/Debug
LIBS += -lopengl32 \
    -lglu32
#PRECOMPILED_HEADER = StdAfx.h
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/debug
OBJECTS_DIR += debug
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
# ------------------------------------------------


SOURCES += main.cpp\
        mainwindow.cpp \
        view.cpp \
    coordinate.cpp

HEADERS  += mainwindow.h \
            view.h \
    coordinate.h
