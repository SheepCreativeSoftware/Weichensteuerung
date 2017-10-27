#include "Speicher.h"


unsigned int Speicher::init(unsigned int address){
	saveAddress = address;
	unsigned int sizeOfInt = sizeof(int);
	saveAddress2 = address + sizeOfInt;
	unsigned int temp = saveAddress2 + sizeOfInt;
	return temp;
}

unsigned int Speicher::ladenMin(){
	unsigned int varMin = 0;
	EEPROM.get(saveAddress2, varMin);
	return varMin;
}
	
unsigned int Speicher::ladenMax(){
	unsigned int varMax = 0;
	EEPROM.get(saveAddress2, varMax);
	return varMax;
}

void Speicher::speichernMin(unsigned int varMin){
	EEPROM.put(saveAddress, varMin);
}

void Speicher::speichernMax(unsigned int varMax){
	EEPROM.put(saveAddress2, varMax);
}
