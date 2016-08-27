#include <QtWidgets>
#include <QtNetwork>

#include "mainwindow.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    statusLabel = new QLabel("Waiting for command");
    startButton = new QPushButton("Start");
    quitButton = new QPushButton("Quit");
    ipText = new QLineEdit("172.16.156.78");\
    ipLabel = new QLabel("IP: ");
    portLabel = new QLabel(":");
    portText = new QLineEdit("7778");
    operatorLabel = new QLabel("Operator: ");
    operatorComboBox = new QComboBox;
    addressLabel = new QLabel("Address: ");
    addressText = new QLineEdit;
    inputLabel = new QLabel("Input: ");
    inputText = new QLineEdit;
    inputText->setEnabled(false);

    //comboBox
    operatorComboBox->addItem("Input Register");
    operatorComboBox->addItem("Read Holding Register");
    operatorComboBox->addItem("Write Holding Register");
    operatorComboBox->addItem("Discrete Input");
    operatorComboBox->addItem("Read Coil");
    operatorComboBox->addItem("Write Coil");


    //layout
    ipLayout = new QHBoxLayout;
    operatorLayout = new QHBoxLayout;
    inputLayout = new QHBoxLayout;
    addressLayout = new QHBoxLayout;

    ipLayout->addWidget(ipLabel);
    ipLayout->addWidget(ipText);
    ipLayout->addWidget(portLabel);
    ipLayout->addWidget(portText);

    operatorLayout->addWidget(operatorLabel);
    operatorLayout->addWidget(operatorComboBox);

    inputLayout->addWidget(inputLabel);
    inputLayout->addWidget(inputText);

    addressLayout->addWidget(addressLabel);
    addressLayout->addWidget(addressText);

    sendtext=new QLineEdit;
    buttonBox = new QDialogButtonBox;
    buttonBox->addButton(startButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);

    //connect
    connect(startButton, SIGNAL(clicked()), this, SLOT(start()));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(&tcpClient, SIGNAL(connected()), this, SLOT(acceptConnection()));
    connect(&tcpClient, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));
    connect(operatorComboBox,SIGNAL(activated(int)),this, SLOT(onChangeOperator(int)));

    //mainLayout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(ipLayout);
    mainLayout->addLayout(operatorLayout);
    mainLayout->addLayout(addressLayout);
    mainLayout->addLayout(inputLayout);
    mainLayout->addWidget(statusLabel);
    mainLayout->addWidget(buttonBox);
    mainWidget = new QWidget;
    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);

    setWindowTitle("ModBus UI");
}

void MainWindow::start()
{
    if (!isConnected)
    {
        startButton->setEnabled(false);
        tcpClient.connectToHost(ipText->text(), portText->text().toInt());
    }
    else //send
    {
        QString command = QString("%1,%2,%3").arg(QString::number(state),inputText->text(),addressText->text());
        char *message = command.toUtf8().data();
        tcpClient.write(message,command.length());
    }
}

void MainWindow::acceptConnection()
{
    connect(&tcpClient, SIGNAL(readyRead()), this, SLOT(dataReady()));

    statusLabel->setText("Connection Accepted");
    isConnected = true;
    startButton->setEnabled(true);
    startButton->setText("Send");
}

void MainWindow::displayError(QAbstractSocket::SocketError socketError)
{
    if (socketError == QTcpSocket::RemoteHostClosedError)
        return;

    isConnected = false;
    tcpClient.close();
    statusLabel->setText("Waiting for command");
    startButton->setEnabled(true);
    startButton->setText("Start");
}

void MainWindow::dataReady()
{
    statusLabel->setText(tcpClient.readAll());
}


void MainWindow::onChangeOperator(int id)
{
    state = static_cast<OperatorState>(id);
    switch (state)
    {
        case INPUT_REGISER:
            inputText->setEnabled(false);
            break;
        case READ_HOLDING_REGISTER:
            inputText->setEnabled(false);
            break;
        case WRITE_HOLDING_REGISTER:
            inputText->setEnabled(true);
            break;
        case DISCRETE_INPUT:
            inputText->setEnabled(false);
            break;
        case READ_COIL:
            inputText->setEnabled(false);
            break;
        case WRITE_COIL:
            inputText->setEnabled(true);
            break;
    }
}
