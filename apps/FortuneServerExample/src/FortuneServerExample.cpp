// Copyright 2018 Qi Yao
HVR_WINDOWS_DISABLE_ALL_WARNING
#include <QApplication>
HVR_WINDOWS_ENABLE_ALL_WARNING
#include "Hvr/FortuneServer/Server.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  QApplication::setApplicationDisplayName(hvr::Server::tr("Fortune Server"));
  hvr::Server server;
  server.show();
  return app.exec();
}
