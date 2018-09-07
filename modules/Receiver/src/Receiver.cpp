// Copyright 2018 Qi Yao

#include "Hvr/BroadcastReceiver/Receiver.h"

HVR_WINDOWS_DISABLE_ALL_WARNING
#include <QtNetwork>
#include <QtWidgets>
HVR_WINDOWS_ENABLE_ALL_WARNING

namespace hvr
{
Receiver::Receiver(QWidget *parent) : QWidget(parent)
{
  statusLabel = new QLabel(tr("Listening for broadcasted messages"));
  statusLabel->setWordWrap(true);

  auto quitButton = new QPushButton(tr("&Quit"));

  udpSocket = new QUdpSocket(this);
  udpSocket->bind(45454, QUdpSocket::ShareAddress);

  connect(
      udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
  connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));

  auto buttonLayout = new QHBoxLayout;
  buttonLayout->addStretch(1);
  buttonLayout->addWidget(quitButton);
  buttonLayout->addStretch(1);

  auto mainLayout = new QVBoxLayout;
  mainLayout->addWidget(statusLabel);
  mainLayout->addLayout(buttonLayout);
  setLayout(mainLayout);

  setWindowTitle(tr("Broadcast Receiver"));
}

void Receiver::processPendingDatagrams()
{
  QByteArray datagram;
  while (udpSocket->hasPendingDatagrams())
  {
    datagram.resize(int(udpSocket->pendingDatagramSize()));
    udpSocket->readDatagram(datagram.data(), datagram.size());
    statusLabel->setText(
        tr("Received datagram: \"%1\"").arg(datagram.constData()));
  }
}
}  // namespace hvr
