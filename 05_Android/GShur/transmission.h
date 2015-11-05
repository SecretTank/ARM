#ifndef TRANSMISSION_H
#define TRANSMISSION_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include <QObject>
#include <QTimer>

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
    void sendJoystick(QString key);
    void sendBuffer();
    void stopJoystick();
private:
    QTcpSocket tcpClient;
    QString message;
    QTimer *bufferTimer;
    char charBuffer;
    bool isBufferEmpty;
};

#endif // TRANSMISSION_H
