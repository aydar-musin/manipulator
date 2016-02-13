#include <math.h>
#define PI (3.141592653589793)
#define MIN_Q1 0
#define MAX_Q1 90
#define MIN_Q2 0
#define MAX_Q2 180
#define MIN_Q3 0
#define MAX_Q3 180


typedef struct
{
  int Q1;
  int Q2;
  int Q3;
} Angles;
typedef struct
{
  int X;
  int Y;
  int Z;
}  Position;

bool Validate(Angles* angles)
{
  if(angles->Q1<=MAX_Q1 && angles->Q1>=MIN_Q1 &&
    angles->Q2<=MAX_Q2 && angles->Q2>=MIN_Q2 &&
    angles->Q3<=MAX_Q3 && angles->Q2>=MIN_Q3)
    return 1;
  else return 0;
    
}
bool ValidateAngle(int * angle, int servoNumber)
{
  if(servoNumber==0)
  {
  if(*angle<MAX_Q1 && *angle> MIN_Q1)
  return 1;
  else 
  return 0;
  }
  else if(servoNumber==1)
  {
    if(*angle<MAX_Q2 && *angle> MIN_Q2)
    return 1;
    else 
    return 0;
  }
  else if(servoNumber==2)
  {
    if(*angle<MAX_Q3 && *angle> MIN_Q3)
  return 1;
  else 
  return 0;
  }
  else
  return 0;
}
Angles GetAngles(int x,int y,int z, int L1,int L2, bool reverse=0)
{
  float B=sqrt(x*x+y*y+z*z);

  float q1=acos(x/B);
  float q2=acos((L1*L1-L2*L2+B*B)/(2*B*L1));
  float q22=PI-acos((L1*L1+L2*L2-B*B)/(2*L1*L2));

  float C=sqrt(x*x+z*z);

  Angles ang;
  ang.Q1=((q2+q1)*180)/PI;
  ang.Q2=180-(-(q22*180)/PI);
  if(C==0)
  {
    ang.Q3=0;
  }
  else
  {
    ang.Q3=(acos(z/C)*180)/PI;
  }
  ang.Q1=90-ang.Q1;
  ang.Q3=ang.Q3;

  if(Validate(&ang)!=1)//if angles is not acceptable then try reverse angles
  {
    ang.Q1=((q2-q1)*180)/PI;
    ang.Q2=180-((q22*180)/PI);

    if(Validate(&ang)!=1)//return default angles
    {
      ang.Q1=0;
      ang.Q2=0;
      ang.Q3=0;
    }
  }
  
  return ang;
}
Position GetPosition(Angles * angles,int L1,int L2)
{
  Position pos;
  pos.X=L1*cos(angles->Q1)+L2*cos(angles->Q1+angles->Q2);
  pos.Y=L1*sin(angles->Q1)+L2*sin(angles->Q1+angles->Q2);
  pos.Z=0;
  return pos;
}

