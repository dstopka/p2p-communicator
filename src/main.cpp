#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "include/MainWindow.hpp"

int main(int argc, char *argv[])
{
    MainWindow mainWindow{argc,argv};
    return mainWindow.run();
}
