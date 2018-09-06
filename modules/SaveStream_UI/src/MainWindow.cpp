// Copyright 2018 Qi Yao

#include "Hvr/SaveStream_UI/MainWindow.h"

HVR_WINDOWS_DISABLE_ALL_WARNING
#include <QtWidgets>

#include <memory>
#include <thread>

#include "QtMath"
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
  // ir_settings_.append([tr("setting_01")],)

  createActions();
  createStatusBar();
  CreateStatWindow();
  CreateSettingWindow();

  setWindowTitle(tr("SaveStream"));

  setUnifiedTitleAndToolBarOnMac(true);

  refresh_thrd_ = std::thread(&MainWindow::GlobalRefresh, this);
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
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}

void MainWindow::OpenNamingXML()
{
  if (maybeSave())
  {
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty()) loadFile(fileName);
  }
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

void MainWindow::CreateStatWindow()
{
  stat_window_          = new QDockWidget(tr("Status Panel"), this);
  QGridLayout *lay_grid = new QGridLayout();
  QGroupBox *tmp_panel  = new QGroupBox();

  for (int i = 0; i < 60; i++)
  {
    QString bl_bg_nam     = tr((std::to_string(i) + "_data_bg").c_str());
    hvr::BlinkBG *blnk_bg = new BlinkBG(bl_bg_nam);
    // blnk_bg->SetBlinkOn();

    QMap<QString, QString> map_test;
    map_test.insert(tr("test_01"), tr("data_01"));
    map_test.insert(tr("test_02"), tr("data_02"));
    map_test.insert(tr("test_03"), tr("data_03"));

    QString cam_panel_nam  = map_test.last();
    StatusPanel *cur_panel = new StatusPanel(cam_panel_nam);
    cur_panel->SetDispList(map_test);

    blnk_bg->SetBlinkColor(Qt::red);
    // blnk_bg->SetBlinkOff();
    QHBoxLayout *lay_h_bx = new QHBoxLayout();
    lay_h_bx->addWidget(cur_panel);
    // blnk_bg->setGeometry(lay_h_bx->geometry());
    blnk_bg->setLayout(lay_h_bx);
    // blnk_bg->show();
    connect(this, &MainWindow::RefreshTrigger, blnk_bg, &BlinkBG::Blink);
    QPair<qint32, qint32> panel_pos = CamPanelPosition(i, 60);
    lay_grid->addWidget(blnk_bg, panel_pos.first, panel_pos.second);
  }
  tmp_panel->setLayout(lay_grid);

  stat_window_->setWidget(tmp_panel);

  addDockWidget(Qt::RightDockWidgetArea, stat_window_);

  QObjectList cams = stat_window_->children();
  hvr::BlinkBG *cur_bl_bg =
      stat_window_->findChild<hvr::BlinkBG *>(tr("1_data_bg"));
  if (!cur_bl_bg)
  {
    qInfo("Retrieving blink background failed!");
    return;
  }
  cur_bl_bg->SetBlinkOn();
}

void MainWindow::CreateSettingWindow()
{
  setting_window_       = new QDockWidget(tr("Setting Panel"), this);
  QGridLayout *lay_grid = new QGridLayout();
  QGroupBox *ir_panel   = new QGroupBox(tr("IR Settings"));
  QVector<QPair<QString, QString>> settings = ir_settings_;
  int row                                   = 0;

  for (QVector<QPair<QString, QString>>::iterator it = settings.begin();
       it != settings.end();
       it++)
  {
    int col             = 0;
    QLabel *setting_nam = new QLabel(it->first);
    lay_grid->addWidget(setting_nam, row, col);
    col += 1;

    QLineEdit *setting_val = new QLineEdit(it->second);
    lay_grid->addWidget(setting_val, row, col);

    row += 1;
  }
  ir_panel->setLayout(lay_grid);

  lay_grid             = new QGridLayout();
  QGroupBox *rgb_panel = new QGroupBox(tr("IR Settings"));
  settings             = rgb_settings_;
  row                  = 0;

  for (QVector<QPair<QString, QString>>::iterator it = settings.begin();
       it != settings.end();
       it++)
  {
    int col             = 0;
    QLabel *setting_nam = new QLabel(it->first);
    lay_grid->addWidget(setting_nam, row, col);
    col += 1;

    QLineEdit *setting_val = new QLineEdit(it->second);
    lay_grid->addWidget(setting_val, row, col);

    row += 1;
  }
  rgb_panel->setLayout(lay_grid);

  QVBoxLayout *lay_v = new QVBoxLayout();
  lay_v->addWidget(ir_panel);
  lay_v->addWidget(rgb_panel);
  QGroupBox *setting_panels = new QGroupBox();
  setting_panels->setObjectName(tr("Holder"));
  setting_window_->setWidget(setting_panels);
}

QPair<qint32, qint32> MainWindow::CamPanelPosition(qint32 idx, qint32 total)
{
  QPair<qint32, qint32> pos;
  qint32 row = static_cast<qint32>(qSqrt(total * 16 / 9));
  // qint32 col = static_cast<qint32>(qSqrt(total * 9 / 16));

  pos.second = idx % row;
  pos.first  = static_cast<qint32>(idx / row);
  return pos;
}

}  // namespace hvr
