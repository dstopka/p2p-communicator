//
// Created by student on 27.01.2020.
//


#include "include/Database.hpp"

Database::Database() {

    QString path{"komunikator.db"};
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
    query.prepare("INSERT INTO conversation(conversation_id, name, ip_address, port) values(:conversation_id, :name, :ip_address, :port)");
    query.bindValue(":conversation_id", conversation.getId());
    query.bindValue(":name", conversation.getName());
    int port = conversation.getConnection()->getSocket()->peerPort();
    QHostAddress ipAddress = conversation.getConnection()->getSocket()->peerAddress();
    query.bindValue(":ip_address", ipAddress.toString().mid(7));
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
    query.prepare("SELECT * FROM conversation ORDER BY conversation_id ASC");

    if (query.exec()) {
        while (query.next()) {

            int conversation_id = query.value(0).toInt();
            QString name = query.value(1).toString();
            QString ipAddress = query.value(2).toString();
            qint16 port = query.value(3).toInt();
            std::shared_ptr<Conversation> ptr = std::make_shared<Conversation>(name, ipAddress, port, loadMessages(conversation_id), conversation_id);
            conversations.append(ptr);
            qDebug() << ptr->getName();
        }
        qDebug() << "Conversations selected successfully";
    } else {
        qDebug() << "Conversations select failed";
    }


    return conversations;
}

void Database::storeMessage(const Message& message, int conversationId) {

    QSqlQuery query;
    query.prepare("INSERT INTO message(text, sender, conversation_id) values(:text, :sender, :conversation_id)");
    query.bindValue(":text", message.getText());
    query.bindValue(":sender", bool{message.isSender()});
    query.bindValue(":conversation_id", conversationId);

    if (query.exec()) {
        qDebug() << "Message stored successfully";
    } else {
        qDebug() << "Message storing failed";
    }
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
            std::shared_ptr<Message> ptr = std::make_shared<Message>(text, sender);
            messages.append(ptr);
        }
        qDebug() << "Messages selected successfully";
    } else {
        qDebug() << "Messages select failed";
    }

    return messages;
}

/*QVector<File> Database::loadFiles() {
    return QVector<File>();
}*/

void Database::onNewMessage(const QString &text, int conversationId) {

    Message message{text, false};
    storeMessage(message, conversationId);
}
