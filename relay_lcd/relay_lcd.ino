#include <Wire.h>              //lib urusan i2c
#include <DS3232RTC.h>         //lib sensor rtc
#include <LiquidCrystal_I2C.h> //lib layar

DS3232RTC RTC;                      //pemnaggilan awal rtc
LiquidCrystal_I2C lcd(0x27, 16, 2); //layar (alamat, kolom, baris)

int Relay = 4;  //pinout relay/pompa/led etc...
int sen1 = A0;  //pinout potensio 1 (jam)
int sen2 = A1;  //pinout potensio 2 (menit)
int sen3 = A2;  //pinout potensio 3 (interval)

/**********************************************************************
   nilai yang dapat berubah digunakan untuk menyimpan nilai sementara
 **********************************************************************/
int Value1 = 0;
int Value2 = 0;
int Value3 = 0;
int Value4 = 0;
int Value5 = 0;

void setup() {
  Serial.begin(9600);  //serial monitar
  lcd.init();          //inisialisasi lcd
  lcd.backlight();     //backlight lcd
  lcd.setCursor(0, 0); //tempat pertama text (kolom, baris)
  lcd.print("timer penyiraman");
  lcd.setCursor(1, 1);
  lcd.print("by : 1999azzar");

  pinMode(4, OUTPUT);    // relay/motor (output = keluaran, input = sensor)
  digitalWrite(4, !LOW); // ! = not, !LOW = HIGH / !HIGH = LOW

  setTime(04, 29, 00, 20, 10, 2022);//Hours / minutes / second / day of month / month / year
  RTC.set(now());                   //set waktu rtc

  setSyncProvider(RTC.get);    // membaca waktu dari rtc
  if (timeStatus() != timeSet) // jika waktu rtc tak terbaca
    Serial.println("Unable to sync with the RTC");
  else
    Serial.println("RTC has set the system time");

  delay(2500);
  lcd.clear(); //membersihkan semua teks di lcd
}

void loop() {
  Value1 = analogRead(sen1);
  Value2 = analogRead(sen2);
  Value3 = analogRead(sen3);

  Serial.println(Value1);
  Serial.println(Value2);
  Serial.println(Value3);

  Value1 =  map(analogRead(sen1), 0, 1023, 1, 24); // map(sensor, minsensor, maxsensor, min, max)
  Value2 =  map(analogRead(sen2), 0, 1023, 0, 59);
  Value3 =  map(analogRead(sen3), 0, 1023, 1, 59);

  Value4 = Value1;
  Value5 = Value2 + Value3;
  if (Value3 > 59) {
    Value4 = Value1 + 1;
    Value5 = 0;
  }

  /*******************************
    printing text data on a lcd
  *******************************/
  lcd.setCursor(0, 1);
  lcd.print("timeset:");
  lcd.setCursor(8, 1);
  lcd.print(Value1);
  lcd.setCursor(10, 1);
  lcd.print(":");
  lcd.setCursor(11, 1);
  lcd.print(Value2);
  lcd.setCursor(14, 1);
  lcd.print(Value3);
  delay(250);
  lcd.setCursor(9, 1);
  lcd.print("       ");

  lcd.setCursor(0, 0);
  lcd.print("timertc:");
  lcd.setCursor(8, 0);
  lcd.print(hour());
  lcd.setCursor(10, 0);
  lcd.print(":");
  lcd.setCursor(11, 0);
  lcd.print(minute());
  lcd.setCursor(14, 0);
  lcd.print("in");
  delay(250);
  lcd.setCursor(9, 1);
  lcd.print("       ");


  /**************
    waktu hidup
  ***************/
  if (hour() == Value1 && minute() == Value2) {
    digitalWrite(Relay, !HIGH);
    Serial.println("LIGHT ON");
  }

  /*************
     waktu mati
  **************/
  else if (hour() == Value4 && minute() == Value3) {
    digitalWrite(Relay, !LOW);
    Serial.println("LIGHT OFF");
  }
}
