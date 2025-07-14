#include <SPI.h>
#include <Ethernet.h>  //app thu vien trong file

// Khai báo các chân SPI kết nối giữa ESP32 và Ethernet W5500
// const int spiMOSI = 23;  // Chân MOSI trên ESP32
// const int spiMISO = 19;  // Chân MISO trên ESP32
// const int spiSCK = 18;   // Chân SCK trên ESP32
const int spiCS = 5;    // Chân CS trên ESP32
const int spiRST = 17;  // Chân RST trên ESP32
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };


void setup() {
  Serial.begin(115200);
  delay(200);

  // Khởi tạo Ethernet W5500
  Serial.println("Begin Ethernet");
  Ethernet.init(spiCS);
  if (Ethernet.begin(mac)) {  // Dynamic IP setup
    Serial.println("DHCP OK!");
  } else {
    Serial.println("Failed to configure Ethernet using DHCP");
    // Check for Ethernet hardware present
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");

      while (true) {
        delay(1000);  // do nothing, no point running without Ethernet hardware
        static int D_reset_Ethernet = 0;
        D_reset_Ethernet++;
        Serial.print("D_reset_Ethernet: " + String(D_reset_Ethernet));
        if (D_reset_Ethernet > 60) {
          Serial.println("RESET_ON");
          Reset();
        }
      }
    }
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
  }
  //Reset module Ethernet W5500
  pinMode(spiRST, OUTPUT);
  digitalWrite(spiRST, HIGH);
  delay(250);
  digitalWrite(spiRST, LOW);
  delay(50);
  digitalWrite(spiRST, HIGH);
  delay(350);
  Ethernet.begin(mac);
  delay(1000);
  Serial.print("Local IP : ");
  Serial.println(Ethernet.localIP());
  Serial.print("Subnet Mask : ");
  Serial.println(Ethernet.subnetMask());
  Serial.print("Gateway IP : ");
  Serial.println(Ethernet.gatewayIP());
  Serial.print("DNS Server : ");
  Serial.println(Ethernet.dnsServerIP());
  Serial.println("Ethernet Successfully Initialized");
}

void loop() {
}
