#include "modbus.h"

#define START_ADDRESS 1
#define Write_Size "10"
#define PORT_NAME "ttyUSB0"
#define PARITY    QSerialPort::NoParity
#define BAUD_RATE QSerialPort::Baud115200
#define DATA_BITS QSerialPort::Data8
#define STOP_BITS QSerialPort::OneStop
#define FLOW_CONT QSerialPort::NoFlowControl

#define RESPONSE_TIME     1000
#define NUMBER_OF_RETRIES 3
#define NUMBER_OF_ENTRIES 1

ModBus::ModBus(QObject *parent) : QObject(parent)
{
    writeModel = new WriteRegisterModel(this);
    writeModel->setStartAddress(START_ADDRESS);
    writeModel->setNumberOfValues(Write_Size);

    modbusDevice = new QModbusRtuSerialMaster(this);

    QObject::connect(modbusDevice, &QModbusClient::errorOccurred, [this](QModbusDevice::Error) {
        qDebug() << modbusDevice->errorString();});

    if (!modbusDevice)
    {
            qDebug() << "Could not create Modbus master.";
    }
    else
    {
        QObject::connect(modbusDevice,SIGNAL(stateChanged(QModbusDevice::State)), this, SLOT(onStateChanged(QModbusDevice::State)));
    }

    QObject::connect(&channel,SIGNAL(data_avalible (OperatorState , int , int )),this,SLOT(on_get_command(OperatorState , int , int )));
}


void ModBus::connect()
{
    if (!modbusDevice) //if already connected
        return;

    if (modbusDevice->state() != QModbusDevice::ConnectedState)
    {
        modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter, PORT_NAME);
        modbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter, PARITY);
        modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, BAUD_RATE);
        modbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, DATA_BITS);
        modbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, STOP_BITS);
        modbusDevice->setTimeout(RESPONSE_TIME);
        modbusDevice->setNumberOfRetries(NUMBER_OF_RETRIES);
        if (!modbusDevice->connectDevice())
        {
            qDebug () << "Connect failed: " << modbusDevice->errorString();
        }
        else
        {
            qDebug () << "Port Opened";
        }
    }
    else
    {
        modbusDevice->disconnectDevice();
        qDebug () << "Disconnect Device";
    }
}

void ModBus::onStateChanged(QModbusDevice::State state)
{
    if (state == QModbusDevice::UnconnectedState)
    {
        qDebug () << "Connect";
    }
    else if (state == QModbusDevice::ConnectedState)
    {
        qDebug () <<  "Disconnect";
    }
}

void ModBus::readReady()
{
    auto reply = qobject_cast<QModbusReply *>(sender());
    if (!reply)
        return;

    if (reply->error() == QModbusDevice::NoError)
    {
        const QModbusDataUnit unit = reply->result();
        qDebug() << "Data aquised";
        for (uint i = 0; i < unit.valueCount(); i++)
        {
            qDebug() << QString("Address: %1, Value: %2").arg(unit.startAddress())
                                     .arg(QString::number(unit.value(i),
                                          unit.registerType() <= QModbusDataUnit::Coils ? 10 : 16));
        }
    }
    else if (reply->error() == QModbusDevice::ProtocolError)
    {
        qDebug() << QString("Read response error: %1 (Mobus exception: 0x%2)").arg(reply->errorString()).
                                    arg(reply->rawResult().exceptionCode(), -1, 16);
    }
    else
    {
        qDebug() << QString("Read response error: %1 (code: 0x%2)").arg(reply->errorString()).
                                    arg(reply->error(), -1, 16);
    }

    reply->deleteLater();
}

void ModBus::on_get_command(OperatorState state, int address, int input)
{
    bool isRead = true;
    int reg_type = 0;
    switch (state)
    {
        case INPUT_REGISER:
            reg_type = 2;
            break;
        case READ_HOLDING_REGISTER:
            reg_type = 3;
            break;
        case DISCRETE_INPUT:
            reg_type = 1;
            break;
        case READ_COIL:
            reg_type = 0;
            break;
        case WRITE_HOLDING_REGISTER:
            reg_type = 3;
            isRead = 0;
        case WRITE_COIL:
            reg_type = 0;
            isRead = 0;
            break;
    }
    if (isRead)
    {
        if (!modbusDevice)
            return;

        if (auto *reply = modbusDevice->sendReadRequest(readRequest(reg_type,address), START_ADDRESS))
        {
            if (!reply->isFinished())
            {
                QObject::connect(reply, SIGNAL(finished()), this, SLOT(readReady()));
            }
            else
                delete reply; // broadcast replies return immediately
        }
        else
        {
            qDebug() << "Read error: " << modbusDevice->errorString();
        }
    }
    else
    {
        if (!modbusDevice)
            return;

        QModbusDataUnit writeUnit = writeRequest(reg_type,address);
        QModbusDataUnit::RegisterType table = writeUnit.registerType();
        for (uint i = 0; i < writeUnit.valueCount(); i++)
        {
            if (table == QModbusDataUnit::Coils)
                writeUnit.setValue(i, writeModel->m_coils[i + writeUnit.startAddress()]);
            else
                writeUnit.setValue(i, writeModel->m_holdingRegisters[i + writeUnit.startAddress()]);
        }

        if (auto *reply = modbusDevice->sendWriteRequest(writeUnit, START_ADDRESS))
        {
            if (!reply->isFinished())
            {
                QObject::connect(reply, &QModbusReply::finished, this, [this, reply]()
                {
                    if (reply->error() == QModbusDevice::ProtocolError)
                    {
                        qDebug() << QString("Write response error: %1 (Mobus exception: 0x%2)").arg(reply->errorString()).arg(reply->rawResult().exceptionCode(), -1, 16);
                    }
                    else if (reply->error() != QModbusDevice::NoError)
                    {
                        qDebug() << QString("Write response error: %1 (code: 0x%2)").
                            arg(reply->errorString()).arg(reply->error(), -1, 16);
                    }
                    reply->deleteLater();
                });
            }
            else
            {
                // broadcast replies return immediately
                reply->deleteLater();
            }
        }
        else
        {
            qDebug() << "Write error: " << modbusDevice->errorString();
        }
    }
}


QModbusDataUnit ModBus::readRequest(int reg_type,int address) const
{
    const auto table =
        static_cast<QModbusDataUnit::RegisterType> (reg_type);

    int startAddress = address;
    Q_ASSERT(startAddress >= 0 && startAddress < 10);

    // do not go beyond 10 entries
    int numberOfEntries = NUMBER_OF_ENTRIES;
    return QModbusDataUnit(table, startAddress, numberOfEntries);
}

QModbusDataUnit ModBus::writeRequest(int reg_type,int address) const
{
    const auto table =
        static_cast<QModbusDataUnit::RegisterType> (reg_type);

    int startAddress = address;
    Q_ASSERT(startAddress >= 0 && startAddress < 10);

    // do not go beyond 10 entries
    int numberOfEntries = NUMBER_OF_ENTRIES;
    return QModbusDataUnit(table, startAddress, numberOfEntries);
}
