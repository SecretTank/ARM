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

    Transmission myClass;
    QObject::connect(item, SIGNAL(morabaSignal()), &myClass, SLOT(morabaaSlot()));
    QObject::connect(item, SIGNAL(mosalasSignal()), &myClass, SLOT(mosalasSlot()));
    QObject::connect(item, SIGNAL(dayereSignal()), &myClass, SLOT(dayereSlot()));
    QObject::connect(item, SIGNAL(zarbdarSignal()), &myClass, SLOT(zarbdarSlot()));

    return app.exec();
}
