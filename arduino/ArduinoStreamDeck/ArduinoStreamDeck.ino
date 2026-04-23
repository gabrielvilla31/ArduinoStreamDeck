/*
  created 2025
  by Gaby
  
*/
#define DELAY_HOLD      1000

// constants won't change. They're used here to set pin numbers:
const int buttonPin1 = 5;   // (D1)
const int buttonPin2 = 4;   // (D2)
const int buttonPin3 = 14;  // (D5)
const int buttonPin4 = 12;  // (D6)


// variables will change:
unsigned long button1PressStart = 0; // Time when button was pressed
bool button1PreviouslyPressed = false;
bool button1_hold_sent = false;

unsigned long button2PressStart = 0; // Time when button was pressed
bool button2PreviouslyPressed = false;
bool button2_hold_sent = false;

unsigned long button3PressStart = 0; // Time when button was pressed
bool button3PreviouslyPressed = false;
bool button3_hold_sent = false;

unsigned long button4PressStart = 0; // Time when button was pressed
bool button4PreviouslyPressed = false;
bool button4_hold_sent = false;

//print template to use <<
template <typename T>
Print& operator<<(Print& printer, T value)
{
    printer.print(value);
    return printer;
}

void setup() {
   Serial.begin(9600); // Serial port on 9600 bauds

  // initialize the LED pin as an output:
  // initialize the pushbutton pins as an input (up):
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // read the state of the pushbuttons values:
  //1 if untouched, 0 if pressed
  bool button1_pressed = digitalRead(buttonPin1) == LOW;  
  bool button2_pressed = digitalRead(buttonPin2) == LOW;  
  bool button3_pressed = digitalRead(buttonPin3) == LOW;  
  bool button4_pressed = digitalRead(buttonPin4) == LOW;  


  if (button1_pressed) {
    if (!button1PreviouslyPressed) {
      // Le bouton vient juste d’être pressé
      button1PressStart = millis();
      button1PreviouslyPressed = true;
    }

    if (millis() - button1PressStart >= DELAY_HOLD && !button1_hold_sent) {
      button1_hold_sent=true;
      Serial<<"Button 1/Hold";
    }
  }
  else {
    if (button1PreviouslyPressed && !button1_hold_sent) {
      Serial<<"Button 1/Press";
    }

    button1_hold_sent=false;
    button1PreviouslyPressed = false;
  }

  if (button2_pressed) {
    if (!button2PreviouslyPressed) {
      // Le bouton vient juste d’être pressé
      button2PressStart = millis();
      button2PreviouslyPressed = true;
    }

    if (millis() - button2PressStart >= DELAY_HOLD && !button2_hold_sent) {
      button2_hold_sent=true;
      Serial<<"Button 2/Hold";
    }
  }
  else {
    if (button2PreviouslyPressed && !button2_hold_sent) {
      Serial<<"Button 2/Press";
    }

    button2_hold_sent=false;
    button2PreviouslyPressed = false;
  }
  
  if (button3_pressed) {
    if (!button3PreviouslyPressed) {
      // Le bouton vient juste d’être pressé
      button3PressStart = millis();
      button3PreviouslyPressed = true;
    }

    if (millis() - button3PressStart >= DELAY_HOLD && !button3_hold_sent) {
      button3_hold_sent=true;
      Serial<<"Button 3/Hold";
    }
  }
  else {
    if (button3PreviouslyPressed && !button3_hold_sent) {
      Serial<<"Button 3/Press";
    }

    button3_hold_sent=false;
    button3PreviouslyPressed = false;
  }

  if (button4_pressed) {
    if (!button4PreviouslyPressed) {
      // Le bouton vient juste d’être pressé
      button4PressStart = millis();
      button4PreviouslyPressed = true;
    }

    if (millis() - button4PressStart >= DELAY_HOLD && !button4_hold_sent) {
      button4_hold_sent=true;
      Serial<<"Button 4/Hold";
    }
  }
  else {
    if (button4PreviouslyPressed && !button4_hold_sent) {
      Serial<<"Button 4/Press";
    }

    button4_hold_sent=false;
    button4PreviouslyPressed = false;
  }

  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(50);                      // wait for 50 ms
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW

}
