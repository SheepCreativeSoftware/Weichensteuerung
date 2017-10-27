#include "Speicher.h"


int Speicher::init(int address){
	saveAddress = address;
	int sizeOfInt = sizeof(int);
	saveAddress2 = address + sizeOfInt;
	int temp = saveAddress2 + sizeOfInt;
	return temp;
}

int Speicher::ladenMin(){
	int varMin = 0;
	EEPROM.get(saveAddress2, varMin);
	return varMin;
}
	
int Speicher::ladenMax(){
	int varMax = 0;
	EEPROM.get(saveAddress2, varMax);
	return varMax;
}

void Speicher::speichernMin(int varMin){
	EEPROM.put(saveAddress, varMin);
}

void Speicher::speichernMax(int varMax){
	EEPROM.put(saveAddress2, varMax);
}
