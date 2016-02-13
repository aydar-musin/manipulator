#include <TimerOne.h>
#include <Servo.h>
#include "kinematics.h"

Servo servo1;
Servo servo2;
Servo servo3;

#define L1 20
#define L2 20

// these are current angles
Angles curAngles;
//these are target angles
Angles tAngles;

#define BUT1 0
#define BUT2 1
#define BUT3 2
#define BUT4 3
#define BUT5 4
#define BUT6 5

#define MDELAY 2
#define SERVOSTEP 2

byte getButtonValue(byte number)
{
  int value=analogRead((int)number);
  delay(MDELAY);
  value+=analogRead((int)number);
  delay(MDELAY);
  value+=analogRead((int)number);
  delay(MDELAY);
  value+=analogRead((int)number);
  
  return value; 
}
byte getState(byte servo)
{
  if(servo==0)
  {
    if(getButtonValue(BUT1)==0) return 1; // UP
    else if (getButtonValue(BUT4)==0) return 2; // DOWN
    else return 0; // NONE
  }
  else if(servo==1)
  {
    if(getButtonValue(BUT2)==0) return 1; // UP
    else if (getButtonValue(BUT5)==0) return 2; // DOWN
    else return 0; // NONE
  }
  else if(servo==2)
  {
    if(getButtonValue(BUT3)==0) return 1; // UP
    else if (getButtonValue(BUT6)==0) return 2; // DOWN
    else return 0; // NONE
  }
}

void setup() {
  Serial.begin(9600);
  
  servo1.attach(9);
  servo2.attach(8);
  servo3.attach(10);
  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
  
  curAngles.Q1=0;
  curAngles.Q2=0;
  curAngles.Q3=0;
}
void moveServo(Servo * servo, int * currentAngle, byte state, byte servoNumber)
{
 if(state==1)
 {
  *currentAngle+=SERVOSTEP;
  if(ValidateAngle(currentAngle,servoNumber))
  servo->write(*currentAngle);
  else *currentAngle-=SERVOSTEP;
  
 }
 else if(state==2 && (*currentAngle)>0)
 {
  *currentAngle-=SERVOSTEP;
  
  if(ValidateAngle(currentAngle,servoNumber))
  servo->write(*currentAngle);
  else *currentAngle+=SERVOSTEP;
 }
}
void loop() {
  DoButtonMovements();
}
void DoButtonMovements()
{
  byte state=getState(0); 
  moveServo(&servo1, &curAngles.Q1, state,0);
  state=getState(1);
  moveServo(&servo2, &curAngles.Q2, state,1);
  
  state=getState(2);
  moveServo(&servo3, &curAngles.Q3, state,2);
  printState();
  delay(10);
}
void printState()
{
  
  Serial.print(curAngles.Q1);
  Serial.print(" ");
  Serial.print(curAngles.Q2);
  Serial.print(" ");
  Serial.print(curAngles.Q3);
  Serial.print(" --->");
  Serial.print(tAngles.Q1);
  Serial.print(" ");
  Serial.print(tAngles.Q2);
  Serial.print(" ");
  Serial.print(tAngles.Q3);
  
  //Serial.print(" ||| ");

  //Position pos=GetPosition(&curAngles,L1,L2);
  //Serial.print(pos.X);
  //Serial.print(" ");
  //Serial.print(pos.Y);
  //Serial.print(" ");
  //Serial.print(pos.Z);
  Serial.print("\n");
  
}

