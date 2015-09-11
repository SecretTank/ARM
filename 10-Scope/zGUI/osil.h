#ifndef OSIL_H
#define OSIL_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <unistd.h>
#include <QtSerialPort/QSerialPort>


QT_BEGIN_NAMESPACE
class QCheckBox;
class QComboBox;
class QLabel;
class QSpinBox;
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
    void shapeChanged();
    void brushChanged();
    void update_osil();
    void openSerialPort();
    void closeSerialPort();
    void readData();
private:
    RenderArea *renderArea;
    QLabel *shapeLabel;
    QComboBox *shapeComboBox;
    int voltage;
    QVector<int> y;
    QSerialPort* serial;
    QLabel* status;
    int turn;
};


#endif // OSIL_H


