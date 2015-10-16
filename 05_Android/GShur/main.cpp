#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QDeclarativeView view(QUrl::fromLocalFile("qrc:/main.qml"));
    QObject *item = view.rootObject();

    Transs myClass;
    QObject::connect(item, SIGNAL(qmlSignal(QString)),
                     &myClass, SLOT(cppSlot(QString)));

    view.show();
    return app.exec();
}
