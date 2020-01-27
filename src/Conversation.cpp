//
// Created by wojtek on 26.01.2020.
//

#include "include/Conversation.hpp"

Conversation::Conversation(QTcpSocket *socket) {
    connection = std::make_unique<Connection>(socket);
}
