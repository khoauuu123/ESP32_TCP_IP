#include <SPI.h>
#include <Ethernet2.h>  //app thu vien trong file

// Khai báo các chân SPI kết nối giữa Arduino Mega và Ethernet W5500
// const int spiMOSI = 51;  // Chân MOSI trên Mega
// const int spiMISO = 50;  // Chân MISO trên Mega
// const int spiSCK = 52;   // Chân SCK trên Mega
const int spiCS = 53;   // Chân CS trên Mega
const int spiRST = 13;  // Chân RST trên Mega

// Khai báo địa chỉ MAC và IP của Arduino
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 177);

const int Port = 8088;
EthernetServer server(Port);

void setup() {
  Serial.begin(9600);
  delay(200);

  // kết nối Ethernet
  Ethernet.init(spiCS);
  pinMode(spiRST, OUTPUT);
  digitalWrite(spiRST, HIGH);
  delay(250);
  digitalWrite(spiRST, LOW);
  delay(50);
  digitalWrite(spiRST, HIGH);
  delay(350);

  Serial.println("Begin Ethernet");
  Ethernet.begin(mac, ip);
  Serial.print("Local IP : ");
  Serial.println(Ethernet.localIP());
  Serial.print("Subnet Mask : ");
  Serial.println(Ethernet.subnetMask());
  Serial.print("Gateway IP : ");
  Serial.println(Ethernet.gatewayIP());
  Serial.print("DNS Server : ");
  Serial.println(Ethernet.dnsServerIP());
  Serial.println("Ethernet Successfully Initialized");

  server.begin();
  Serial.print("Port : ");
  Serial.println(Port);
}
String GET = "";
String SEND = "";
void loop() {
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    while (client.connected()) {  //GET DATA TCP/IP
      if (client.available() > 0) {
        char c = client.read();
        if (c == '\n') {
          Serial.print("C#: ");
          Serial.println(GET);
          GET = "";
        } else GET += c;
      }
      if (Serial.available() > 0) {  //GET DATA SERIAL
        char c = Serial.read();
        if (c == '\n') {
          Serial.print("ESP: ");
          Serial.println(SEND);
          client.println(SEND);  //SEND DATA TCP/IP
          SEND = "";
        } else SEND += c;
      }
    }
    client.stop();
    Serial.println("Client disconnected");
  }
}
