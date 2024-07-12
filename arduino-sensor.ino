/*************************************************************
  Blynk is a platform with iOS and Android apps to control
  ESP32, Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build mobile and web interfaces for any
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: https://www.blynk.io
    Sketch generator:           https://examples.blynk.cc
    Blynk community:            https://community.blynk.cc
    Follow us:                  https://www.fb.com/blynkapp
                                https://twitter.com/blynk_app

  Blynk library is licensed under MIT license
 *************************************************************
  Blynk.Edgent implements:
  - Blynk.Inject - Dynamic WiFi credentials provisioning
  - Blynk.Air    - Over The Air firmware updates
  - Device state indication using a physical LED
  - Credentials reset using a physical Button
 *************************************************************/

/* Fill in information from your Blynk Template here */
/* Read more: https://bit.ly/BlynkInject */
#define BLYNK_TEMPLATE_ID           "TMPL3xRD2wlFd"
#define BLYNK_TEMPLATE_NAME         "Quickstart Device"
#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
//#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI

#include <ESP8266WiFi.h>
#include "BlynkEdgent.h"

#include "Wire.h"
#include "SHT31.h"
#define SHT31_ADDRESS 0x44

uint32_t start;
uint32_t stop;

SHT31 sht;
float t;
float h;

BlynkTimer timer;


void setup()
{
  
  Serial.begin(115200);
  delay(100);

  BlynkEdgent.begin();
  Wire.begin(D6,D5);
  sht.begin();
  timer.setInterval(10000, sendTemp);

}

void sendTemp()
{ 
  sht.read();
  t=sht.getTemperature();
  h=sht.getHumidity();

  Serial.print("\t");
  Serial.print(t);
  Serial.print("\t");
  Serial.println(h);
  Blynk.virtualWrite(V10,t);
  Blynk.virtualWrite(V11,h);
}

void loop() {
  BlynkEdgent.run();
  timer.run();
}


