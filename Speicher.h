#ifndef _SPEICHER_H_
#define _SPEICHER_H_
#include <EEPROM.h>

class Speicher {
		unsigned int saveAddress, saveAddress2;
	public:
		unsigned int init(unsigned int);
		unsigned int ladenMin();
		unsigned int ladenMax();
		void speichernMin(unsigned int);
		void speichernMax(unsigned int);
};

#endif