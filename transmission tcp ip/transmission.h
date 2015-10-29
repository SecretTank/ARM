#ifndef TRANSMISSION_H
#define TRANSMISSION_H

#include <QDialog>
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
class QTcpServer;
class QTcpSocket;
class QAction;
class QDialogButtonBox;
QT_END_NAMESPACE

class Transmission : public QObject
{
    Q_OBJECT
public:
    Transmission(QObject *parent);
    ~Transmission();
public slots:
    void morabaaSlot();
    void mosalasSlot();
    void dayereSlot();
    void zarbdarSlot();
    void connected();
    void start();
    void startTransfer(char* command);
    void displayError(QAbstractSocket::SocketError socketError);
private:
    QTcpSocket tcpClient;
    QString message;
};

#endif // TRANSMISSION_H
