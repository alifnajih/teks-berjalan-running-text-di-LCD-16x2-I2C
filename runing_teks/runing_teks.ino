#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Teks baris 1 dan 2
String teks1 = "Smart GreenBox: Inovasi Sistem Pertanian Organik Mini Berbasis IoT dengan Integrasi Sensor Lingkungan untuk Mendukung Pertanian Efisien dan Berkelanjutan";
String teks2 = "asdsfjakcmhjsjkhj";

void setup() {
  lcd.init();
  lcd.backlight();
}

void loop() {
  int panjang1 = teks1.length();
  int panjang2 = teks2.length();
  int maxPanjang = max(panjang1, panjang2);

  for (int pos = 0; pos < maxPanjang + 16; pos++) {
    lcd.clear();

    int start1 = max(0, pos - 16);
    int end1 = min(pos, panjang1);
    int start2 = max(0, pos - 16);
    int end2 = min(pos, panjang2);

    lcd.setCursor(0, 0);
    if (start1 < panjang1) lcd.print(teks1.substring(start1, end1));

    lcd.setCursor(0, 1);
    if (start2 < panjang2) lcd.print(teks2.substring(start2, end2));

    delay(250);
  }
}
