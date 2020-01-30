//
// Created by student on 27.01.2020.
//

#include <QtCore/QtAlgorithms>
#include "include/Connection.hpp"

Connection::Connection(QTcpSocket *sock) {
    socket = std::unique_ptr<QTcpSocket>(sock);
    connect(socket.get(), SIGNAL(readyRead()), this, SLOT(onReceivedData()));
}

Connection::Connection(const QString &ip, qint16 port) {
    socket = std::make_unique<QTcpSocket>();
    socket->connectToHost(ip, port);
    connect(socket.get(), SIGNAL(readyRead()), this, SLOT(onReceivedData()));
}

void Connection::onReceivedData() {

    char c;
    socket->read(&c,1);
    switch (c)
    {
        case 'm': {
            QTextStream stream(socket.get());
            QString str;
            str = stream.readAll();
            emit receivedMessage(std::make_shared<Message>(str, false));
            break;
        }
        case 's': {
            QTextStream stream(socket.get());
            QChar s;
            stream >> s;
            emit receivedStatus(s);
            break;
        }
        case 'f':{
            quint32 nameSize=0;
            socket->read(reinterpret_cast<char *>(&nameSize), sizeof(quint32));
            qDebug()<<nameSize;
            char *nameData = new char[nameSize];
            socket->read(nameData,nameSize);
            quint64 fileSize;
            socket->read(reinterpret_cast<char *>(&fileSize), sizeof(quint64));
            QFile in(nameData);
            in.open(QIODevice::WriteOnly);
            QByteArray data(fileSize,Qt::Initialization::Uninitialized);
            data = socket->readAll();
            in.write(data);
            in.close();
        }
    }
}

void Connection::sendMessage(const std::shared_ptr<Message> &msg) {
    QTextStream stream(socket.get());
    stream << 'm' << msg->getText();
}

void Connection::sendStatus(Message::Status status) {
    QTextStream stream(socket.get());
    QString str('s');
    switch (status)
    {
        case Message::ACCEPT:
            str.append('a');
            stream<<str;
    }
}


void Connection::sendFile(const std::shared_ptr<File> &file)
{
    QFile out(file->getUrl());
    out.open(QIODevice::ReadOnly);
    QByteArray data = out.readAll();
    quint32 nameSize = file->getName().size();
    quint64 fileSize = data.size();
    socket->write("f",1);
    socket->write((char*)&(nameSize), sizeof(quint32));
    socket->write(file->getName().toLatin1(),nameSize);
    socket->write((char*)&(fileSize), sizeof(quint64));
    socket->write(data);
    socket->waitForBytesWritten();
    out.close();
}