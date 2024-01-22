/**
 * @file ISleep.h
 * @author Christian Neukam
 * @brief Definition of the mididmxbridge::ISleep interface.
 * @version 1.0
 * @date 2024-01-06
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
#ifndef __MIDIDMXBRIDGE_I_SLEEP_H__
#define __MIDIDMXBRIDGE_I_SLEEP_H__

#include <stdint.h>

namespace mididmxbridge {

/**
 * @brief Interface of an object delaying/sleeping the current process.
 *
 */
class ISleep {
 public:
  /**
   * @brief Destroy the ISleep object.
   *
   */
  virtual ~ISleep() = default;

  /**
   * @brief Sleep the current thread for the given time.
   *
   * @param[in] sleep_ms the wait time in ms
   */
  virtual void sleep(uint16_t sleep_ms) = 0;
};
}  // namespace mididmxbridge
#endif
