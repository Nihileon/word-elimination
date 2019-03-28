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
    ui/registerdialog_ui.ui



HEADERS += \
    widgets/LoginDialog.h \
    widgets/mainwindow.h \
    data/basic.h \
    data/login.h \
    data/word.h \
    ui/gamedialog_ui.h \
    ui/LeaderboardDialog_ui.h \
    ui/LoginDialog_ui.h \
    ui/MainWindow_ui.h \
    ui/RegisterDialog_ui.h \
    widgets/registerdialog.h



SOURCES += \
    widgets/LoginDialog.cpp \
    main.cpp \
    mainwindow.cpp \
    data/login.cpp \
    data/words.cpp \
    widgets/registerdialog.cpp \
    data/loginsingleton.cpp


SUBDIRS += \
    src.pro \
    ../../libs/qt-material-widgets/components/resources.qrc \

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += sqlite3
