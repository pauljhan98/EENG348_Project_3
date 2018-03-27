int input_pin = A0;                // Pin where voltage from voltage divider is taken as input
int red_pin = 8;                  // Pin where analog value is output to power red LED
int input_voltage = 0;            // The unmodified input voltage
int adjusted_voltage = 0;         // The adjusted input voltage


void setup() {
  pinMode(input_pin, INPUT);
  pinMode(red_pin, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  input_voltage = analogRead(input_pin);                      // Takes the input voltage, then maps it to some value [0, 1023]
  adjusted_voltage = map(input_voltage, 0, 1023, 0, 255);     // We want to re-map the input voltage value to the range [0, 255]

  Serial.print("Input voltage : ");  // Print the input voltage; mapped [0, 5], to [0, 1023]
  Serial.println(input_voltage);

  Serial.print("Adjusted voltage : ");  // Print the output voltage to LED; mapped [0, 5], to [0, 255]
  Serial.println(adjusted_voltage);

  analogWrite(red_pin, adjusted_voltage);  // Output voltage to power RGB LED

  delay(500); //temp. for debugging

}
