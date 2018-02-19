// Copyright 2015 Jason Juang

#include "Hvr/MainWindow/MainWindow.h"

HVR_WINDOWS_DISABLE_ALL_WARNING
#include <QtWidgets>

#include <iostream>
HVR_WINDOWS_ENABLE_ALL_WARNING

namespace hvr
{
MainWindow::MainWindow() : textEdit_(std::make_shared<QPlainTextEdit>)
{
  setCentralWidget(textEdit_.get());

  createActions();
  createStatusBar();

  readSettings();

  connect(textEdit_->document(),
          &QTextDocument::contentsChanged,
          this,
          &MainWindow::documentWasModified);

#ifndef QT_NO_SESSIONMANAGER
  QGuiApplication::setFallbackSessionManagementEnabled(false);
  connect(
      qApp, &QGuiApplication::commitDataRequest, this, &MainWindow::commitData);
#endif

  setCurrentFile(QString());
  setUnifiedTitleAndToolBarOnMac(true);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
  if (maybeSave())
  {
    writeSettings();
    event->accept();
  }
  else
  {
    event->ignore();
  }
}

void MainWindow::open()
{
  if (maybeSave())
  {
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty()) loadFile(fileName);
  }
}

bool MainWindow::save()
{
  if (curFile_.isEmpty())
  {
    return saveAs();
  }
  else
  {
    return saveFile(curFile_);
  }
}

bool MainWindow::saveAs()
{
  QFileDialog dialog(this);
  dialog.setWindowModality(Qt::WindowModal);
  dialog.setAcceptMode(QFileDialog::AcceptSave);
  if (dialog.exec() != QDialog::Accepted) return false;
  return saveFile(dialog.selectedFiles().first());
}

}  // namespace hvr
