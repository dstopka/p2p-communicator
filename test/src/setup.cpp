//
// Created by karolina on 30.01.2020.
//

#include <QtCore/QCoreApplication>
#include <gtest/gtest.h>
#include <QtCore/QTimer>
#include <include/Message.hpp>

// Initialize QApplication with event loop for google test runner
int main(int argc, char **argv) {
    QCoreApplication app(argc, argv);
    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();

    QTimer exitTimer;
    QObject::connect(&exitTimer, &QTimer::timeout, &app, QCoreApplication::quit);
    exitTimer.start();
    app.exec();
    return ret;
}