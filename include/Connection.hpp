//
// Created by student on 27.01.2020.
//

#ifndef OOP_2019_KOMUNIKATOR_P2P_CONNECTION_HPP
#define OOP_2019_KOMUNIKATOR_P2P_CONNECTION_HPP

#include "include/Message.hpp"
#include "include/File.hpp"

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>
#include <QFile>
#include <QTimer>
#include <memory>

class Connection : public QObject {
Q_OBJECT
public:
    void sendMessage(const std::shared_ptr<Message> &msg);
    void sendStatus(Message::Status status);
    void sendFile(const std::shared_ptr<File> &file);

    explicit Connection(QTcpSocket *);

    explicit Connection(const QString &ip, quint16 port);

    const std::unique_ptr<QTcpSocket>& getSocket();
    quint16 port;
    QString ip;

private:
    bool isReadingFile=false;
    quint64 lastBytes=0;
    QFile in;
    std::unique_ptr<QTimer> timer;
    std::unique_ptr<QTcpSocket> socket;

    void setup();

signals:
    void receivedMessage(const std::shared_ptr<Message> &);
    void receivedStatus(QChar);
    void receivedFile(const std::shared_ptr<File> &file);

public slots:

    void onReceivedData();
};

#endif //OOP_2019_KOMUNIKATOR_P2P_CONNECTION_HPP
