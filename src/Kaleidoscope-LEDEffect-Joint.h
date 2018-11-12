#pragma once

#include "Kaleidoscope-LEDControl.h"
#include "LEDUtils.h"

namespace kaleidoscope {
class LEDJointEffect : public LEDMode {
 public:
  LEDJointEffect(void) {}

 protected:
  void update(void) final;

 private:
  uint8_t current_anim_counter = 0;
  int anim_level = 0;
  static const uint8_t anim_threshold = 10;
  static const unsigned int joint_threshold = 650;
};
}

extern kaleidoscope::LEDJointEffect LEDJointEffect;
