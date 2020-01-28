//
// Created by wojtek on 26.01.2020.
//

#ifndef OOP_2019_KOMUNIKATOR_P2P_CONVERSATION_HPP
#define OOP_2019_KOMUNIKATOR_P2P_CONVERSATION_HPP

#include "include/Connection.hpp"

#include <QObject>
#include <QTcpSocket>
#include <memory>

class Conversation : public QObject {
Q_OBJECT
public:
    explicit Conversation(QString name, QTcpSocket *);

    explicit Conversation(QString name, const QString& ip, qint16 port);

    void sendMessage(const QString &);

    QString getName();

private:
    std::unique_ptr<Connection> connection;
    QString name;

signals:

    void newMessage(const QString &);

public slots:

    void onReceivedMessage(const QString &);
};


#endif //OOP_2019_KOMUNIKATOR_P2P_CONVERSATION_HPP
