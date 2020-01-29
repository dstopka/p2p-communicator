//
// Created by student on 27.01.2020.
//

#ifndef OOP_2019_KOMUNIKATOR_P2P_DATABASE_HPP
#define OOP_2019_KOMUNIKATOR_P2P_DATABASE_HPP

#include <QObject>
#include "Conversation.hpp"
#include <QSqlDatabase>
#include <QtSql/QSqlQuery>

class Database : public QObject {
Q_OBJECT
public:

    Database();
    ~Database();

    void storeConversation(Conversation conversation);
    QVector<Conversation> loadConversations();

private:
    std::unique_ptr<QSqlDatabase> database;
//    QString connectionName;
    void storeMessage(Message message);
    void storeFile(File file);


signals:

public slots:
//    void onNewMessage(const QString &str);
//    void onNewFile(const QFile &file);

};

#endif //OOP_2019_KOMUNIKATOR_P2P_DATABASE_HPP
