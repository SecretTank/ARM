#ifndef CLIENT_H
#define CLIENT_H

#include <QDialog>
#include "transmission.h"

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QLabel;
class QPushButton;
class QAction;
class QLineEdit;
QT_END_NAMESPACE

class client : public QDialog
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
};

#endif // CLIENT_H
