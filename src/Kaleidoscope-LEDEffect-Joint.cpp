#include "Kaleidoscope-LEDEffect-Joint.h"

namespace kaleidoscope {
void LEDJointEffect::update(void) {
  if (current_anim_counter ++ < anim_threshold) {
    return;
  }
  current_anim_counter = 0;

  int joint = KeyboardHardware.readJoint();

  if(joint > joint_threshold)
  {
    anim_level += 10;
    if(anim_level > 255)
        anim_level = 255;
  }
  else
  {
    anim_level -= 10;
    if(anim_level < 0)
        anim_level = 0;
  }

  ::LEDControl.set_all_leds_to(255-anim_level,anim_level,0);

}
}

kaleidoscope::LEDJointEffect LEDJointEffect;
