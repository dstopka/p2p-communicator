//
// Created by karolina on 30.01.2020.
//
#include "TestIncludes.h"
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <include/Message.hpp>


void dummyServer() {
    QTcpServer server;
    server.listen(QHostAddress::LocalHost, PORT);
    if (!server.waitForNewConnection(-1)) {
        std::cout << "Connection establishment failure" << std::endl;
        return;
    };
    QTcpSocket *socket = server.nextPendingConnection();
    socket->waitForReadyRead(-1);
    QByteArray a = socket->readAll();
    socket->write(a);
    socket->waitForBytesWritten(TIMEOUT);
}

