//===-- TimeDisplay.cpp - Renders a 32x32 Time Panel --------------- c++ --===//
//
//                               UWH Timer
//
//           This file is distributed under the BSD 3-Clause License.
//                      See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "uwhd/display/TimeDisplay.h"

#include "uwhd/display/BigNumber.h"
#include "uwhd/display/SecondsRing.h"
#include "uwhd/model/GameModel.h"

#include <graphics.h>

#include <ctime>

using namespace rgb_matrix;
using namespace uwhtimer;

void TimeDisplay::Render(Canvas *C) {
  GameModel M = Mgr.getModel();
  unsigned Now = M.GameClockSecs;

  // Note that we show 1h30m as 90m here:
  unsigned Mins = (Now / 60) % 100;
  unsigned MTens = Mins / 10;
  unsigned MOnes = Mins % 10;

  // Minutes
  if (MTens) {
    BigNumber::RenderHalfSingle(C, DisplayNum, MTens, 1, 2, MinutesColor, &Background);
    BigNumber::RenderHalfSingle(C, DisplayNum, MOnes, 15, 2, MinutesColor, &Background);
  } else {
    BigNumber::RenderHalfSingle(C, DisplayNum, MOnes, 8, 2, MinutesColor, &Background);
  }

  unsigned Secs = Now % 60;
  unsigned STens = Secs / 10;
  unsigned SOnes = Secs % 10;

  // Seconds
  BigNumber::RenderQuarterSingle(C, DisplayNum, STens, 8, 20, SecondsColor, &Background);
  BigNumber::RenderQuarterSingle(C, DisplayNum, SOnes, 15, 20, SecondsColor, &Background);

  unsigned xoffs = DisplayNum * 32;

  // Top Colon
  C->SetPixel(xoffs + 6, 22, ColonColor.r, ColonColor.g, ColonColor.b);
  C->SetPixel(xoffs + 7, 22, ColonColor.r, ColonColor.g, ColonColor.b);
  C->SetPixel(xoffs + 6, 23, ColonColor.r, ColonColor.g, ColonColor.b);
  C->SetPixel(xoffs + 7, 23, ColonColor.r, ColonColor.g, ColonColor.b);

  // Bottom Colon
  C->SetPixel(xoffs + 6, 25, ColonColor.r, ColonColor.g, ColonColor.b);
  C->SetPixel(xoffs + 7, 25, ColonColor.r, ColonColor.g, ColonColor.b);
  C->SetPixel(xoffs + 6, 26, ColonColor.r, ColonColor.g, ColonColor.b);
  C->SetPixel(xoffs + 7, 26, ColonColor.r, ColonColor.g, ColonColor.b);

  SecondsRing::Render(C, DisplayNum, 120 - (Now % 120), RingColor, &Background);
}
