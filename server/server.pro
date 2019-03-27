QT += core
QT -= gui

CONFIG += c++11

TARGET = Server
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    src/main.cpp \
    lib/sqlite3.c \
    src/main.cpp

HEADERS += \
    lib/catch.hpp \
    lib/json.hpp \
    lib/sqlite3.h \
    lib/poorormlite.h \
    lib/helper.h \
    lib/catch.hpp \
    lib/json.hpp \
    lib/nullable.h \
    lib/ormlite.h \
    lib/sqlite3.h
