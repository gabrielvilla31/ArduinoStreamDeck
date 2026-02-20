/*
  created 2025
  by Gaby
  
*/

// constants won't change. They're used here to set pin numbers:
const int buttonPin1 = 5;   // (D1)
const int buttonPin2 = 4;   // (D2)
const int buttonPin3 = 14;  // (D5)
const int buttonPin4 = 12;  // (D6)


// variables will change:
int button1_previous_state = 0;  // variable for reading the pushbutton status
int button1_state = 0;  // variable for reading the pushbutton status
int button2_previous_state = 0;  // variable for reading the pushbutton status
int button2_state = 0;  // variable for reading the pushbutton status
int button3_previous_state = 0;  // variable for reading the pushbutton status
int button3_state = 0;  // variable for reading the pushbutton status
int button4_previous_state = 0;  // variable for reading the pushbutton status
int button4_state = 0;  // variable for reading the pushbutton status
int valeur = 0; // Lire une valeur sur la broche A0

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
  button1_state = digitalRead(buttonPin1);
  button2_state = digitalRead(buttonPin2);
  button3_state = digitalRead(buttonPin3);
  button4_state = digitalRead(buttonPin4);

// check if the pushbuttons are pressed. If it is,send a message through:
  if (button1_state == LOW && button1_state != button1_previous_state) {
    Serial<<"Button 1"; 
  }
  if (button2_state == LOW && button2_state != button2_previous_state) {
    Serial<<"Button 2"; 
  }
  if (button3_state == LOW && button3_state != button3_previous_state) {
    Serial<<"Button 3";
   }
  if (button4_state == LOW && button4_state != button4_previous_state) {
    Serial<<"Button 4"; 
  }

  //Remember previous pushbuttons values
  button1_previous_state=button1_state;
  button2_previous_state=button2_state;
  button3_previous_state=button3_state;
  button4_previous_state=button4_state;
  
  //Serial<<"BouttonUp 1 : "<< buttonState1<<'\n'; // Envoyer la valeur via le port série
  //Serial<<"BouttonUp 2 : "<< buttonState2<<'\n'; // Envoyer la valeur via le port série
  //Serial<<"BouttonUp 3 : "<< buttonState3<<'\n'; // Envoyer la valeur via le port série
  //Serial<<"BouttonUp 4 : "<< buttonState4<<'\n'; // Envoyer la valeur via le port série
  

  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(50);                      // wait for 50 ms
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW

}
