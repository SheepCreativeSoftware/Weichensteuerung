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