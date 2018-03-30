// Pins that take input from
// rotary encoder
int input_pin1 = 2;
int input_pin2 = 1;

// Counter that keeps track of saturating turns
// i.e [0,255] turns
int counter = 0; 

// Pins for color output
int blue_pin = 9;
int red_pin = 10;
int green_pin = 11;

// Color Values
// Set initial color values to zero
int red_value = 0;
int blue_value = 0;
int green_value = 0;

//Set initial states to zero
int state = 0;
int prior_state = 0;  


// Pin where analog input is output
int output_voltage_pin = 3;
double adjusted_voltage = 0;


// Analog input pin that
// reads the voltage from the
// voltage divider
int photo_res_pin = A0;

// Stores value of input 
// voltage from voltage divider
int input_voltage = 0;

 
void setup() { 

   // Pins for digital input from rotary encoder
   pinMode(input_pin1, INPUT);
   pinMode(input_pin2, INPUT);


   // Pins for analog output for rgb led
   pinMode(blue_pin, OUTPUT);
   pinMode(red_pin, OUTPUT);
   pinMode(green_pin, OUTPUT);

   pinMode(photo_res_pin, INPUT);
   pinMode(output_voltage_pin, OUTPUT);

   // Setting rotary input pins to high so we can get input
   // The rotary is connected to ground
   digitalWrite(input_pin1, HIGH);
   digitalWrite(input_pin2, HIGH);
   
   Serial.begin(9600);  
 } 

void loop() { 
  
   // Read the voltage, then adjust it and constrain it
   // to a useful output
   input_voltage = analogRead(photo_res_pin);
   adjusted_voltage = constrain((6.5*(map(input_voltage, 0, 1023, 0, 255))),0,255); 

   // adjusted_voltage controls the intensity of the LED
   analogWrite(output_voltage_pin, adjusted_voltage);


   // Reads the current state
   // and checks against prior_state
   // to see if the state changed
   // if state changed, encoder has rotated
   state = digitalRead(input_pin1);             

   if (state != prior_state)
   {
    // A delay here could be useful for debouncing, however we
    // found that after accidently breaking off the rotary pins and
    // re-soldering, debouncing / delaying was not needed for our rotary.
     
    // delay(10);  
      
    // Rotating in one direction
     if (digitalRead(input_pin2) != state)   
     { 
       if (counter <= 254)
       {
        counter = counter + 1;
        Serial.println(counter);
       }
     } 
     else 
     {
      // Rotating in opposite direction
      if (counter >= 1)
      {
       counter = counter - 1;
       Serial.println(counter);
      }
     }

     // Serial Outputs for Debugging
     // Serial.print("Value: ");
     // Serial.println(counter);

     // Serial.print("green value: ");
     // Serial.println(green_value);

     // Serial.print("blue value: ");
     // Serial.println(blue_value);
    
     // Serial.print("red value: ");
     // Serial.println(red_value);
   } 
   prior_state = state;                       

   // Change the color and color output,
   // Depending on the current value of
   // counter
   color_change();
   color_output();
 }



// The color_change function provides a rudamentary color wheel that changes the color of the LED
// When a color_value is high, i,e 255, the output voltage on the output pin matches the voltage
// being input to the LED. Since delta V is equal to zero, no current flows and the LED does not
// light up. When we decrease a color_value, delta V increases, causing current to flow and 
// causes the corresponding LED to light up.

 void color_change()
 {
  // Case 1
   if ((counter >= 0) && (counter <= 43))
   {    
    red_value = 0;
    blue_value = 255;   
    green_value = 255 - 5*(counter);   
   }
 
 // Case 2
   if ((counter >= 44) && (counter <= 85))
   {
    green_value = 0;
    blue_value = 255;
    red_value = 0 + 6*(counter - 44);
   }

 // Case 3
   if ((counter >= 86) && (counter <= 127))
   {
    green_value = 0;
    blue_value = 255 - 6*(counter - 86);
    red_value = 255;  
   }

 // Case 4
   if ((counter >= 128) && (counter <= 170))
   {
     red_value = 255;
     green_value = 0 + 6*(counter - 128);
     blue_value = 0;
   }

 // Case 5
   if ((counter >= 171) && (counter <= 213))
   {
    red_value = 255 - 6*(counter - 171);
    green_value = 255;
    blue_value = 0;
   }

// Case 6
   if ((counter >= 214) && (counter <= 255))
   {
    red_value = 0;
    green_value = 255;
    blue_value = 0 + 6*(counter - 214);
   } 
 }


// Outputs the colors of the LED

 void color_output()
 {
  analogWrite(red_pin, red_value);
  analogWrite(blue_pin, blue_value);
  analogWrite(green_pin, green_value); 
 }

