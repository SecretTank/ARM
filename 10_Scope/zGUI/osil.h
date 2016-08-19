#ifndef OSIL_H
#define OSIL_H

#include <QMainWindow>
#include <QWidget>
#include <QtSerialPort/QSerialPort>

class osil : public QObject
{
    Q_OBJECT

public:
    osil(QVector<int> *data);
    ~osil();
    bool openSerialPort();
    void closeSerialPort();

    QVector<int> *adc_data;
private slots:
    void readData();
private:
    int voltage;
    QSerialPort* serial;
    int turn;
    int x;
};


#endif // OSIL_H


