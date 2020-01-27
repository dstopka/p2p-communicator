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
    Connection(QTcpSocket *);

private:
    std::unique_ptr<QTcpSocket> socket;

signals:

public slots:

};

#endif //OOP_2019_KOMUNIKATOR_P2P_CONNECTION_HPP
