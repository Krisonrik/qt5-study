// Copyright 2018 Qi Yao

#ifndef MODULES_SAVESTREAM_UI_INCLUDE_HVR_SAVESTREAM_UI_MAINWINDOW_H_
#define MODULES_SAVESTREAM_UI_INCLUDE_HVR_SAVESTREAM_UI_MAINWINDOW_H_

HVR_WINDOWS_DISABLE_ALL_WARNING
#include <memory>

#include "QtGui/QSessionManager.h"
#include "QtWidgets/qmainwindow.h"

HVR_WINDOWS_ENABLE_ALL_WARNING

class QTextEdit;
class QListWidget;
class QMenu;

namespace hvr
{
class MainWindow : public QMainWindow
{
  Q_OBJECT

 public:
  SAVESTREAM_WIDGETS_DLL
  MainWindow();

 private Q_SLOTS:  // NOLINT

  SAVESTREAM_WIDGETS_DLL
  void OpenNamingXML();
  SAVESTREAM_WIDGETS_DLL
  void OpenConfigXML();
  SAVESTREAM_WIDGETS_DLL
  void about();

 private:
  void createActions();
  void createStatusBar();
  void createDockWindows();

  QListWidget *customerList;
  QListWidget *paragraphsList;
  QMenu *viewMenu;
};

}  // namespace hvr

#endif  // MODULES_SAVESTREAM_UI_INCLUDE_HVR_SAVESTREAM_UI_MAINWINDOW_H_
