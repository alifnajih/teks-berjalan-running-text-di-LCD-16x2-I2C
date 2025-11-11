Program ini berfungsi untuk menampilkan **teks berjalan (running text)** di **LCD 16x2 I2C**.
Teks pada **baris 1** dan **baris 2** akan **bergerak dari kanan ke kiri**, seperti efek “marquee” pada layar.

---

## ⚙️ **2. Penjelasan Baris demi Baris**

### 🔹 Bagian Import Library

```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
```

* `Wire.h` → library komunikasi **I2C (Inter-Integrated Circuit)**
* `LiquidCrystal_I2C.h` → library khusus untuk mengontrol **LCD 16x2** melalui **modul I2C**

---

### 🔹 Inisialisasi LCD

```cpp
LiquidCrystal_I2C lcd(0x27, 16, 2);
```

* `0x27` → alamat I2C modul LCD (kadang bisa juga `0x3F`, tergantung modulnya)
* `16, 2` → ukuran LCD (16 kolom × 2 baris)

---

### 🔹 Teks yang akan ditampilkan

```cpp
String teks1 = "Smart GreenBox: Inovasi Sistem Pertanian Organik Mini Berbasis IoT ...";
String teks2 = "asdsfjakcmhjsjkhj";
```

* `teks1` → teks panjang yang ditampilkan di baris pertama
* `teks2` → teks yang ditampilkan di baris kedua

---

### 🔹 Inisialisasi Awal

```cpp
void setup() {
  lcd.init();
  lcd.backlight();
}
```

* `lcd.init()` → menginisialisasi LCD
* `lcd.backlight()` → menyalakan lampu latar LCD agar tulisan terlihat

---

### 🔹 Loop Utama

```cpp
void loop() {
  int panjang1 = teks1.length();
  int panjang2 = teks2.length();
  int maxPanjang = max(panjang1, panjang2);
```

* Mengambil panjang masing-masing teks
* Menentukan teks mana yang paling panjang untuk dijadikan acuan scroll

---

### 🔹 Proses Scrolling (Running Text)

```cpp
for (int pos = 0; pos < maxPanjang + 16; pos++) {
  lcd.clear();
```

* `pos` menentukan posisi “geser” teks
* `lcd.clear()` membersihkan tampilan LCD setiap kali pergeseran baru ditampilkan

---

### 🔹 Hitung Bagian Teks yang Ditampilkan

```cpp
int start1 = max(0, pos - 16);
int end1 = min(pos, panjang1);
int start2 = max(0, pos - 16);
int end2 = min(pos, panjang2);
```

* Menentukan bagian teks mana yang sedang terlihat di LCD
* LCD hanya bisa menampilkan **16 karakter**, jadi substring dari `start` sampai `end` yang aktif saja yang dicetak

---

### 🔹 Menampilkan ke LCD

```cpp
lcd.setCursor(0, 0);
if (start1 < panjang1) lcd.print(teks1.substring(start1, end1));

lcd.setCursor(0, 1);
if (start2 < panjang2) lcd.print(teks2.substring(start2, end2));
```

* Baris pertama (`y=0`) menampilkan bagian teks1
* Baris kedua (`y=1`) menampilkan bagian teks2
* `substring(start, end)` mengambil potongan teks dari indeks tertentu

---

### 🔹 Delay Scroll

```cpp
delay(250);
```

* Menentukan kecepatan scroll
* Semakin kecil angka (misal 100), teks berjalan semakin cepat

---

## 🔌 **3. Wiring LCD I2C ke ESP8266 (NodeMCU atau Wemos D1 Mini)**

| LCD I2C Pin | ESP8266 Pin    | Keterangan                                  |
| ----------- | -------------- | ------------------------------------------- |
| **VCC**     | **3V3**        | Daya 3.3V (beberapa modul LCD bisa juga 5V) |
| **GND**     | **GND**        | Ground                                      |
| **SDA**     | **D2 (GPIO4)** | Data I2C                                    |
| **SCL**     | **D1 (GPIO5)** | Clock I2C                                   |

🧩 **Keterangan tambahan:**

* Gunakan **resistor pull-up 4.7kΩ – 10kΩ** jika komunikasi I2C tidak stabil.
* Pastikan alamat I2C LCD benar (`0x27` atau `0x3F`). Kamu bisa cek dengan **I2C Scanner**.

---

## 🖥️ **4. Alur Kerja Singkat**

1. ESP8266 menyalakan LCD dan backlight.
2. Membaca teks yang panjang (lebih dari 16 karakter).
3. Menggeser tampilan teks sedikit demi sedikit dari kanan ke kiri.
4. Ketika teks sudah selesai tampil, loop diulang sehingga teks berjalan terus.

---

## 📊 **5. Tampilan Hasil**

LCD akan menampilkan:

```
Smart GreenBox: I
nasi Sistem Per...
```

...dan terus bergeser seperti **running text dua baris**.
