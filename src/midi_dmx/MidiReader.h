/**
 * @file MidiReader.h
 * @author Christian Neukam
 * @brief Definition of the mididmxbridge::midi::MidiReader class
 * @version 1.0
 * @date 2023-12-31
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
#ifndef __MIDIDMXBRIDGE_MIDI_READER_H__
#define __MIDIDMXBRIDGE_MIDI_READER_H__

#include <stdint.h>

namespace mididmxbridge {
class ISerialReader; /**< forward declaration */
}

namespace mididmxbridge::midi {
/**
 * @brief This class defines the reading feature for MIDI data.
 *
 */
class MidiReader {
 public:
  /**
   * @brief Construct a new MidiReader object.
   *
   * As MIDI channels are usually 1-indexed and therefore cover a value range of [1, 16] with a
   * 4-bit resolution, this nominal value is also used here. If this value range is exceeded, the
   * channel is clipped to the next limit, e.g. 0 -> 1 or 17 -> 16.
   *
   * @param[in] channel the MIDI channel to listen to in the range [1, 16]
   * @param[in] serial the serial interface
   */
  MidiReader(const uint8_t channel, ISerialReader& serial);

  /**
   * @brief Destroy the MidiReader object.
   *
   */
  virtual ~MidiReader() = default;

  /**
   * @brief Initialize the MidiReader object.
   *
   */
  void begin();

  /**
   * @brief Read the next MIDI Continuous Controller (CC) from the serial interface.
   *
   * @param[out] controller the MIDI CC controller, i.e. the second MIDI byte
   * @param[out] value the MIDI CC controller value, i.e. the third MIDI byte
   * @return true - the \p controller and \p value got updated
   * @return false - otherwise
   */
  bool readCc(uint8_t& controller, uint8_t& value);

 private:
  /**
   * @brief Search the MIDI Continuous Controller (CC) sync byte.
   *
   * The sync byte is the or-link between the MIDI CC signature 0xB0 and the MIDI channel 0x0*, e.g.
   * 0xB5 by using channel 5.
   *
   * @return true - the sync byte was found
   * @return false - otherwise
   */
  bool syncCc();

  /**
   * @brief Read the next MIDI byte.
   *
   * The next byte is transferred if it is in the permitted range [0x00, 0x7f]. Otherwise, the
   * parameter \p data is not modified and `false` is returned.
   *
   * @param[out] date the next MIDI byte if it is in the range [0x00, 0x7f]
   * @return true - the byte is in the allowed range
   * @return false - otherwise
   */
  bool readByte(uint8_t& date);

  const uint8_t mMidiCcSyncFilter; /**< the MIDI CC sync byte to listen to */
  ISerialReader& mSerial;          /**< the serial interface */
};
}  // namespace mididmxbridge::midi
#endif
