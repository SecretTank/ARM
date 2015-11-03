#ifndef CLIENT_H
#define CLIENT_H

#include <QDialog>
#include "transmission.h"
#include <QObject>
#include <QtWidgets>

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QLabel;
class QPushButton;
class QAction;
class QLineEdit;
QT_END_NAMESPACE

class client : public QMainWindow
{
    Q_OBJECT
public:
    client(QWidget *parent=0);
    ~client();
public slots:
    void start();
private:
    QLabel *clientStatusLabel;
    Transmission* transmitter;
    QPushButton *startButton;
    QPushButton *quitButton;
    QPushButton *z;
    QPushButton *d;
    QPushButton *mos;
    QPushButton *mor;
    QDialogButtonBox *buttonBox;
    QLineEdit *ip_text;
    QLabel *ip_label;
    QHBoxLayout *ipLayout;
    QHBoxLayout *controlBox;
    QVBoxLayout *mainLayout;
    QWidget *mainWidget;
};

#endif // CLIENT_H
