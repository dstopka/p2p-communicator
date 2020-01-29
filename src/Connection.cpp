//
// Created by student on 27.01.2020.
//

#include "include/Connection.hpp"

Connection::Connection(QTcpSocket *sock) {
    socket = std::unique_ptr<QTcpSocket>(sock);
    connect(socket.get(), SIGNAL(readyRead()), this, SLOT(onReceivedData()));
}

Connection::Connection(const QString &ip, qint16 port) {
    socket = std::make_unique<QTcpSocket>();
    socket->connectToHost(ip, port);
    connect(socket.get(), SIGNAL(readyRead()), this, SLOT(onReceivedData()));
}

void Connection::onReceivedData() {
    QTextStream stream(socket.get());
    QChar c;
    stream >> c;
    if (c == 'm') {
        QString str;
        str = stream.readAll();
        emit receivedMessage(std::make_shared<Message>(str,false));
    }
}

void Connection::sendMessage(const std::shared_ptr<Message> &msg) {
    QTextStream stream(socket.get());
    stream << 'm' << msg->getText();
}

void Connection::sendFile(const std::shared_ptr<File> &file)
{
    QDataStream stream(socket.get());
    QFile out(file->getUrl());
    stream << 'f' << out.readAll();
}
