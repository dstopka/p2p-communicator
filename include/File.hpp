//
// Created by student on 27.01.2020.
//

#ifndef OOP_2019_KOMUNIKATOR_P2P_FILE_HPP
#define OOP_2019_KOMUNIKATOR_P2P_FILE_HPP

#include <QObject>

class File : public QObject {
Q_OBJECT

    Q_PROPERTY(QString url
                       READ
                       getUrl
                       WRITE
                       setUrl)
    Q_PROPERTY(bool sender
                       READ
                       isSender)
public:
    explicit File(QString str, bool sent);


    QString getUrl();

    void setUrl(QString url);

    bool isSender();

private:
    QString url;
    bool sender;

signals:

public slots:

};

#endif //OOP_2019_KOMUNIKATOR_P2P_FILE_HPP
