int trigger_pin = 9;               // Pin which sends a signal to trigger the ultrasonic sensor to take a reading 
int echo_pin = A0;                 // Pin which receives a timed pulse from sensor. Try pin 10 (digital) if pin A0 (analog) doesn't work
int red_pin = 10;                   // Pin where analog value is output to power red LED

long int time_value = 0;   //int to store the time of the pulse
float distance = 0;        //float to store the distance of the object from the sensor; try int if it doesn't work
int output_voltage = 0;    //value of analog output voltage

void setup() {
  pinMode(trigger_pin, OUTPUT);
  pinMode(echo_pin,INPUT);
  pinMode(red_pin, OUTPUT);
  Serial.begin(9600);

}

void loop() {

  digitalWrite(trigger_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_pin, LOW);

  time_value = pulseIn(echo_pin, HIGH);   // Records how long the pulse was

  distance = time_value / 58; //calculate the distance in cm
 
  // **************the range 0 to 1023 may need to change!! just a placeholder for now!!!*******************
 
  output_voltage = constrain((6.5*(map(input_voltage, 0, 1023, 0, 255))),0,255);     
  // We want to re-map the input voltage value to the range [0, 255] 
  // We multiply by 6.5 to account for the low input voltage     
  // Constrain is used to hard limit output values between 0 and 255  
  
  Serial.print("Distance (cm): ");
  Serial.println(distance);


  Serial.print("Output voltage: ");      // for debugging; output the voltage value [0,255].
  Serial.println(output_voltage);

  
  

  


  analogWrite(red_pin, output_voltage);
  delay(1000);                            //delay program by one second

}
