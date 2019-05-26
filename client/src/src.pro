QT += core gui widgets network
TEMPLATE = app
CONFIG += c++17

TARGET = client

unix:OBJECTS_DIR = ../../libs/qt-material-widgets/components/
win32:OBJECTS_DIR = ../../libs/qt-material-widgets/components/release/

LIBS += \
    $(OBJECTS_DIR)libcomponents.a

INCLUDEPATH += \
    ../../libs/qt-material-widgets/components \
    ./ui

PRE_TARGETDEPS = \
    $(OBJECTS_DIR)libcomponents.a

HEADERS += \
    data/basicInfo.h \
    data/transformation.h \
    tcpclient.h \
    data/word.h \
    ui/GameDialog_ui.h \
    ui/LeaderboardDialog_ui.h \
    ui/LoginDialog_ui.h \
    ui/MainWindow_ui.h \
    ui/RegisterDialog_ui.h \
    widgets/DoubleplayerDialog.h \
    widgets/LoginDialog.h \
    widgets/MultiplayerMatchingDialog.h \
    windowmanager.h \
    ui/BuildWordDialog_ui.h \
    widgets/BuildWordDialog.h \
    widgets/LeaderBoardDialog.h \
    data/user.h \
    ui/SearchDialog_ui.h \
    widgets/SearchDialog.h \
    widgets/GameDialog.h \
    widgets/RegisterDialog.h \
    widgets/MainWindow.h \
    ui/radiusprogressbar.h \
    ui/materialmessagebox.h \
    ui/MultiPlayerMatchDialog_ui.h \
    ui/DoublePlayerDialog_ui.h



SOURCES += \
    tcpclient.cpp \
    data/words.cpp \
    widgets/DoubleplayerDialog.cpp \
    widgets/LoginDialog.cpp \
    main.cpp \
    widgets/MultiplayerMatchingDialog.cpp \
    windowmanager.cpp \
    widgets/BuildWordDialog.cpp \
    widgets/LeaderBoardDialog.cpp \
    data/user.cpp \
    widgets/SearchDialog.cpp \
    widgets/GameDialog.cpp \
    widgets/MainWindow.cpp \
    widgets/RegisterDialog.cpp


SUBDIRS += \
    resource

RESOURCES += \
    ../../libs/qt-material-widgets/components/resources.qrc \
    ./customprogressbar.qrc

