#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EMUSerial.h>
#include <SoftwareSerial.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);
EMUSerial emu(Serial);

char intStringBuff[3];

void setup() {
  Serial.begin(19200);

  lcd.init();
  lcd.backlight();
  lcd.clear();
  printSplashScreen();
}

void printSplashScreen(){
  lcd.home();
  lcd.print("DUCK");
  delay(1500);
  lcd.setCursor(0, 1);  //jump to new line
  lcd.print("   QUACK");
  delay(1500);
  lcd.setCursor(0, 2);  //jump to new line
  lcd.print("      QUACK");
  delay(1500);
  lcd.setCursor(0, 3);  //jump to new line
  lcd.print("         QUACK");
  delay(1500);
  delay(1500);
}

void loop() {
  emu.checkEmuSerial();

  // Available channels: https://github.com/GTO2013/EMUSerial
  printFirstLine();
  printSecondLine();
  printThirdLine();
  printFourthLine();
}

void printFirstLine() {
  lcd.home();

  lcd.print("CLT: ");
  printThreeDigitInt(emu.emu_data.CLT);

  lcd.print(" ");

  lcd.print("TPS: ");
  printThreeDigitInt(emu.emu_data.TPS);
}

void printSecondLine() {
  lcd.setCursor(0, 1);  //jump to new line

  lcd.print("IAT: ");
  printThreeDigitInt(emu.emu_data.IAT);

  lcd.print(" ");

  lcd.print("MAP: ");
  printThreeDigitInt(emu.emu_data.MAP);
}

void printThirdLine() {
  lcd.setCursor(0, 2);  //jump to new line

  lcd.print("OT:  ");
  printThreeDigitInt(emu.emu_data.oilTemperature);

  lcd.print(" ");

  lcd.print("FP:  ");
  lcd.print(emu.emu_data.fuelPressure);
}

void printFourthLine() {
  lcd.setCursor(0, 3);  //jump to new line

  lcd.print("TS:  ");
  printThreeDigitInt(emu.emu_data.tablesSet);

  lcd.print(" ");

  lcd.print("AFR: ");
  lcd.print(emu.emu_data.wboAFR);
}

void printThreeDigitInt(int value) {
  sprintf(intStringBuff, "%3d", value);
  lcd.print(intStringBuff);
}