// Copyright 2018 Qi Yao
HVR_WINDOWS_DISABLE_ALL_WARNING
#include <QApplication>
#include <QCommandLineOption>
#include <QCommandLineParser>

// #include <iostream>
HVR_WINDOWS_ENABLE_ALL_WARNING

#include <QApplication>

#include "Hvr/BlockingFortuneClient/BlockingClient.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  hvr::BlockingClient client;
  client.show();
  return app.exec();
}
