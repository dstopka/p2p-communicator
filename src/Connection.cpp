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
    switch (c.toLatin1())
    {
        case 'm': {
            QString str;
            str = stream.readAll();
            emit receivedMessage(std::make_shared<Message>(str, false));
            break;
        }
        case 's': {
            QChar s;
            stream >> s;
            emit receivedStatus(s);
            break;
        }
    }
}

void Connection::sendMessage(const std::shared_ptr<Message> &msg) {
    QTextStream stream(socket.get());
    stream << 'm' << msg->getText();
}

void Connection::sendStatus(Message::Status status) {
    QTextStream stream(socket.get());
    QString str('s');
    switch (status)
    {
        case Message::ACCEPT:
            str.append('a');
            stream<<str;
    }
}
