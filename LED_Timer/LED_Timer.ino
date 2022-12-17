#include "lib.h"
void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  pinMode(LED, OUTPUT);
  lcd.init();
  lcd.backlight();

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  DateTime now = rtc.now();

  jam = now.hour();
  menit = now.minute();
  detik = now.second();

  Serial.print("JAM =");
  Serial.println(jam);
  Serial.print("MENIT =");
  Serial.println(menit);
  Serial.print("DETIK =");
  Serial.println(detik);

  hidup_mati();

  if (jam < 10) {
    lcd.setCursor(0, 0);
    lcd.print("0");
    lcd.print(jam);
  }
  else if (jam > 9) {
    lcd.setCursor(0, 0);
    lcd.print("");
    lcd.print(jam);
  }
  if (menit < 10) {
    lcd.setCursor(2, 0);
    lcd.print(":0");
    lcd.print(menit);
  }
  else if (menit > 9) {
    lcd.setCursor(2, 0);
    lcd.print(":");
    lcd.print(menit);
  }
  if (detik < 10) {
    lcd.setCursor(5, 0);
    lcd.print(":0");
    lcd.print(detik);
  }
  else if (detik > 9) {
    lcd.setCursor(5, 0);
    lcd.print(":");
    lcd.print(detik);
  }
  delay(1000);

}
