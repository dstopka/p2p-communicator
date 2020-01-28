//
// Created by student on 27.01.2020.
//

#include "include/Connection.hpp"

Connection::Connection(QTcpSocket *sock) {
    socket = std::unique_ptr<QTcpSocket>(sock);
    connect(socket.get(), SIGNAL(readyRead()), this, SLOT(onReceivedData()));
}

void Connection::sendMessage(const QString &str) {
    QTextStream stream(socket.get());
    stream << str << "\n";
}

void Connection::onReceivedData() {
    QTextStream stream(socket.get());
    QString text;
    stream >> text;
    emit receivedMessage(text);
}

Connection::Connection(const QString &ip, qint16 port) {
    socket = std::make_unique<QTcpSocket>();
    socket->connectToHost(ip, port);
}