#ifndef TRANSMISSION_H
#define TRANSMISSION_H

#include <QDialog>
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include <QMessageBox>
#include <QObject>



class Transmission : public QDialog
{
    Q_OBJECT

public:
    explicit Transmission(QString IP,QWidget *parent=0);
    ~Transmission();
signals:
    void errorConnection();
private slots:
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
