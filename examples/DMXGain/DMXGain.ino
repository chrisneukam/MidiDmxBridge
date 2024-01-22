/**
 * @file DMXGain.ino
 * @author Christian Neukam
 * @brief MidiDmxBridge library example to demonstrate the DMX gain functionality.
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
#include <MidiDmxBridge.h>

/**
 * @brief Implementation of the mididmxbridge::ISerialReader interface.
 *
 * In this example, the implementation of the mididmxbridge::ISerialReader interface simulates MIDI
 * CC data. The bytes 0xb0, 0x00 and 0x7f are provided cyclically.
 *
 */
class SerialReader : public mididmxbridge::ISerialReader {
 public:
  void begin() override {}

  int available() override { return 3; }

  int read() override { return data[(idx++) % 3]; }

  void sleep(uint16_t sleep_ms) override { delay(sleep_ms); }

 private:
  const uint8_t data[3] = {0xb0, 0x00, 0x7f}; /**< MIDI CC data to simulate */
  uint8_t idx = 0;                            /**< pointer to data */
};

/**
 * @brief Implementation of the callback mididmxbridge::dmx::DmxOnChangeCallback.
 *
 * This callback is always called as soon as a new DMX date is generated from a
 * different MIDI CC signal. The built-in LED lights up for different lengths of time depending on
 * the set gain value. The DMX data can then be sent further via a DMX library, e.g. DMXSerial.
 *
 * @see https://www.arduino.cc/reference/en/libraries/dmxserial/
 *
 * @param[in] channel the DMX channel in the range [1, 255]
 * @param[in] value the DMX value in the range [1, 255]
 */
void onDmxChange(const uint8_t channel, const uint8_t value) {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(value * 4);  // light up the LED
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000 - value * 4);  // switch off the LED until 1s is reached
}

#define kMidiChannel 1      /**< the MIDI channel to listen to in the range [1, 16] */
static SerialReader reader; /**< the implementation of mididmxbridge::ISerialReader */
static MidiDmxBridge MDXBridge(kMidiChannel, onDmxChange, reader); /**< the MidiDmxBridge object */
static uint16_t gain = 200; /**< initial DMX gain value, the valid range is [0, 1023] */

/**
 * @brief Setup the Arduino board.
 *
 */
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  MDXBridge.begin();
}

/**
 * @brief Main processing loop.
 *
 */
void loop() {
  MDXBridge.setAttenuation(gain);
  MDXBridge.listen();

  gain += 200;
  if (gain > 800) {
    gain = 200;
  }
}
