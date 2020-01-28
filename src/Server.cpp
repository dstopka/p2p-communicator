//
// Created by wojtek on 26.01.2020.
//

#include "include/Server.hpp"
#include "QDebug"

Server::Server(QObject *parent) : QObject(parent) {
    server = std::make_unique<QTcpServer>();
    server->listen(QHostAddress::Any, 8000);
    connect(server.get(), SIGNAL(newConnection()), this, SLOT(makeNewConnection()));
}

void Server::makeNewConnection() {
    emit newConnection(server->nextPendingConnection());
}
