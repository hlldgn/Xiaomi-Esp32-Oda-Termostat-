#include <SPI.h>
#include <RF24.h>
#include <BTLE.h>
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <FirebaseESP32.h> 
#include <addons/RTDBHelper.h>
#define DATABASE_URL "Your Firebase Database URL"
#define DATABASE_SECRET "Your Firebase Database Secret"
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

RF24 radio(17, 5); // NRF24 PİN
BTLE btle(&radio);
int temp = 0;
int hum = 0;
int bat = 0;
int signaLed = 2;
byte relayPin = 13;


void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFiManager wm;
  bool res;
  res = wm.autoConnect("Your Wifi Name");
  if (!res) {
    Serial.println("Connection failed");
    ESP.restart();
  }
  else {
    Serial.println("Connection Successful)");
  }
  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
  Serial.println("BTLE advertisement receiver");
  pinMode(relayPin, OUTPUT);
  pinMode(signaLed, OUTPUT);
}
void loop() {
  
  btle.begin("");
  uint8_t *recv = btle.buffer.payload;
  if (btle.listen())
  {
    //10 16 1a 18 a4 c1 38 6a c0 b6 00 e4 28 57 0b ad b8 // Xiaomi Mi Temp
    if (recv[4] == 0xa4 && recv[7] == 0x6a && recv[8] == 0xc0 && recv[9] == 0xb6)
    {
      for (int i = 1; i < 4; i++)
      {
        digitalWrite(signaLed, HIGH);
        delay(50);
        digitalWrite(signaLed, LOW);
        delay(50);
      }
      char charValue[5] = {0,};
      sprintf(charValue, "%02X%02X", recv[10], recv[11]);
      temp = strtol(charValue, 0, 16);
      bat = recv[13];
      hum=recv[12];
      Serial.print("temp : "); Serial.println(temp);
      Serial.print("bat : %"); Serial.println(bat);
      Serial.print("hum : %"); Serial.println(hum);
    }

//temp1=desired temperature
//temp=instant temperature
//hum=humidity
//sens=sensibility
//bstat=combi boiler status
//bat=battery status
    
    Firebase.begin(&config, &auth);
    String temp10 = Firebase.getInt(fbdo, "AppModels/temp1") ? String(fbdo.to<int>()).c_str() : fbdo.errorReason().c_str();
    String sens0 = Firebase.getInt(fbdo, "AppModels/sens") ? String(fbdo.to<int>()).c_str() : fbdo.errorReason().c_str();
    String bstat0 = Firebase.getInt(fbdo, "AppModels/bstat") ? String(fbdo.to<int>()).c_str() : fbdo.errorReason().c_str();
    Firebase.setInt(fbdo, "TermoModels/temp", temp);
    Firebase.setInt(fbdo, "TermoModels/hum", hum);
    Firebase.setInt(fbdo, "TermoModels/bat", bat);
    int temp100 = temp10.toInt();
    int sens10 = sens0.toInt();

    if (bstat == "1")
    {
      if (temp != 0)
      {
        if (temp >= (temp100 + sens10))
        {
          digitalWrite(relayPin, LOW);
        }
        else if (temp <= (temp100 - sens10))
        {
          digitalWrite(relayPin, HIGH);
        }

      }
    }
    else
    {
      digitalWrite(relayPin, LOW);
    }
  }
  btle.hopChannel();
}
