#include "datalink.h"
#include <QtNetwork>

DataLink::DataLink(QObject *parent) : QObject(parent)
{
    connect(&tcpServer, SIGNAL(newConnection()), this, SLOT(acceptConnection()));

    //find local IP address
    QHostAddress server_ip;
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses())
    {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
        {
            server_ip = address;
            break;
        }
    }
    //we just not used QHostAddress::LocalHost as it's not work cross platform
    while (!tcpServer.isListening() && !tcpServer.listen(server_ip, 7778 ))
    {
        qDebug() << QString("Unable to start the test: %1.").arg(tcpServer.errorString());
    }
    qDebug() << QString("%1:%2").arg(server_ip.toString()).arg(tcpServer.serverPort());
}

void DataLink::acceptConnection()
{
    connection = tcpServer.nextPendingConnection();
    connect(connection, SIGNAL(readyRead()), this, SLOT(data_read()));
    connect(connection, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));

    qDebug() << "Connection accepted";
    //tcpServer.close();
}

void DataLink::data_read()
{
    QString message = connection->readAll();
    QRegExp rx("(\\,)"); //RegEx for ' ' or ',' or '.' or ':' or '\t'
    QStringList query = message.split(rx);
    int operator_id = query[0].toInt();
    OperatorState state = static_cast<OperatorState>(operator_id);
    int address = query[1].toInt();
    int input = query[2].toInt();
    qDebug() << "operator_id: " << operator_id << "address: " << address << "input: " << input;
    emit data_avalible(state,address,input);
}

void DataLink::displayError(QAbstractSocket::SocketError socketError)
{
    if (socketError == QTcpSocket::RemoteHostClosedError)
        return;

    tcpServer.close();
    qDebug() <<  "Server ready";
}
