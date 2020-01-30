//
// Created by karolina on 30.01.2020.
//
#include <include/Controller.hpp>
#include <QtTest/QSignalSpy>
#include <QTimer>
#include "TestIncludes.h"

TEST(Controller, onNewConnection) {
    Controller c;
    QSignalSpy newConnectionSpy(&c, SIGNAL(newPendingConnection(QString, QString, QString)));
    QSignalSpy changeConversationSpy(&c, SIGNAL(clearMessagesAndChangeCurrentConversation(int)));
    QTcpSocket s;
    s.connectToHost(QHostAddress::LocalHost, PORT);

    if (newConnectionSpy.count() == 0) newConnectionSpy.wait(TIMEOUT);
    ASSERT_EQ(newConnectionSpy.count(), 1);
    if (changeConversationSpy.count() == 0) changeConversationSpy.wait(TIMEOUT);
    ASSERT_EQ(changeConversationSpy.count(), 1);
}

TEST(Controller, newMessage) {
    Controller c;
    QSignalSpy newConnectionSpy(&c, SIGNAL(newPendingConnection(QString, QString, QString)));
    QSignalSpy changeConversationSpy(&c, SIGNAL(clearMessagesAndChangeCurrentConversation(int)));
    QTcpSocket s;
    s.connectToHost(QHostAddress::LocalHost, PORT);

    if (newConnectionSpy.count() == 0) newConnectionSpy.wait(TIMEOUT);
    if (changeConversationSpy.count() == 0) changeConversationSpy.wait(TIMEOUT);

    QString expectedMessage = QString("test");
    QSignalSpy newMessageSpy(&c, SIGNAL(newMessage()));
    c.onNewMessage(expectedMessage);
    if (newMessageSpy.count() == 0) newMessageSpy.wait(TIMEOUT);
    ASSERT_EQ(newMessageSpy.count(), 1);
    ASSERT_EQ(c.getMessage(), expectedMessage);
}