/**
 * @file DmxTypes.h
 * @author Christian Neukam
 * @brief Definition os DMX data types.
 * @version 1.0
 * @date 2024-01-21
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
#ifndef __MIDIDMXBRIDGE_DMXTYPES_H__
#define __MIDIDMXBRIDGE_DMXTYPES_H__

#include <stdint.h>

#ifndef ARDUINO
#include <functional>
#endif

#include "midi_dmx/vector.h"

namespace mididmxbridge {
using mididmxbridge::vector;

/**
 * @brief Definition of the callback signature.
 *
 */
#ifdef ARDUINO
using DmxOnChangeCallback = void (*)(const uint8_t channel, const uint8_t value);
#else
using DmxOnChangeCallback = std::function<void(const uint8_t, const uint8_t)>;
#endif

/**
 * @brief This struct defines a DMX color in the red-green-blue (RGB) domain.
 *
 */
struct DmxRgb {
  uint8_t red;   /**< the red color intensity in the range [0, 254] */
  uint8_t green; /**< the green color intensity in the range [0, 254] */
  uint8_t blue;  /**< the blue color intensity in the range [0, 254] */
};

/**
 * @brief This struct defines the DMX channels that are assigned to the primary colors red, green
 * and blue.
 *
 */
struct DmxRgbChannels {
  vector<uint8_t> red;   /**< the red DMX channels */
  vector<uint8_t> green; /**< the green DMX channels */
  vector<uint8_t> blue;  /**< the blue DMX channels */
};
}  // namespace mididmxbridge
#endif
