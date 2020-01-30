//
// Created by wojtek on 26.01.2020.
//

#ifndef OOP_2019_KOMUNIKATOR_P2P_CONTROLLER_HPP
#define OOP_2019_KOMUNIKATOR_P2P_CONTROLLER_HPP

#include "include/Server.hpp"
#include "include/Conversation.hpp"
#include "include/Database.hpp"

#include <QObject>
#include <memory>

class Controller : public QObject {
Q_OBJECT
    Q_PROPERTY(QString message
                       READ
                       getMessage)
public:
    Controller();

    Q_INVOKABLE void sendMessage(const QString &str, const QChar ind);
    Q_INVOKABLE void createNewConnection(QString name, const QString& ip, qint16 port);
    Q_INVOKABLE void acceptConnection(qint8 idx);
    const QString &getMessage();
    Q_INVOKABLE void changeCurrentConversation(int index);

private:
    std::unique_ptr<Server> server;
    std::unique_ptr<Database> database;
    std::shared_ptr<Conversation> currentConversation;
    QList<std::shared_ptr<Conversation>> conversations;
    QString lastMessage;

    void changeCurrentConversation(const std::shared_ptr<Conversation>& conversation);

signals:

    void newMessage(const QString &str);
    void newConnection(QString ipAdress, QString port, QString name);
    void newPendingConnection(QString ipAdress, QString port, QString name);
    void clearMessagesAndChangeCurrentConversation(int index);
    void loadMessage(const QString &str, bool sender);
    void setAccepted(int index);

public slots:

    void onNewMessage(const QString &, int conversationId);
    void onNewConnection(QTcpSocket *socket);

};


#endif //OOP_2019_KOMUNIKATOR_P2P_CONTROLLER_HPP
