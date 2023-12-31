// MUX Parameters
// signal pins
int signal0 = 4;
int signal1 = 15;
int signal2 = 8;
// enable pins
int enableMux0 = 16;
int enableMux1 = 14;
int enableMux2 = 10; 
// common signal
int muxCommon = 7;

// Array to store the previous state of each button
int previousButtonState[24] = { 0 };  // Updated array size

void setup() {
  Serial.begin(9600);
  pinMode(muxCommon, INPUT_PULLUP);

  pinMode(signal0, OUTPUT);
  pinMode(signal1, OUTPUT);
  pinMode(signal2, OUTPUT);

  pinMode(enableMux0, OUTPUT);
  pinMode(enableMux1, OUTPUT);
  pinMode(enableMux2, OUTPUT);
}

void loop() {
  buttonMux();
}

void handleButtonPress(int i) {
  Serial.print("Button ");
  Serial.print(i);
  Serial.println(" Pressed!");
}

void handleButtonRelease(int i) {
  Serial.print("Button ");
  Serial.print(i);
  Serial.println(" Released!");
}

void buttonMux() {
  // Loop through all the button channels on the MUX
  for (int i = 0; i < 24; ++i) {
    // Enable the appropriate MUX
    enableMux(i < 8 ? 0 : (i < 16 ? 1 : 2));

    // Control the selector pins based on the binary representation of i
    digitalWrite(signal0, (i & 0x01) ? HIGH : LOW);
    digitalWrite(signal1, (i & 0x02) ? HIGH : LOW);
    digitalWrite(signal2, (i & 0x04) ? HIGH : LOW);

    // Read the value from the selected button
    int buttonValue = digitalRead(muxCommon);
    // Serial.println(buttonValue);

    // Check for button press
    if (buttonValue == 0 && previousButtonState[i] == 0) {
      // Button is pressed
      handleButtonPress(i);
      previousButtonState[i] = 1;
    }
    // Check for button release
    else if (buttonValue > 0 && previousButtonState[i] == 1) {
      // Button is released
      handleButtonRelease(i);
      previousButtonState[i] = 0;
    }
  }
}

void enableMux(int mux) {
  switch (mux) {
    case 0:
      digitalWrite(enableMux0, LOW);
      digitalWrite(enableMux1, HIGH);
      digitalWrite(enableMux2, HIGH);
      break;
    case 1:
      digitalWrite(enableMux0, HIGH);
      digitalWrite(enableMux1, LOW);
      digitalWrite(enableMux2, HIGH);
      break;
    case 2:
      digitalWrite(enableMux0, HIGH);
      digitalWrite(enableMux1, HIGH);
      digitalWrite(enableMux2, LOW);
      break;
  }
}
