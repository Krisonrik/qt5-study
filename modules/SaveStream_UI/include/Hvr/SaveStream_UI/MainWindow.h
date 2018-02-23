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
  void CreateStatWindow();
  void CreateSettingWindow();

  QPair<qint32, qint32> CamPanelPosition(qint32 index, qint32 total);

  std::thread refresh_thrd_;

  QDockWidget *stat_window_;
  QDockWidget *setting_window_;
  QDockWidget *ctrl_panel;
  QMenu *viewMenu;

  QVector<QPair<QString, QString>> ir_settings_;
  QVector<QPair<QString, QString>> rgb_settings_;
};

}  // namespace hvr

#endif  // MODULES_SAVESTREAM_UI_INCLUDE_HVR_SAVESTREAM_UI_MAINWINDOW_H_
