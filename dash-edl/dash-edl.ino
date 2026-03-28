#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "EDLSerial.h"
#include <SoftwareSerial.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);
EDLSerial edl;

char intStringBuff[3];

void setup() {
  Serial.begin(115200);
  edl.begin(Serial);

  lcd.init();
  lcd.backlight();
  lcd.clear();
  printSplashScreen();
}

void printSplashScreen() {
  lcd.home();
  lcd.print("DUCK");
  delay(500);
  lcd.setCursor(0, 1);  //jump to new line
  lcd.print("   QUACK");
  delay(500);
  lcd.setCursor(0, 2);  //jump to new line
  lcd.print("      QUACK");
  delay(500);
  lcd.setCursor(0, 3);  //jump to new line
  lcd.print("         QUACK");
  delay(1000);
}

void loop() {

  if (edl.update()) {  //updates the frame, returns true if frame is valid
    printFirstLine();
    printSecondLine();
    printThirdLine();
    printFourthLine();
  }
}

void printFirstLine() {
  lcd.home();

  lcd.print("CLT: ");
  printThreeDigitInt(edl.getFrame().CLT);

  lcd.print(" ");

  lcd.print("WCT: ");
  printThreeDigitInt(edl.getFrame().acEvap);
}

void printSecondLine() {
  lcd.setCursor(0, 1);  //jump to new line

  lcd.print("IAT: ");
  printThreeDigitInt(edl.getFrame().IAT);

  lcd.print(" ");

  lcd.print("MAP: ");
  printThreeDigitInt(edl.getFrame().MAP);
}

void printThirdLine() {
  lcd.setCursor(0, 2);  //jump to new line

  lcd.print("OP: ");
  lcd.print(edl.getFrame().oilPressure);

  lcd.print(" ");

  lcd.print("FP:  ");
  lcd.print(edl.getFrame().fuelPressure);
}

void printFourthLine() {
  lcd.setCursor(0, 3);  //jump to new line

  lcd.print("TS:  ");
  printThreeDigitInt(edl.getFrame().boostTableSet);

  lcd.print(" ");

  lcd.print("AFR: ");
  lcd.print(edl.getFrame().wboLambda);
}

void printThreeDigitInt(int value) {
  sprintf(intStringBuff, "%3d", value);
  lcd.print(intStringBuff);
}