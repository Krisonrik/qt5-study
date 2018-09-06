// Copyright 2018 Qi Yao

#ifndef MODULES_BLOCKINGCLIENT_INCLUDE_HVR_BLOCKINGFORTUNECLIENT_FORTUNETHREAD_H_
#define MODULES_BLOCKINGCLIENT_INCLUDE_HVR_BLOCKINGFORTUNECLIENT_FORTUNETHREAD_H_

HVR_WINDOWS_DISABLE_ALL_WARNING
#include <QMutex>
#include <QThread>
#include <QWaitCondition>

HVR_WINDOWS_ENABLE_ALL_WARNING

namespace hvr
{
/**
 * @brief      Minimal class
 *
 * @ingroup    Sample
 * @author     Jason Juang
 * @attention  This is for internal use only, DO NOT distribute the code
 */
class FortuneThread : public QThread
{
  Q_OBJECT

 public:
  BLOCKING_CLIENT_DLL
  explicit FortuneThread(QObject *parent = 0);

  BLOCKING_CLIENT_DLL
  ~FortuneThread();

  BLOCKING_CLIENT_DLL
  void requestNewFortune(const QString &hostName, quint16 port);

  BLOCKING_CLIENT_DLL
  void run() override;

 signals:
  void newFortune(const QString &fortune);
  void error(int socketError, const QString &message);

 private:
  QString host_nam_;
  quint16 port_;
  QMutex mtx_;
  QWaitCondition cond_;
  bool quit_;
};
}  // namespace hvr

#endif  // MODULES_BLOCKINGCLIENT_INCLUDE_HVR_BLOCKINGFORTUNECLIENT_FORTUNETHREAD_H_
