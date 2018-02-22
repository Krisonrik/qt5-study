// Copyright 2018 Qi Yao

#ifndef MODULES_SAVESTREAM_UI_INCLUDE_HVR_SAVESTREAM_UI_STATUSPANEL_H_
#define MODULES_SAVESTREAM_UI_INCLUDE_HVR_SAVESTREAM_UI_STATUSPANEL_H_

HVR_WINDOWS_DISABLE_ALL_WARNING
#include <QtGui>
#include "QtWidgets/qgroupbox.h"

HVR_WINDOWS_ENABLE_ALL_WARNING

namespace hvr
{
class StatusPanel : public QGroupBox
{
  Q_OBJECT

 public:
  SAVESTREAM_WIDGETS_DLL
  explicit StatusPanel(QString panel_nam);

  SAVESTREAM_WIDGETS_DLL
  bool SetDispList(QMap<QString, QString> setting_list);

 private Q_SLOTS:  // NOLINT

 private:
  void createActions();

  QString panel_nam_;
};

}  // namespace hvr

#endif  // MODULES_SAVESTREAM_UI_INCLUDE_HVR_SAVESTREAM_UI_STATUSPANEL_H_
