// Copyright 2018 Qi Yao

#ifndef MODULES_BLOCKINGCLIENT_INCLUDE_HVR_BLOCKINGFORTUNECLIENT_BLOCKINGCLIENT_H_
#define MODULES_BLOCKINGCLIENT_INCLUDE_HVR_BLOCKINGFORTUNECLIENT_BLOCKINGCLIENT_H_

HVR_WINDOWS_DISABLE_ALL_WARNING
#include <QWidget>

#include "Hvr/BlockingFortuneClient/FortuneThread.h"

HVR_WINDOWS_ENABLE_ALL_WARNING
class QDialogButtonBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QAction;
namespace hvr
{
/**
 * @brief      Minimal class
 *
 * @ingroup    Sample
 * @author     Jason Juang
 * @attention  This is for internal use only, DO NOT distribute the code
 */
class BlockingClient : public QWidget
{
  Q_OBJECT

 public:
  BLOCKING_CLIENT_DLL
  explicit BlockingClient(QWidget *parent = 0);

 private slots:  // NOLINT
  BLOCKING_CLIENT_DLL
  void requestNewFortune();

  BLOCKING_CLIENT_DLL
  void showFortune(const QString &fortune);

  BLOCKING_CLIENT_DLL
  void displayError(int socketError, const QString &message);

  BLOCKING_CLIENT_DLL
  void enableGetFortuneButton();

 private:
  QLabel *hostLabel;
  QLabel *portLabel;
  QLineEdit *hostLineEdit;
  QLineEdit *portLineEdit;
  QLabel *statusLabel;
  QPushButton *getFortuneButton;
  QPushButton *quitButton;
  QDialogButtonBox *buttonBox;

  FortuneThread thread;
  QString currentFortune;
};

}  // namespace hvr

#endif  // MODULES_BLOCKINGCLIENT_INCLUDE_HVR_BLOCKINGFORTUNECLIENT_BLOCKINGCLIENT_H_
