#pragma once

#include "Kaleidoscope-LEDControl.h"

namespace kaleidoscope {
namespace plugin {
class LEDJointEffect : public LEDMode {
 public:
  LEDJointEffect(void) {}
  EventHandlerResult beforeReportingState();
  EventHandlerResult onSetup();

  typedef struct settings_t {
    uint16_t split;
    uint16_t joined;
  } settings_t;

  static settings_t settings;

 protected:
  void update(void) final;

 private:
  static uint8_t anim_timer;
  static int anim_level;
  static uint16_t joint_threshold;
  static const uint8_t anim_timeout = 10;
  static uint16_t settings_base_;
};
}
}

extern kaleidoscope::plugin::LEDJointEffect LEDJointEffect;
