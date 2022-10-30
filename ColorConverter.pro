
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ColorConverter
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS


CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        color.h \
        mainwindow.h

FORMS += \
        mainwindow.ui

