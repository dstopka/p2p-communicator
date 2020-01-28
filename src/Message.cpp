//
// Created by student on 27.01.2020.
//

#include "include/Message.hpp"

QString Message::getText() {
    return text;
}

void Message::setText(QString text) {
    this->text=text;
}

bool Message::isSender() {
    return sender;
};

