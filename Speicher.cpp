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
