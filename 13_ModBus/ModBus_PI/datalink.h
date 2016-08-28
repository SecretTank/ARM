#ifndef DATALINK_H
#define DATALINK_H

#include <QObject>
#include <QTcpServer>
#include "define.h"



class DataLink : public QObject
{
    Q_OBJECT
public:
    explicit DataLink(QObject *parent = 0);

signals:
    void data_avalible (OperatorState state, int address, int input);

public slots:
    void acceptConnection();
    void displayError(QAbstractSocket::SocketError socketError);
    void data_read();

private:
    QTcpServer tcpServer;
    QTcpSocket *connection;
};

#endif // DATALINK_H
