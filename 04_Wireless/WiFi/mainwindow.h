#ifndef DIALOG_H
#define DIALOG_H

#include <QString>
#include <QDialog>
#include <QTcpServer>
#include <QTcpSocket>
#include <QLineEdit>
#include <QMainWindow>
#include <QDialogButtonBox>
#include <QLabel>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

public slots:
    void start();
    void acceptConnection();
    void displayError(QAbstractSocket::SocketError socketError);
    void send(QString message);

private:
    QLabel *serverStatusLabel;
    QLabel *result;
    QPushButton *startButton;
    QPushButton *sendButton;
    QPushButton *quitButton;
    QDialogButtonBox *buttonBox;
    QLineEdit *sendtext;
    QLineEdit *ipText;
    QTcpServer tcpServer;
    QTcpSocket *tcpServerConnection;
    int bytesReceived;
    QWidget *mainWidget;
};

#endif
