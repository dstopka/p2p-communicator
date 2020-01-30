//
// Created by student on 27.01.2020.
//

#ifndef OOP_2019_KOMUNIKATOR_P2P_CONNECTION_HPP
#define OOP_2019_KOMUNIKATOR_P2P_CONNECTION_HPP

#include "include/Message.hpp"

#include <QObject>
#include <QTcpSocket>
#include <memory>

class Connection : public QObject {
Q_OBJECT
public:
    void sendMessage(const std::shared_ptr<Message> &msg);

    explicit Connection(QTcpSocket *);

    explicit Connection(const QString &ip, qint16 port);

    const std::unique_ptr<QTcpSocket>& getSocket();

private:
    std::unique_ptr<QTcpSocket> socket;

signals:

    void receivedMessage(const std::shared_ptr<Message> &);
public slots:

    void onReceivedData();
};

#endif //OOP_2019_KOMUNIKATOR_P2P_CONNECTION_HPP
