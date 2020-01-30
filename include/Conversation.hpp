//
// Created by wojtek on 26.01.2020.
//

#ifndef OOP_2019_KOMUNIKATOR_P2P_CONVERSATION_HPP
#define OOP_2019_KOMUNIKATOR_P2P_CONVERSATION_HPP

#include "include/Connection.hpp"
#include "include/Message.hpp"
#include "include/File.hpp"

#include <QObject>
#include <QTcpSocket>
#include <QtCore/QFile>
#include <memory>

class Conversation : public QObject {
Q_OBJECT
public:
    explicit Conversation(QString name, QTcpSocket *);

    explicit Conversation(QString name, const QString& ip, qint16 port);

    explicit Conversation(QString name, const QString& ip, qint16 port, QVector<std::shared_ptr<Message>> messages, int id);


    void sendMessage(const QString &str);

    const QVector<std::shared_ptr<Message>> &getMessages();

    QString getName() const;

    const std::unique_ptr<Connection>& getConnection() const;

    int getId();

private:
    QVector<std::shared_ptr<Message>> messages;
    std::unique_ptr<Connection> connection;
    QString name;
    int id;
    static int currentId;

signals:

    void newMessage(const QString &, int conversationId);

public slots:

    void onReceivedMessage(const std::shared_ptr<Message> &);
};


#endif //OOP_2019_KOMUNIKATOR_P2P_CONVERSATION_HPP
