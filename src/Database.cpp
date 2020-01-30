//
// Created by student on 27.01.2020.
//


#include "include/Database.hpp"

Database::Database() {
    QString path{"db.sqlite"};
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    database=std::unique_ptr<QSqlDatabase>(&db);
    database->setHostName("test");
    database->setDatabaseName(path);
    bool ok = database->open();
    if (ok) {
        qDebug() << "Database opened successfully";
    } else{
        qDebug() << "Database opening error";
    }

    QSqlQuery query;
    query.prepare("CREATE TABLE IF NOT EXISTS conversation "
                  "(conversation_id INTEGER PRIMARY KEY, "
                  "name TEXT, "
                  "ip_address TEXT, "
                  "port INTEGER)");

    ok = query.exec();
    if (ok) {
        qDebug() << "Table \"conversation\" created successfully";
    } else {
        qDebug() << "Table \"conversation\" creation failed";
    }

    query.prepare("CREATE TABLE IF NOT EXISTS message "
                  "(message_id INTEGER PRIMARY KEY, "
                  "text TEXT, "
                  "sender INTEGER, "
                  "conversation_id INTEGER, "
                  "FOREIGN KEY(conversation_id) "
                  "REFERENCES conversation (conversation_id))");

    ok = query.exec();
    if (ok) {
        qDebug() << "Table \"message\" created successfully";
    } else {
        qDebug() << "Table \"message\" creation failed";
    }

}

Database::~Database() {
    database->close();
}

void Database::storeConversation(const Conversation& conversation) {
    QSqlQuery query;
    query.prepare("INSERT INTO conversation(name, ip_address, port) values(:name, :ip_address, :port)");
    query.bindValue(":name", conversation.getName());
    int port = conversation.getConnection()->getSocket()->peerPort();
    QHostAddress ipAddress = conversation.getConnection()->getSocket()->peerAddress();
    query.bindValue(":ip_address", ipAddress.toString());
    query.bindValue(":port", port);

    if (query.exec()) {
        qDebug() << "Conversation stored successfully";
    } else {
        qDebug() << "Conversation storing failed";
    }
}

QList<std::shared_ptr<Conversation>> Database::loadConversations() {

    QList<std::shared_ptr<Conversation>> conversations;

    QSqlQuery query;
    query.prepare("SELECT * FROM conversation");

    if (query.exec()) {
        while (query.next()) {

            int conversation_id = query.value(0).toInt();
            QString name = query.value(1).toString();
            QString ipAddress = query.value(2).toString();
            qint16 port = query.value(3).toInt();
            Conversation conversation{name, ipAddress, port, loadMessages(conversation_id), conversation_id};
            std::shared_ptr<Conversation> ptr{&conversation};
            conversations.append(ptr);
        }
    }
    return QList<std::shared_ptr<Conversation>>();
}

void Database::storeMessage(Message message) {

    QSqlQuery query;
    query.prepare("INSERT INTO message(name, ip_address, port) values(:name, :ip_address, :port)");
}

void Database::storeFile(File file) {

}

QVector<std::shared_ptr<Message>> Database::loadMessages(int conversationId) {

    QVector<std::shared_ptr<Message>> messages;

    QSqlQuery query;
    query.prepare("SELECT * FROM message WHERE conversation_id = :conversation_id");
    query.bindValue(":conversation_id", conversationId);

    if (query.exec()) {
        while (query.next()) {
            QString text = query.value(1).toString();
            bool sender = query.value(2).toBool();
            Message message{text, sender};
            std::shared_ptr<Message> ptr{&message};
            messages.append(ptr);
        }
    }
    return messages;
}

QVector<File> Database::loadFiles() {
    return QVector<File>();
}
