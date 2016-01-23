__author__ = 'Aydar'

from Structures import *
import math

def GetAngles(x,y,z):
    B = math.sqrt(x*x+y*y+z*z)
    q1=math.acos(x/B)
    q2=math.acos((math.pow(Configuration.L1,2)-math.pow(Configuration.L2,2)+math.pow(B,2))/(2*B*Configuration.L1))

    q22=math.pi-math.acos((math.pow(Configuration.L1,2)+math.pow(Configuration.L2,2)-math.pow(B,2))/(2*Configuration.L1*Configuration.L2))

    C=math.sqrt(x*x+z*z)

    ang=Angles()
    ang.Q1=math.trunc(((q1+q2)*180)/math.pi)
    ang.Q2=(q22*180)/math.pi
    if(C==0):
        ang.Q3=0
    else:
        ang.Q3=(math.acos(z/C)*180)/math.pi

    return ang

def GetCoordinates(angles):
    try:
        x=Configuration.L1*math.cos(angles.Q1)+Configuration.L2*math.cos(angles.Q1+angles.Q2)
        y=Configuration.L1*math.sin(angles.Q1)+Configuration.L2*math.sin(angles.Q1+angles.Q2)
        return (math.trunc(x),math.trunc(y))
    except ZeroDivisionError:
        return (-1,-1)

q1=0
q2=0
q3=0

while q1<90:
    while q2<180:
        while q3<180:
            ang=Angles()
            ang.Q1=q1
            ang.Q2=q2
            ang.Q3=q3
            print(GetCoordinates(ang))
            q3=q3+1

        q2=q2+1
    q1=q1+1