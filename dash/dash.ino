#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EMUSerial.h>
#include <SoftwareSerial.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
EMUSerial emu(Serial);

void setup() {
  Serial.begin(19200);

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.print("EMU BIEDADU");
}

void loop() {
  emu.checkEmuSerial();

  // Available channels: https://github.com/GTO2013/EMUSerial

  lcd.home();
  lcd.print("WT:");
  lcd.print(emu.emu_data.CLT);
  lcd.print(" ");
  lcd.print("TPS:");
  lcd.print(emu.emu_data.TPS);


  lcd.setCursor(0, 1);  //jump to new line
  lcd.print("OT:");
  lcd.print(emu.emu_data.oilTemperature);
  lcd.print(" ");
  lcd.print("FP:");
  lcd.print(emu.emu_data.fuelPressure);
}
