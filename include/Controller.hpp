//
// Created by wojtek on 26.01.2020.
//

#ifndef OOP_2019_KOMUNIKATOR_P2P_CONTROLLER_HPP
#define OOP_2019_KOMUNIKATOR_P2P_CONTROLLER_HPP

#include "include/Server.hpp"
#include "include/Conversation.hpp"
#include "include/Database.hpp"

#include <QObject>
#include <memory>

class Controller : public QObject {
Q_OBJECT
public:
    Controller();

private:
    std::unique_ptr<Server> server;
    std::unique_ptr<Database> database;
    std::shared_ptr<Conversation> currentConversation;
    QList<std::shared_ptr<Conversation>> conversations;

    bool acceptConnection();

signals:

public slots:

    void onNewConnection(QTcpSocket *socket);
};


#endif //OOP_2019_KOMUNIKATOR_P2P_CONTROLLER_HPP
