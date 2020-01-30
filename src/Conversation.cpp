//
// Created by wojtek on 26.01.2020.
//

#include "include/Conversation.hpp"

#include <utility>

int Conversation::currentId=0;

Conversation::Conversation(QString name, QTcpSocket *socket) : name(std::move(name)) {
    id=currentId++;
    connection = std::make_unique<Connection>(socket);
    connect(connection.get(), SIGNAL(receivedMessage(
                                             const std::shared_ptr<Message> &)),
            this, SLOT(onReceivedMessage(
                               const std::shared_ptr<Message> &)));
}

Conversation::Conversation(QString name, const QString& ip, qint16 port) : name(std::move(name)) {
    id=currentId++;
    connection = std::make_unique<Connection>(ip, port);
    connect(connection.get(), SIGNAL(receivedMessage(
                                             const std::shared_ptr<Message> &)),
            this, SLOT(onReceivedMessage(
                               const std::shared_ptr<Message> &)));
}

Conversation::Conversation(QString name, const QString &ip, qint16 port, QVector<std::shared_ptr<Message>> messages, int id)  : name(std::move(name)) {
    this->id=id;
    if (currentId > id)
        currentId++;
    else
        currentId=id+1;

    connection = std::make_unique<Connection>(ip, port);
    this->messages = std::move(messages);
    connect(connection.get(), SIGNAL(receivedMessage(
                                             const std::shared_ptr<Message> &)),
            this, SLOT(onReceivedMessage(
                               const std::shared_ptr<Message> &)));
}

void Conversation::sendMessage(const QString &str) {
    std::shared_ptr<Message> msg = std::make_shared<Message>(str,true);
    messages.push_back(msg);
    connection->sendMessage(msg);
}

QString Conversation::getName() const {
    return name;
}

void Conversation::onReceivedMessage(const std::shared_ptr<Message> &msg) {
    messages.push_back(msg);
    emit newMessage(msg->getText());
}

const QVector<std::shared_ptr<Message>> &Conversation::getMessages() {
    return messages;
}

const std::unique_ptr<Connection> &Conversation::getConnection() const {
    return connection;
}

int Conversation::getId() {
    return id;
}


