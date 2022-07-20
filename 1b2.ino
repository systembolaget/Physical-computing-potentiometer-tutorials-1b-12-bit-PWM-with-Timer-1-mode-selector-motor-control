// Tutorial 1b2. Mode selector

// Main parts: Adafruit Metro Mini, potentiometer, capacitor, LEDs,
// resistors

// Variables that remain constant
const byte pinPotentiometer = A0; // Analog input pin from potentiometer
const byte pinsLED[] = {3, 4, 5, 6,}; // Array to store the LED pin numbers
const size_t numLEDs = sizeof pinsLED / sizeof pinsLED[0]; // Find out and store size of the array
const int timeR = 4000; // Duration of how long each function shall run
const int timeY = 6000;
const int timeG = 7000;
const int timeB = 5000;

// Variables that can change
unsigned long timestampR = 0; // Timestamp of when a case was matched
unsigned long timestampY = 0;
unsigned long timestampG = 0;
unsigned long timestampB = 0;
bool runR = false; // Flag to allow a function to start running
bool runY = false;
bool runG = false;
bool runB = false;

void setup()
{
  // Serial printing only necessary to understand which functions run
  Serial.begin(9600);

  // Loop through the array with the LED pin numbers
  for (int i = 0; i < numLEDs; i++)
  {
    // Initialise Metro Mini's digital pins specified above
    pinMode(pinsLED[i], OUTPUT);
  }
}

void loop()
{
  // The potentiometer is hardware smoothed with a 10uF capacitor; no code
  // is necessary. Read the voltage from the potentiometer pin
  int readingPotentiometer = analogRead(A0);

  // Set a flag so in each case we can check if a function just ran, so
  // it can't be called immediately again, if the potentiometer knob was
  // not rotated. The keyword static means the variable is not created
  // and destroyed with every function call, but lives on and so retains
  // its value between function calls
  static char lastFunctionThatRan = -1;

  // Depending on the potentiometer rotation, each case in a switch case
  // statement allows for convenient setting of variables, flags or the
  // calling of functions that do something. If a case is matched, code
  // execution continues below the switch
  switch (readingPotentiometer)
  {
    case 0 ... 255:
      // If the flag for this case was set, continue below the switch
      if (lastFunctionThatRan == 0) break;
      // First, remember when the case was matched
      timestampR = millis();
      // Next, flag the function that shall run
      runR = true;
      // Then flag this case for being blocked if the potentiometer was
      // not rotated. This prevents this case's function from being run
      // immediately again instead of ending after the desired duration.
      // Each case has its own flag value, so a function can be run again
      // only if the potentiometer knob was rotated to another case first
      lastFunctionThatRan = 0;
      break;

    case 256 ... 511:
      if (lastFunctionThatRan == 1) break;
      timestampY = millis();
      runY = true;
      lastFunctionThatRan = 1;
      break;

    case 512 ... 767:
      if (lastFunctionThatRan == 2) break;
      timestampG = millis();
      runG = true;
      lastFunctionThatRan = 2;
      break;

    case 768 ...1023:
      if (lastFunctionThatRan == 3) break;
      timestampB = millis();
      runB = true;
      lastFunctionThatRan = 3;
      break;
  }

  // We check if the function's running time has not expired yet and if
  // it was flagged to run in the matching case
  if ((millis() - timestampR <= timeR) && (runR))
  {
    // If so, we keep calling the function
    functionR();

    // And keep the corresponding indicator LED switched on
    digitalWrite(pinsLED[3], HIGH); // Red LED
  }

  // Finally, when the function's running time has expired
  else
  {
    // The matching indicator LED is also switched off
    digitalWrite(pinsLED[3], LOW);
  }

  if ((millis() - timestampY <= timeY) && (runY))
  {
    functionY();
    digitalWrite(pinsLED[2], HIGH); // Yellow LED
  }
  else
  {
    digitalWrite(pinsLED[2], LOW);
  }

  if ((millis() - timestampG <= timeG) && (runG))
  {
    functionG();
    digitalWrite(pinsLED[1], HIGH); // Green LED
  }
  else
  {
    digitalWrite(pinsLED[1], LOW);
  }

  if ((millis() - timestampB <= timeB) && (runB))
  {
    functionB();
    digitalWrite(pinsLED[0], HIGH); // Blue LED
  }
  else
  {
    digitalWrite(pinsLED[0], LOW);
  }
}

// Each function can do something useful and, more importantly, doing
// it independently from what the other functions are doing. Because of
// the millis() approach, no code is blocking execution like delay()
void functionR()
{
  // Just to see that a function is running
  Serial.println("Function R is doing something");
}

void functionY()
{
  Serial.println("Function Y is doing another thing");
}

void functionG()
{
  Serial.println("Function G is doing something else");
}

void functionB()
{
  Serial.println("Function B is doing a different thing");
}
