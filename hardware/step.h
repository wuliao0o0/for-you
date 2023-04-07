#ifndef __STEPMOTOR_H__
#define __STEPMOTOR_H__
#define uint unsigned int
#define uchar unsigned char
void MotorRun(uint angle,uint drct,uint speed);
extern uchar mark;
void MotoStop();
#endif