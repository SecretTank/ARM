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
    QObject *item = engine.rootObjects().at(0);

    Transmission myClass;
    QObject::connect(item, SIGNAL(qmlSignal(QString)),
                     &myClass, SLOT(cppSlot(QString)));

    return app.exec();
}
