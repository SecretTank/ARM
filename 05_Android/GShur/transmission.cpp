#include "transmission.h"
#include <string.h>

Transmission::Transmission(QObject *parent) : QObject(parent)
{
    connect(&tcpClient, SIGNAL(connected()), this, SLOT(connected()));
    connect(&tcpClient, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));
}

void Transmission::morabaaSlot()
{
    if(stack.size() == 1)
        return;
    stack.push_back("morabaa");
    code = 0xff0;
    //startTransfer(stack.toUtf8().data());
}

void Transmission::mosalasSlot()
{
    switch(stack.size()){
    case 0:
        code = 0xf1f;
        itoa(code,code_char,4);
        startTransfer(code_char);
        code = 0xfff;
        break;
    case 1:
        stack.push_back("mosalas");
        code = code - 0x0e0;
        break;
    case 2:
        code = code - 0xe00;
        itoa(code,code_char,4);
        startTransfer(code_char);
        stack.pop_back();
        stack.pop_back();
        code = 0xfff;
        break;
    default:
        code = 0xf1f;
        itoa(code,code_char,4);
        startTransfer(code_char);
        code = 0xfff;
        break;
    }
}

void Transmission::dayereSlot()
{
    switch(stack.size()){
    case 0:
        code = 0xf2f;
        itoa(code,code_char,4);
        startTransfer(code_char);
        code = 0xfff;
        break;
    case 1:
        stack.push_back("dayere");
        code = code - 0x0d0;
        break;
    case 2:
        code = code - 0xd00;
        itoa(code,code_char,4);
        startTransfer(code_char);
        stack.pop_back();
        stack.pop_back();
        code = 0xfff;
        break;
    default:
        code = 0xf2f;
        itoa(code,code_char,4);
        startTransfer(code_char);
        code = 0xfff;
        break;
    }
    }
}

void Transmission::zarbdarSlot()
{
    switch(stack.size()){
    case 0:
        code = 0xf3f;
        itoa(code,code_char,4);
        startTransfer(code_char);
        code = 0xfff;
        break;
    case 1:
        stack.push_back("zarbdar");
        code = code - 0x0c0;
        break;
    case 2:
        code = code - 0xc00;
        itoa(code,code_char,4);
        startTransfer(code_char);
        stack.pop_back();
        stack.pop_back();
        code = 0xfff;
        break;
    default:
        code = 0xf3f;
        itoa(code,code_char,4);
        startTransfer(code_char);
        code = 0xfff;
        break;
    }
}

Transmission::~Transmission()
{
    tcpClient.close();
}

void Transmission::startTransfer(char* command)
{
    int bytesToWrite = tcpClient.write(command);
    qDebug() << bytesToWrite;
}

void Transmission::displayError(QAbstractSocket::SocketError socketError)
{
    if (socketError == QTcpSocket::RemoteHostClosedError)
        return;

    qDebug() << tr("Network error") << tr("The following error occurred: %1.").arg(tcpClient.errorString());
    tcpClient.close();
    emit errorConnection();

}

void Transmission::connected()
{
    qDebug() << "connected";
}

void Transmission::start(QString IP)
{
    tcpClient.connectToHost(QHostAddress(IP), 7778 );
    qDebug() << "connecting to " << IP;
}
