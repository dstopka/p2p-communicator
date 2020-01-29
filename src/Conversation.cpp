//
// Created by wojtek on 26.01.2020.
//

#include "include/Conversation.hpp"

#include <utility>

void Conversation::connectSlots()
{
    connect(connection.get(), SIGNAL(receivedMessage(const std::shared_ptr<Message> &)),
            this, SLOT(onReceivedMessage(const std::shared_ptr<Message> &)));
    connect(connection.get(), SIGNAL(receivedStatus(QChar)),
            this, SLOT(onReceivedStatus(QChar)));
}

Conversation::Conversation(QString name, QTcpSocket *socket) : name(std::move(name)) {
    connection = std::make_unique<Connection>(socket);
    connectSlots();
}

Conversation::Conversation(QString name, const QString& ip, qint16 port) : name(std::move(name)) {
    connection = std::make_unique<Connection>(ip, port);
    connectSlots();
}

void Conversation::sendMessage(const QString &str)
{
    std::shared_ptr<Message> msg = std::make_shared<Message>(str,true);
    messages.push_back(msg);
    connection->sendMessage(msg);
}

void Conversation::sendFile(const QString &str)
{
    std::shared_ptr<File> file = std::make_shared<File>(str,true);
    files.push_back(file);
    connection->sendFile(file);
}

QString Conversation::getName() {
    return name;
}

void Conversation::onReceivedMessage(const std::shared_ptr<Message> &msg) {
    messages.push_back(msg);
    emit newMessage(msg->getText());
}

const QVector<std::shared_ptr<Message>> &Conversation::getMessages() {
    return messages;
}

const std::unique_ptr<Connection> &Conversation::getConnection() {
    return connection;
}

void Conversation::onReceivedStatus(QChar c) {
    switch (c.toLatin1()){
        case 'a':
            emit status(Message::ACCEPT);
            break;
    }
}


