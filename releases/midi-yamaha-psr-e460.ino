/*
  Midi Out USB Yamaha PSR-E360
    - plug in usb cable starts midi out automatically if you use it on computer (devicename=leonardo)
    - attention: plugged in usb cable may consume battery from tablet even the keyboard is off
    - unplug usb cable to deactivating midi
*/

#include "MIDIUSB.h"

// Flags for status displays and pulse processing
bool impulsCounterIsRunning = LOW;     // Indicates whether the pulse counter is active
bool impulsCounterStatusImpuls = LOW;  // Status of the detected pulse
bool validImpuls = LOW;                // Valid pulse detected
bool pressedAnalogPin = LOW;           // Indicates if an analog pin was pressed
// Counters and values for pulse processing
int impulsCounterIsRunningValue = 0;  // Counter value for active pulse
int impulsCounterDetectedImpuls = 0;  // Number of detected pulses
// Key status for the interval
bool keyWasPressedinLastInterval[61];  // Stores whether a key was pressed in the last interval
// Musical parameters
const int octave = 36;  // Current octave (36 = C, +12 for next octave)
int key = 0;      // Current key
// Pin assignment
int selectedAnalogPin = 5;   // Selected analog pin
int selectedDigitalPin = 0;  // Selected digital pin
// matrix for notes: [analogPins][digitalPins]
const int note[6][12] = {
  { 0, 6, 12, 18, 24, 30, 0, 36, 42, 48, 54, 60 },
  { 0, 3, 9, 15, 21, 27, 33, 0, 39, 45, 51, 57 },
  { 0, 2, 8, 14, 20, 26, 32, 0, 38, 44, 50, 56 },
  { 0, 5, 11, 17, 23, 29, 35, 0, 41, 47, 53, 59 },
  { 0, 4, 10, 16, 22, 28, 34, 0, 40, 46, 52, 58 },
  { 0, 1, 7, 13, 19, 25, 31, 0, 37, 43, 49, 55 }
};
// lookup table analog pins
const int analogPins[] = { 
  0, 5, 2, 1, 4, 3, 0, 5, 2, 1, 4, 3, 0, 5, 2, 1,
  4, 3, 0, 5, 2, 1, 4, 3, 0, 5, 2, 1, 4, 3, 0, 5,
  2, 1, 4, 3, 0, 5, 2, 1, 4, 3, 0, 5, 2, 1, 4, 3,
  0, 5, 2, 1, 4, 3, 0, 5, 2, 1, 4, 3, 0 };
// lookup table digital pins
const int digitalPins[] = { 
  0, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3,
  3, 3, 3, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 6,
  6, 6, 6, 6, 7, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9,
  9, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11 };

