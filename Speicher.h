#ifndef _SPEICHER_H_
#define _SPEICHER_H_
#include <EEPROM.h>

class Speicher {
		unsigned int saveAddress, saveAddress2, saveAddress3;
	public:
		unsigned int init(unsigned int);
		unsigned int ladenMin();
		unsigned int ladenMax();
		bool ladenDirection();
		void speichernMin(unsigned int);
		void speichernMax(unsigned int);
		void speichernDirection(bool);
};

#endif