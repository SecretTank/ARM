#ifndef OSIL_H
#define OSIL_H

#include <QMainWindow>
#include <QWidget>
#include <QtSerialPort/QSerialPort>


QT_BEGIN_NAMESPACE
class QLabel;
QT_END_NAMESPACE
class RenderArea;

//! [0]
class osil : public QWidget
{
    Q_OBJECT

public:
    osil();
    ~osil();
private slots:
    void update_osil();
    void openSerialPort();
    void closeSerialPort();
    void readData();
private:
    RenderArea *renderArea;
    int voltage;
    QVector<int> y;
    int x;
    QSerialPort* serial;
    QLabel* status;
    int turn;
};


#endif // OSIL_H


