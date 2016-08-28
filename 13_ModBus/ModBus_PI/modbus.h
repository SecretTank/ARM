#ifndef MODBUS_H
#define MODBUS_H

#include <QObject>
#include <QModbusDataUnit>
#include "writeregistermodel.h"

#include <QModbusTcpClient>
#include <QModbusRtuSerialMaster>
#include <QUrl>
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include "datalink.h"

class ModBus : public QObject
{
    Q_OBJECT
public:
    explicit ModBus(QObject *parent = 0);

signals:

private:
    void initActions();
    QModbusDataUnit readRequest(int reg_type,int address) const;
    QModbusDataUnit writeRequest(int reg_type, int address) const;

    void connect();

private slots:
    void onStateChanged(QModbusDevice::State state);

    void readReady();

    void on_get_command(OperatorState state, int address, int input);

private:
    DataLink channel;
    QModbusReply *lastRequest;
    QModbusClient *modbusDevice;
    WriteRegisterModel *writeModel;
};

#endif // MODBUS_H
