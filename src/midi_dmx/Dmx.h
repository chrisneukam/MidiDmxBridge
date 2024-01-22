/**
 * @file Dmx.h
 * @author Christian Neukam
 * @brief Definition of the mididmxbridge::dmx::Dmx class
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
#ifndef __MIDIDMXBRIDGE_DMX_H__
#define __MIDIDMXBRIDGE_DMX_H__

#include "DmxTypes.h"
#include "DmxValue.h"
#include "constants.h"
#include "vector.h"

namespace mididmxbridge::dmx {
/**
 * @brief This class provides the processing of DMX values.
 *
 */
class Dmx {
 public:
  /**
   * @brief Construct a new Dmx object.
   *
   * An object created via this constructor calls the registered callback as soon as the DMX values
   * have changed.
   *
   * @param[in] callback the callback to trigger once the DMX values change
   */
  Dmx(DmxOnChangeCallback callback);

  /**
   * @brief Destroy the Dmx object.
   *
   */
  virtual ~Dmx() = default;

  /**
   * @brief Set the DMX gain.
   *
   * The gain is only updated if the parameter passed is outside the dead zone as indicated by
   * \p kGainDeadZone.
   *
   * The gain shall be in the range [0, ::kUnityGainValue] otherwise it is clipped.
   *
   * @param[in] gain the integer based gain value to apply
   */
  void setGain(const uint16_t gain);

  /**
   * @brief Set the DMX value pair based on a mididmxbridge::dmx::DmxValue.
   *
   * @param[in] dmxValue the DMX value pair to apply
   */
  void setDmxValue(const DmxValue& dmxValue);

  /**
   * @brief Set the DMX value pair based on MIDI CC values.
   *
   * @param[in] midiCcController the input MIDI CC controller
   * @param[in] midiCcValue the input MIDI CC value
   */
  void setMidiCcValue(const uint8_t midiCcController, const uint8_t midiCcValue);

  /**
   * @brief Setup the static RGB scene.
   *
   * @param[in] channels the DMX channels associated with RGB
   * @param[in] rgb the RGB value to set
   */
  void setStaticScene(const DmxRgbChannels& channels, const DmxRgb& rgb);

  /**
   * @brief Activate the static DMX scene.
   *
   * Only either the dynamic scene or the static scene can be active. The last request takes
   * over the scene.
   *
   * @see activateDynamicScene
   *
   */
  void activateStaticScene();

  /**
   * @brief Activate the dynamic DMX scene.77Only either the dynamic scene or the static scene can
   * be active. The last request takes over the scene.
   *
   * @see activateStaticScene
   *
   */
  void activateDynamicScene();

 private:
  /**
   * @brief Apply the supplied gain value to the DMX value.
   *
   * @param[in] value the DMX value to scale with the stored gain
   * @return uint8_t - the modified DMX value
   */
  uint8_t scaleValue(const uint8_t value) const;

  /**
   * @brief Update the current active DMX scene.
   *
   * @param[in] dmxValue the DMX value pair to apply
   * @return true - the active scene got updated
   * @return false - otherwise
   */
  bool updateScene(const DmxValue& dmxValue);

  /**
   * @brief Send the currently selected scene via the DmxOnChangeCallback callback.
   *
   */
  void sendScene() const;

  /**
   * @brief Blackout the currently **not** selected scene via the DmxOnChangeCallback callback.
   *
   */
  void blackoutScene() const;

  /**
   * @brief Register the color value on the specified DMX channels.
   *
   * @param[in] channels the DMX channels to assign the \p color to
   * @param[in] color the color value to assign
   */
  void setRgbColor(const vector<uint8_t>& channels, const uint8_t color);

  bool mUseDynamicScene;          /**< use the static scene if true, use dynamic otherwise */
  vector<DmxValue> mStaticScene;  /**< the static scene description */
  vector<DmxValue> mDynamicScene; /**< the dynamic scene description */
  uint16_t mGain;                 /**< the current DMX gain factor */
  DmxOnChangeCallback mCallback;  /**< the registered on-change callback */
};
}  // namespace mididmxbridge::dmx
#endif
