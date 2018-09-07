// Copyright 2018 Qi Yao

#ifndef MODULES_RECEIVER_INCLUDE_HVR_BROADCASTRECEIVER_RECEIVER_H_
#define MODULES_RECEIVER_INCLUDE_HVR_BROADCASTRECEIVER_RECEIVER_H_

HVR_WINDOWS_DISABLE_ALL_WARNING
#include <QWidget>
HVR_WINDOWS_ENABLE_ALL_WARNING
class QLabel;
class QUdpSocket;
namespace hvr
{
/**
 * @brief      Minimal class
 *
 * @ingroup    Sample
 * @author     Jason Juang
 * @attention  This is for internal use only, DO NOT distribute the code
 */
class Receiver : public QWidget
{
  Q_OBJECT

 public:
  RECEIVER_DLL
  explicit Receiver(QWidget *parent = nullptr);

 private slots:  // NOLINT
  void processPendingDatagrams();

 private:
  QLabel *statusLabel   = nullptr;
  QUdpSocket *udpSocket = nullptr;
};
}  // namespace hvr

#endif  // MODULES_RECEIVER_INCLUDE_HVR_BROADCASTRECEIVER_RECEIVER_H_
