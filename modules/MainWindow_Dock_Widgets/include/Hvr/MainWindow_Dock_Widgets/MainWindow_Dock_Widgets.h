// Copyright 2018 Qi Yao

#ifndef MODULES_MAINWINDOW_DOCK_WIDGETS_INCLUDE_HVR_MAINWINDOW_DOCK_WIDGETS_MAINWINDOW_DOCK_WIDGETS_H_
#define MODULES_MAINWINDOW_DOCK_WIDGETS_INCLUDE_HVR_MAINWINDOW_DOCK_WIDGETS_MAINWINDOW_DOCK_WIDGETS_H_

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
class MainWindow_Dock_Widgets : public QMainWindow
{
  Q_OBJECT

 public:
  MAINWINDOW_DOCK_WIDGETS_DLL
  MainWindow_Dock_Widgets();

 private Q_SLOTS:  // NOLINT
  void newLetter();
  void save();
  void print();
  void undo();
  void about();
  void insertCustomer(const QString &customer);
  void addParagraph(const QString &paragraph);

 private:
  void createActions();
  void createStatusBar();
  void createDockWindows();

  // std::shared_ptr<QTextEdit> textEdit_;
  QTextEdit *textEdit;
  // std::shared_ptr<QListWidget> customerList_;
  QListWidget *customerList;
  // std::shared_ptr<QListWidget> paragraphsList_;
  QListWidget *paragraphsList;
  // std::shared_ptr<QMenu> viewMenu_;
  QMenu *viewMenu;
};

}  // namespace hvr

#endif  // MODULES_MAINWINDOW_DOCK_WIDGETS_INCLUDE_HVR_MAINWINDOW_DOCK_WIDGETS_MAINWINDOW_DOCK_WIDGETS_H_
