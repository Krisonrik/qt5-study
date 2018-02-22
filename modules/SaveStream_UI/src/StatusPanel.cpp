// Copyright 2018 Qi Yao

#include "Hvr/SaveStream_UI/StatusPanel.h"

HVR_WINDOWS_DISABLE_ALL_WARNING
#include <QtWidgets>

#include <memory>

// #include <iostream>
HVR_WINDOWS_ENABLE_ALL_WARNING

namespace hvr
{
StatusPanel::StatusPanel(QString panel_nam)
{
  panel_nam_ = panel_nam;
  createActions();
  setWindowTitle(tr(panel_nam_.toStdString().c_str()));
}

bool StatusPanel::SetDispList(QMap<QString, QString> setting_list)
{
  QLabel *tmp_labl;
  QLabel *tmp_disp_data;
  QGridLayout *lay_grid = new QGridLayout();
  int row               = 0;

  for (QMap<QString, QString>::iterator it = setting_list.begin();
       it != setting_list.end();
       it++)
  {
    int col = 0;

    tmp_labl = new QLabel(tr(it.key().toStdString().c_str()));
    lay_grid->addWidget(tmp_labl, row, col);

    col += 1;
    tmp_disp_data = new QLabel(tr(it.value().toStdString().c_str()));
    lay_grid->addWidget(tmp_disp_data, row, col);
    row += 1;
    // vbox->addWidget(tmp_labl);
  }

  this->setLayout(lay_grid);
  return true;
}

void StatusPanel::createActions()
{
}

}  // namespace hvr
