#ifndef TRANSMISSION_H
#define TRANSMISSION_H

#include <QObject>
#include <QDebug>

class Transmission : public QObject
{
    Q_OBJECT
public:
    explicit Transmission(QObject *parent = 0);

signals:

public slots:
    void cppSlot(const QString &msg) {
        qDebug() << "Called the C++ slot with message:" << msg;
    }
};

#endif // TRANSMISSION_H
