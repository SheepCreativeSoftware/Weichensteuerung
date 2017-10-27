#ifndef _SPEICHER_H_
#define _SPEICHER_H_
#include <EEPROM.h>

class Speicher {
		int saveAddress, saveAddress2;
	public:
		int init(int);
		int ladenMin();
		int ladenMax();
		void speichernMin(int);
		void speichernMax(int);
};

#endif