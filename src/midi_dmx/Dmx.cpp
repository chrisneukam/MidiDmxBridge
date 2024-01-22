/**
 * @file Dmx.cpp
 * @author Christian Neukam
 * @brief Implementation of the mididmxbridge::dmx::Dmx class
 * @version 1.0
 * @date 2023-12-25
 *
 * @copyright Copyright 2023 Christian Neukam. All rights reserved.
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
#include "Dmx.h"

#include "ContinuousController.h"
#include "constants.h"
#include "util.h"

namespace mididmxbridge::dmx {
using namespace mididmxbridge::util;

using midi::ContinuousController;

static const uint16_t kGainDeadZone = 5; /**< the offset specifying the dead zone for gain values */

Dmx::Dmx(DmxOnChangeCallback callback)
    : mUseDynamicScene(true),
      mDynamicScene(kMaxMidiValue),
      mGain(kUnityGainValue),
      mCallback(callback) {}

uint8_t Dmx::scaleValue(const uint8_t value) const {
  return ((uint32_t)value * (uint32_t)mGain) >> kAnalogReadBits;
}

bool Dmx::updateScene(const DmxValue& dmxValue) {
  bool sceneChanged = false;

  if (dmxValue && (dmxValue.channel() <= kMaxMidiValue)) {
    sceneChanged = mDynamicScene[dmxValue.channel()] != dmxValue;
    mDynamicScene[dmxValue.channel()] = dmxValue;
  }

  return sceneChanged;
}

void Dmx::sendScene() const {
  const auto& scene = mUseDynamicScene ? mDynamicScene : mStaticScene;

  if (mCallback) {
    for (uint8_t idx = 0; idx < scene.size(); idx++) {
      const auto& dmxValue = scene[idx];

      if (dmxValue) {
        mCallback(dmxValue.channel(), scaleValue(dmxValue.value()));
      }
    }
  }
}

void Dmx::blackoutScene() const {
  const auto& scene = mUseDynamicScene ? mStaticScene : mDynamicScene;

  if (mCallback) {
    for (uint8_t idx = 0; idx < scene.size(); idx++) {
      const auto& dmxValue = scene[idx];

      if (dmxValue) {
        mCallback(dmxValue.channel(), 0);
      }
    }
  }
}

void Dmx::setGain(const uint16_t gain) {
  const bool isToSet = (absDiff_t(gain, mGain) > kGainDeadZone) ? true : false;

  if (isToSet) {
    mGain = min_t(gain, kUnityGainValue);
    sendScene();
  }
}

void Dmx::setDmxValue(const DmxValue& dmxValue) {
  const bool triggerCallback = updateScene(dmxValue) && mUseDynamicScene;

  if (mCallback && triggerCallback) {
    mCallback(dmxValue.channel(), scaleValue(dmxValue.value()));
  }
}

void Dmx::setMidiCcValue(const uint8_t midiCcController, const uint8_t midiCcValue) {
  setDmxValue(ContinuousController{midiCcController, midiCcValue}.toDmx());
}

void Dmx::setStaticScene(const DmxRgbChannels& channels, const DmxRgb& rgb) {
  setRgbColor(channels.red, rgb.red);
  setRgbColor(channels.green, rgb.green);
  setRgbColor(channels.blue, rgb.blue);
}

void Dmx::setRgbColor(const vector<uint8_t>& channels, const uint8_t color) {
  for (uint8_t ch = 0; ch < channels.size(); ch++) {
    if (channels[ch] <= kMaxMidiValue) {
      mStaticScene.push_back(DmxValue{channels[ch], color});
    }
  }
}

void Dmx::activateStaticScene() {
  bool sendCompleteUpdate = mUseDynamicScene;
  mUseDynamicScene = false;

  if (sendCompleteUpdate) {
    blackoutScene();
    sendScene();
  }
}

void Dmx::activateDynamicScene() {
  bool sendCompleteUpdate = !mUseDynamicScene;
  mUseDynamicScene = true;

  if (sendCompleteUpdate) {
    blackoutScene();
    sendScene();
  }
}
}  // namespace mididmxbridge::dmx
