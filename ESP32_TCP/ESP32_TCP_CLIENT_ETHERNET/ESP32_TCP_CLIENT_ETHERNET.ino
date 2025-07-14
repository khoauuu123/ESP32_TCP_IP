#include <SPI.h>
#include <Ethernet.h> // OR #include <Ethernet2.h>

// Khai báo các chân SPI kết nối giữa ESP32 và Ethernet W5500
// const int spiMOSI = 19;  // Chân MOSI trên ESP32 
// const int spiMISO = 23;  // Chân MISO trên ESP32 
// const int spiSCK = 18;   // Chân SCK trên ESP32 
const int spiCS = 5;    // Chân CS trên ESP32 
const int spiRST = 21;  // Chân RST trên ESP32 

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
#define MYIPADDR 192,168,0,126
//#define MYIPMASK 255,255,255,0
//#define MYDNS 192,168,1,1
//#define MYGW 192,168,1,1

const char* host = "192.168.0.119";
const int port = 8088;
EthernetClient client;
bool connected = false;

void setup() {
  Serial.begin(115200);
  delay(200);
  Serial.println("Begin Ethernet");
  Ethernet.init(spiCS);
  pinMode(spiRST, OUTPUT);
  digitalWrite(spiRST, HIGH);
  delay(250);
  digitalWrite(spiRST, LOW);
  delay(50);
  digitalWrite(spiRST, HIGH);
  delay(350);
  if (Ethernet.begin(mac)) { // Dynamic IP setup
    Serial.println("DHCP OK!");
  } else {
    Serial.println("Failed to configure Ethernet using DHCP");
    // Check for Ethernet hardware present
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
      while (true) {
        delay(1); // do nothing, no point running without Ethernet hardware
      }
    }
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }

    IPAddress ip(MYIPADDR);
    //    IPAddress dns(MYDNS);
    //    IPAddress gw(MYGW);
    //    IPAddress sn(MYIPMASK);
    //    Ethernet.begin(mac, ip, dns, gw, sn);
    Ethernet.begin(mac, ip);
    Serial.println("STATIC OK!");
  }
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
  delay(5000);
  Serial.print("connecting to ");
  Serial.println(host);

  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    return;
  }
  /* This will send the data to the server */
  client.print("hello world");

}
