QT += core gui widgets sql network
TEMPLATE = app
CONFIG += c++17

TARGET = client

LIBS += \
    #../../libs/modern-sqlite/libsqlite3.a \
    ../../libs/qt-material-widgets/components/$(OBJECTS_DIR)/libcomponents.a

INCLUDEPATH += \
    $$top_srcdir/components/ \
    ../../libs/modern-sqlite \
    ../../libs/qt-material-widgets/components \
    ./ui

PRE_TARGETDEPS = \
    ../../libs/qt-material-widgets/components/$(OBJECTS_DIR)/libcomponents.a

FORMS += \
    ui/doubleplayerdialog_ui.ui \
    ui/gamedialog_ui.ui \
    ui/leaderboarddialog_ui.ui \
    ui/logindialog_ui.ui \
    ui/mainwindow.ui \
    ui/multiplayerMatchdialog_ui.ui \
    ui/registerdialog_ui.ui \
    ui/buildworddialog_ui.ui \
    ui/searchdialog_ui.ui



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
    widgets/LoginDialog.h \
    widgets/doubleplayerdialog.h \
    widgets/multiplayermatchdialog.h \
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
    widgets/LoginDialog.cpp \
    main.cpp \
    widgets/doubleplayerdialog.cpp \
    widgets/multiplayermatchdialog.cpp \
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

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += sqlite3

DISTFILES +=
