#include <LoRa.h>
#include <Adafruit_ADS1X15.h> //this testing has use the ADS1115 ADC expander
#include <PCF8574.h> //this testing has use the PCF8574 I/O expander

#include "Wire.h"
#include "BH1750.h" //this testing has use the ambientLight sensor (BH1750)

PCF8574 PCF(0x20);
Adafruit_ADS1115 ads0;
Adafruit_ADS1115 ads1;
BH1750 lightSensor;

// custom pin connect to LoRa module 
//#define ss D0    //D0
//#define rst D1   //D1
//#define dio0 D2  //D2

// Define Node Address
byte masterNode = 0xFF;     
byte slaveNode1 = 0xBB;
// byte slaveNode2 = 0xCC; 

int data0 = 0;
int data1 = 0;
int data2 = 0;
int data3 = 0;

String NODE = "node1";

//================================================< main function >
//------------------------------------------------< Setup >
void setup() {
  Serial.begin(9600);
  Serial.println("Role: Slave1");

  LoRa_setup();
  PCF8574_setup();
  ADS1115_setup();

  BH1750_setup();

  //if init succeeded!
  PCF.digitalWrite(P4, 0); //this testing has use PCF8574 I/O expander pin P4 and P5 connect with LED
  PCF.digitalWrite(P5, 0); //this testing has use PCF8574 I/O expander pin P4 and P5 connect with LED
}

//------------------------------------------------< Loop >
void loop() {
  // when master call every slave node. slave must listen.. it me?
  onReceive(LoRa.parsePacket());
}

//================================================< Custom function >
//------------------------------------------------< The slave node check the request from master.. him call me? >
void onReceive(int packetSize) {
  if (packetSize == 0){
    return;                           // if there's no packet, return 
  }
  else{
    byte recipient = LoRa.read();         // 1. the slave address who master call.
    byte sender = LoRa.read();            // 2. sender address
    byte incomingLength = LoRa.read();      // 3. incoming msg length

    String incoming = "";
    while (LoRa.available()) {
      incoming += (char)LoRa.read();        // 4. incoming payload (the slave who master call)
    }
  
    if (incomingLength != incoming.length()) {   // check length for error
      // Serial.println("error: message length does not match length");
      return;
    }

    if (recipient != slaveNode1) { // check master send a slave address if not match my address
      // Serial.println("This message is not for me.");
      return;
    }

  
    String masterMsg = incoming;
    if(masterMsg == "req -> node1"){ 

      //create data form and response to LoRa end-device (Master)
      
      String dataForm = "";
      int16_t soilMoisture_val = SoilMoisture();
      float lux_val = lightSensor.readLightLevel();

      dataForm += "{";
      dataForm += "\"Slave\" : \""  + NODE +   "\", ";
      dataForm += "\"Data0\" : \""  + String(soilMoisture_val) +  "\", ";
      dataForm += "\"Data1\" : \""  + String(lux_val) +  "\", ";
      dataForm += "\"Data2\" : \""  + String(data2) +  "\", ";
      dataForm += "\"Data3\" : \""  + String(data3) +  "\", ";
      // dataForm += "\"RSSI\" : \""  + rssi +   "\" ";
      // dataForm += "}";

      sendMessage(dataForm, masterNode, slaveNode1);
      delay(100);
    }

  }

}

//------------------------------------------------< response data to the master >
void sendMessage(String outgoing, byte MasterNode, byte otherNode) {
  LoRa.beginPacket();                   // start packet
  LoRa.write(MasterNode);               // 1. add Master address
  LoRa.write(otherNode);                // 2. add my slave address
  LoRa.write(outgoing.length());        // 3. add payload length
  LoRa.print(outgoing);                 // 4. add payload
  LoRa.endPacket();                     // finish packet and send it
}

//------------------------------------------------< LoRa setup >
void LoRa_setup(){
  //setup LoRa transceiver module
  LoRa.setPins(ss, rst, dio0);

  while (!LoRa.begin(433E6)) { // or 915E6, the MHz speed of yout module
    // Serial.println("Starting LoRa failed!..");
    delay(500);
  }
   // Change sync word (0xF3) to match the receiver
  // The sync word assures you don't get LoRa messages from other LoRa transceivers
  // ranges from 0-0xFF
  LoRa.setSpreadingFactor(10);           // ranges from 6-12,default 7 see API docs
  LoRa.setSignalBandwidth(125E3);           // for -139dB (page - 112)
  LoRa.setCodingRate4(5);                   // for -139dB (page - 112)
  LoRa.setSyncWord(0x31);

  Serial.println("LoRa init succeeded!");
}

//------------------------------------------------< PCF8574 setup >
void PCF8574_setup(){
  // address 0x20 (A0: 0 (GND), A1: 0 (GND), A2: 0 (GND))

  // PCF.pinMode(P0, OUTPUT);
  // PCF.pinMode(P1, OUTPUT);
  // PCF.pinMode(P2, OUTPUT);
  // PCF.pinMode(P3, OUTPUT);
  PCF.pinMode(P4, OUTPUT);
  PCF.pinMode(P5, OUTPUT);
  // PCF.pinMode(P6, OUTPUT);
  // PCF.pinMode(P7, OUTPUT);

  PCF.begin();
}

//------------------------------------------------< PCF8574 setup >
void ADS1115_setup(){
  ads0.begin(0x48); // ADDR pin connect GND
  ads1.begin(0x49); // ADDR pin connect VCC

  while(!ads0.begin(0x48)){
    Serial.println("Failed to initialize ADS0.");
    delay(200);
  }
  Serial.println("ADS0 Connected");

  while(!ads1.begin(0x49)){
    Serial.println("Failed to initialize ADS1.");
    delay(200);
  }
  Serial.println("ADS1 Connected");
}

//------------------------------------------------< Soil moisture sensor >
int16_t SoilMoisture(){
  int16_t adc0 = ads1.readADC_SingleEnded(0);
  if(adc0 >= 19300){
    adc0 = 19300;
  }
  else if(adc0 <= 13000){
    adc0 = 13000;
  }
  int16_t adc0_map = map(adc0, 13000, 19300, 100, 0);
  // Serial.println("AIN0: " + String(adc0) + ", " + "%: " + String(adc0_map));
  return adc0_map;
}

//------------------------------------------------< BH1750 setup >
void BH1750_setup(){
  Wire.begin();
  lightSensor.begin(); //address 0x23 (default)
}








