//
// Created by wojtek on 26.01.2020.
//

#include "include/Conversation.hpp"

Conversation::Conversation(QTcpSocket *socket) {
    connection = std::make_unique<Connection>(socket);
    connect(connection.get(), SIGNAL(receivedMessage(
                                             const QString &)), this, SLOT(onReceivedMessage(
                                                                                   const QString &)));
}

void Conversation::sendMessage(const QString &str) {
    connection->sendMessage(str);
}

void Conversation::onReceivedMessage(const QString &str) {
    emit newMessage(str);
}
