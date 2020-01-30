//
// Created by karolina on 30.01.2020.
//

#include <include/Conversation.hpp>
#include <thread>
#include <QtTest/QSignalSpy>
#include "TestIncludes.h"

TEST(Conversation, sendMessageReceiveMessage) {
    std::thread serverThread(dummyServer);
    Conversation c("name", "127.0.0.1", PORT);
    QSignalSpy newMessageSpy(&c, SIGNAL(newMessage(const QString &)));
    c.sendMessage("mtest");
    if (newMessageSpy.count() == 0) newMessageSpy.wait(TIMEOUT);
    ASSERT_EQ(newMessageSpy.count(), 1);

    serverThread.join();
}

Q_DECLARE_METATYPE(Message::Status);
TEST(Conversation, sendStatusReceiveStatus) {
    qRegisterMetaType<Message::Status>();
    std::thread serverThread(dummyServer);
    Conversation c("name", "127.0.0.1", PORT);
    QSignalSpy statusSpy(&c, SIGNAL(status(Message::Status)));
    c.getConnection()->sendStatus(Message::Status::ACCEPT);
    if (statusSpy.count() == 0) statusSpy.wait(TIMEOUT);
    ASSERT_EQ(statusSpy.count(), 1);

    serverThread.join();
}