//
// Created by student on 27.01.2020.
//

#include "include/Connection.hpp"

Connection::Connection(QTcpSocket *sock) {
    socket = std::make_unique<QTcpSocket>(sock);
}
