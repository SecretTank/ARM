#ifndef OSIL_H
#define OSIL_H

#include "define.h"
#include <QWidget>
#include <QtSerialPort/QSerialPort>

class osil : public QObject
{
    Q_OBJECT

public:
    osil(oscope_data *data);
    ~osil();
    bool openSerialPort();
    void closeSerialPort();

private slots:
    void readData();
private:
    oscope_data *adc_data;
    QSerialPort* serial;
    int turn;
    int x;
};


#endif // OSIL_H


