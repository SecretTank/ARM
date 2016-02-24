#include <QtWidgets>
#include <QtNetwork>

#include "dialog.h"
#include <QDebug>


static const int TotalBytes = 50 * 1024 * 1024;
static const int PayloadSize = 64 * 1024; // 64 KB

Dialog::Dialog(QWidget *parent)
    : QMainWindow(parent)
{
    serverProgressBar = new QProgressBar;
    serverStatusLabel = new QLabel(tr("Server ready"));
    result = new QLabel("bib bib bib!");
    startButton = new QPushButton(tr("&Start"));
    quitButton = new QPushButton(tr("&Quit"));
    sendButton=new QPushButton(tr("&send"));
    sendtext=new QLineEdit();
    buttonBox = new QDialogButtonBox;
    buttonBox->addButton(startButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);

    connect(startButton, SIGNAL(clicked()), this, SLOT(start()));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(sendButton, SIGNAL(clicked()), this, SLOT(send()));
    connect(&tcpServer, SIGNAL(newConnection()),
            this, SLOT(acceptConnection()));
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(serverProgressBar);
    mainLayout->addWidget(serverStatusLabel);
    sendButton->setEnabled(false);
    mainLayout->addWidget(result);
    //mainLayout->addStretch(1);
    //mainLayout->addSpacing(10);
    mainLayout->addWidget(buttonBox);
    mainLayout->addWidget(sendButton);
    mainLayout->addWidget(sendtext);
    mainWidget = new QWidget;
    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);

    setWindowTitle(tr("Loopback"));
}

void Dialog::start()
{
    startButton->setEnabled(false);

#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif

    bytesReceived = 0;

    //find local IP address
    QHostAddress server_ip;
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
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

void Dialog::acceptConnection()
{
    tcpServerConnection = tcpServer.nextPendingConnection();
    connect(tcpServerConnection, SIGNAL(readyRead()),
            this, SLOT(updateServerProgress()));
    connect(tcpServerConnection, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));

    serverStatusLabel->setText(tr("Accepted connection"));
    sendButton->setEnabled(true);
    tcpServer.close();
}

void Dialog::send(){
    QString text=sendtext->text();
    tcpServerConnection->write(text.toUtf8().data(),15);
}
void Dialog::send(QString message){
    tcpServerConnection->write(message.toUtf8().data(),15);
}
void Dialog::updateServerProgress()
{
    char recievedBytes[100];
    qDebug() << "tcpServerConnection->bytesAvailable()";
    bytesReceived += (int)tcpServerConnection->bytesAvailable();
    strcpy(recievedBytes ,tcpServerConnection->readAll().data());
    send("HELLO World)");
    //int length = tcpServerConnection->read(recievedBytes,tcpServerConnection->bytesAvailable());
    qDebug() << recievedBytes << " " ;//<< length;
    result->setText(tr(recievedBytes));
    serverProgressBar->setMaximum(100);
    serverProgressBar->setValue(bytesReceived);
    serverStatusLabel->setText(tr("Received %1char").arg(bytesReceived));
    startButton->setEnabled(true);
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

}

void Dialog::displayError(QAbstractSocket::SocketError socketError)
{
    if (socketError == QTcpSocket::RemoteHostClosedError)
        return;

    tcpServer.close();
    serverProgressBar->reset();
    serverStatusLabel->setText(tr("Server ready"));
    startButton->setEnabled(true);
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif
}
