//
// Created by student on 27.01.2020.
//

#ifndef OOP_2019_KOMUNIKATOR_P2P_CONNECTION_HPP
#define OOP_2019_KOMUNIKATOR_P2P_CONNECTION_HPP

#include <QObject>
#include <QTcpSocket>
#include <memory>

class Connection : public QObject {
Q_OBJECT
public:
    void sendMessage(const QString &);

    explicit Connection(QTcpSocket *);

private:
    std::unique_ptr<QTcpSocket> socket;

signals:

    void receivedMessage(const QString &);
public slots:

    void onReceivedData();
};

#endif //OOP_2019_KOMUNIKATOR_P2P_CONNECTION_HPP
