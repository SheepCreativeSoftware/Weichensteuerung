/************************************ 
 * Weichensteuerung v1.0.0
 * Date: 09.05.2020 | 20-13
 * <Steuerung von Weichen mit Hilfe von Servos und einem LCD Display>
 * Copyright (C) 2020 Marina Egner <info@sheepindustries.de>
 *
 * This program is free software: you can redistribute it and/or modify it 
 * under the terms of the GNU General Public License as published by the 
 * Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program. 
 * If not, see <https://www.gnu.org/licenses/>.
 ************************************/
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