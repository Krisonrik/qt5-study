// Copyright 2018 Qi Yao

#include "Hvr/SaveStream_UI/MainWindow.h"

HVR_WINDOWS_DISABLE_ALL_WARNING
#include <QtWidgets>

#include <memory>
#include <thread>

#include "QtWidgets/qplaintextedit.h"
// #include <iostream>
HVR_WINDOWS_ENABLE_ALL_WARNING

#include "Hvr/SaveStream_UI/BlinkBG.h"
#include "Hvr/SaveStream_UI/StatusPanel.h"

namespace hvr
{
MainWindow::MainWindow()
{
  // setCentralWidget(textEdit);

  createActions();
  createStatusBar();
  createDockWindows();

  setWindowTitle(tr("SaveStream"));

  // newLetter();
  setUnifiedTitleAndToolBarOnMac(true);

  refresh_thrd_ = std::thread(&MainWindow::GlobalRefresh, this);

  // connect(this, &MainWindow::close, this, &MainWindow::StopThread);
}

MainWindow::~MainWindow()
{
  StopThread();
}

void MainWindow::StopThread()
{
  refresh_thrd_.join();
}

void MainWindow::GlobalRefresh()
{
  while (true)
  {
    emit RefreshTrigger();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }
}

void MainWindow::OpenNamingXML()
{
}
void MainWindow::OpenConfigXML()
{
}

void MainWindow::about()
{
  QMessageBox::about(this,
                     tr("About Dock Widgets"),
                     tr("The <b>Dock Widgets</b> example demonstrates how to "
                        "use Qt's dock widgets. You can enter your own text, "
                        "click a customer to add a customer name and "
                        "address, and click standard paragraphs to add them."));
}

void MainWindow::createActions()
{
  QMenu *fileMenu       = menuBar()->addMenu(tr("&File"));
  QToolBar *fileToolBar = addToolBar(tr("File"));
  (void)fileMenu;
  (void)fileToolBar;

  fileMenu->addSeparator();

  QAction *quitAct = fileMenu->addAction(tr("&Quit"), this, &QWidget::close);
  quitAct->setShortcuts(QKeySequence::Quit);
  quitAct->setStatusTip(tr("Quit the application"));

  QMenu *editMenu       = menuBar()->addMenu(tr("&Edit"));
  QToolBar *editToolBar = addToolBar(tr("Edit"));

  (void)editMenu;
  (void)editToolBar;

  viewMenu = menuBar()->addMenu(tr("&View"));

  menuBar()->addSeparator();

  QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));

  QAction *aboutAct =
      helpMenu->addAction(tr("&About"), this, &MainWindow::about);
  aboutAct->setStatusTip(tr("Show the application's About box"));

  QAction *aboutQtAct =
      helpMenu->addAction(tr("About &Qt"), qApp, &QApplication::aboutQt);
  aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
}

void MainWindow::createStatusBar()
{
  statusBar()->showMessage(tr("Ready"));
}

void MainWindow::createDockWindows()
{
  QDockWidget *dock     = new QDockWidget(tr("Status Panel"), this);
  QGridLayout *lay_grid = new QGridLayout();
  QGroupBox *tmp_panel  = new QGroupBox();

  for (int i = 0; i < 3; i++)
  {
    hvr::BlinkBG *blnk_bg = new BlinkBG();
    blnk_bg->SetBlinkOn();
    StatusPanel *cur_panel = new StatusPanel(tr("test"));
    QMap<QString, QString> map_test;
    map_test.insert(tr("test_01"), tr("data_01"));
    map_test.insert(tr("test_02"), tr("data_02"));
    map_test.insert(tr("test_03"), tr("data_03"));
    cur_panel->SetDispList(map_test);

    blnk_bg->SetBGColorRange(Qt::red);
    QHBoxLayout *lay_h_bx = new QHBoxLayout();
    lay_h_bx->addWidget(cur_panel);
    blnk_bg->setLayout(lay_h_bx);

    connect(this, &MainWindow::RefreshTrigger, blnk_bg, &BlinkBG::Blink);

    lay_grid->addWidget(blnk_bg, 0, i);
  }
  tmp_panel->setLayout(lay_grid);

  dock->setWidget(tmp_panel);

  // dock->setWidget(cur_panel);

  addDockWidget(Qt::RightDockWidgetArea, dock);
}

}  // namespace hvr
