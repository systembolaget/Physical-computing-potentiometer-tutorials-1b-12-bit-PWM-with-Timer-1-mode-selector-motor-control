// Tutorial 1b3. Motor control

// Main parts: Adafruit Metro Mini, L293D, DC motor, potentiometer,
// capacitor, LEDs, resistors

// Variables that remain constant
const byte pinPotentiometer = A0; // Analog input pin from potentiometer
const byte pinLEDG = 4; // Green LED pin number
const byte pinLEDR = 6; // Red LED pin number
const byte pin21A = 9; // Motor driver pin number (L293D pin 2 1A)
const byte pin72A = 10; // Motor driver pin number (L293D pin 7 2A)

// Variables that can change
int readingPotentiometer;

void setup()
{
  // Serial printing only necessary to see the changing values
  Serial.begin(9600);

  // Initialise Metro Mini's digital pins specified above
  pinMode(pinLEDG, OUTPUT);
  pinMode(pinLEDR, OUTPUT);
  pinMode(pin72A, OUTPUT);
  pinMode(pin21A, OUTPUT);
}

void loop()
{
  // The potentiometer is hardware smoothed with a 10uF capacitor; no code
  // is necessary. Read the voltage from the potentiometer pin
  readingPotentiometer = analogRead(pinPotentiometer);
  
  // A bit shift to the right divides the values 0 to 1023 by 2 (= 0 to 511)
  // A useful technique to divide by powers of two; >> 2 would divide by 4,
  // >> 3 would divide by 8, and so forth. "<<" multiplies correspondingly
  readingPotentiometer = readingPotentiometer >> 1;

  // Test if the potentiometer is turned to the right of the deadband, see
  // at the end
  if (readingPotentiometer > 265)
  {
    // If it is, turn the L293D's direction pin 1A off
    digitalWrite(pin21A, 0);

    // And turn the direction pin 2A on, with a PWM value (duty cycle) of
    // 0 - 255
    analogWrite(pin72A, (readingPotentiometer - 256));

    // Also turn the "starboard" (right) green LED on, and the red LED off
    digitalWrite(pinLEDG, HIGH); digitalWrite(pinLEDR, LOW);

    // Only to observe the changing values
    Serial.print("Forward: "); Serial.println(readingPotentiometer - 256);
  }

  // Test if the potentiometer is turned to the left of the deadband, see
  // at the end
  else if (readingPotentiometer < 245)
  {
    // If it is, turn the L293D's direction pin 1A on, with a PWM value
    // (duty cycle) of 0 - 255
    analogWrite(pin21A, (255 - readingPotentiometer));

    // And turn the direction pin 2A off
    digitalWrite(pin72A, 0);

    // Also turn the "port" (left) red LED on, and the green LED off
    digitalWrite(pinLEDR, HIGH); digitalWrite(pinLEDG, LOW);

    // Only to observe the changing values
    Serial.print("Backward: "); Serial.println(255 - readingPotentiometer);
  }

  // You have seen above we don't test for < or > 255, but a bit more and
  // less. This "deadband" provides a small region where the potentiometer
  // knob is centered to turn the motor off. For a real-world design, you
  // would buy a potentiometer with a center detent to provide tactile user
  // feedback! So, otherwise, if the potentiometer knob is centered
  else
  {
    // Turn off both direction pins, so that the motor stops
    digitalWrite(pin72A, 0);
    digitalWrite(pin21A, 0);

    // And also turn both indicator LEDs off
    digitalWrite(pinLEDG, LOW); digitalWrite(pinLEDR, LOW);

    // Only to observe the changing values
    Serial.print("Deadband: "); Serial.println(readingPotentiometer);
  }
}
