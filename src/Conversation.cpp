//
// Created by wojtek on 26.01.2020.
//

#include "include/Conversation.hpp"

#include <utility>

Conversation::Conversation(QString name, QTcpSocket *socket) : name(std::move(name)) {
    connection = std::make_unique<Connection>(socket);
    connect(connection.get(), SIGNAL(receivedMessage(const QString &)),
            this, SLOT(onReceivedMessage(const QString &)));
}

Conversation::Conversation(QString name, const QString& ip, qint16 port) : name(std::move(name)) {
    connection = std::make_unique<Connection>(ip, port);
    connect(connection.get(), SIGNAL(receivedMessage(const QString &)),
            this, SLOT(onReceivedMessage(const QString &)));
}

void Conversation::sendMessage(const QString &str) {
    connection->sendMessage(str);
}

void Conversation::onReceivedMessage(const QString &str) {
    emit newMessage(str);
}

QString Conversation::getName() {
    return name;
}


