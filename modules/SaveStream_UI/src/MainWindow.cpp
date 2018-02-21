// Copyright 2018 Qi Yao

#include "Hvr/SaveStream_UI/MainWindow.h"

HVR_WINDOWS_DISABLE_ALL_WARNING
#include <QtWidgets>
#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printdialog)
#include <QtPrintSupport/QtprintSupport>
#endif
#endif

#include <memory>

#include "QtWidgets/qplaintextedit.h"
// #include <iostream>
HVR_WINDOWS_ENABLE_ALL_WARNING

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

  StatusPanel *cur_panel = new StatusPanel(tr("test"));
  QVector<QString> vec_test;
  vec_test.push_back(tr("test_01"));
  vec_test.push_back(tr("test_02"));
  vec_test.push_back(tr("test_03"));

  cur_panel->SetDispList(vec_test);

  // const QIcon newIcon =
  //    QIcon::fromTheme("document-new", QIcon(":/images/new.png"));
  // QAction *newLetterAct = new QAction(newIcon, tr("&New Letter"),
  // this); newLetterAct->setShortcuts(QKeySequence::New);
  // newLetterAct->setStatusTip(tr("Create a new form letter"));
  // connect(newLetterAct, &QAction::triggered, this,
  // &MainWindow::newLetter); fileMenu->addAction(newLetterAct);
  // fileToolBar->addAction(newLetterAct);

  // const QIcon saveIcon =
  //    QIcon::fromTheme("document-save",
  //    QIcon(":/images/save.png"));
  // QAction *saveAct = new QAction(saveIcon, tr("&Save..."), this);
  // saveAct->setShortcuts(QKeySequence::Save);
  // saveAct->setStatusTip(tr("Save the current form letter"));
  // connect(saveAct, &QAction::triggered, this, &MainWindow::save);
  // fileMenu->addAction(saveAct);
  // fileToolBar->addAction(saveAct);

  // const QIcon printIcon =
  //    QIcon::fromTheme("document-print",
  //    QIcon(":/images/print.png"));
  // QAction *printAct = new QAction(printIcon, tr("&Print..."),
  // this); printAct->setShortcuts(QKeySequence::Print);
  // printAct->setStatusTip(tr("Print the current form
  // letter")); connect(printAct, &QAction::triggered, this,
  // &MainWindow::print); fileMenu->addAction(printAct);
  // fileToolBar->addAction(printAct);

  fileMenu->addSeparator();

  QAction *quitAct = fileMenu->addAction(tr("&Quit"), this, &QWidget::close);
  quitAct->setShortcuts(QKeySequence::Quit);
  quitAct->setStatusTip(tr("Quit the application"));

  QMenu *editMenu       = menuBar()->addMenu(tr("&Edit"));
  QToolBar *editToolBar = addToolBar(tr("Edit"));

  (void)editMenu;
  (void)editToolBar;
  // const QIcon undoIcon =
  //    QIcon::fromTheme("edit-undo", QIcon(":/images/undo.png"));
  // QAction *undoAct = new QAction(undoIcon, tr("&Undo"), this);
  // undoAct->setShortcuts(QKeySequence::Undo);
  // undoAct->setStatusTip(tr("Undo the last editing action"));
  //// connect(undoAct, &QAction::triggered, this, &MainWindow::undo);
  // editMenu->addAction(undoAct);
  // editToolBar->addAction(undoAct);

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
  // QDockWidget *dock = new QDockWidget(tr("Customers"), this);
  // dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
  // customerList = new QListWidget(dock);
  // customerList->addItems(
  //    QStringList() << "John Doe, Harmony Enterprises, 12 Lakeside, Ambleton"
  //                  << "Jane Doe, Memorabilia, 23 Watersedge, Beaton"
  //                  << "Tammy Shea, Tiblanka, 38 Sea Views, Carlton"
  //                  << "Tim Sheen, Caraba Gifts, 48 Ocean Way, Deal"
  //                  << "Sol Harvey, Chicos Coffee, 53 New Springs, Eccleston"
  //                  << "Sally Hobart, Tiroli Tea, 67 Long River, Fedula");
  // dock->setWidget(customerList);
  // addDockWidget(Qt::RightDockWidgetArea, dock);
  // viewMenu->addAction(dock->toggleViewAction());

  // dock           = new QDockWidget(tr("Paragraphs"), this);
  // paragraphsList = new QListWidget(dock);
  // paragraphsList
  //    ->addItems(QStringList()
  //               << "Thank you for your payment which we have received today."
  //               << "Your order has been dispatched and should be with you "
  //                  "within 28 days."
  //               << "We have dispatched those items that were in stock. The "
  //                  "rest of your order will be dispatched once all the "
  //                  "remaining items have arrived at our warehouse. No "
  //                  "additional shipping charges will be made."
  //               << "You made a small overpayment (less than $5) which we "
  //                  "will keep on account for you, or return at your request."
  //               << "You made a small underpayment (less than $1), but we have
  //               "
  //                  "sent your order anyway. We'll add this underpayment to "
  //                  "your next bill."
  //               << "Unfortunately you did not send enough money. Please remit
  //               "
  //                  "an additional $. Your order will be dispatched as soon as
  //                  " "the complete amount has been received."
  //               << "You made an overpayment (more than $5). Do you wish to "
  //                  "buy more items, or should we return the excess to you?");
  // dock->setWidget(paragraphsList);
  // addDockWidget(Qt::RightDockWidgetArea, dock);
  // viewMenu->addAction(dock->toggleViewAction());

  // connect(customerList,
  //        &QListWidget::currentTextChanged,
  //        this,
  //        &MainWindow::insertCustomer);
  // connect(paragraphsList,
  //        &QListWidget::currentTextChanged,
  //        this,
  //        &MainWindow::addParagraph);
}

}  // namespace hvr
