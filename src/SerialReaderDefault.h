/**
 * @file SerialReaderDefault.h
 * @author Christian Neukam
 * @brief Default implementation of the MidiDmxBridge::ISerialReader interface.
 * @version 1.0
 * @date 2024-01-15
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
#ifndef __MIDIDMXBRIDGE_SERIAL_READER_DEFAULT_H__
#define __MIDIDMXBRIDGE_SERIAL_READER_DEFAULT_H__

#ifdef ARDUINO
#include <Arduino.h>
#include <SoftwareSerial.h>

#include "ISerialReader.h"

#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(__AVR_ATmega32U4__)
#define kRxPin 10 /**< the software serial RX pin */
#define kTxPin 11 /**< the software serial TX pin (not used further) */
#else
#define kRxPin 2 /**< the software serial RX pin */
#define kTxPin 3 /**< the software serial TX pin (not used further) */
#endif

/**
 * @brief Default implementation of the mididmxbridge::ISerialReader interface.
 *
 * As the interface mididmxbridge::ISerialReader is defined as an abstraction layer
 * of the Arduino Serial API it just forwards the calls.
 *
 * Because the DMX serial library already uses the UART/Serial adapter with a
 * DMX baud rate of 250000, the serial adapter for receiving MIDI control
 * signals must be connected to the software serial adapter with a baud rate of
 * 31500.
 *
 * The default implementation is using the following digital pins for input and output depending
 * on the Arduino board:
 *
 * Mega, Mega 2560, Leonardo and Micro:
 *  - ::kRxPin (10) for receiving data bytes
 *  - ::kTxPin (11) for sending data, not used
 *
 * other Arduino boards:
 *  - ::kRxPin (2) for receiving data bytes
 *  - ::kTxPin (3) for sending data, not used
 *
 * @see https://docs.arduino.cc/learn/built-in-libraries/software-serial/
 *
 */
class SerialReaderDefault : public mididmxbridge::ISerialReader {
 public:
  /**
   * @brief Construct a new SerialReaderDefault object.
   *
   * Initialize the software serial adapter at the MIDI baud rate.
   *
   */
  SerialReaderDefault() : mRxPin(kRxPin), mTxPin(kTxPin), mSoftSerial(kRxPin, kTxPin) {}

  /**
   * @brief Construct a new SerialReaderDefault object.
   *
   * Initialize the software serial adapter at the MIDI baud rate and the given IO pins.
   *
   * @param[in] rxPin the input pin receiving the serial data
   * @param[in] txPin the output pin for transmitting the serial data
   */
  SerialReaderDefault(const uint8_t rxPin, const uint8_t txPin)
      : mRxPin(rxPin), mTxPin(txPin), mSoftSerial(rxPin, txPin) {}

  /**
   * @brief Destroy the SerialReaderDefault object
   *
   */
  ~SerialReaderDefault() = default;

  void begin() override {
    pinMode(mRxPin, INPUT);
    pinMode(mTxPin, OUTPUT);

    mSoftSerial.begin(31250);
  }

  int available() override { return mSoftSerial.available(); }

  int read() override { return mSoftSerial.read(); }

  void sleep(uint16_t sleep_ms) override { delay(sleep_ms); }

 private:
  const uint8_t mRxPin;       /**< the receiving input pin */
  const uint8_t mTxPin;       /**< the transmission output pin */
  SoftwareSerial mSoftSerial; /**< the software serial adapter */
};
#endif
#endif
