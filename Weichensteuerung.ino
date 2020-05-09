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
#define WeichePin17 22
#define WeichePin18 24
#define WeichePin19 26
#define WeichePin20 28

#define TasterPin1 11
#define TasterPin2 10
#define TasterPin3 9
#define TasterPin4 8

#define printByte(args)  write(args);

unsigned int indexHauptmenu = 1;
unsigned int indexWeichenMenu = 0;
unsigned int indexEinstellungMenu = 0;
unsigned int indexStrassenMenu = 0;
unsigned int indexWeicheIntern = 0;
unsigned int indexEinstellungWeiche = 0;
unsigned int indexEinstellungWeicheIntern = 0;
unsigned int indexWeicheSub = 1;

bool starteNeuesMenu = true;
bool positionWeiche[20] = { 0 };
unsigned int SubMenuSelection = 0;
unsigned int indexEinstellungWeicheSub = 0;

bool runterTaste = false;
bool hochTaste = false;
bool linksTaste = false;
bool rechtsTaste = false;



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
void lcdHauptmenu();
void lcdWeichenmenu();
void lcdEinstellungenMenu();
void lcdEinstellungWeicheSub();

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
	runterTaste = Taster[0].readFlanke();
	hochTaste = Taster[1].readFlanke();
	linksTaste = Taster[2].readFlanke();
	rechtsTaste = Taster[3].readFlanke();
	//lcd.printByte(0x7E); //Pfeil nach rechts
	if(starteNeuesMenu) {
		lcd.clear();
		starteNeuesMenu = false;
	}
	lcdEinstellungWeicheSub();
	lcdEinstellungenMenu();
	lcdWeichenmenu();
	lcdHauptmenu();
	
	runterTaste = false;
	hochTaste = false;
	linksTaste = false;
	rechtsTaste = false;

	
}


void ladeAusEEPROM(){
	unsigned int posMin = 0;
	unsigned int posMax = 0;
	bool posDirection = 0;
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
		
		posDirection = speicherWeiche[i].ladenDirection();
		weiche[i].setposDirection(posDirection);

		weiche[i].setWeiche(false);
	}

}

void lcdHauptmenu(){
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
			/*if(rechtsTaste) {
				starteNeuesMenu = true;
				indexHauptmenu = 0;
				indexStrassenMenu = 1;
			}*/
		} else if(indexHauptmenu == 3){ //Einstellungen
			lcd.setCursor(0,3);
			lcd.printByte(0x7E);
			lcd.setCursor(0,1);
			lcd.print(" ");
			lcd.setCursor(0,2);
			lcd.print(" ");
			if(rechtsTaste) {
				starteNeuesMenu = true;
				indexHauptmenu = 0;
				indexEinstellungMenu = 1;
			}
		}
		runterTaste = false;
		hochTaste = false;
		linksTaste = false;
		rechtsTaste = false;

		
	}
}

void lcdWeichenmenu(){
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
		lcd.print("----Weichen----");
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
		runterTaste = false;
		hochTaste = false;
		linksTaste = false;
		rechtsTaste = false;

	}
	
}

