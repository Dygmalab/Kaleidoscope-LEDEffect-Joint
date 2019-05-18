#include "Kaleidoscope-LEDEffect-Joint.h"
#include <Kaleidoscope-EEPROM-Settings.h>

namespace kaleidoscope {
namespace plugin {

uint16_t LEDJointEffect::settings_base_;
uint16_t LEDJointEffect::joint_threshold = 450;
uint8_t LEDJointEffect::anim_timer = 0;
int LEDJointEffect::anim_level = 0;

LEDJointEffect::settings_t LEDJointEffect::settings = {
  .split = 300, // defaults
  .joined = 600,
};

// on setup, request some storage space to write the joint min and max
EventHandlerResult LEDJointEffect::onSetup() {
  settings_base_ = ::EEPROMSettings.requestSlice(sizeof(settings));

  // If split is max, assume that EEPROM is uninitialized, and store the
  // defaults.
  uint16_t split;
  KeyboardHardware.storage().get(settings_base_, split);
  if (split == 0xffff) {
    KeyboardHardware.storage().put(settings_base_, settings);
    KeyboardHardware.storage().commit();
  }

  KeyboardHardware.storage().get(settings_base_, settings);
  return EventHandlerResult::OK;
}

EventHandlerResult LEDJointEffect::beforeReportingState() {
  // 1st row left 3 keys to set joined level
  bool changed = false;
  if (KeyboardHardware.isKeyswitchPressed(R0C0) &&
      KeyboardHardware.isKeyswitchPressed(R0C1) &&
      KeyboardHardware.isKeyswitchPressed(R0C2) &&
      KeyboardHardware.pressedKeyswitchCount() == 3) {
      changed = true;
      settings.joined = KeyboardHardware.readJoint();
  }
  // 2nd row left 3 keys to set split level
  if (KeyboardHardware.isKeyswitchPressed(R1C0) &&
      KeyboardHardware.isKeyswitchPressed(R1C1) &&
      KeyboardHardware.isKeyswitchPressed(R1C2) &&
      KeyboardHardware.pressedKeyswitchCount() == 3) {
      changed = true;
      settings.split = KeyboardHardware.readJoint();
  }

  if(changed) {
      // commit the changes
      KeyboardHardware.storage().put(settings_base_, settings);
      KeyboardHardware.storage().commit();
      // calculate mid point
      if(settings.split > settings.joined)
          joint_threshold = (settings.split - settings.joined) / 2 + settings.joined;
      else
          joint_threshold = (settings.joined - settings.split) / 2 + settings.split;
  }

  return EventHandlerResult::OK;
}

void LEDJointEffect::update(void) {
  if (anim_timer ++ < anim_timeout) {
    return;
  }
  anim_timer = 0;

  int joint = KeyboardHardware.readJoint();

  // animate the colour change
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
}

kaleidoscope::plugin::LEDJointEffect LEDJointEffect;
