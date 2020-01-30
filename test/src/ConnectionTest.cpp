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
    if (connectSpy.count() == 0) connectSpy.wait(TIMEOUT);
    ASSERT_EQ(connectSpy.count(), 1);

    c.sendMessage(std::make_shared<Message>("test", true));
    if (writeSpy.count() == 0) writeSpy.wait(TIMEOUT);
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
    if (connectSpy.count() == 0) connectSpy.wait(TIMEOUT);
    ASSERT_EQ(connectSpy.count(), 1);

    c.sendStatus(Message::Status::ACCEPT);
    if (writeSpy.count() == 0) writeSpy.wait(TIMEOUT);
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
    if (connectSpy.count() == 0) connectSpy.wait(TIMEOUT);
    ASSERT_EQ(connectSpy.count(), 1);

    socket->write("mtest");
    if (writeSpy.count() == 0) writeSpy.wait(TIMEOUT);
    ASSERT_EQ(writeSpy.count(), 1);
    if (readSpy.count() == 0) readSpy.wait(TIMEOUT);
    ASSERT_EQ(readSpy.count(), 1);
    if (receivedMessageSpy.count() == 0) receivedMessageSpy.wait(TIMEOUT);
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
    if (connectSpy.count() == 0) connectSpy.wait(TIMEOUT);
    ASSERT_EQ(connectSpy.count(), 1);

    socket->write("sa");
    if (writeSpy.count() == 0) writeSpy.wait(TIMEOUT);
    ASSERT_EQ(writeSpy.count(), 1);
    if (readSpy.count() == 0) readSpy.wait(TIMEOUT);
    ASSERT_EQ(readSpy.count(), 1);
    if (receivedStatusSpy.count() == 0) receivedStatusSpy.wait(TIMEOUT);
    ASSERT_EQ(receivedStatusSpy.count(), 1);

    serverThread.join();
}