void setup() {
  // Configuration of analog inputs (columns)
  pinMode(A0, INPUT_PULLUP);  // INP1_2 COL
  pinMode(A1, INPUT_PULLUP);  // INP1_3 COL
  pinMode(A2, INPUT_PULLUP);  // INP1_6 COL
  pinMode(A3, INPUT_PULLUP);  // INP2_1 COL
  pinMode(A4, INPUT_PULLUP);  // INP2_4 COL
  pinMode(A5, INPUT_PULLUP);  // INP2_5 COL
  // Configuration of digital inputs (rows)
  pinMode(0, INPUT_PULLUP);   // OUT1_1 ROW
  pinMode(1, INPUT_PULLUP);   // OUT1_2 ROW
  pinMode(2, INPUT_PULLUP);   // OUT1_3 ROW
  pinMode(3, INPUT_PULLUP);   // OUT1_4 ROW
  pinMode(4, INPUT_PULLUP);   // OUT1_5 ROW
  pinMode(5, INPUT_PULLUP);   // OUT1_6 ROW
  pinMode(6, INPUT_PULLUP);   // OUT1_7 ROW
  pinMode(7, INPUT_PULLUP);   // OUT2_1 ROW
  pinMode(8, INPUT_PULLUP);   // OUT2_2 ROW
  pinMode(9, INPUT_PULLUP);   // OUT2_3 ROW
  pinMode(10, INPUT_PULLUP);  // OUT2_4 ROW
  pinMode(11, INPUT_PULLUP);  // OUT2_5 ROW
  // Configuration of debug output
  pinMode(13, OUTPUT);  // D13 Debug
  // Initialization of key status for the interval
  for (int i = 0; i < 61; i++) {
    keyWasPressedinLastInterval[i] = LOW;
  }
}
void loop() {
  do {
    // Filter for line disturbance (two pulses)
    // Start condition when the counter starts running
    if (impulsCounterIsRunning == LOW) {
      if (!digitalPinStatus(selectedDigitalPin))  // Is a digital pin low? (checked only once in the window)
      {
        // Start window to check if only 1 pulse comes
        impulsCounterIsRunning = HIGH;
        impulsCounterDetectedImpuls = 1;
        // Store the key status
        pressedAnalogPin = !(analogPinStatus(selectedAnalogPin));
      }
    }
    // If the pulse counter is running, check for multiple pulses; otherwise, set validImpuls to LOW
    if (impulsCounterIsRunning == HIGH) {
      impulsCounterIsRunningValue++;
      impulsCounterStatusImpuls = digitalPinStatus(selectedDigitalPin);
      if ((impulsCounterDetectedImpuls == 1) && (impulsCounterStatusImpuls == HIGH)) impulsCounterDetectedImpuls = 2;
      if ((impulsCounterDetectedImpuls == 2) && (impulsCounterStatusImpuls == LOW)) impulsCounterDetectedImpuls = 3;
      if ((impulsCounterDetectedImpuls == 3) && (impulsCounterStatusImpuls == HIGH)) {
        impulsCounterIsRunning = LOW;
        impulsCounterIsRunningValue = 0;
        validImpuls = LOW;
      }
    }
    // After 40 samples, stop sampling = window checking for two pulses
    // If no two pulses exist, the pulse counts as valid = validImpuls = HIGH
    if (impulsCounterIsRunningValue > 40)  // a good value as it lies outside the pulses
    {
      // Close window
      impulsCounterIsRunning = LOW;
      impulsCounterIsRunningValue = 0;
      validImpuls = HIGH;
    }
    // END Filtering
    // Only proceed with 1 pulse
  } while (validImpuls != HIGH);

  if (validImpuls == HIGH) {
    validImpuls = LOW;
    // Key not pressed but pressed in the last interval -> NoteOff
    if ((pressedAnalogPin == LOW) && (keyWasPressedinLastInterval[key] == HIGH)) {
      // Serial.println("NoteOff");
      noteOff(0, octave + note[selectedAnalogPin][selectedDigitalPin], 64);  // Channel 0, middle C, normal velocity
      MidiUSB.flush();
      keyWasPressedinLastInterval[key] = LOW;
    }
    // Key pressed but not pressed in the last interval -> NoteON
    if ((pressedAnalogPin == HIGH) && (keyWasPressedinLastInterval[key] == LOW)) {
      // Serial.println("NoteOn");
      noteOn(0, octave + note[selectedAnalogPin][selectedDigitalPin], 64);  // Channel 0, middle C, normal velocity
      MidiUSB.flush();
      keyWasPressedinLastInterval[key] = HIGH;
    }
    key++;
    if (key == 61) key = 0;
    selectedAnalogPin = analogPins[key];
    selectedDigitalPin = digitalPins[key];
  }
}
// Current status of the digital pins
bool digitalPinStatus(int i) {
  if (i == 0) return PIND & B00000100;
  if (i == 1) return PIND & B00001000;
  if (i == 2) return PIND & B00000010;
  if (i == 3) return PIND & B00000001;
  if (i == 4) return PIND & B00010000;
  if (i == 5) return PINC & B01000000;
  if (i == 6) return PIND & B10000000;
  if (i == 7) return PINE & B01000000;
  if (i == 8) return PINB & B00010000;
  if (i == 9) return PINB & B00100000;
  if (i == 10) return PINB & B01000000;
  if (i == 11) return PINB & B10000000;
}
// Current status of the analog pins
bool analogPinStatus(int i) {
  if (i == 0) return PINF & B10000000;
  if (i == 1) return PINF & B01000000;
  if (i == 2) return PINF & B00100000;
  if (i == 3) return PINF & B00010000;
  if (i == 4) return PINF & B00000010;
  if (i == 5) return PINF & B00000001;
}
// set midi comamnd
void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = { 0x09, 0x90 | channel, pitch, velocity };
  MidiUSB.sendMIDI(noteOn);
}
// reset midi command
void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = { 0x08, 0x80 | channel, pitch, velocity };
  MidiUSB.sendMIDI(noteOff);
}
