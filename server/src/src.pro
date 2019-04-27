QT += core network sql
QT -= gui
CONFIG += c++11

TARGET = SocksServerConsole
CONFIG   += server
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    main.cpp \
    mytcpserver.cpp


HEADERS += \
    mytcpserver.h

