// Copyright 2018 Qi Yao
HVR_WINDOWS_DISABLE_ALL_WARNING
#include <QApplication>
#include <QCommandLineOption>
#include <QCommandLineParser>

// #include <iostream>
HVR_WINDOWS_ENABLE_ALL_WARNING

#include "Hvr/SaveStream_UI/MainWindow.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  Q_INIT_RESOURCE(savestream);
  hvr::MainWindow mainWin;
  mainWin.show();
  return app.exec();
}
