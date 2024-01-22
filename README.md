# MIDI-DMX Bridge Arduino library

![Arduino Checks](https://github.com/chrisneukam/MidiDmxBridge/actions/workflows/arduino-checks.yml/badge.svg)
![Spell Check](https://github.com/chrisneukam/MidiDmxBridge/actions/workflows/spell-check.yml/badge.svg)
[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

This library allows you to translate MIDI Continuous Controller signals received at a user-defined channel into DMX commands. The library is compatible with Arduino boards and can be used to control DMX fixtures such as lights, fog machines, and more.

## Installation

1. Download the latest version of the library from the [GitHub repository](https://github.com/chrisneukam/MidiDmxBridge).
2. Extract the ZIP file and copy the folder to your Arduino libraries directory.
3. Restart the Arduino IDE.

## Usage

1. Include the library in your Arduino sketch by adding the following line at the beginning of your code:

```cpp
#include <MidiDmxBridge.h>
```

2. Define the callback method `mididmxbridge::dmx::DmxOnChangeCallback` with the signature `(const uint8_t, const uint8_t)`, which receives the DMX updates:

```cpp
static void onDmxChange(const uint8_t channel, const uint8_t value) {
}
```

3. Instantiate a `MidiDmxBridge` and `mididmxbridge::ISerialReader` object in you sketch:

```cpp
static SerialReaderDefault reader;
static MidiDmxBridge MDXBridge(kMidiChannel, onDmxChange, reader);
```

4. Initialize the library by calling the `begin()` function in the `setup()` function of your sketch:

```cpp
void setup() {
  MDXBridge.begin();
}
```

5. In the `loop()` function of your sketch, call the `listen()` function to listen to incoming MIDI messages and translate them into DMX commands:

```cpp
void loop() {
  MDXBridge.listen();
}
```

6. Use the `setAttenuation()` function to adjust the intensity of the dynamic and static scenes:

```cpp
MDXBridge.setAttenuation(512);
```

7. Use the `switchToDynamicScene()` function to switch to the dynamic scene:

```cpp
MDXBridge.switchToDynamicScene();
```

8. Use the `switchToStaticScene()` function to switch to the static scene:

```cpp
MDXBridge.switchToStaticScene();
```

## Example

Here's an example sketch that uses the library to control a DMX light fixture listening on MIDI channel 1 and using pins 3 and 4 for MIDI IO:

```cpp
#include <MidiDmxBridge.h>

static void onDmxChange(const uint8_t channel, const uint8_t value) {}

static SerialReaderDefault reader(3, 4);
static MidiDmxBridge MDXBridge(1, onDmxChange, reader);

void setup() {
  MIDI_DMX.begin();
  MDXBridge.setStaticScene();

}

void loop() {
  MDXBridge.setAttenuation(512);
  MDXBridge.listen();
  MDXBridge.switchToStaticScene();
  delay(1000);
  MDXBridge.switchToDynamicScene();
  delay(1000);
}
```

## License

This library is released under the Apache V2.0 License. See [LICENSE](./LICENSE) for more information.

Please let me know if you have any questions or feedback. I'm happy to help! 😊
