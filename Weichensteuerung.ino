#include "Weiche.h"
#include "Speicher.h"
#include <LiquidCrystal_I2C.h>

#define WeichePin1 23
#define WeichePin2 25
#define WeichePin3 27
#define WeichePin4 29
#define WeichePin5 31
#define WeichePin6 33
#define WeichePin7 35
#define WeichePin8 37
#define WeichePin9 39
#define WeichePin10 41
#define WeichePin11 43
#define WeichePin12 45
#define WeichePin13 47
#define WeichePin14 49
#define WeichePin15 51
#define WeichePin16 53
#define WeichePin17 46
#define WeichePin18 48
#define WeichePin19 50
#define WeichePin20 52

#define TasterPin1 5
#define TasterPin2 4
#define TasterPin3 3
#define TasterPin4 2

#define printByte(args)  write(args);

unsigned int indexHauptmenu = 1;
unsigned int indexWeichenMenu = 0;
unsigned int indexEinstellungMenu = 0;
unsigned int indexStrassenMenu = 0;
unsigned int indexWeicheIntern = 0;
bool starteNeuesMenu = true;
bool positionWeiche[20] = { 0 };

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
void lcdHauptmenu(bool, bool, bool, bool);
void lcdWeichenmenu(bool, bool, bool, bool);


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
	lcd.clear();
}

void loop() {
	bool runterTaste = Taster[0].readFlanke();
	bool hochTaste = Taster[1].readFlanke();
	bool linksTaste = Taster[2].readFlanke();
	bool rechtsTaste = Taster[3].readFlanke();
	//lcd.printByte(0x7E); //Pfeil nach rechts
	if(starteNeuesMenu) {
		lcd.clear();
		starteNeuesMenu = false;
	}
	lcdWeichenmenu(runterTaste, hochTaste, linksTaste, rechtsTaste);
	lcdHauptmenu(runterTaste, hochTaste, linksTaste, rechtsTaste);
}


void ladeAusEEPROM(){
	unsigned int posMin = 0;
	unsigned int posMax = 0;
	for(int i = 0; i <= 20; i++) {
		posMin = speicherWeiche[i].ladenMin();
		if(posMin >= 1500) {
			posMin = 1200;
			speicherWeiche[i].speichernMin(posMin);
		}
		weiche[i].setPosMin(posMin);
		posMax = speicherWeiche[i].ladenMax();
		if(posMax >= 3000) {
			posMax = 1800;
			speicherWeiche[i].speichernMax(posMax);
		}
		weiche[i].setPosMax(posMax);

		weiche[i].setWeiche(false);
	}

}

