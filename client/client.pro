#-------------------------------------------------
#
# Project created by QtCreator 2019-03-12T14:57:43
#
#-------------------------------------------------
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = client
TEMPLATE = subdirs
SUBDIRS = ../libs/qt-material-widgets/components src
CONFIG += ordered


# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

