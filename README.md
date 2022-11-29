# Xiaomi-Esp32-Oda-Termostat-
Xiaomi Mi Temp-Esp32 Uzaktan kontrollü oda termostatı


Gerekli Malzemeler

1-Xiomi Mi Temp //https://www.hepsiburada.com/xiaomi-mijia-bluetooth-termometre-2-p-HBV00001AIHYY?magaza=Tek%20Sepeti
2- Esp32 Wroom 32U
3- Nrf24
4- 5v Röle
5- Jumper Kablolar

Öncelikle Xiaomi termostatında bir kaç ayar yapmamız gerekiyor. Bunun için sizi bir siteye yönlendiriyorum.

https://github.com/atc1441/ATC_MiThermometer

Üstte bıraktığım linkteki uygulamaları termostatımıza yapalım.

Sizlere esp32-nrf24 ve 5v röle bağlantı tablosunu paylaşıyorum.


![Pinout-nRF24L01-PA-LNA-External-Antenna-Wireless-Transceiver-Module](https://user-images.githubusercontent.com/100942011/204525532-a223fe63-9a05-4757-aadc-066dcac1453f.png)
![ESP32-DOIT-DEV-KIT-v1-pinout-mischianti-1024x501](https://user-images.githubusercontent.com/100942011/204525578-49b2ba06-03fd-4871-91b3-1672eb51a020.png)


nrf24-esp32

3.3v   -   3.3v
csn    -    d5
mosi   -    d23
IRQ    -    Boş Pin
GND    -    GND
CE      -   17 TX2
SCK     -   d18
MISO    -   d19

5vröle esp32

VCC     -    5v
GND     -    GND
IN      -    d13
