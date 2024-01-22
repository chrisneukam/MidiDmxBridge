/**
 * @file MidiReader.cpp
 * @author Christian Neukam
 * @brief Implementation of the mididmxbridge::midi::MidiReader class
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
#include "MidiReader.h"

#include "ISerialReader.h"
#include "util.h"

namespace mididmxbridge::midi {
using namespace mididmxbridge::util;

/**
 * @brief Normalize the input MIDI channel.
 *
 * MIDI nominally uses channels in the range [1, 16]. However, 4-bit values in the range [0, 15] are
 * transmitted at protocol level. With this function, the input values are normalized and clipped to
 * the value range of the protocol level.
 *
 * @param[in] channel the MIDI channel
 * @return uint8_t - the normalized MIDI channel in the range [0, 15]
 */
static uint8_t normalizeChannel(const uint8_t channel) {
  const uint8_t minMidiChannel = 1;
  const uint8_t maxMidiChannel = 16;
  return max_t(minMidiChannel, min_t(maxMidiChannel, channel)) - minMidiChannel;
}

MidiReader::MidiReader(const uint8_t channel, ISerialReader& serial)
    : mMidiCcSyncFilter(0xb0 | (0x0f & normalizeChannel(channel))), mSerial(serial) {}

void MidiReader::begin() { mSerial.begin(); }

bool MidiReader::syncCc() {
  bool returnValue = false;

  while (mSerial.available()) {
    uint8_t value = (uint8_t)mSerial.read();

    if (value == mMidiCcSyncFilter) {
      returnValue = true;
      break;
    }
  }

  return returnValue;
}

bool MidiReader::readByte(uint8_t& data) {
  bool returnValue = false;
  const uint8_t byte = (uint8_t)mSerial.read();

  if (!(byte & 0x80)) {
    data = byte;
    returnValue = true;
  }

  return returnValue;
}

bool MidiReader::readCc(uint8_t& controller, uint8_t& value) {
  bool returnValue = false;

  if (syncCc() && (mSerial.available() >= 2)) {
    returnValue = readByte(controller) & readByte(value);
  }

  return returnValue;
}
}  // namespace mididmxbridge::midi
