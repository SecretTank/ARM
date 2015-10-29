#include <QtWidgets>
#include "client.h"

client::client(QWidget *parent)
    : QDialog(parent)
{
    clientStatusLabel = new QLabel(tr("Client ready"));
    startButton = new QPushButton(tr("&Start"));
    quitButton = new QPushButton(tr("&Quit"));
    z = new QPushButton(tr("z"));
    z->setEnabled(false);
    d = new QPushButton(tr("d"));
    d->setEnabled(false);
    mor = new QPushButton(tr("mor"));
    mor->setEnabled(false);
    mos = new QPushButton(tr("mos"));
    mos->setEnabled(false);
    buttonBox = new QDialogButtonBox;
    buttonBox->addButton(startButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);

    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(startButton,SIGNAL(clicked()),this,SLOT(start()));

    QHBoxLayout *controlBox = new QHBoxLayout;
    QVBoxLayout *mainLayout = new QVBoxLayout;
    controlBox->addWidget(z);
    controlBox->addWidget(d);
    controlBox->addWidget(mos);
    controlBox->addWidget(mor);
    mainLayout->addWidget(clientStatusLabel);
    mainLayout->addStretch(1);
    mainLayout->addSpacing(10);
    mainLayout->addLayout(controlBox);
    mainLayout->addWidget(buttonBox);

    setLayout(mainLayout);
    setWindowTitle(tr("Loopback"));

}

void client::start()
{
    startButton->setEnabled(false);
    clientStatusLabel->setText(tr("Connecting"));
    transmitter = new Transmission();
    mos->setEnabled(true);
    mor->setEnabled(true);
    z->setEnabled(true);
    d->setEnabled(true);
    connect(mos,SIGNAL(clicked()),transmitter,SLOT(mosalasSlot()));
    connect(z,SIGNAL(clicked()),transmitter,SLOT(zarbdarSlot()));
    connect(mor,SIGNAL(clicked()),transmitter,SLOT(morabaaSlot()));
    connect(d,SIGNAL(clicked()),transmitter,SLOT(dayereSlot()));
}

client::~client()
{
    delete transmitter;
}
