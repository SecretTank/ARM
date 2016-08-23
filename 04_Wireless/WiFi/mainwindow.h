#ifndef DIALOG_H
#define DIALOG_H

#include <QString>
#include <QDialog>
#include <QTcpServer>
#include <QTcpSocket>
#include <QLineEdit>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QLabel;
class QProgressBar;
class QPushButton;
class QTcpServer;
class QTcpSocket;
class QAction;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

public slots:
    void start();
    void acceptConnection();
    void updateServerProgress();
    void displayError(QAbstractSocket::SocketError socketError);
    void send();
    void send(QString message);

private:
    QProgressBar *serverProgressBar;
    QLabel *serverStatusLabel;
    QLabel *result;
    QPushButton *startButton;
    QPushButton *sendButton;
    QPushButton *quitButton;
    QDialogButtonBox *buttonBox;
    QLineEdit *sendtext;
    QTcpServer tcpServer;
    QTcpSocket *tcpServerConnection;
    int bytesReceived;
    QWidget *mainWidget;
};

#endif
