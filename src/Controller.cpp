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
    database->storeConversation(*conversations[idx]);
}

void Controller::onNewConnection(QTcpSocket *socket) {
    emit newPendingConnection(socket->peerAddress().toString().mid(7), QString::number(socket->peerPort()), "name");
    changeCurrentConversation(std::make_shared<Conversation>("name", socket));
    conversations.push_back(currentConversation);
    connect(currentConversation.get(), &Conversation::newMessage,
            database.get(), &Database::onNewMessage);
}

void Controller::sendMessage(const QString &str, const QChar ind) {
    if (currentConversation != nullptr)
    {
        if(ind == 'm') {
            currentConversation->sendMessage(str);
            Message message{str, true};
            database->storeMessage(message, currentConversation->getId());
        }
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
    connect(currentConversation.get(), &Conversation::newMessage,
            database.get(), &Database::onNewMessage);
    conversations.push_back(currentConversation);

}

    void Controller::onNewMessage(const QString &str, int conversationId) {
    lastMessage = str;
    emit newMessage(str);
}

const QString &Controller::getMessage() {
    return lastMessage;
}

void Controller::changeCurrentConversation(const std::shared_ptr<Conversation> &conversation) {
    if(currentConversation != nullptr)
        disconnect(currentConversation.get(), SIGNAL(newMessage(const QString &, int)),
                   this, SLOT(onNewMessage(const QString &, int)));
    currentConversation = conversation;
    connect(currentConversation.get(), SIGNAL(newMessage(const QString &, int)),
            this, SLOT(onNewMessage(const QString &, int)));

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

void Controller::loadConversations() {
    conversations.append(database->loadConversations());

    if (!conversations.isEmpty()) {

        for(const std::shared_ptr<Conversation>& conversation : conversations) {
            QString ipAddress = conversation->getConnection()->getSocket()->peerAddress().toString();
            qint16 port = conversation->getConnection()->getSocket()->peerPort();
            emit newConnection(ipAddress, QString::number(port), conversation->getName());
        }
        Conversation::setCurrentId(conversations.last()->getId());
    }
}
