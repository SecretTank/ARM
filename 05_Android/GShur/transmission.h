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
    void morabaaSlot();
    void mosalasSlot();
    void dayereSlot();
    void zarbdarSlot();
};

#endif // TRANSMISSION_H