void lcdEinstellungenMenu(){
	//Einstellungen Weiche
	
	if(indexEinstellungWeiche >= 1) {
		if(linksTaste){
			starteNeuesMenu = true;
			indexEinstellungMenu = 1;
			indexEinstellungWeiche = 0;
		}
		for(int i = 0; i <= 19; i++){
			positionWeiche[i] = weiche[i].readPosMin();
		}

		lcd.setCursor(0,0);
		lcd.print("--Weichen Einstell--");
		lcd.setCursor(2,1);
		lcd.print("Weiche "); lcd.print(indexEinstellungWeicheIntern+1);
		lcd.setCursor(2,2);
		lcd.print("Weiche "); lcd.print(indexEinstellungWeicheIntern+2);
		lcd.setCursor(2,3);
		lcd.print("Weiche "); lcd.print(indexEinstellungWeicheIntern+3);
		
		if(hochTaste){
			indexEinstellungWeiche++;
			lcd.setCursor(10,1);
			lcd.print(" ");
			lcd.setCursor(10,2);
			lcd.print(" ");
			lcd.setCursor(10,3);
			lcd.print(" ");
			if(indexEinstellungWeiche == 4) {
				indexEinstellungWeiche = 1;
				if(indexEinstellungWeicheIntern == 18) {
					indexEinstellungWeicheIntern = 0;
				} else {
					indexEinstellungWeicheIntern += 3;
				}
			}			
		} else if(runterTaste){
			indexEinstellungWeiche--;
			lcd.setCursor(10,1);
			lcd.print(" ");
			lcd.setCursor(10,2);
			lcd.print(" ");
			lcd.setCursor(10,3);
			lcd.print(" ");
			if(indexEinstellungWeiche == 0) {
				indexEinstellungWeiche = 3;
				if(indexEinstellungWeicheIntern == 0) {
					indexEinstellungWeicheIntern = 18;
				} else {
					indexEinstellungWeicheIntern -= 3;
				}
			}
		} else if(rechtsTaste){
			int tempVar = indexEinstellungWeicheIntern+indexEinstellungWeiche-1;
			starteNeuesMenu = true;
			indexEinstellungWeiche = 0;
			indexEinstellungWeicheSub = tempVar+1;
		}
		if(indexEinstellungWeiche == 1){ //1.Zeile Pfeil
			lcd.setCursor(0,1);
			lcd.printByte(0x7E);
			lcd.setCursor(0,2);
			lcd.print(" ");
			lcd.setCursor(0,3);
			lcd.print(" ");
		} else if(indexEinstellungWeiche == 2){ //2.Zeile Pfeil
			lcd.setCursor(0,2);
			lcd.printByte(0x7E);
			lcd.setCursor(0,1);
			lcd.print(" ");
			lcd.setCursor(0,3);
			lcd.print(" ");
		} else if(indexEinstellungWeiche == 3){ //3.Zeile Pfeil
			lcd.setCursor(0,3);
			lcd.printByte(0x7E);
			lcd.setCursor(0,1);
			lcd.print(" ");
			lcd.setCursor(0,2);
			lcd.print(" ");
		}
		runterTaste = false;
		hochTaste = false;
		linksTaste = false;
		rechtsTaste = false;

	}
	
	//Einstellungsmenu
	if(indexEinstellungMenu >= 1){
		if(linksTaste){
			starteNeuesMenu = true;
			indexHauptmenu = 1;
			indexEinstellungMenu = 0;
		}
		lcd.setCursor(3,0);
		lcd.print("--Einstellungen--");
		lcd.setCursor(2,1);
		lcd.print("Weichen");
		lcd.setCursor(2,2);
		lcd.print("Strassen");
		if(hochTaste){
			indexEinstellungMenu++;
			if(indexEinstellungMenu == 3) indexEinstellungMenu = 1;
		} else if(runterTaste){
			indexEinstellungMenu--;
			if(indexEinstellungMenu == 0) indexEinstellungMenu = 2;
		}
		if(indexEinstellungMenu == 1){ //Weichen
			lcd.setCursor(0,1);
			lcd.printByte(0x7E);
			lcd.setCursor(0,2);
			lcd.print(" ");
			lcd.setCursor(0,3);
			lcd.print(" ");
			if(rechtsTaste) {
				starteNeuesMenu = true;
				indexEinstellungMenu = 0;
				indexEinstellungWeiche = 1;
			}
		} else if(indexEinstellungMenu == 2){ //Strassen
			lcd.setCursor(0,2);
			lcd.printByte(0x7E);
			lcd.setCursor(0,1);
			lcd.print(" ");
			lcd.setCursor(0,3);
			lcd.print(" ");
			/*if(rechtsTaste) {
				starteNeuesMenu = true;
				indexEinstellungMenu = 0;
				indexEinstellungStrasse = 1;
			}*/
		} 
		runterTaste = false;
		hochTaste = false;
		linksTaste = false;
		rechtsTaste = false;

	}
	
	
	
}

