#include "transmission.h"

Transmission::Transmission(QObject *parent) : QObject(parent)
{

}

void Transmission::morabaaSlot()
{
    qDebug() << "morabaa";
}

void Transmission::mosalasSlot()
{
    qDebug() << "mosalas";
}

void Transmission::dayereSlot()
{
    qDebug() << "dayere";
}

void Transmission::zarbdarSlot()
{
    qDebug() << "zarbdar";
}
