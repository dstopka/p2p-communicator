//
// Created by student on 27.01.2020.
//


#include "include/Database.hpp"

Database::Database() {
    QString path{"db.sqlite"};
//    connectionName="connection";
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
                  "name TEXT, "
                  "text TEXT, "
                  "sender INTEGER)");

    ok = query.exec();
    if (ok) {
        qDebug() << "Table \"message\" created successfully";
    } else {
        qDebug() << "Table \"message\" creation failed";
    }
}

Database::~Database() {
    database->close();
//   QSqlDatabase::removeDatabase(connectionName);
}