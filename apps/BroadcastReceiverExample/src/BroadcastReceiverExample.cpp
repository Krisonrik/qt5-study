// Copyright 2018 Qi Yao
HVR_WINDOWS_DISABLE_ALL_WARNING
#include <QApplication>
HVR_WINDOWS_ENABLE_ALL_WARNING
#include "Hvr/BroadcastReceiver/Receiver.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  hvr::Receiver receiver;
  receiver.show();
  return app.exec();
}
