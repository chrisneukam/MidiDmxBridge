/**
 * @file constants.h
 * @author Christian Neukam
 * @brief Definition of shared constant values
 * @version 1.0
 * @date 2024-01-10
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
#ifndef __MIDIDMXBRIDGE_CONSTANTS_H__
#define __MIDIDMXBRIDGE_CONSTANTS_H__

#include <stdint.h>

namespace mididmxbridge {
const uint8_t kMaxMidiValue = 0x7f;                      /**< maximum possible MIDI value */
const uint8_t kAnalogReadBits = 10;                      /**< bit resolution of analog read */
const uint16_t kUnityGainValue = (1 << kAnalogReadBits); /**< factor for unity gain */
}  // namespace mididmxbridge
#endif
