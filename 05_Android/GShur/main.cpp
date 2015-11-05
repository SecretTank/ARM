#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <transmission.h>
#include <QQuickView>
#include <QQuickItem>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    QObject *item = engine.rootObjects().first();

    Transmission channel;
    QObject::connect(item, SIGNAL(morabaSignal()), &channel, SLOT(morabaaSlot()));
    QObject::connect(item, SIGNAL(mosalasSignal()), &channel, SLOT(mosalasSlot()));
    QObject::connect(item, SIGNAL(dayereSignal()), &channel, SLOT(dayereSlot()));
    QObject::connect(item, SIGNAL(zarbdarSignal()), &channel, SLOT(zarbdarSlot()));
    QObject::connect(item, SIGNAL(startSignal(QString)), &channel, SLOT(start(QString)));

    return app.exec();
}

