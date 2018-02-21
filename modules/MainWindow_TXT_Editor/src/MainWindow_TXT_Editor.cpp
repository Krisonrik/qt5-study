// Copyright 2018 Qi Yao

#include "Hvr/MainWindow_TXT_Editor/MainWindow_TXT_Editor.h"

HVR_WINDOWS_DISABLE_ALL_WARNING
#include <QtWidgets>

#include <iostream>
HVR_WINDOWS_ENABLE_ALL_WARNING

namespace hvr
{
MainWindow_TXT_Editor::MainWindow_TXT_Editor()
    : textEdit_(std::make_shared<QPlainTextEdit>())
{
  setCentralWidget(textEdit_.get());

  createActions();
  createStatusBar();

  readSettings();

  connect(textEdit_->document(),
          &QTextDocument::contentsChanged,
          this,
          &MainWindow_TXT_Editor::documentWasModified);

#ifndef QT_NO_SESSIONMANAGER
  QGuiApplication::setFallbackSessionManagementEnabled(false);
  connect(qApp,
          &QGuiApplication::commitDataRequest,
          this,
          &MainWindow_TXT_Editor::commitData);
#endif

  setCurrentFile(QString());
  setUnifiedTitleAndToolBarOnMac(true);
}

void MainWindow_TXT_Editor::closeEvent(QCloseEvent *event)
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

void MainWindow_TXT_Editor::newFile()
{
  if (maybeSave())
  {
    textEdit_->clear();
    setCurrentFile(QString());
  }
}

void MainWindow_TXT_Editor::open()
{
  if (maybeSave())
  {
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty()) loadFile(fileName);
  }
}

bool MainWindow_TXT_Editor::save()
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

bool MainWindow_TXT_Editor::saveAs()
{
  QFileDialog dialog(this);
  dialog.setWindowModality(Qt::WindowModal);
  dialog.setAcceptMode(QFileDialog::AcceptSave);
  if (dialog.exec() != QDialog::Accepted) return false;
  return saveFile(dialog.selectedFiles().first());
}

void MainWindow_TXT_Editor::about()
{
  QMessageBox::about(
      this,
      tr("About Application"),
      tr("The <b>Application</b> example demonstrates how to "
         "write modern GUI applications using Qt, with a menu bar, "
         "toolbars, and a status bar."));
}

void MainWindow_TXT_Editor::documentWasModified()
{
  setWindowModified(textEdit_->document()->isModified());
}

void MainWindow_TXT_Editor::createActions()
{
  QMenu *fileMenu       = menuBar()->addMenu(tr("&File"));
  QToolBar *fileToolBar = addToolBar(tr("File"));
  const QIcon newIcon =
      QIcon::fromTheme("document-new", QIcon(":/images/new.png"));
  QAction *newAct = new QAction(newIcon, tr("&New"), this);
  newAct->setShortcuts(QKeySequence::New);
  newAct->setStatusTip(tr("Create a new file"));
  connect(newAct, &QAction::triggered, this, &MainWindow_TXT_Editor::newFile);
  fileMenu->addAction(newAct);
  fileToolBar->addAction(newAct);

  const QIcon openIcon =
      QIcon::fromTheme("document-open", QIcon(":/images/open.png"));
  QAction *openAct = new QAction(openIcon, tr("&Open..."), this);
  openAct->setShortcuts(QKeySequence::Open);
  openAct->setStatusTip(tr("Open an existing file"));
  connect(openAct, &QAction::triggered, this, &MainWindow_TXT_Editor::open);
  fileMenu->addAction(openAct);
  fileToolBar->addAction(openAct);

  const QIcon saveIcon =
      QIcon::fromTheme("document-save", QIcon(":/images/save.png"));
  QAction *saveAct = new QAction(saveIcon, tr("&Save"), this);
  saveAct->setShortcuts(QKeySequence::Save);
  saveAct->setStatusTip(tr("Save the document to disk"));
  connect(saveAct, &QAction::triggered, this, &MainWindow_TXT_Editor::save);
  fileMenu->addAction(saveAct);
  fileToolBar->addAction(saveAct);

  const QIcon saveAsIcon = QIcon::fromTheme("document-save-as");
  QAction *saveAsAct     = fileMenu->addAction(
      saveAsIcon, tr("Save &As..."), this, &MainWindow_TXT_Editor::saveAs);
  saveAsAct->setShortcuts(QKeySequence::SaveAs);
  saveAsAct->setStatusTip(tr("Save the document under a new name"));

  fileMenu->addSeparator();

  const QIcon exitIcon = QIcon::fromTheme("application-exit");
  QAction *exitAct =
      fileMenu->addAction(exitIcon, tr("E&xit"), this, &QWidget::close);
  exitAct->setShortcuts(QKeySequence::Quit);
  exitAct->setStatusTip(tr("Exit the application"));

  QMenu *editMenu       = menuBar()->addMenu(tr("&Edit"));
  QToolBar *editToolBar = addToolBar(tr("Edit"));
#ifndef QT_NO_CLIPBOARD
  const QIcon cutIcon = QIcon::fromTheme("edit-cut", QIcon(":/images/cut.png"));
  QAction *cutAct     = new QAction(cutIcon, tr("Cu&t"), this);
  cutAct->setShortcuts(QKeySequence::Cut);
  cutAct->setStatusTip(
      tr("Cut the current selection's contents to the "
         "clipboard"));
  connect(cutAct, &QAction::triggered, textEdit_.get(), &QPlainTextEdit::cut);
  editMenu->addAction(cutAct);
  editToolBar->addAction(cutAct);

  const QIcon copyIcon =
      QIcon::fromTheme("edit-copy", QIcon(":/images/copy.png"));
  QAction *copyAct = new QAction(copyIcon, tr("&Copy"), this);
  copyAct->setShortcuts(QKeySequence::Copy);
  copyAct->setStatusTip(
      tr("Copy the current selection's contents to the "
         "clipboard"));
  connect(copyAct, &QAction::triggered, textEdit_.get(), &QPlainTextEdit::copy);
  editMenu->addAction(copyAct);
  editToolBar->addAction(copyAct);

  const QIcon pasteIcon =
      QIcon::fromTheme("edit-paste", QIcon(":/images/paste.png"));
  QAction *pasteAct = new QAction(pasteIcon, tr("&Paste"), this);
  pasteAct->setShortcuts(QKeySequence::Paste);
  pasteAct->setStatusTip(
      tr("Paste the clipboard's contents into the current "
         "selection"));
  connect(
      pasteAct, &QAction::triggered, textEdit_.get(), &QPlainTextEdit::paste);
  editMenu->addAction(pasteAct);
  editToolBar->addAction(pasteAct);

  menuBar()->addSeparator();

#endif  // !QT_NO_CLIPBOARD

  QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
  QAction *aboutAct =
      helpMenu->addAction(tr("&About"), this, &MainWindow_TXT_Editor::about);
  aboutAct->setStatusTip(tr("Show the application's About box"));

  QAction *aboutQtAct =
      helpMenu->addAction(tr("About &Qt"), qApp, &QApplication::aboutQt);
  aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));

