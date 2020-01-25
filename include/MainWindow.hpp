//
// Created by wojtek on 26.01.2020.
//

#ifndef OOP_2019_KOMUNIKATOR_P2P_MAINWINDOW_HPP
#define OOP_2019_KOMUNIKATOR_P2P_MAINWINDOW_HPP




#include <QtCore/QObject>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <memory>

class MainWindow : public QObject{
public:
    MainWindow(int argc,char** argv);
    int run();

private:
    std::unique_ptr<QCoreApplication> app;
    std::unique_ptr<QQmlApplicationEngine> engine;
};


#endif //OOP_2019_KOMUNIKATOR_P2P_MAINWINDOW_HPP
