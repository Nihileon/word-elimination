/*
 * @Author: Nihil Eon
 * @Date: 2019-05-01 20:17:04
 * @Last Modified by:   Nihil Eon
 * @Last Modified time: 2019-05-01 20:17:04
 */
#include "windowmanager.h"

Manager *Manager::_instance = nullptr;
Manager &Manager::instance() {
    if (_instance == nullptr) {
        _instance = new Manager();
    }
    return *_instance;
}

void Manager::destroy() { delete _instance; }

void Manager::init() {
    l->show();
    r->hide();
    mw->hide();
    QObject::connect(l, &LoginDialog::toReg, r, &RegisterDialog::show);
    QObject::connect(l, &LoginDialog::toMain, mw, &MainWindow::show);
    QObject::connect(l, &LoginDialog::sendUser, mw, &MainWindow::setUser);

    QObject::connect(r, &RegisterDialog::toLogin, l, &LoginDialog::show);
    QObject::connect(r, &RegisterDialog::sendUser, mw, &MainWindow::setUser);
    QObject::connect(r, &RegisterDialog::toMainWindow, mw, &MainWindow::show);

    QObject::connect(mw, &MainWindow::toSingleGame, g, &GameDialog::gameBegin);
    QObject::connect(mw, &MainWindow::sendChallenger, g,
                     &GameDialog::setChallenger);
    QObject::connect(mw, &MainWindow::sendChallenger, mm,
                     &MultiPlayerMatchDialog::setChallenger);
    QObject::connect(mw, &MainWindow::sendWordBuilder, b,
                     &BuildWordDialog::setWordBuilder);
    QObject::connect(mw, &MainWindow::toBuildWord, b, &BuildWordDialog::show);
    QObject::connect(mw, &MainWindow::toLeader, lb,
                     &LeaderboardDialog::showThis);
    QObject::connect(mw, &MainWindow::toSearch, s, &SearchDialog::show);
    QObject::connect(mw, &MainWindow::toMatching, mm,
                     &MultiPlayerMatchDialog::matchPlayer);

    QObject::connect(g, &GameDialog::toMain, mw, &MainWindow::show);
    QObject::connect(g, &GameDialog::sendChallenger, mw,
                     &MainWindow::setChallenger);

    QObject::connect(b, &BuildWordDialog::sendWordBuilder, mw,
                     &MainWindow::setWordBuilder);
    QObject::connect(b, &BuildWordDialog::toMain, mw, &MainWindow::show);

    QObject::connect(lb, &LeaderboardDialog::toMain, mw, &MainWindow::show);

    QObject::connect(s, &SearchDialog::toMainWindow, mw, &MainWindow::show);

    QObject::connect(d, &DoublePlayerDialog::hideMultiPlayerMatchWindow, mm,
                     &MultiPlayerMatchDialog::hide);
    QObject::connect(d, &DoublePlayerDialog::toMain, &TCPClient::instance(),
                     &TCPClient::gameEnd);

    QObject::connect(mm, &MultiPlayerMatchDialog::toMain, mw,
                     &MainWindow::show);
    QObject::connect(mm, &MultiPlayerMatchDialog::beginMatching,
                     &TCPClient::instance(),
                     &TCPClient::sendBeginMatchingRequest);
    QObject::connect(mm, &MultiPlayerMatchDialog::endMatching,
                     &TCPClient::instance(),
                     &TCPClient::sendEndMatchingRequest);

    QObject::connect(&TCPClient::instance(), &TCPClient::beginMultiPlayerGame,
                     d, &DoublePlayerDialog::beginGame);
    QObject::connect(&TCPClient::instance(), &TCPClient::toMain, mw,
                     &MainWindow::refreshAfterDoubleGame);
    QObject::connect(&TCPClient::instance(), &TCPClient::toMain, d,
                     &DoublePlayerDialog::hide);
    QObject::connect(&TCPClient::instance(), &TCPClient::sendMultiPlayerTable,
                     mm, &MultiPlayerMatchDialog::setMultiPlayerTbale);
    QObject::connect(&TCPClient::instance(), &TCPClient::sendCompeteRequest, mm,
                     &MultiPlayerMatchDialog::receiveCompeteQuery);
}
