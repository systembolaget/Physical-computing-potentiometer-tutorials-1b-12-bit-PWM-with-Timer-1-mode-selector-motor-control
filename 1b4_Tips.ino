// Tutorial 1b4. Tips

// Main parts: Adafruit Metro Mini, potentiometer, capacitors

// Variables that remain constant
const byte pinPotentiometer = A0; // Analog input pin from potentiometer

// Variables that can change
int i;
int n;
int readingPotentiometer;
int readingPotentiometerPrevious;
int badValueDistribution;
int goodValueDistribution;

void setup()
{
  // To observe the value changes in the serial monitor and plotter
  Serial.begin(9600); delay(5000);

  // Code in setup() is executed only once at the start
  for (i = 0; i <= 1023; ++i)
  {
    // You would expect that the range of values 0 to 1023 are evenly mapped
    // to the range of values 0 to 7, but they are not. The value 7 appears
    // only once at ADC value 1023! So, if the potentiometer knob rotation
    // (or sensor output on analog input pin) must be mapped correctly, you
    // must increment 1023 and 7 by one, so 1024 and 8
    n = map(i, 0, 1024, 0, 8);

    Serial.print(i);
    Serial.print(" is mapped to ");
    Serial.println(n);
  }
}

void loop()
{
  //Read the voltage from the potentiometer pin
  //readingPotentiometer = analogRead(pinPotentiometer);

  //Serial.println(readingPotentiometer);

  // The plus and minus 3 deliver a "deadband" to filter out noise
  /*if (readingPotentiometer < (readingPotentiometerPrevious - 3) || readingPotentiometer > (readingPotentiometerPrevious + 3))
    {
    // Update the value, which keeps it nicely static, see serial plotter
    readingPotentiometerPrevious = readingPotentiometer;
    Serial.println(readingPotentiometerPrevious);
    }*/

  // The potentiometer is 1. not hardware filtered, then 2. with a 100uf and
  // finally 3. with a 1000uF capacitor

  // Observe the serial plotter graph for 1., 2. and 3. while slowly rotating
  // the potentiometer knob, and then also rapidly rotating it from left to
  // right, and back. The higher the capacitor's capacitance (uF), the higher
  // the lag. So, choose the capacitance depending on the desired behaviour
  /*Serial.print("RawADC:"); Serial.print(readingPotentiometer);
    Serial.print(", ");
    Serial.println("Min:0,Max:1023");*/
}
