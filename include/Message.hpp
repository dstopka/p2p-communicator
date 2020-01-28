//
// Created by student on 27.01.2020.
//

#ifndef OOP_2019_KOMUNIKATOR_P2P_MESSAGE_HPP
#define OOP_2019_KOMUNIKATOR_P2P_MESSAGE_HPP

#include <QObject>

class Message : public QObject {
Q_OBJECT
public:
    QString getText();
    void setText();

private:
    QString text;
    bool isSender;

signals:

public slots:

};

#endif //OOP_2019_KOMUNIKATOR_P2P_MESSAGE_HPP
