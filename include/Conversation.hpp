//
// Created by wojtek on 26.01.2020.
//

#ifndef OOP_2019_KOMUNIKATOR_P2P_CONVERSATION_HPP
#define OOP_2019_KOMUNIKATOR_P2P_CONVERSATION_HPP

#include "include/Connection.hpp"
#include "include/Message.hpp"

#include <QObject>
#include <QTcpSocket>
#include <memory>
enum Status {ACCEPT};

class Conversation : public QObject {
Q_OBJECT
public:

    explicit Conversation(QString name, QTcpSocket *);

    explicit Conversation(QString name, const QString& ip, qint16 port);

    void sendMessage(const QString &str);

    const QVector<std::shared_ptr<Message>> &getMessages();

    QString getName();

    const std::unique_ptr<Connection> &getConnection();

private:
    QVector<std::shared_ptr<Message>> messages;
    std::unique_ptr<Connection> connection;
    QString name;

    void connectSlots();

signals:

    void newMessage(const QString &);
    void status(Message::Status);

public slots:

    void onReceivedMessage(const std::shared_ptr<Message> &);
    void onReceivedStatus(QChar c);
};


#endif //OOP_2019_KOMUNIKATOR_P2P_CONVERSATION_HPP
