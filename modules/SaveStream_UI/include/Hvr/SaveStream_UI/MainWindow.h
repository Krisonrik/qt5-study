// Copyright 2018 Qi Yao

#ifndef MODULES_SAVESTREAM_UI_INCLUDE_HVR_SAVESTREAM_UI_MAINWINDOW_H_
#define MODULES_SAVESTREAM_UI_INCLUDE_HVR_SAVESTREAM_UI_MAINWINDOW_H_

HVR_WINDOWS_DISABLE_ALL_WARNING
#include <memory>
#include <thread>

#include "QtGui/QSessionManager.h"
#include "QtWidgets/qmainwindow.h"

HVR_WINDOWS_ENABLE_ALL_WARNING

class QMenu;

namespace hvr
{
class MainWindow : public QMainWindow
{
  Q_OBJECT

 public:
  SAVESTREAM_WIDGETS_DLL
  MainWindow();
  SAVESTREAM_WIDGETS_DLL
  ~MainWindow();

  SAVESTREAM_WIDGETS_DLL
  void StopThread();

 private Q_SLOTS:  // NOLINT

  SAVESTREAM_WIDGETS_DLL
  void OpenNamingXML();
  SAVESTREAM_WIDGETS_DLL
  void OpenConfigXML();
  SAVESTREAM_WIDGETS_DLL
  void about();

 Q_SIGNALS:
  void RefreshTrigger();

 private:
  void GlobalRefresh();
  void createActions();
  void createStatusBar();
  void createDockWindows();

  std::thread refresh_thrd_;

  QMenu *viewMenu;
};

}  // namespace hvr

#endif  // MODULES_SAVESTREAM_UI_INCLUDE_HVR_SAVESTREAM_UI_MAINWINDOW_H_
