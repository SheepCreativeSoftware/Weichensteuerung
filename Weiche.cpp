#include "Weiche.h"

void Weiche::setPosMin(int x){
  posMin = x;
  myServo.writeMicroseconds(posMin);
}

void Weiche::setPosMax(int x){
  posMax = x;
  myServo.writeMicroseconds(posMax);
}

int Weiche::readPosMin(){
  return posMin;
}

int Weiche::readPosMax(){
  return posMax;
}

void Weiche::setposDirection (bool x){
	posDirection = x;
}

bool Weiche::readposDirection (){
	return posDirection;
}

void Weiche::attach(int pin){
	myServo.attach(pin);	
}

void Weiche::setWeiche(bool position){
	if(posDirection) {
		if(position){
			this->myServo.writeMicroseconds(posMin);
		} else {
			this->myServo.writeMicroseconds(posMax);
		}
	} else {
		if(position){
			this->myServo.writeMicroseconds(posMax);
		} else {
			this->myServo.writeMicroseconds(posMin);
		}
	}
	positionWeiche = position;
}

bool Weiche::readPosWeiche(){
	return positionWeiche;
}