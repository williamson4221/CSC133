/*===========================================================================
 |   Assignment:  "Lab 2c"
 |
 |       Author:  Michael Williamson
 |
 |     Platform:  Arduino UNO
 |          IDE:  Arduino 1.8.15, Windows version
 |
 |        Class:  C Programming (2021FA.CSC.133.4101)
 |               
 |   Instructor:  Professor Connie Keen
 |     Due Date:  2021-08-31
 |
 +---------------------------------------------------------------------------
 |
 |  Description:  Any Arduino compatible analog sensor could be used to drive 
 |  the RGB output.  For this sketch, use one potentiometer as a stand-in for 
 |  a temperature sensor.  Create your own scaling algorithm so that ‘0’ 
 |  input gives a pure blue light, ‘1023’ input gives a pure red light, and 
 |  values in between transition from blue to red, with green included in the 
 |  transition.
 |
 |  Input:  The pot is the only input and is meant to simulate the signal 
 |  from a temperature sensor.
 |
 |  Output:  The color of the RGB LED.
 |
 |  Algorithm:  Each color has it's own algorithm
 |    Blue = 255 - (scaled control value * 2) and then constrained so it doesn't go negative.
 |    Red = 255 - (2 * (255 - scaled control value)) and then constrained so it doesn't go negative.
 |    Green = 255 - (scaled red value - scaled blue value)
 |
 |  Lab Observations/Questions: 
 |    Green was the tricky one. At first I had the green command before the red command executed. So
 |    the value never changed. I could have made it static, but I decided to just change the order of
 |    the commands instead.  
 |
*==========================================================================*/

int redPin = 9;
int bluePin = 11;
int greenPin = 10;

void setup() {
  pinMode (redPin, OUTPUT);
  pinMode (bluePin, OUTPUT);
  pinMode (greenPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int scaled_control_red, scaled_control_blue, scaled_control_green;            //Declaring the variables
  float control_temp, scaled_control_temp;
  
  control_temp = analogRead(A0);                                                //Initializing the variable to whatever voltage is being read from the pot
  
  scaled_control_temp = control_temp/3.53;                                      //Scales the voltage input. Actual measured value was from 0 - 900 instead of 0 - 1023
  scaled_control_blue = constrain((255 - (scaled_control_temp * 2)), 0, 255);   //Provides blue light at '0' input
  scaled_control_red = constrain((255-(2*(255-scaled_control_temp))), 0, 255);  //Provides red light at '900' input
  scaled_control_green = 255 - scaled_control_red - scaled_control_blue;

  Serial.print("Control_temp : ");
  Serial.print(control_temp);
  Serial.print(" Scaled_control_temp : ");
  Serial.print(scaled_control_temp);
       
  Serial.print(" - Scaled blue : ");
  Serial.print(scaled_control_blue);
  
  Serial.print(" - Scaled green : ");
  Serial.print(scaled_control_green);

  Serial.print(" - Scaled red : ");
  Serial.println(scaled_control_red);
      
  analogWrite(redPin, scaled_control_red);                                      //Sends control_red value to digital PWM to set light brightness
  analogWrite(bluePin, scaled_control_blue);
  analogWrite(greenPin, scaled_control_green);
  delay(100);                                                                   //Delay to save processing

  
}
