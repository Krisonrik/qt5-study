// Copyright 2018 Qi Yao

#ifndef MODULES_SAVESTREAM_UI_INCLUDE_HVR_SAVESTREAM_UI_BLINKBG_H_
#define MODULES_SAVESTREAM_UI_INCLUDE_HVR_SAVESTREAM_UI_BLINKBG_H_

HVR_WINDOWS_DISABLE_ALL_WARNING
#include <QtGui>
#include "QtWidgets/qgroupbox.h"

HVR_WINDOWS_ENABLE_ALL_WARNING

namespace hvr
{
class BlinkBG : public QGroupBox
{
  Q_OBJECT

 public:
  SAVESTREAM_WIDGETS_DLL
  BlinkBG();

  SAVESTREAM_WIDGETS_DLL
  void SetBGColorRange(QColor blink_color);

 public Q_SLOTS:  // NOLINT
  SAVESTREAM_WIDGETS_DLL
  void Blink();
  SAVESTREAM_WIDGETS_DLL
  void SetBlinkOn();

  SAVESTREAM_WIDGETS_DLL
  void StopBlink();

 private:
  QColor blink_color_;
  qreal cur_alpha_;
  QPalette palette_;
  bool upward     = true;
  bool can_blink_ = false;
};

}  // namespace hvr

#endif  // MODULES_SAVESTREAM_UI_INCLUDE_HVR_SAVESTREAM_UI_BLINKBG_H_
