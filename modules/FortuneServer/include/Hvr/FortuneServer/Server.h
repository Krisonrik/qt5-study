// Copyright 2018 Qi Yao

#ifndef MODULES_FORTUNESERVER_INCLUDE_HVR_FORTUNESERVER_SERVER_H_
#define MODULES_FORTUNESERVER_INCLUDE_HVR_FORTUNESERVER_SERVER_H_

HVR_WINDOWS_DISABLE_ALL_WARNING
#include <QDialog>
#include <QString>
#include <QVector>

HVR_WINDOWS_ENABLE_ALL_WARNING
class QLabel;
class QTcpServer;
class QNetworkSession;
namespace hvr
{
class Server : public QDialog
{
  Q_OBJECT

 public:
  explicit Server(QWidget *parent = nullptr);

 private slots:  // NOLINT
  void sessionOpened();
  void sendFortune();

 private:
  QLabel *statusLabel   = nullptr;
  QTcpServer *tcpServer = nullptr;
  QVector<QString> fortunes;
  QNetworkSession *networkSession = nullptr;
};

}  // namespace hvr

#endif  // MODULES_FORTUNESERVER_INCLUDE_HVR_FORTUNESERVER_SERVER_H_
