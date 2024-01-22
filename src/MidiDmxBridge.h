/**
 * @file MidiDmxBridge.h
 * @author Christian Neukam
 * @brief API header file of the MidiDmxBridge library.
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
#ifndef __MIDIDMXBRIDGE_H__
#define __MIDIDMXBRIDGE_H__

#include "DmxTypes.h"
#include "ISerialReader.h"
#include "SerialReaderDefault.h"
#include "midi_dmx/Dmx.h"
#include "midi_dmx/MidiReader.h"
#include "midi_dmx/vector.h"

using mididmxbridge::DmxOnChangeCallback;
using mididmxbridge::DmxRgb;
using mididmxbridge::DmxRgbChannels;
using mididmxbridge::ISerialReader;
using mididmxbridge::dmx::Dmx;
using mididmxbridge::midi::MidiReader;

namespace mididmxbridge {
class ISleep; /**< forward declaration */
}

/**
 * @brief This class defines the API of the MidiDmxBridge library.
 *
 * With the help of this API, MIDI Continuous Controller (CC) signals can be converted into DMX
 * control signals. The MIDI data is provided via a serial interface, which is abstracted via
 * mididmxbridge::ISerialReader and must be implemented by the application.
 *
 * As soon as valid MIDI CC signals are received via a specific MIDI channel, a
 * mididmxbridge::dmx::DmxOnChangeCallback callback is triggered, which contains the current DMX
 * control signals. One callback is triggered for each MIDI CC signal received.
 *
 * In order to adapt the brightness of the connected lighting to the local conditions, a gain can be
 * set to adjust the brightness. The signal can only be attenuated.
 *
 */
class MidiDmxBridge {
 public:
  /**
   * @brief Construct a new MidiDmxBridge object.
   *
   * @param[in] channel the MIDI channel to listen to in the range [1, 16]
   * @param[in] callback the callback to trigger once the DMX values change
   * @param[in] serial the serial interface
   */
  MidiDmxBridge(const uint8_t channel, DmxOnChangeCallback callback, ISerialReader& serial);

  /**
   * @brief Destroy the MidiDmxBridge object.
   *
   */
  virtual ~MidiDmxBridge() = default;

  /**
   * @brief Initialize the MidiDmxBridge object.
   *
   * This function should be called before all other API functions in the Arduino sketch in setup().
   *
   */
  void begin();

  /**
   * @brief Setup the static scene.
   *
   * This function should be used in the Arduino sketch in setup() after begin().
   *
   * @param[in] channels the DMX channels associated with RGB
   * @param[in] rgb the RGB value to set
   */
  void setStaticScene(const DmxRgbChannels& channels, const DmxRgb& rgb);

  /**
   * @brief Sets the attenuation of the generated DMX signal.
   *
   * The attenuation shall be in the range [0, mididmxbridge::dmx::kUnityGainValue] otherwise it is
   * clipped whereas unity gain does mean no attenuation.
   *
   * This function should be used in the Arduino sketch in loop().
   *
   * @param[in] attenuation the integer based attenuation to apply
   */
  void setAttenuation(const uint16_t attenuation);

  /**
   * @brief Switch to the dynamic scene.
   *
   * If MIDI CC values are received via the listen() function, they are saved in the dynamic scene.
   *
   * This function can always be called after begin().
   *
   */
  void switchToDynamicScene();

  /**
   * @brief Switch to the static scene.
   *
   * The scene defined via setStaticScene() is output here.
   *
   * This function can always be called after begin().
   *
   */
  void switchToStaticScene();

  /**
   * @brief Listen on the serial interface for the next MIDI CC value and update the DMX state.
   *
   * This function should be used in the Arduino sketch in loop().
   *
   */
  void listen();

 private:
  mididmxbridge::ISleep& mSleep; /**< the sleep handler object */
  Dmx mDmx;                      /**< the DMX handler object */
  MidiReader mReader;            /**< the MIDI reader object */
};
#endif
