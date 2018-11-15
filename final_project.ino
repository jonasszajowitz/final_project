
int buttonPins [4] = {25, 26, 27, 28};
boolean lastButtonState [4] = {LOW, LOW, LOW, LOW};
boolean buttonState[4] = {LOW, LOW, LOW, LOW};
boolean on[4] = {false, false, false, false};

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
  
    }
  }
}
