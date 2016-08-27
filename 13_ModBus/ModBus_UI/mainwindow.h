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
#include <QComboBox>
#include <QHBoxLayout>

enum OperatorState {
    INPUT_REGISER,
    READ_HOLDING_REGISTER,
    WRITE_HOLDING_REGISTER,
    DISCRETE_INPUT,
    READ_COIL,
    WRITE_COIL
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

public slots:
    void start();
    void acceptConnection();
    void displayError(QAbstractSocket::SocketError socketError);
    void dataReady();
    void onChangeOperator(int id);

private:
    QLabel *statusLabel;
    QLabel *ipLabel;
    QLabel *portLabel;
    QLineEdit *ipText;
    QLineEdit *portText;
    QLabel *operatorLabel;
    QComboBox *operatorComboBox;
    QLabel *inputLabel;
    QLineEdit *inputText;
    QLabel *addressLabel;
    QLineEdit *addressText;

    QHBoxLayout *ipLayout;
    QHBoxLayout *operatorLayout;
    QHBoxLayout *inputLayout;
    QHBoxLayout *addressLayout;


    QPushButton *startButton;
    QPushButton *quitButton;
    QDialogButtonBox *buttonBox;
    QLineEdit *sendtext;
    QTcpSocket tcpClient;
    QWidget *mainWidget;

    bool isConnected;
    OperatorState state;
};

#endif
