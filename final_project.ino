
int buttonPins [8] = {25, 26, 27, 28, 33, 34, 36, 37};
int ledPins [8] = {1, 3, 5, 7, 9, 11, 22, 20, 18, 16};
int slideSwitch = 35;
boolean lastButtonState [8] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW};
boolean buttonState[8] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW};
boolean on[8] = {false, false, false, false, false, false, false, false};
unsigned long lastPress = 0;
int midiNotes [8] = {38, 42, 45, 48, 52, 56, 58, 62};
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

  for (int i = 0; i < 8; i++) {
    pinMode(buttonPins[i], INPUT);
    pinMode(ledPins[i], OUTPUT);
    pinMode(slideSwitch, INPUT);

  }
}

void loop() {

  if (digitalRead(slideSwitch) == HIGH) {
    manualMode();
  }
  if (digitalRead(slideSwitch) == LOW) {
    randomMode();
    manualMode();
  }
}

void manualMode() {

  if (lastPress + 200 > millis()) {
    return;
  }

  for (int i = 0; i < 8; i++) {

    lastButtonState[i] = buttonState[i];
    buttonState[i] = digitalRead(buttonPins[i]);

    if (buttonState[i] == HIGH && lastButtonState[i] == LOW) {

      lastPress = millis();

      triggerButton(i);
    }
  }
}

void randomMode() {

  if (random(1000000) == 1) {
    triggerButton(0);
  }
  if (random(1000000) == 3) {
    triggerButton(1);
    
  
  //will eventually add more to sequence 
  
  }
}

void triggerButton (int button) {

  on[button] = !on[button];

  if (on[button] == true) {
    usbMIDI.sendNoteOn (midiNotes[button], 127, 1);
    digitalWrite(ledPins[button], HIGH);
  }
  else if (on[button] == false) {
    usbMIDI.sendNoteOff (midiNotes[button], 127, 1);
    digitalWrite(ledPins[button], LOW);
  }

}
