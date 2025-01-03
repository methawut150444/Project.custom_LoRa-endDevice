#include <LoRa.h>

//custom pin to connect to LoRa modle
//#define ss D0 //DO (esp32 XIAO c3)
//#define rst D1 //D1 (esp32 XIAO c3)
//#define dio0 D2 //D2 (esp32 XIAO c3) 

void setup() {
  // Serial.begin(9600);
  // Serial.println("Role: Transmitter");

  LoRa.setPins(ss, rst, dio0); //default setting in LoRa library -> ss: 10, rst: 9, dio0: 2

  while (!LoRa.begin(433E6)) { // or 915E6, the MHz speed of yout module
    // Serial.println("Starting LoRa failed!..");
    delay(100);
  }
   // Change sync word (0xF3) to match the receiver
  // The sync word assures you don't get LoRa messages from other LoRa transceivers
  // ranges from 0-0xFF
  LoRa.setSpreadingFactor(10);           // ranges from 6-12,default 7 see API docs
  LoRa.setSignalBandwidth(125E3);           // for -139dB (page - 112)
  LoRa.setCodingRate4(5);                   // for -139dB (page - 112)
  LoRa.setSyncWord(0x31);

  // Serial.println("LoRa init succeeded!");
}

void loop() {
  //Send LoRa packet to receiver
  LoRa.beginPacket();
  LoRa.print(jsonData);
  LoRa.endPacket();

  delay(1000);
}
