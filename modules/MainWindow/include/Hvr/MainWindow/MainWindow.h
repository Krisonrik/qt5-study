// Copyright 2015 Jason Juang

#ifndef MODULES_MAINWINDOW_INCLUDE_HVR_MAINWINDOW_MAINWINDOW_H_
#define MODULES_MAINWINDOW_INCLUDE_HVR_MAINWINDOW_MAINWINDOW_H_

HVR_WINDOWS_DISABLE_ALL_WARNING
#include <memory>

#include "QtGui/QSessionManager.h"
#include "QtWidgets/qmainwindow.h"
#include "QtWidgets/qplaintextedit.h"

HVR_WINDOWS_ENABLE_ALL_WARNING

namespace hvr
{
/**
 * @brief      Minimal class
 *
 * @ingroup    Sample
 * @author     Jason Juang
 * @attention  This is for internal use only, DO NOT distribute the code
 */
class MainWindow : public QMainWindow
{
  Q_OBJECT

 public:
  HVR_SAMPLE_DLL
  MainWindow();

  HVR_SAMPLE_DLL
  void loadFile(const QString &fileName);

 protected:
  HVR_SAMPLE_DLL
  void closeEvent(QCloseEvent *event) override;

 private Q_SLOTS:  // NOLINT
  void newFile();
  void open();
  bool save();
  bool saveAs();
  void about();
  void documentWasModified();
#ifndef QT_NO_SESSIONMANAGER
  void commitData(QSessionManager &);
#endif

 private:
  void createActions();
  void createStatusBar();
  void readSettings();
  void writeSettings();
  bool maybeSave();
  bool saveFile(const QString &fileName);
  void setCurrentFile(const QString &fileName);
  QString strippedName(const QString &fullFileName);

  std::shared_ptr<QPlainTextEdit> textEdit_;
  QString curFile_;
};

}  // namespace hvr

#endif  // MODULES_MAINWINDOW_INCLUDE_HVR_MAINWINDOW_MAINWINDOW_H_
