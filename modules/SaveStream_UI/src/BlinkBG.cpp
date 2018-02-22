// Copyright 2018 Qi Yao

#include "Hvr/SaveStream_UI/BlinkBG.h"

HVR_WINDOWS_DISABLE_ALL_WARNING
#include <QtWidgets>

#include <memory>
HVR_WINDOWS_ENABLE_ALL_WARNING

namespace hvr
{
BlinkBG::BlinkBG()
{
  cur_alpha_ = 0.0;
}

void BlinkBG::SetBGColorRange(QColor blink_color)
{
  blink_color_ = blink_color;
  palette_.setColor(QPalette::Background, blink_color);
  this->setAutoFillBackground(true);
  this->setPalette(palette_);
}

void BlinkBG::Blink()
{
  if (can_blink_)
  {
    if (upward)
    {
      cur_alpha_ += 0.1;
      if (cur_alpha_ >= 1.0)
      {
        cur_alpha_ = 1.0;
        upward     = false;
      }
    }
    else
    {
      cur_alpha_ -= 0.1;
      if (cur_alpha_ <= 0.0)
      {
        cur_alpha_ = 0.0;
        upward     = true;
      }
    }

    blink_color_.setAlphaF(cur_alpha_);
    palette_.setColor(QPalette::Background, blink_color_);
    this->setPalette(palette_);
    this->setWindowOpacity(cur_alpha_);
  }
}

void BlinkBG::SetBlinkOn()
{
  can_blink_ = true;
}

void BlinkBG::StopBlink()
{
  can_blink_ = false;
  palette_.setColor(QPalette::Background, Qt::gray);
  this->setPalette(palette_);
}

}  // namespace hvr
