//
// Created by wojtek on 26.01.2020.
//

#ifndef OOP_2019_KOMUNIKATOR_P2P_MAINWINDOW_HPP
#define OOP_2019_KOMUNIKATOR_P2P_MAINWINDOW_HPP

#include "include/Server.hpp"
#include "include/Conversation.hpp"

#include <QtCore/QObject>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <memory>

class MainWindow : public QObject {
Q_OBJECT
public:
    MainWindow(int argc, char **argv);

    int run();

private:
    std::unique_ptr<QCoreApplication> app;
    std::unique_ptr<QQmlApplicationEngine> engine;
    //std::unique_ptr<Server> server;
    Server *server;
    std::shared_ptr<Conversation> currentConversation;
    QVector<Conversation> conversations;

    bool acceptConnection();

signals:

public slots:

    void onNewConnection(QTcpSocket *socket);
};


#endif //OOP_2019_KOMUNIKATOR_P2P_MAINWINDOW_HPP
