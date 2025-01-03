#include <WiFi.h>
#include <HTTPClient.h>

//Input your ssid and password Wi-Fi network
//#define ssid "PlanetCentric"
//#define password "BearLab!"

#include <LoRa.h>

// custom pin to connect LoRa module
//#define ss D0    //D0
//#define rst D1   //D1
//#define dio0 D2  //D2

// Define Node Address
byte masterNode = 0xFF;     
byte slaveNode1 = 0xBB;
//byte slaveNode2 = 0xCC; //if you have a LoRa slave more than 1 module
//byte slaveNode3 = 0xEE; //if you have a LoRa slave more than 1 module

// Time Interval
unsigned long last_ms = 0;
unsigned long int last_s = 0; 
unsigned long int current_s = 0; 
unsigned long current_ms = 0;
int interval = 1 ; // updated every 1 second
int Secs = 0; 


//================================================< main function >
//------------------------------------------------< Setup >
void setup() {
  Serial.begin(9600);
  Serial.println("Role: Master");

  LoRa_setup();
  WiFi_setup(); //if you want not to connect Wi-Fi please comment this function.
}

//------------------------------------------------< Loop >
void loop() {
  current_ms = millis();
  current_s = current_ms / 1000;
  if((unsigned long)(current_s - last_s) >= interval){
    Secs = Secs + 1;
    if(Secs >= 10){
      Secs = 0; 
    }
    //------------------< start request data from node> 
    //define your time interval each slaves
    if(Secs == 0){
      String message = "req -> node1"; 
      sendMessage(message, masterNode, slaveNode1);
    }
    if(Secs == 4){
     
      String message = "req -> node2"; 
      sendMessage(message, masterNode, slaveNode2);
    }
    //if you have a LoRa slave more than 1 module
    // if(Secs == 8){
     
    //   String message = "req -> node3"; 
    //   sendMessage(message, masterNode, slaveNode3);
    // }

    //------------------< end > 
    last_s = current_s;
  }
  onReceive(LoRa.parsePacket());
}


//================================================< Custom function >
//------------------------------------------------< Master send request to other slave node >
void sendMessage(String outgoing, byte MasterNode, byte otherNode) {

  // you can reduce or add function LoRa.write(); that sending data function  
  
  LoRa.beginPacket();                 // start packet
  LoRa.write(otherNode);              // 1. add destination address
  LoRa.write(MasterNode);             // 2. add sender address
  LoRa.write(outgoing.length());      // 3. add payload length
  LoRa.print(outgoing);               // 4. add payload
  LoRa.endPacket();                   // finish packet and send it
}

//------------------------------------------------< Master get response from some slave node >
void onReceive(int packetSize){
  if (packetSize == 0){
    return;                           // if there's no packet, return 
  }
  else{
    byte recipient = LoRa.read();         // 1. recipient address
    byte sender = LoRa.read();            // 2. sender address

    String SenderNode = "";
    if(sender == 0xBB){
      SenderNode = "Node1";
    }
    if(sender == 0xCC ){
      SenderNode = "Node2";
    }
    if(sender == 0xEE ){
      SenderNode = "Node3";
    }

    byte incomingLength = LoRa.read();    // 3. incoming msg length

    String incoming = "";
    while(LoRa.available()) {
      incoming += (char)LoRa.read();      // 4. incoming payload from slave
    }
  
    if (incomingLength != incoming.length()) {   // check length for error
      //Serial.println("error: message length does not match length");
      return;
    }
    if (recipient != masterNode) { // check  slave send a address if not match the masterNode address
      // Serial.println("This message is not for me.");
      return;
    }

    
    Serial.println(SenderNode + " " + incoming + " | RSSI: " + String(LoRa.packetRssi()));

    
    //incoming += "\"RSSI\" : \""  + String(LoRa.packetRssi()) +   "\" ";
    //incoming += "}";
    
    recordMessage(incoming); //if you want not to connect API please comment this function.
  }
}

//------------------------------------------------< send to server and DB >
void recordMessage(String jsonBody) {
  if(WiFi.status()== WL_CONNECTED){
    HTTPClient http;
    http.begin("http://feb-by.gl.at.ply.gg:64487/api/v1/independentStudy/LoRa_Module/record");

    http.addHeader("Content-Type", "application/json");

    // String jsonData = "";

    // jsonData += "{";
    // jsonData += "\"Slave\" : \""  + Node +   "\", ";
    // jsonData += "\"Data\" : \""  + data +   "\", ";
    // jsonData += "\"RSSI\" : \""  + rssi +   "\" ";
    // jsonData += "}";

    // Serial.println(jsonData);

    int httpResponseCode = http.POST(jsonBody);

    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      String payload = http.getString();
      Serial.println(payload);
    } 
    else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
  }
  else{
    Serial.println("WiFi Disconnected");
  }
  
}

//------------------------------------------------< LoRa setup >
void LoRa_setup(){
  //setup LoRa transceiver module
  LoRa.setPins(ss, rst, dio0);

  Serial.println("Connecting LoRa.");
  while (!LoRa.begin(433E6)) { // or 915E6, the MHz speed of yout module
    Serial.print(".");
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

//------------------------------------------------< WiFi setup >
void WiFi_setup(){
  WiFi.begin(ssid, password);

  Serial.println("Connecting Wi-Fi.");
  while(WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }
  Serial.println("WiFi Connected");
}
