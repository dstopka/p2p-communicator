//
// Created by wojtek on 26.01.2020.
//

#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <memory>

class Server : public QObject {
Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

private:
    std::unique_ptr<QTcpServer> server;

signals:
    void newConnection(QTcpSocket *);
public slots:
    void makeNewConnection();
};

#endif // SERVER_H