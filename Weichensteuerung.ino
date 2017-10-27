#include "Weiche.h"
#include "Speicher.h"
#include <LiquidCrystal_I2C.h>

#define WeichePin1 6
#define WeichePin2 6
#define WeichePin3 6
#define WeichePin4 6
#define WeichePin5 6
#define WeichePin6 6
#define WeichePin7 6
#define WeichePin8 6
#define WeichePin9 6
#define WeichePin10 6
#define WeichePin11 6
#define WeichePin12 6
#define WeichePin13 6
#define WeichePin14 6
#define WeichePin15 6
#define WeichePin16 6
#define WeichePin17 6
#define WeichePin18 6
#define WeichePin19 6
#define WeichePin20 6

#define TasterPin1 5
#define TasterPin2 4
#define TasterPin3 3
#define TasterPin4 2

unsigned int indexHauptmenu = 0;
unsigned int indexWeichenMenu = 0;
unsigned int indexEinstellungMenu = 0;
unsigned int indexStrassenMenu = 0;

class ButtonFlanke {
      bool lastFlanke;
      int buttonPin;
    public:
      void init(int Pin);
      bool readFlanke();
};

bool ButtonFlanke::readFlanke(){
  bool temp1 = !digitalRead(buttonPin);
  if((temp1) && (!lastFlanke)){
    lastFlanke = true;
    return true;
  } else if((!temp1) && (lastFlanke)){
    lastFlanke = false;
    delay(20); //Pause beim loslassen
    return false;
  } 
  return false;
}

void ButtonFlanke::init(int Pin){
  buttonPin = Pin;
}

Weiche weiche[20];
ButtonFlanke Taster[4];
Speicher speicherWeiche[20];
LiquidCrystal_I2C lcd(0x27,20,4);

void ladeAusEEPROM();


void setup() {
	Serial.begin(9600); //Aktiviere Serielle Kommunkation
	/*Definiere Weichen*/
	weiche[0].attach(WeichePin1);
	weiche[1].attach(WeichePin2);
	weiche[2].attach(WeichePin3);
	weiche[3].attach(WeichePin4);
	weiche[4].attach(WeichePin5);
	weiche[5].attach(WeichePin6);
	weiche[6].attach(WeichePin7);
	weiche[7].attach(WeichePin8);
	weiche[8].attach(WeichePin9);
	weiche[9].attach(WeichePin10);
	weiche[10].attach(WeichePin11);
	weiche[11].attach(WeichePin12);
	weiche[12].attach(WeichePin13);
	weiche[13].attach(WeichePin14);
	weiche[14].attach(WeichePin15);
	weiche[15].attach(WeichePin16);
	weiche[16].attach(WeichePin17);
	weiche[17].attach(WeichePin18);
	weiche[18].attach(WeichePin19);
	weiche[19].attach(WeichePin20);
	/*Definiere Taster*/
	pinMode(TasterPin1, INPUT_PULLUP);
	pinMode(TasterPin2, INPUT_PULLUP);
	pinMode(TasterPin3, INPUT_PULLUP);
	pinMode(TasterPin4, INPUT_PULLUP);
	/*Initialisiere Taster*/
	Taster[0].init(TasterPin1);
	Taster[1].init(TasterPin2);
	Taster[2].init(TasterPin3);
	Taster[3].init(TasterPin4);
	/*Definiere Speicherplatz*/
    int speicherAdresse = 0;
	speicherAdresse = speicherWeiche[0].init(speicherAdresse);
	speicherAdresse = speicherWeiche[1].init(speicherAdresse);
	speicherAdresse = speicherWeiche[2].init(speicherAdresse);
	speicherAdresse = speicherWeiche[3].init(speicherAdresse);
	speicherAdresse = speicherWeiche[4].init(speicherAdresse);
	speicherAdresse = speicherWeiche[5].init(speicherAdresse);
	speicherAdresse = speicherWeiche[6].init(speicherAdresse);
	speicherAdresse = speicherWeiche[7].init(speicherAdresse);
	speicherAdresse = speicherWeiche[8].init(speicherAdresse);
	speicherAdresse = speicherWeiche[9].init(speicherAdresse);
	speicherAdresse = speicherWeiche[10].init(speicherAdresse);
	speicherAdresse = speicherWeiche[11].init(speicherAdresse);
	speicherAdresse = speicherWeiche[12].init(speicherAdresse);
	speicherAdresse = speicherWeiche[13].init(speicherAdresse);
	speicherAdresse = speicherWeiche[14].init(speicherAdresse);
	speicherAdresse = speicherWeiche[15].init(speicherAdresse);
	speicherAdresse = speicherWeiche[16].init(speicherAdresse);
	speicherAdresse = speicherWeiche[17].init(speicherAdresse);
	speicherAdresse = speicherWeiche[18].init(speicherAdresse);
	speicherAdresse = speicherWeiche[19].init(speicherAdresse);
	ladeAusEEPROM();
	lcd.init();
	lcd.backlight();
}

void loop() {
	lcd.setCursor(3,0);
	lcd.print("Hello, world!");
	
  
}

void ladeAusEEPROM(){
	int posMin = 0;
	int posMax = 0;
	for(int i = 0; i <= 20; i++) {
		posMin = speicherWeiche[i].ladenMin();
		if(posMin == 0) {
			posMin = 1200;
			speicherWeiche[i].speichernMin(posMin);
		}
		weiche[i].setPosMin(posMin);
		posMax = speicherWeiche[i].ladenMax();
		if(posMax == 0) {
			posMax = 1800;
			speicherWeiche[i].speichernMax(posMax);
		}
		weiche[i].setPosMax(posMax);
		weiche[i].setWeiche(false);
	}

}






