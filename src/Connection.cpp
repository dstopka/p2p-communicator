//
// Created by student on 27.01.2020.
//

#include <QtCore/QtAlgorithms>
#include "include/File.hpp"
#include "include/Connection.hpp"
#include <QHostAddress>

void Connection::setup(){
    timer = std::make_unique<QTimer>();
    connect(timer.get(),&QTimer::timeout,
            [this](){socket->connectToHost(ip,port);
                qDebug()<<"try to connect!";});
    timer->start(10'000);
    connect(socket.get(),&QTcpSocket::connected,
            [this](){timer->stop();
                qDebug()<<"CONNECTED!";});
    connect(socket.get(),&QTcpSocket::disconnected,
            [this](){timer->start(10'000);
                qDebug()<<"LOST CONNECTION!";});
}

Connection::Connection(QTcpSocket *sock) {
    setup();
    timer->stop();
    socket = std::unique_ptr<QTcpSocket>(sock);
    connect(socket.get(), SIGNAL(readyRead()), this, SLOT(onReceivedData()));
}

Connection::Connection(const QString &ip, quint16 port) : port(port), ip(ip){
    setup();
    socket = std::make_unique<QTcpSocket>();
    socket->connectToHost(ip, port);
    qDebug() << socket->peerPort();
    connect(socket.get(), SIGNAL(readyRead()), this, SLOT(onReceivedData()));
}

void Connection::onReceivedData() {

    char c;
    if(!isReadingFile) {
        socket->read(&c, 1);
        switch (c) {
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
            case 'f': {//10.204.42.54
                isReadingFile = true;
                quint32 nameSize = 0;
                socket->read(reinterpret_cast<char *>(&nameSize), sizeof(quint32));
                char *nameData = new char[nameSize];
                socket->read(nameData, nameSize);
                quint64 fileSize;
                socket->read(reinterpret_cast<char *>(&fileSize), sizeof(quint64));
                lastBytes = fileSize;
                in.setFileName(nameData);
                in.open(QIODevice::WriteOnly);
                char *data = new char[fileSize];
                quint64 readBytes = socket->read(data, fileSize);
                in.write(data, readBytes);
                lastBytes -= readBytes;
                delete[] nameData;
                delete[] data;
                break;
            }
        }
    }
    else{
        char *data = new char[lastBytes];
        quint64 readBytes = socket->read(data, lastBytes);
        in.write(data, readBytes);
        lastBytes -= readBytes;
        if (lastBytes <= 0) {
            in.close();
            isReadingFile = false;
            socket->flush();
            receivedFile(std::make_shared<File>(in.fileName(), false));
            qDebug() << "koniec KURWA";
        }
        delete[] data;
    }
}

void Connection::sendMessage(const std::shared_ptr<Message> &msg) {
    QTextStream stream(socket.get());
    stream << 'm' << msg->getText();
}

const std::unique_ptr<QTcpSocket>& Connection::getSocket() {
    return socket;
}

void Connection::sendStatus(Message::Status status) {
    QTextStream stream(socket.get());
    QString str('s');
    switch (status)
    {
        case Message::ACCEPT:
            str.append('a');
            stream<<str;

        case Message::REJECT:
            str.append('r');
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
