// Tutorial 1b2. Mode selector

// Main parts: Adafruit Metro Mini, potentiometer, momentary switch,
// capacitors, LEDs, resistors

// Variables that remain constant
const byte pinSwitch = 8; // Digital input pin from momentary switch
const byte pinsLED[] = {3, 4, 5, 6}; // Array to store LED pin numbers
const size_t numLEDs = sizeof pinsLED / sizeof pinsLED[0]; // Find out and store size of the array
const unsigned long functionIntervals[numLEDs] = {7900, 4800, 2700, 1100}; // Array to store function durations

// Variables that can change
bool functionState[numLEDs] = {false}; // Array to store the running status of each function
unsigned long timestamp[numLEDs] = {0}; // Array to store a timestamp for each function
byte selection = 0;
byte lastSelection = 0;
bool lastSwitchState = HIGH; // Tracks the last switch state, open (= HIGH) at start

void setup()
{
  // Serial printing only necessary to understand which functions run
  Serial.begin(9600); delay(3000);

  // Loop through the array with the LED pin numbers
  for (byte i = 0; i < numLEDs; i++)
  {
    // And initialise Metro Mini's digital pins specified above
    pinMode(pinsLED[i], OUTPUT);
  }

  // Initialise momentary switch pin with an internal pull-up resistor so
  // that the momentary switch is read as open (= HIGH) at start
  pinMode (pinSwitch, INPUT_PULLUP);
}

void loop()
{
  // Self-explanatory; everything is broken up into simple functions
  checkSelection();
  setSelectionLED();
  checkSwitch();
  setFunction();
}

void setFunction()
{
  // Loop for as many times (i) as there are functions (and LEDs)
  for (byte i = 0; i < numLEDs; i++)
  {
    // If a function (i) ran for as long as its matching interval (i)
    if (millis() - timestamp[i] >= functionIntervals[i])
    {
      // Then set function (i)'s running status to "I'm done running!"
      functionState[i] = false;
    }

    // If a function (i) was allowed to run by the checkSwitch() function
    if (functionState[i] == true)
    {
      switch (i)
      {
        case 0: function0(); break; // Run function0()

        case 1: function1(); break; // Run function1()

        case 2: function2(); break; // Run function2()

        case 3: function3(); break; // Run function3()
      }
    }
  }
}

void setSelectionLED()
{
  // Check, if the potentiometer knob was rotated, and the selection changed
  if (lastSelection != selection)
  {
    // If it changed, first switch all LEDs off
    for (byte i = 0; i < numLEDs; i++)
    {
      digitalWrite(pinsLED[i], LOW);
    }

    // And switch on the LED that matches the new selection
    digitalWrite(pinsLED[selection], HIGH);

    // Remember the current selection for the next check
    lastSelection = selection;
  }
}

void checkSelection()
{
  // The potentiometer is hardware smoothed with a 10uF capacitor; no code
  // is necessary. Read the voltage from the potentiometer pin
  int readingPotentiometer = analogRead(A0);

  // Depending on the potentiometer knob rotation, set the selection
  // variable to the matching number. If a case matches, code execution
  // continues below the switch statement (= break keyword)
  switch (readingPotentiometer)
  {
    case 0 ... 255: selection = 0; break; // function0() = Red LED

    case 256 ... 511: selection = 1; break; // function1() = Yellow LED

    case 512 ... 767: selection = 2; break; // function2() = Green LED

    case 768 ...1023: selection = 3; break; // function3() = Blue LED
  }
}

void checkSwitch()
{
  // The momentary switch is hardware debounced with a 0.1uF capacitor; no
  // debouncing code is necessary. See http://www.gammon.com.au/switches
  // Read the voltage from the momentary switch pin to see if something
  // has changed (was the button pressed or released?)
  bool switchState = digitalRead (pinSwitch);

  // Has the momentary switch state changed since the last time it was
  // checked?
  if (switchState != lastSwitchState)
  {
    // Then, test if the switch was opened (button released)
    if (switchState == HIGH)
    {
      // If so, allow the selected function to run
      functionState[selection] = true;

      // And take the time of when that happened
      timestamp[selection] = millis();
    }

    // Last, store the current switch state for the next time around
    lastSwitchState =  switchState;
  }
}

// Each function can do something useful and, more importantly, do it
// independently from what another function is doing, because of the
// millis() approach explained above, instead of code-blocking delay()
void function0()
{
  Serial.println("function0"); // Only to see the function is running
}

void function1()
{
  Serial.println("function1");
}

void function2()
{
  Serial.println("function2");
}

void function3()
{
  Serial.println("function3");
}
