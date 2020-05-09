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
#include "Speicher.h"


unsigned int Speicher::init(unsigned int address){
	saveAddress = address;
	unsigned int sizeOfInt = sizeof(int);
	saveAddress2 = saveAddress + sizeOfInt;
	saveAddress3 = saveAddress2 + sizeOfInt;
	unsigned int temp = saveAddress3 + sizeOfInt;
	return temp;
}

unsigned int Speicher::ladenMin(){
	unsigned int varMin = 0;
	EEPROM.get(saveAddress, varMin);
	return varMin;
}
	
unsigned int Speicher::ladenMax(){
	unsigned int varMax = 0;
	EEPROM.get(saveAddress2, varMax);
	return varMax;
}

bool Speicher::ladenDirection(){
	bool varDirection = 0;
	EEPROM.get(saveAddress3, varDirection);
	return varDirection;
}

void Speicher::speichernMin(unsigned int varMin){
	EEPROM.put(saveAddress, varMin);
}

void Speicher::speichernMax(unsigned int varMax){
	EEPROM.put(saveAddress2, varMax);
}

void Speicher::speichernDirection(bool varDirection){
	EEPROM.put(saveAddress3, varDirection);
}
