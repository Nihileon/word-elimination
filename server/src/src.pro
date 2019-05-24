    QT += core network sql
QT -= gui
CONFIG += c++17

TARGET = SocksServerConsole
CONFIG   += server
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    data/user.cpp \
    data/words.cpp \
    main.cpp \
    mysocket.cpp \
    mytcpserver.cpp \


HEADERS += \
    data/transformation.h  \
    data/basic.h \
    data/user.h \
    data/word.h \
    mysocket.h \
    mytcpserver.h \
