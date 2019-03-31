QT += core gui widgets
TEMPLATE = app
CONFIG += c++17

TARGET = client

LIBS += \
    #../../libs/modern-sqlite/libsqlite3.a \
    #../../libs/qt-material-widgets/components/$(OBJECTS_DIR)/libcomponents.a

INCLUDEPATH += \
    $$top_srcdir/components/ \
    ../../libs/modern-sqlite \

PRE_TARGETDEPS = \
    #../../libs/qt-material-widgets/components/$(OBJECTS_DIR)/libcomponents.a

FORMS += \
    ui/gamedialog_ui.ui \
    ui/leaderboarddialog_ui.ui \
    ui/logindialog_ui.ui \
    ui/mainwindow.ui \
    ui/registerdialog_ui.ui \
    ui/buildworddialog_ui.ui



HEADERS += \
    data/basic.h \
    data/login.h \
    data/word.h \
    ui/GameDialog_ui.h \
    ui/LeaderboardDialog_ui.h \
    ui/LoginDialog_ui.h \
    ui/MainWindow_ui.h \
    ui/RegisterDialog_ui.h \
    widgets/gamedialog.h \
    widgets/LoginDialog.h \
    widgets/mainWindow.h \
    widgets/registerdialog.h \
    windowmanager.h \
    ui/BuildWordDialog_ui.h \
    widgets/BuildWordDialog.h \
    widgets/LeaderBoardDialog.h



SOURCES += \
    data/login.cpp \
    data/loginsingleton.cpp \
    data/words.cpp \
    widgets/gamedialog.cpp \
    widgets/LoginDialog.cpp \
    widgets/mainWindow.cpp \
    widgets/registerdialog.cpp \
    main.cpp \
    windowmanager.cpp \
    widgets/BuildWordDialog.cpp \
    widgets/LeaderBoardDialog.cpp


SUBDIRS += \
    src.pro \
    ../../libs/qt-material-widgets/components/resources.qrc \

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += sqlite3

DISTFILES +=
