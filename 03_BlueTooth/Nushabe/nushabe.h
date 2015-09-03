#ifndef NUSHABE_H
#define NUSHABE_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QProgressBar>
#include <QDial>
#include <QtGui>
#include"QVBoxLayout"
#include <QList>
#include <QtBluetooth/QBluetoothLocalDevice>
#include <qbluetoothaddress.h>
#include <QBluetoothAddress>
#include <QBluetoothDeviceInfo>
#include <QBluetoothHostInfo>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothServiceDiscoveryAgent>
#include <QBluetoothSocket>
#include <QMessageBox>
#include <QBluetoothServer>
#include <QBluetoothTransferRequest>
#include <QBluetoothTransferManager>
#include <QBluetoothTransferReply>
#include <QVector>

namespace Ui {
class Nushabe;
}

class Nushabe : public QMainWindow
{
    Q_OBJECT

public:
    explicit Nushabe(QWidget *parent = 0);
    QDial* dial;
    QProgressBar* progressbar;
    QLabel* status;
    QBluetoothSocket* socket;
    QBluetoothServer* rfcommServer;
    ~Nushabe();
    QVector <QBluetoothDeviceInfo> dev_list;
    QBluetoothLocalDevice localDevice;

public:
    Ui::Nushabe *ui;
public slots:
    void valueChangedSlot(int value);
    void startDeviceDiscovery();
    void deviceDiscovered(const QBluetoothDeviceInfo &device);
    void startClient();
    void bt_connected();
    void bt_disconnected();
    void error(QBluetoothSocket::SocketError);

};

#endif // NUSHABE_H
