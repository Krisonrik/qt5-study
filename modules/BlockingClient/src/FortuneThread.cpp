// Copyright 2018 Qi Yao

#include "Hvr/BlockingFortuneClient/FortuneThread.h"

HVR_WINDOWS_DISABLE_ALL_WARNING
#include <QtNetwork>
HVR_WINDOWS_ENABLE_ALL_WARNING

namespace hvr
{
FortuneThread::FortuneThread(QObject *parent) : QThread(parent), quit_(false)
{
}

FortuneThread::~FortuneThread()
{
  mtx_.lock();
  quit_ = true;
  cond_.wakeOne();
  mtx_.unlock();
  wait();
}

void FortuneThread::requestNewFortune(const QString &hostName, quint16 port)
{
  QMutexLocker locker(&mtx_);
  this->host_nam_ = hostName;
  this->port_     = port;
  if (!isRunning())
    start();
  else
    cond_.wakeOne();
}

void FortuneThread::run()
{
  mtx_.lock();
  QString serverName = host_nam_;
  quint16 serverPort = port_;
  mtx_.unlock();

  while (!quit_)
  {
    const int Timeout = 5 * 1000;

    QTcpSocket socket;
    socket.connectToHost(serverName, serverPort);

    if (!socket.waitForConnected(Timeout))
    {
      emit error(socket.error(), socket.errorString());
      return;
    }

    QDataStream in(&socket);
    in.setVersion(QDataStream::Qt_4_0);
    QString fortune;

    do
    {
      if (!socket.waitForReadyRead(Timeout))
      {
        emit error(socket.error(), socket.errorString());
        return;
      }

      in.startTransaction();
      in >> fortune;
    } while (!in.commitTransaction());

    mtx_.lock();
    emit newFortune(fortune);

    cond_.wait(&mtx_);
    serverName = host_nam_;
    serverPort = port_;
    mtx_.unlock();
  }
}
}  // namespace hvr
