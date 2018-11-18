
int buttonPins [4] = {25, 26, 27, 28};
boolean lastButtonState [4] = {LOW, LOW, LOW, LOW};
boolean buttonState[4] = {LOW, LOW, LOW, LOW};
boolean on[4] = {false, false, false, false};
int midiNotes [4] = {38, 42, 45, 48};
int startTimes [3][4];
//for loop in setup multi array 3 of 4 -- place random numbers , check every time millis -- moves forward
//generate sequence -- loop generate sequence (generateSequence();) mode ;; within array, check current time, if it has become that time, if so turn note on
// auto sequence (randomized)
// (in setup) -- for (int j = 0; i < 4; i++)
//  int x = RandomNumberGenerator-range set from 0-3
//  pinMode(buttonPins[x], INPUT);
//  to start, send "open MIDI message"
//  to stop, send "close MIDI message"

void setup() {

  for (int i = 0; i < 4; i++) {
    pinMode(buttonPins[i], INPUT);
  }
}

void loop() {

  checkButton();

}

void checkButton() {

  for (int i = 0; i < 4; i++) {

    lastButtonState[i] = buttonState[i];
    buttonState[i] = digitalRead(buttonPins[i]);

    if (buttonState[i] == HIGH && lastButtonState[i] == LOW) {
      on[i] = !on[i];

      if (on[i] == true) {
        usbMIDI.sendNoteOn (midiNotes[i], 127, 1);
      }
      else if (on[i] == false) {
        usbMIDI.sendNoteOff (midiNotes[i], 127, 1);
      }

    }
  }
}
