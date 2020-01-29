//
// Created by wojtek on 26.01.2020.
//


#include "include/Controller.hpp"
#include <QDebug>

Controller::Controller() {
    server = std::make_unique<Server>();
    database = std::make_unique<Database>();
    connect(server.get(), SIGNAL(newConnection(QTcpSocket * )), this, SLOT(onNewConnection(QTcpSocket * )));
}

void Controller::acceptConnection(qint8 idx) {
    conversations[idx]->getConnection()->sendStatus(Message::ACCEPT);
}

void Controller::onNewConnection(QTcpSocket *socket) {
    emit newPendingConnection(socket->peerAddress().toString().mid(7), QString::number(socket->peerPort()), "name");
    changeCurrentConversation(std::make_shared<Conversation>("name", socket));
    conversations.push_back(currentConversation);
}

void Controller::sendMessage(const QString &str, const QChar ind) {
    if (currentConversation != nullptr)
    {
        if(ind == 'm')
            currentConversation->sendMessage(str);
        else if (ind == 'f')
            currentConversation->sendFile(str);
    }
}

void Controller::createNewConnection(QString name, const QString &ip, qint16 port)
{
    emit newConnection(ip, QString::number(port), name);
    changeCurrentConversation(std::make_shared<Conversation>(name, ip, port));
    int index = conversations.size();
    connect(currentConversation.get(),&Conversation::status,
            [this,index](){emit setAccepted(index);});
    conversations.push_back(currentConversation);

}

void Controller::onNewMessage(const QString &str) {
    lastMessage = str;
    emit newMessage(str);
}

const QString &Controller::getMessage() {
    return lastMessage;
}

void Controller::changeCurrentConversation(const std::shared_ptr<Conversation> &conversation) {
    if(currentConversation != nullptr)
        disconnect(currentConversation.get(), SIGNAL(newMessage(const QString &)),
                   this, SLOT(onNewMessage(const QString &)));
    currentConversation = conversation;
    connect(currentConversation.get(), SIGNAL(newMessage(const QString &)),
            this, SLOT(onNewMessage(const QString &)));

    int index = conversations.indexOf(conversation);
    if(index == -1)
        index = conversations.size();

    emit clearMessagesAndChangeCurrentConversation(index);
    for(const auto& msg: currentConversation->getMessages())
    {
        loadMessage(msg->getText(),msg->isSender());
    }
}

void Controller::changeCurrentConversation(int index) {
    changeCurrentConversation(conversations[index]);
}
