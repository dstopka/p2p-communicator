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
    Conversation(QTcpSocket *);

    void sendMessage(QString);

private:
    std::unique_ptr<Connection> connection;

signals:

    void newMessage(QString);

public slots:

};


#endif //OOP_2019_KOMUNIKATOR_P2P_CONVERSATION_HPP
