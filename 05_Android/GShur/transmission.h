#ifndef TRANSMISSION_H
#define TRANSMISSION_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include <QObject>

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
    QString message;
};

#endif // TRANSMISSION_H
