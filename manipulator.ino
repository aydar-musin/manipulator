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

short position_index=-1;//index of position
bool flag=0;//flag for switch position
int pos_n=6;
Position positions[6]={{25,12,-10},{40,0,0},{10,10,10},{0,40,0},{25,12,0},{20,20,0}};

int _step=1;

void switch_pos()
{
  flag=0;
  position_index++;
  if(position_index<pos_n)
  {
    Position pos=positions[position_index];
    tAngles=GetAngles(pos.X,pos.Y,pos.Z,20,20);
  }
  else
  {
    Serial.println("riched");
    delay(500);
    position_index=-1;
    switch_pos();
  }
}
void setup() {
  Serial.begin(9600);
  
  servo1.attach(9);
  servo2.attach(8);
  servo3.attach(10);
  
  curAngles.Q1=0;
  curAngles.Q2=0;
  curAngles.Q3=0;

  //Timer1.initialize(200000);
  //Timer1.attachInterrupt(timer_tick);
  switch_pos();
}

void loop() {
  if(flag)
  {
    switch_pos();
  }
  timer_tick();
  delay(20);
  // put your main code here, to run repeatedly:
  
  //MoveServo(&servo1, Q1, 100);
  //MoveServo(&servo2, 0,180);
  //delay(1000);
  //MoveServo(&servo1, 100, 0);
  //MoveServo(&servo2,180,0);
}
void timer_tick()
{
  if(curAngles.Q1<tAngles.Q1)
  {
    curAngles.Q1+=_step;
  }
  else if(curAngles.Q1>tAngles.Q1)
  {
    curAngles.Q1-=_step;
  }
  
  if(curAngles.Q2<tAngles.Q2)
  {
    curAngles.Q2+=_step;
  }
  else if(curAngles.Q2>tAngles.Q2)
  {
    curAngles.Q2-=_step;
  }
  
  if(curAngles.Q3<tAngles.Q3)
  {
    curAngles.Q3+=_step;
  }
  else if(curAngles.Q3>tAngles.Q3)
  {
    curAngles.Q3-=_step;
  }

  printState();
  servo1.write(curAngles.Q1);
  servo2.write(curAngles.Q2);
  servo3.write(curAngles.Q3);
  if(curAngles.Q1==tAngles.Q1&&curAngles.Q2==tAngles.Q2&&curAngles.Q3==tAngles.Q3)
  {
    flag=1;
  }
  else
  {
    
  }
}
void printState()
{
  Serial.print(curAngles.Q1);
  Serial.print("\t");
  Serial.print(curAngles.Q2);
  Serial.print("\t");
  Serial.print(curAngles.Q3);
  Serial.print("\t--->");
  Serial.print(tAngles.Q1);
  Serial.print("\t");
  Serial.print(tAngles.Q2);
  Serial.print("\t");
  Serial.print(tAngles.Q3);
  Serial.print("\n");
}
void MoveServo(Servo *servo, int current_angle,int angle)
{
  
  /*while(current_angle!=angle)
  {
    if(current_angle<angle)
    {
      current_angle++;
    }
    else
    {
      current_angle--;
    }

    servo->write(current_angle);
    delay(20);
  }*/
}

