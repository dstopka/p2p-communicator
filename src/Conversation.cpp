//
// Created by wojtek on 26.01.2020.
//

#include "include/Conversation.hpp"

#include <QDir>
#include <utility>

void Conversation::connectSlots()
{
    connect(connection.get(), SIGNAL(receivedMessage(const std::shared_ptr<Message> &)),
            this, SLOT(onReceivedMessage(const std::shared_ptr<Message> &)));
    connect(connection.get(), SIGNAL(receivedStatus(QChar)),
            this, SLOT(onReceivedStatus(QChar)));
    connect(connection.get(), SIGNAL(receivedFile(const std::shared_ptr<File> &)),
            this, SLOT(onReceivedFile(const std::shared_ptr<File> &)));
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
    messages.push_back(std::make_shared<Message>("<style type='text/css'>a{color: #ffffff;font-size:12px;}</style><a href='" + str + "'><i> "+file->getName()+"</i></a>",true));connection->sendFile(file);
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

void Conversation::onReceivedFile(const std::shared_ptr<File> &file) {
    files.push_back(file);
    messages.push_back(std::make_shared<Message>("<style type='text/css'>a{color: #ffffff;font-size:12px;}</style><a href='file://" + QDir::currentPath() + '/' + file->getName() + "'><i> "+file->getName()+"</i></a>",false));
    emit newMessage(messages.last()->getText());
}


