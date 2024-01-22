/**
 * @file ContinuousController.cpp
 * @author Christian Neukam
 * @brief Implementation of the mididmxbridge::midi::ContinuousController class
 * @version 1.0
 * @date 2023-12-12
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
#include "ContinuousController.h"

#include "DmxValue.h"
#include "constants.h"
#include "util.h"

namespace mididmxbridge::midi {
using namespace mididmxbridge::util;

static const uint8_t kMidiToDmxFactor = 0x02; /**< scaling factor converting midi to dmx */

ContinuousController::ContinuousController() : mController(0), mValue(0) {}

ContinuousController::ContinuousController(const uint8_t controller, const uint8_t value)
    : mController(min_t(controller, kMaxMidiValue)), mValue(min_t(value, kMaxMidiValue)) {}

bool ContinuousController::operator==(const ContinuousController& rhs) const {
  return mController == rhs.mController && mValue == rhs.mValue;
}

bool ContinuousController::operator!=(const ContinuousController& rhs) const {
  return !(*this == rhs);
}

DmxValue ContinuousController::toDmx() const {
  const uint8_t value = mValue * kMidiToDmxFactor;
  return {mController, value};
}
}  // namespace mididmxbridge::midi
