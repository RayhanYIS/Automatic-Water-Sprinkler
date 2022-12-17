#include <Wire.h>
#include <DS3232RTC.h>
#include <LiquidCrystal_I2C.h>

DS3232RTC waktu;
LiquidCrystal_I2C lcd(0x27, 16, 2);

int pumper = A1;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);  //serial monitar
  lcd.init();          //inisialisasi lcd
  lcd.backlight();     //backlight lcd

  setTime(19, 9, 30, 9, 12, 2022);    //Hours / minutes / second / day of month / month / year
  waktu.set(now());                   //set waktu rtc

  lcd.setCursor(0, 0);
  lcd.print("Hello welcome");
  delay(1000);
  lcd.clear();

  pinMode(A1, OUTPUT);
  digitalWrite(pumper, !LOW);
}

void loop() {

  lcd.setCursor(0, 0);
  lcd.print("waktu : ");
  lcd.setCursor(8, 0);
  lcd.print(hour());
  lcd.setCursor(10, 0);
  lcd.print(":");
  lcd.setCursor(11, 0);
  lcd.print(minute());
  lcd.setCursor(13, 0);
  lcd.print(":");
  lcd.setCursor(14, 0);
  lcd.print(second());

  delay(250);
  lcd.clear();

  if (hour() == 19 && minute() == 10 && second() == 00) {
    digitalWrite(pumper, !HIGH);
    Serial.println("LIGHT ON");
    lcd.setCursor(0, 1);
    lcd.print("PUMPER ON");
    delay(10000);
    digitalWrite(pumper, !LOW);
    Serial.println("PUMPER OFF");
    lcd.setCursor(0, 1);
    lcd.print("PUMPER OFF");
  }
}
