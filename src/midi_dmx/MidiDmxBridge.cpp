/**
 * @file MidiDmxBridge.cpp
 * @author Christian Neukam
 * @brief Implementation of the MidiDmxBridge class.
 * @version 1.0
 * @date 2024-01-04
 *
 * @copyright Copyright 2024 Christian Neukam. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "../MidiDmxBridge.h"

MidiDmxBridge::MidiDmxBridge(const uint8_t channel, DmxOnChangeCallback callback,
                             ISerialReader& serial)
    : mSleep(serial), mDmx(callback), mReader(channel, serial) {}

void MidiDmxBridge::begin() { mReader.begin(); }

void MidiDmxBridge::setStaticScene(const DmxRgbChannels& channels, const DmxRgb& rgb) {
  mDmx.setStaticScene(channels, rgb);
}

void MidiDmxBridge::setAttenuation(const uint16_t attenuation) { mDmx.setGain(attenuation); }

void MidiDmxBridge::switchToDynamicScene() { mDmx.activateDynamicScene(); }

void MidiDmxBridge::switchToStaticScene() { mDmx.activateStaticScene(); }

void MidiDmxBridge::listen() {
  uint8_t controller;
  uint8_t value;

  if (mReader.readCc(controller, value)) {
    mDmx.setMidiCcValue(controller, value);
  }

  mSleep.sleep(3);  // short refresh to process the callback
}
