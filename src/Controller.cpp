//
// Created by wojtek on 26.01.2020.
//


#include "include/Controller.hpp"
#include <QDebug>

Controller::Controller() {
    server = std::make_unique<Server>();
    database = std::make_unique<Database>();
    connect(server.get(), SIGNAL(newConnection(QTcpSocket * )), this, SLOT(onNewConnection(QTcpSocket * )));
}

bool Controller::acceptConnection() {
    //TODO
    return true;
}

void Controller::onNewConnection(QTcpSocket *socket) {
    if (acceptConnection()) {
        currentConversation = std::make_shared<Conversation>(socket);
        conversations.push_front(currentConversation);
    }
}