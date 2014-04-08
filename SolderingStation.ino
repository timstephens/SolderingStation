/********************************************************
 * PID Soldering Iron Control
 * Reading analog input 0 to control analog PWM output 3
 * Based on PID_Basic example from the PID Library
 * Tim Stephens, 6 April 2014.
 *
 *
 * Requirements:
 * PID Library https://github.com/br3ttb/Arduino-PID-Library/
 ********************************************************/

#include <PID_v1.h>

//Define Variables we'll be connecting to
double Setpoint, Input, Output;
//These setpoints roughly correspond to 260, 295, 310, 330, 350C
//Based on one experiment cooling down...
//Your Iron may Vary

int setpoints[] = {70, 200, 250, 340, 450};
int currentSetpoint = 0; //Always start at the coolest temperature.
int upButton = 5;
int downButton = 6;

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint,1,0.1,0.5, DIRECT);

void setup()
{
  pinMode(upButton, INPUT);
  pinMode(downButton, INPUT);
  Serial.begin(9600);
  //initialize the variables we're linked to
  Input = analogRead(0);
  Setpoint = setpoints[currentSetpoint];

  //turn the PID on
  myPID.SetMode(AUTOMATIC);
}

void loop()
{
  Input = analogRead(0);
  
  myPID.Compute();
  Serial.print("Setpoint = ");
  Serial.print(Setpoint, DEC);
  Serial.print(" Temp Reading = ");
  Serial.print(Input, DEC);
  Serial.print(" Output PWNM Value");
  Serial.println(Output, DEC);
  analogWrite(3,Output);
  delay(200);

  
  //Now to set an appropriate temperature setpoint 
  //(and make sure we stay within the bounds of the array)
  if(digitalRead(5)==1) {
    currentSetpoint++;
    if(currentSetpoint > 4) {
        currentSetpoint=4;
    }
  } else if (digitalRead(6) == 1) {
    currentSetpoint--;
    if(currentSetpoint < 0) {
        currentSetpoint=0;
    }
  }
  
  Setpoint = setpoints[currentSetpoint];
}