void lcdHauptmenu(bool runterTaste, bool hochTaste, bool linksTaste, bool rechtsTaste){
	if(indexHauptmenu >= 1){
		lcd.setCursor(3,0);
		lcd.print("--Hauptmenu--");
		lcd.setCursor(2,1);
		lcd.print("Weichen");
		lcd.setCursor(2,2);
		lcd.print("Strassen");
		lcd.setCursor(2,3);
		lcd.print("Einstellungen");
		if(hochTaste){
			indexHauptmenu++;
			if(indexHauptmenu == 4) indexHauptmenu = 1;
		} else if(runterTaste){
			indexHauptmenu--;
			if(indexHauptmenu == 0) indexHauptmenu = 3;
		}
		if(indexHauptmenu == 1){ //Weichen
			lcd.setCursor(0,1);
			lcd.printByte(0x7E);
			lcd.setCursor(0,2);
			lcd.print(" ");
			lcd.setCursor(0,3);
			lcd.print(" ");
			if(rechtsTaste) {
				starteNeuesMenu = true;
				indexHauptmenu = 0;
				indexWeichenMenu = 1;
				indexWeicheIntern = 0;
			}
		} else if(indexHauptmenu == 2){ //Strassen
			lcd.setCursor(0,2);
			lcd.printByte(0x7E);
			lcd.setCursor(0,1);
			lcd.print(" ");
			lcd.setCursor(0,3);
			lcd.print(" ");
		} else if(indexHauptmenu == 3){ //Einstellungen
			lcd.setCursor(0,3);
			lcd.printByte(0x7E);
			lcd.setCursor(0,1);
			lcd.print(" ");
			lcd.setCursor(0,2);
			lcd.print(" ");
		}

		
	}
}
void lcdWeichenmenu(bool runterTaste, bool hochTaste, bool linksTaste, bool rechtsTaste){
		if(indexWeichenMenu >= 1) {
		if(linksTaste){
			starteNeuesMenu = true;
			indexHauptmenu = 1;
			indexWeichenMenu = 0;
		}
		for(int i = 0; i <= 19; i++){
			positionWeiche[i] = weiche[i].readPosWeiche();
		}

		lcd.setCursor(3,0);
		lcd.print("--Weichen--");
		lcd.setCursor(2,1);
		lcd.print("Weiche "); lcd.print(indexWeicheIntern+1);
		lcd.setCursor(12,1);
		if(positionWeiche[indexWeicheIntern]) {
			lcd.print("Gebogen");
		}else {
			lcd.print("Gerade ");
		}
		lcd.setCursor(2,2);
		lcd.print("Weiche "); lcd.print(indexWeicheIntern+2);
		lcd.setCursor(12,2);
		if(positionWeiche[indexWeicheIntern+1]) {
			lcd.print("Gebogen");
		}else {
			lcd.print("Gerade ");
		}
		lcd.setCursor(2,3);
		lcd.print("Weiche "); lcd.print(indexWeicheIntern+3);
		lcd.setCursor(12,3);
		if(positionWeiche[indexWeicheIntern+2]) {
			lcd.print("Gebogen");
		}else {
			lcd.print("Gerade ");
		}
		
		if(hochTaste){
			indexWeichenMenu++;
			lcd.setCursor(10,1);
			lcd.print(" ");
			lcd.setCursor(10,2);
			lcd.print(" ");
			lcd.setCursor(10,3);
			lcd.print(" ");
			if(indexWeichenMenu == 4) {
				indexWeichenMenu = 1;
				if(indexWeicheIntern == 18) {
					indexWeicheIntern = 0;
				} else {
					indexWeicheIntern += 3;
				}
			}			
		} else if(runterTaste){
			indexWeichenMenu--;
			lcd.setCursor(10,1);
			lcd.print(" ");
			lcd.setCursor(10,2);
			lcd.print(" ");
			lcd.setCursor(10,3);
			lcd.print(" ");
			if(indexWeichenMenu == 0) {
				indexWeichenMenu = 3;
				if(indexWeicheIntern == 0) {
					indexWeicheIntern = 18;
				} else {
					indexWeicheIntern -= 3;
				}
			}
		} else if(rechtsTaste){
			int tempVar = indexWeicheIntern+indexWeichenMenu-1;
			weiche[tempVar].setWeiche(!positionWeiche[tempVar]);

		}
		if(indexWeichenMenu == 1){ //Weichen
			lcd.setCursor(0,1);
			lcd.printByte(0x7E);
			lcd.setCursor(0,2);
			lcd.print(" ");
			lcd.setCursor(0,3);
			lcd.print(" ");
		} else if(indexWeichenMenu == 2){ //Strassen
			lcd.setCursor(0,2);
			lcd.printByte(0x7E);
			lcd.setCursor(0,1);
			lcd.print(" ");
			lcd.setCursor(0,3);
			lcd.print(" ");
		} else if(indexWeichenMenu == 3){ //Einstellungen
			lcd.setCursor(0,3);
			lcd.printByte(0x7E);
			lcd.setCursor(0,1);
			lcd.print(" ");
			lcd.setCursor(0,2);
			lcd.print(" ");
		}
	}
	
}





