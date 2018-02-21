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

bool StatusPanel::SetDispList(QVector<QString> setting_list)
{
  QLabel *tmp_labl;
  QVBoxLayout *vbox = new QVBoxLayout;
  for (qint32 i = 0; i < setting_list.size(); i++)
  {
    tmp_labl = new QLabel(tr(setting_list[i].toStdString().c_str()));
    vbox->addWidget(tmp_labl);
  }

  this->setLayout(vbox);
  return true;
}

void StatusPanel::createActions()
{
}

}  // namespace hvr
