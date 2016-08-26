#include <QtWidgets>
#include <QtNetwork>

#include "mainwindow.h"
#include <QDebug>


static const int TotalBytes = 50 * 1024 * 1024;
static const int PayloadSize = 64 * 1024; // 64 KB

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    serverStatusLabel = new QLabel(tr("Server ready"));
    result = new QLabel("Waiting for command");
    startButton = new QPushButton(tr("&Start"));
    quitButton = new QPushButton(tr("&Quit"));
    sendButton=new QPushButton(tr("&send"));
    sendtext=new QLineEdit;
    ipText = new QLineEdit;
    buttonBox = new QDialogButtonBox;
    buttonBox->addButton(startButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);

    connect(startButton, SIGNAL(clicked()), this, SLOT(start()));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(&tcpServer, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(serverStatusLabel);
    sendButton->setEnabled(false);
    mainLayout->addWidget(result);
    mainLayout->addWidget(buttonBox);
    mainLayout->addWidget(sendButton);
    mainLayout->addWidget(sendtext);
    mainWidget = new QWidget;
    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);

    setWindowTitle(tr("Loopback"));
}

void MainWindow::start()
{
    startButton->setEnabled(false);
    bytesReceived = 0;

    //find local IP address
    QHostAddress server_ip;
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses())
    {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
        {
            server_ip = address;
            break;
        }
    }
    //we just not used QHostAddress::LocalHost as it's not work cross platform
    while (!tcpServer.isListening() && !tcpServer.listen(server_ip, 7778 )) {
        QMessageBox::StandardButton ret = QMessageBox::critical(this,
                                        tr("Loopback"),
                                        tr("Unable to start the test: %1.")
                                        .arg(tcpServer.errorString()),
                                        QMessageBox::Retry
                                        | QMessageBox::Cancel);
        if (ret == QMessageBox::Cancel)
        {
            startButton->setEnabled(true);
            return;
        }
    }
    serverStatusLabel->setText(tr("%1.").arg(tcpServer.serverPort()));
}

void MainWindow::acceptConnection()
{
    tcpServerConnection = tcpServer.nextPendingConnection();
    connect(tcpServerConnection, SIGNAL(readyRead()), this, SLOT(updateServerProgress()));
    connect(tcpServerConnection, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));

    serverStatusLabel->setText(tr("Accepted connection"));
    sendButton->setEnabled(true);
    tcpServer.close();
}

void MainWindow::send(QString message)
{
    tcpServerConnection->write(message.toUtf8().data(),15);
}

void MainWindow::displayError(QAbstractSocket::SocketError socketError)
{
    if (socketError == QTcpSocket::RemoteHostClosedError)
        return;

    tcpServer.close();
    serverStatusLabel->setText(tr("Server ready"));
    startButton->setEnabled(true);
}
