//
// Created by karolina on 29.01.2020.
//
#include <thread>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <Connection.hpp>
#include <Message.hpp>

#include <QtTest>
#include "TestIncludes.h"

TEST(Connection, sendMessage) {
    std::thread serverThread(dummyServer);
    auto *socket = new QTcpSocket();

    QSignalSpy connectSpy(socket, SIGNAL(connected()));
    QSignalSpy writeSpy(socket, SIGNAL(bytesWritten(qint64)));
    socket->connectToHost(QHostAddress::LocalHost, PORT);
    Connection c(socket);
    connectSpy.wait(TIMEOUT);
    ASSERT_EQ(connectSpy.count(), 1);

    c.sendMessage(std::make_shared<Message>("test", true));
    writeSpy.wait(TIMEOUT);
    ASSERT_EQ(writeSpy.count(), 1);

    serverThread.join();
}

TEST(Connection, sendStatus) {
    std::thread serverThread(dummyServer);
    auto *socket = new QTcpSocket();

    QSignalSpy connectSpy(socket, SIGNAL(connected()));
    QSignalSpy writeSpy(socket, SIGNAL(bytesWritten(qint64)));
    socket->connectToHost(QHostAddress::LocalHost, PORT);
    Connection c(socket);
    connectSpy.wait(TIMEOUT);
    ASSERT_EQ(connectSpy.count(), 1);

    c.sendStatus(Message::Status::ACCEPT);
    writeSpy.wait(TIMEOUT);
    ASSERT_EQ(writeSpy.count(), 1);

    serverThread.join();
}


Q_DECLARE_METATYPE(std::shared_ptr<Message>);
TEST(Connection, onReceivedData_message) {
    qRegisterMetaType<std::shared_ptr<Message>>();

    std::thread serverThread(dummyServer);
    auto *socket = new QTcpSocket();

    QSignalSpy connectSpy(socket, SIGNAL(connected()));
    QSignalSpy readSpy(socket, SIGNAL(readyRead()));
    QSignalSpy writeSpy(socket, SIGNAL(bytesWritten(qint64)));
    socket->connectToHost(QHostAddress::LocalHost, PORT);
    Connection c(socket);
    QSignalSpy receivedMessageSpy(&c, SIGNAL(receivedMessage(const std::shared_ptr<Message> &)));
    connectSpy.wait(TIMEOUT);
    ASSERT_EQ(connectSpy.count(), 1);

    socket->write("mtest");
    writeSpy.wait(TIMEOUT);
    ASSERT_EQ(writeSpy.count(), 1);
    readSpy.wait(TIMEOUT);
    ASSERT_EQ(readSpy.count(), 1);
    receivedMessageSpy.wait(TIMEOUT);
    ASSERT_EQ(receivedMessageSpy.count(), 1);

    serverThread.join();
}

TEST(Connection, onReceivedData_status) {
    std::thread serverThread(dummyServer);
    auto *socket = new QTcpSocket();

    QSignalSpy connectSpy(socket, SIGNAL(connected()));
    QSignalSpy readSpy(socket, SIGNAL(readyRead()));
    QSignalSpy writeSpy(socket, SIGNAL(bytesWritten(qint64)));
    socket->connectToHost(QHostAddress::LocalHost, PORT);
    Connection c(socket);
    QSignalSpy receivedStatusSpy(&c, SIGNAL(receivedStatus(QChar)));
    connectSpy.wait(TIMEOUT);
    ASSERT_EQ(connectSpy.count(), 1);

    socket->write("sa");
    writeSpy.wait(TIMEOUT);
    ASSERT_EQ(writeSpy.count(), 1);
    readSpy.wait(TIMEOUT);
    ASSERT_EQ(readSpy.count(), 1);
    receivedStatusSpy.wait(TIMEOUT);
    ASSERT_EQ(receivedStatusSpy.count(), 1);

    serverThread.join();
}