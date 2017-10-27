#ifndef _WEICHE_H_
#define _WEICHE_H_
#include <Servo.h>

class Weiche {
    int posMax, posMin;
	bool posDirection;
	Servo myServo;
  public:
    void setPosMin(int);
    void setPosMax(int);
	void setposDirection(bool);
    int readPosMin();
    int readPosMax();
	bool readposDirection();
	void setWeiche(bool);
	void attach(int);
};

#endif