#ifndef _WEICHE_H_
#define _WEICHE_H_
#include <Servo.h>

class Weiche {
    int posMax, posMin = 1500;
	bool posDirection = false;
	bool positionWeiche = false;
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
	bool readPosWeiche();
};

#endif