#ifndef QT_NO_CLIPBOARD
  cutAct->setEnabled(false);
  copyAct->setEnabled(false);
  connect(textEdit_.get(),
          &QPlainTextEdit::copyAvailable,
          cutAct,
          &QAction::setEnabled);
  connect(textEdit_.get(),
          &QPlainTextEdit::copyAvailable,
          copyAct,
          &QAction::setEnabled);
#endif  // !QT_NO_CLIPBOARD
}

void MainWindow_TXT_Editor::createStatusBar()
{
  statusBar()->showMessage(tr("Ready"));
}

void MainWindow_TXT_Editor::readSettings()
{
  QSettings settings(QCoreApplication::organizationName(),
                     QCoreApplication::applicationName());
  const QByteArray geometry =
      settings.value("geometry", QByteArray()).toByteArray();
  if (geometry.isEmpty())
  {
    const QRect availableGeometry =
        QApplication::desktop()->availableGeometry(this);
    resize(availableGeometry.width() / 3, availableGeometry.height() / 2);
    move((availableGeometry.width() - width()) / 2,
         (availableGeometry.height() - height()) / 2);
  }
  else
  {
    restoreGeometry(geometry);
  }
}

void MainWindow_TXT_Editor::writeSettings()
{
  QSettings settings(QCoreApplication::organizationName(),
                     QCoreApplication::applicationName());
  settings.setValue("geometry", saveGeometry());
}

bool MainWindow_TXT_Editor::maybeSave()
{
  if (!textEdit_->document()->isModified()) return true;
  const QMessageBox::StandardButton ret = QMessageBox::warning(
      this,
      tr("Application"),
      tr("The document has been modified.\n"
         "Do you want to save your changes?"),
      QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
  switch (ret)
  {
    case QMessageBox::Save: return save();
    case QMessageBox::Cancel: return false;
    default: break;
  }
  return true;
}

void MainWindow_TXT_Editor::loadFile(const QString &fileName)
{
  QFile file(fileName);
  if (!file.open(QFile::ReadOnly | QFile::Text))
  {
    QMessageBox::warning(
        this,
        tr("Application"),
        tr("Cannot read file %1:\n%2.")
            .arg(QDir::toNativeSeparators(fileName), file.errorString()));
    return;
  }

  QTextStream in(&file);
#ifndef QT_NO_CURSOR
  QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
  textEdit_->setPlainText(in.readAll());
#ifndef QT_NO_CURSOR
  QApplication::restoreOverrideCursor();
#endif

  setCurrentFile(fileName);
  statusBar()->showMessage(tr("File loaded"), 2000);
}

bool MainWindow_TXT_Editor::saveFile(const QString &fileName)
{
  QFile file(fileName);
  if (!file.open(QFile::WriteOnly | QFile::Text))
  {
    QMessageBox::warning(
        this,
        tr("Application"),
        tr("Cannot write file %1:\n%2.")
            .arg(QDir::toNativeSeparators(fileName), file.errorString()));
    return false;
  }

  QTextStream out(&file);
#ifndef QT_NO_CURSOR
  QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
  out << textEdit_->toPlainText();
#ifndef QT_NO_CURSOR
  QApplication::restoreOverrideCursor();
#endif

  setCurrentFile(fileName);
  statusBar()->showMessage(tr("File saved"), 2000);
  return true;
}

void MainWindow_TXT_Editor::setCurrentFile(const QString &fileName)
{
  QString curFile = fileName;
  textEdit_->document()->setModified(false);
  setWindowModified(false);

  QString shownName = curFile;
  if (curFile.isEmpty())
  {
    shownName = "untitled.txt";
  }

  setWindowFilePath(shownName);
}

QString MainWindow_TXT_Editor::strippedName(const QString &fullFileName)
{
  return QFileInfo(fullFileName).fileName();
}

#ifndef QT_NO_SESSIONMANAGER
void MainWindow_TXT_Editor::commitData(QSessionManager &manager)
{
  if (manager.allowsInteraction())
  {
    if (!maybeSave()) manager.cancel();
  }
  else
  {
    // Non-interactive: save without asking
    if (textEdit_->document()->isModified())
    {
      save();
    }
  }
}
#endif

}  // namespace hvr
