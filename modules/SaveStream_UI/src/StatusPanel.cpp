// Copyright 2018 Qi Yao

#include "Hvr/SaveStream_UI/StatusPanel.h"

HVR_WINDOWS_DISABLE_ALL_WARNING
#include <QtWidgets>

#include <memory>

HVR_WINDOWS_ENABLE_ALL_WARNING

#include "Hvr/SaveStream_UI/BlinkBG.h"

namespace hvr
{
StatusPanel::StatusPanel(QString panel_nam)
{
  // panel_nam_ = panel_nam;
  // createActions();
  setObjectName(panel_nam);
  setTitle(panel_nam);
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
    QString bl_bg_nam       = tr((it.key().toStdString() + "_bg").c_str());
    hvr::BlinkBG *tmp_bl_bg = new hvr::BlinkBG(bl_bg_nam);
    QHBoxLayout *tmp_h_lay  = new QHBoxLayout();
    tmp_bl_bg->SetBlinkColor(Qt::blue);
    // tmp_bl_bg->SetBlinkOn();
    tmp_bl_bg->SetBlinkOff();
    tmp_disp_data = new QLabel(tr(it.value().toStdString().c_str()));
    tmp_h_lay->addWidget(tmp_disp_data);
    tmp_bl_bg->setLayout(tmp_h_lay);
    lay_grid->addWidget(tmp_bl_bg, row, col);
    row += 1;
    // vbox->addWidget(tmp_labl);
  }

  this->setLayout(lay_grid);
  return true;
}

// void StatusPanel::createActions()
//{
//}

}  // namespace hvr
