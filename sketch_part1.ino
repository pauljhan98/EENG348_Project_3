int input_pin = A0;                // Pin where voltage from voltage divider is taken as input
int red_pin = 9;                  // Pin where analog value is output to power red LED
int input_voltage = 0;            // The unmodified input voltage
int adjusted_voltage = 0;         // The adjusted input voltage


void setup() {
  pinMode(input_pin, INPUT);
  pinMode(red_pin, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  input_voltage = analogRead(input_pin);  // Takes the input voltage, then maps it to some value [0, 1023]
  
  adjusted_voltage = constrain((6.5*(map(input_voltage, 0, 1023, 0, 255))),0,255);     
  // We want to re-map the input voltage value to the range [0, 255] 
  // We multiply by 6.5 to account for the low input voltage     
  // Constrain is used to hard limit output values between 0 and 255                                                                            

  Serial.print("Input voltage : ");  // Print the input voltage; mapped [0, 5], to [0, 1023]
  Serial.println(input_voltage);

  Serial.print("Adjusted voltage : ");  // Print the output voltage to LED; mapped [0, 5], to [0, 255]
  Serial.println(adjusted_voltage);

  analogWrite(red_pin, adjusted_voltage);  // Output voltage to power RGB LED
  delay(1000);



}

//Implementing AnalogRead() using I/O Registers 
/*
        We first set which psin the ADC will read from using the ADMUX register.Bits 3:0 set which pin, and A0 is set by 0000.
   The ADC is started by writing 0 to the "Power Reduction ADC bit in the Power Reduction
Register (PRR.PRADC), and writing a '1' to the ADC Start Conversion bit in the ADC Control and Status
Register A (ADCSRA.ADSC)." We can determine when the ADC is finished by polling the ADSC bit, once the ADC has completed
the operation, it will go back to 0. Once it has gone back to zero we can read the 10-bit result from reading ADCL, which has the 
lower 8 bits, and ADCH, which has the upper 2 bits. We can discard bits 2-7 in ADCH.

*/
