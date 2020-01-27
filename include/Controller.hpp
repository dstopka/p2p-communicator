//
// Created by wojtek on 26.01.2020.
//

#ifndef OOP_2019_KOMUNIKATOR_P2P_CONTROLLER_HPP
#define OOP_2019_KOMUNIKATOR_P2P_CONTROLLER_HPP

#include "include/Server.hpp"
#include "include/Conversation.hpp"

#include <QObject>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <memory>

class Controller : public QObject {
Q_OBJECT
public:
    Controller();

private:
    std::unique_ptr<Server> server;
    std::shared_ptr<Conversation> currentConversation;
    QVector<Conversation> conversations;

    bool acceptConnection();

signals:

public slots:

    void onNewConnection(QTcpSocket *socket);
};


#endif //OOP_2019_KOMUNIKATOR_P2P_CONTROLLER_HPP
