#ifndef TRANSMISSION_H
#define TRANSMISSION_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include <QObject>
#include <QVector>
#include <stdio.h>
#include <stdlib.h>

class Transmission : public QObject
{
    Q_OBJECT

public:
    explicit Transmission(QObject *parent = 0);
    ~Transmission();
signals:
    void errorConnection();
private slots:
    void morabaaSlot();
    void mosalasSlot();
    void dayereSlot();
    void zarbdarSlot();
    void connected();
    void start(QString IP);
    void startTransfer(char* command);
    void displayError(QAbstractSocket::SocketError socketError);
private:
    QTcpSocket tcpClient;
    QVector<QString> stack;
    int code;
    char code_char[4];
};

#endif // TRANSMISSION_H