void lcdEinstellungWeicheSub(){
	
	if(indexEinstellungWeicheSub >= 1) {
		if(SubMenuSelection >= 1) {
			if(linksTaste){
				SubMenuSelection = 0;
				weiche[indexEinstellungWeicheSub-1].setWeiche(false);
			}
			if(SubMenuSelection == 1){
				lcd.setCursor(11,1);
				lcd.print("    ");
				unsigned int positionWeicheMin = weiche[indexEinstellungWeicheSub-1].readPosMin();
				lcd.setCursor(11,1);
				lcd.print(positionWeicheMin);
				if(hochTaste){
					positionWeicheMin += 5;
					if(positionWeicheMin >=2301) positionWeicheMin = 2300;
					weiche[indexEinstellungWeicheSub-1].setPosMin(positionWeicheMin);
				} else if(runterTaste){
					positionWeicheMin -= 5;
					if(positionWeicheMin <=699) positionWeicheMin = 700;
					weiche[indexEinstellungWeicheSub-1].setPosMin(positionWeicheMin);
				}
				if(rechtsTaste) {
					speicherWeiche[indexEinstellungWeicheSub-1].speichernMin(positionWeicheMin);
					SubMenuSelection = 0;
					weiche[indexEinstellungWeicheSub-1].setWeiche(false);
				}
			} else if(SubMenuSelection == 2){
				lcd.setCursor(11,2);
				lcd.print("    ");
				unsigned int positionWeicheMax = weiche[indexEinstellungWeicheSub-1].readPosMax();
				lcd.setCursor(11,2);
				lcd.print(positionWeicheMax);
				if(hochTaste){
					positionWeicheMax += 5;
					if(positionWeicheMax >=2301) positionWeicheMax = 2300;
					weiche[indexEinstellungWeicheSub-1].setPosMax(positionWeicheMax);
				} else if(runterTaste){
					positionWeicheMax -= 5;
					if(positionWeicheMax <=699) positionWeicheMax = 700;
					weiche[indexEinstellungWeicheSub-1].setPosMax(positionWeicheMax);
					
				}
				if(rechtsTaste) {
					speicherWeiche[indexEinstellungWeicheSub-1].speichernMax(positionWeicheMax);
					SubMenuSelection = 0;
					weiche[indexEinstellungWeicheSub-1].setWeiche(false);
				}
			} else if(SubMenuSelection == 3){
				lcd.setCursor(11,3);
				lcd.print("      ");
				bool directionWeiche = weiche[indexEinstellungWeicheSub-1].readposDirection();
				lcd.setCursor(11,3);
				if(directionWeiche){
					lcd.print("Rechts");
				} else {
					lcd.print("Links");
				}
				if(hochTaste){
					directionWeiche = true;
					weiche[indexEinstellungWeicheSub-1].setposDirection(directionWeiche);
				} else if(runterTaste){
					directionWeiche = false;
					weiche[indexEinstellungWeicheSub-1].setposDirection(directionWeiche);
				}
				if(rechtsTaste) {
					speicherWeiche[indexEinstellungWeicheSub-1].speichernDirection(directionWeiche);
					SubMenuSelection = 0;
					weiche[indexEinstellungWeicheSub-1].setWeiche(false);
				}
			}
		} else {
			if(linksTaste){
				starteNeuesMenu = true;
				indexEinstellungWeicheSub = 0;
				indexEinstellungWeiche = 1;
			}
			unsigned int positionWeicheMin = weiche[indexEinstellungWeicheSub-1].readPosMin();
			unsigned int positionWeicheMax = weiche[indexEinstellungWeicheSub-1].readPosMax();
			bool directionWeiche = weiche[indexEinstellungWeicheSub-1].readposDirection();
			lcd.setCursor(3,0);
			lcd.print("  Weiche "); lcd.print(indexEinstellungWeicheSub);
			lcd.setCursor(2,1);
			lcd.print("PosMin   "); lcd.print(positionWeicheMin);
			lcd.setCursor(2,2);
			lcd.print("PosMax   "); lcd.print(positionWeicheMax);
			lcd.setCursor(2,3);
			lcd.print("Richtung "); 
			if(directionWeiche){
				lcd.print("Rechts");
			} else {
				lcd.print("Links");
			}
			
			if(hochTaste){
				indexWeicheSub++;
				if(indexWeicheSub == 4) indexWeicheSub = 1;
			} else if(runterTaste){
				indexWeicheSub--;
				if(indexWeicheSub == 0) indexWeicheSub = 3;
			}
			if(indexWeicheSub == 1){ //PosMin
				lcd.setCursor(0,1);
				lcd.printByte(0x7E);
				lcd.setCursor(0,2);
				lcd.print(" ");
				lcd.setCursor(0,3);
				lcd.print(" ");
				if(rechtsTaste) {
					SubMenuSelection = 1;
				}
			} else if(indexWeicheSub == 2){ //PosMax
				lcd.setCursor(0,2);
				lcd.printByte(0x7E);
				lcd.setCursor(0,1);
				lcd.print(" ");
				lcd.setCursor(0,3);
				lcd.print(" ");
				if(rechtsTaste) {
					SubMenuSelection = 2;
				}
			} else if(indexWeicheSub == 3){ //Richtung
				lcd.setCursor(0,3);
				lcd.printByte(0x7E);
				lcd.setCursor(0,1);
				lcd.print(" ");
				lcd.setCursor(0,2);
				lcd.print(" ");
				if(rechtsTaste) {
					SubMenuSelection = 3;
				}
			}
			runterTaste = false;
			hochTaste = false;
			linksTaste = false;
			rechtsTaste = false;
		}
	
		
	}
}
