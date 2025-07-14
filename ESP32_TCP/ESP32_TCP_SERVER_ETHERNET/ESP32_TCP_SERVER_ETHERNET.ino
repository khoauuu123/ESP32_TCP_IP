#include <SPI.h>
#include <Ethernet2.h>  //app thu vien trong file

// Khai báo các chân SPI kết nối giữa ESP32 và Ethernet W5500
// const int spiMOSI = 19;  // Chân MOSI trên ESP32
// const int spiMISO = 23;  // Chân MISO trên ESP32
// const int spiSCK = 18;   // Chân SCK trên ESP32
const int spiCS = 53;  // Chân CS trên ESP32
const int spiRST = 8;  // Chân RST trên ESP32

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 177);
const int Port = 8088;

EthernetServer server(Port);

void setup() {
  Serial.begin(9600);
  delay(200);
  Serial.println("Begin Ethernet");
  Ethernet.init(spiCS);
  // pinMode(spiRST, OUTPUT);
  // digitalWrite(spiRST, HIGH);
  // delay(250);
  // digitalWrite(spiRST, LOW);
  // delay(50);
  // digitalWrite(spiRST, HIGH);
  // delay(350);
  Ethernet.begin(mac, ip);
  server.begin();
  delay(1000);
  Serial.print("Local IP : ");
  Serial.println(Ethernet.localIP());
  Serial.print("Port : ");
  Serial.println(Port);
  Serial.print("Subnet Mask : ");
  Serial.println(Ethernet.subnetMask());
  Serial.print("Gateway IP : ");
  Serial.println(Ethernet.gatewayIP());
  Serial.print("DNS Server : ");
  Serial.println(Ethernet.dnsServerIP());
  Serial.println("Ethernet Successfully Initialized");
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
