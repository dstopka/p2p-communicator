//
// Created by student on 27.01.2020.
//

#include "include/Connection.hpp"

Connection::Connection(QTcpSocket *sock) {
    socket = std::unique_ptr<QTcpSocket>(sock);
    connect(socket.get(), SIGNAL(readyRead()), this, SLOT(onReceivedData()));
}

void Connection::onReceivedData() {
    QTextStream stream(socket.get());
    QChar c;
    stream >> c;
    if (c == 'm') {
        QString str;
        stream >> str;
        emit receivedMessage(std::make_shared<Message>(str));
    }

}

Connection::Connection(const QString &ip, qint16 port) {
    socket = std::make_unique<QTcpSocket>();
    socket->connectToHost(ip, port);
}

void Connection::sendMessage(const std::shared_ptr<Message> &msg) {
    QTextStream stream(socket.get());
    stream << 'm' << msg->getText();
}