//
// Created by student on 27.01.2020.
//

#ifndef OOP_2019_KOMUNIKATOR_P2P_MESSAGE_HPP
#define OOP_2019_KOMUNIKATOR_P2P_MESSAGE_HPP

#include <QObject>

class Message : public QObject {
Q_OBJECT

    Q_PROPERTY(QString text
                       READ
                               getText
                       WRITE
                       setText)
    Q_PROPERTY(bool sender
                       READ
                       isSender)

public:
    enum Status {ACCEPT};

    explicit Message(QString str, bool sent);


    QString getText();

    void setText(QString text);

    bool isSender();


private:
    QString text;
    bool sender;

signals:

public slots:

};

#endif //OOP_2019_KOMUNIKATOR_P2P_MESSAGE_HPP
