// Copyright 2018 Qi Yao
HVR_WINDOWS_DISABLE_ALL_WARNING
#include <QApplication>
#include <QCommandLineOption>
#include <QCommandLineParser>

// #include <iostream>
HVR_WINDOWS_ENABLE_ALL_WARNING

#include "Hvr/MainWindow/MainWindow.h"

int main(int argc, char *argv[])
{
  Q_INIT_RESOURCE(application);

  QApplication app(argc, argv);
  QCoreApplication::setOrganizationName("QtProject");
  QCoreApplication::setApplicationName("Application Example");
  QCoreApplication::setApplicationVersion(QT_VERSION_STR);
  QCommandLineParser parser;
  parser.setApplicationDescription(QCoreApplication::applicationName());
  parser.addHelpOption();
  parser.addVersionOption();
  parser.addPositionalArgument("file", "The file to open.");
  parser.process(app);

  hvr::MainWindow mainWin;
  if (!parser.positionalArguments().isEmpty())
  {
    mainWin.loadFile(parser.positionalArguments().first());
  }
  mainWin.show();
  return app.exec();
}
