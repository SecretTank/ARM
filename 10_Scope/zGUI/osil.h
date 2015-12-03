#ifndef OSIL_H
#define OSIL_H

#include <QMainWindow>
#include <QWidget>
#include <QtSerialPort/QSerialPort>
#include "line.h"


QT_BEGIN_NAMESPACE
class QLabel;
QT_END_NAMESPACE

//! [0]
class osil : public QWidget
{
    Q_OBJECT

public:
    osil();
    ~osil();
    int y[200];
private slots:
    void update_osil();
    void openSerialPort();
    void closeSerialPort();
    void readData();
private:
    int voltage;
    int x;
    QSerialPort* serial;
    int turn;
};


#endif // OSIL_H


