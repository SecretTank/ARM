#include "client.h"

client::client(QWidget *parent)
    : QMainWindow(parent)
{
    clientStatusLabel = new QLabel(tr("Client ready"));
    startButton = new QPushButton(tr("&Start"));
    stopButton = new QPushButton(tr("&Quit"));
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
    buttonBox->addButton(stopButton, QDialogButtonBox::RejectRole);


    connect(stopButton, SIGNAL(clicked()), this, SLOT(stop()));
    connect(startButton,SIGNAL(clicked()),this,SLOT(start()));

    controlBox = new QHBoxLayout;
    ipLayout  = new QHBoxLayout;
    mainLayout = new QVBoxLayout;

    //IP Input
    ip_text = new QLineEdit ("192.168.88.24");
    ip_label = new QLabel();
    ip_label->setText("IP: ");
    ipLayout->addWidget(ip_label);
    ipLayout->addWidget(ip_text);


    controlBox->addWidget(z);
    controlBox->addWidget(d);
    controlBox->addWidget(mos);
    controlBox->addWidget(mor);
    mainLayout->addWidget(clientStatusLabel);
    mainLayout->addStretch(1);
    mainLayout->addSpacing(10);
    mainLayout->addLayout(ipLayout);
    mainLayout->addLayout(controlBox);
    mainLayout->addWidget(buttonBox);

    mainWidget = new QWidget;
    mainWidget->setLayout(mainLayout);

    setCentralWidget(mainWidget);
    setWindowTitle(tr("Loopback"));

}

void client::start()
{
    startButton->setEnabled(false);
    clientStatusLabel->setText(tr("Connecting"));
    transmitter = new Transmission(ip_text->text());
    mos->setEnabled(true);
    mor->setEnabled(true);
    z->setEnabled(true);
    d->setEnabled(true);
    connect(mos,SIGNAL(clicked()),transmitter,SLOT(mosalasSlot()));
    connect(z,SIGNAL(clicked()),transmitter,SLOT(zarbdarSlot()));
    connect(mor,SIGNAL(clicked()),transmitter,SLOT(morabaaSlot()));
    connect(d,SIGNAL(clicked()),transmitter,SLOT(dayereSlot()));
    connect(transmitter,SIGNAL(errorConnection()),this,SLOT(stop()));
}

void client::stop()
{
    startButton->setEnabled(true);
    mos->setEnabled(false);
    mor->setEnabled(false);
    z->setEnabled(false);
    d->setEnabled(false);
}

client::~client()
{
    delete transmitter;
}
