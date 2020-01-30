//
// Created by student on 27.01.2020.
//

#ifndef OOP_2019_KOMUNIKATOR_P2P_DATABASE_HPP
#define OOP_2019_KOMUNIKATOR_P2P_DATABASE_HPP

#include <QObject>
#include "Conversation.hpp"
#include <QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtNetwork/QHostAddress>

class Database : public QObject {
Q_OBJECT
public:

    Database();
    ~Database();

    void storeConversation(const Conversation& conversation);

    QList<std::shared_ptr<Conversation>> loadConversations();
    static void storeMessage(const Message& message, int conversationId);

private:
    std::unique_ptr<QSqlDatabase> database;
    void storeFile(File file);
    static QVector<std::shared_ptr<Message>> loadMessages(int conversationId);
//    QVector<File> loadFiles();

signals:


public slots:
    void onNewMessage(const QString &text, int conversationId);

};

#endif //OOP_2019_KOMUNIKATOR_P2P_DATABASE_HPP
