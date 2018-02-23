// Copyright 2018 Qi Yao

#include "Hvr/SaveStream_UI/BlinkBG.h"

HVR_WINDOWS_DISABLE_ALL_WARNING
#include <QtWidgets>

#include <memory>
HVR_WINDOWS_ENABLE_ALL_WARNING

namespace hvr
{
BlinkBG::BlinkBG(const QString &name)
{
  cur_alpha_ = 0.0;
  setObjectName(name);
}

void BlinkBG::SetBlinkColor(QColor blink_color)
{
  blink_color_ = blink_color;
  // palette_.setColor(QPalette::Background, blink_color);
  this->setAutoFillBackground(true);
  // this->setPalette(palette_);
}

void BlinkBG::Blink()
{
  if (can_blink_)
  {
    if (upward)
    {
      cur_alpha_ += 0.2;
      if (cur_alpha_ >= 1.0)
      {
        cur_alpha_ = 1.0;
        upward     = false;
      }
    }
    else
    {
      cur_alpha_ -= 0.2;
      if (cur_alpha_ <= 0.0)
      {
        cur_alpha_ = 0.0;
        upward     = true;
      }
    }

    blink_color_.setAlphaF(cur_alpha_);
    palette_.setColor(QPalette::Background, blink_color_);
    this->setPalette(palette_);
    // this->setWindowOpacity(cur_alpha_);
  }
}

void BlinkBG::SetBlinkOn()
{
  can_blink_ = true;
}

void BlinkBG::SetBlinkOff()
{
  can_blink_          = false;
  QColor tmp_bg_color = Qt::gray;
  tmp_bg_color.setAlphaF(0.0);
  palette_.setColor(QPalette::Background, tmp_bg_color);
  this->setPalette(palette_);
}

void BlinkBG::SetSteadyOn()
{
  can_blink_          = false;
  QColor tmp_bg_color = blink_color_;
  tmp_bg_color.setAlphaF(1.0);
  palette_.setColor(QPalette::Background, tmp_bg_color);
  this->setPalette(palette_);
}

void BlinkBG::SetSteadyOff()
{
  can_blink_          = false;
  QColor tmp_bg_color = Qt::gray;
  tmp_bg_color.setAlphaF(0.0);
  palette_.setColor(QPalette::Background, tmp_bg_color);
  this->setPalette(palette_);
}

}  // namespace hvr
