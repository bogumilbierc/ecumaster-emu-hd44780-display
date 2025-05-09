#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EMUSerial.h>
#include <SoftwareSerial.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
EMUSerial emu(Serial);

char intStringBuff[3];

void setup() {
  Serial.begin(19200);

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.print("KACZKA");
  delay(3000);
}

void loop() {
  emu.checkEmuSerial();

  // Available channels: https://github.com/GTO2013/EMUSerial
  printFirstLine();
  printSecondLine();
}

void printFirstLine() {
  lcd.home();

  lcd.print("WT:");
  printThreeDigitInt(emu.emu_data.CLT);

  lcd.print(" ");

  lcd.print("TPS:");
  printThreeDigitInt(emu.emu_data.TPS);
}

void printSecondLine() {
  lcd.setCursor(0, 1);  //jump to new line

  lcd.print("OT:");
  printThreeDigitInt(emu.emu_data.oilTemperature);

  lcd.print(" ");

  lcd.print("FP:");
  lcd.print(emu.emu_data.fuelPressure);
}

void printThreeDigitInt(int value) {
  sprintf(intStringBuff, "%3d", value);
  lcd.print(intStringBuff);
}