#include <WiFi.h>
const char* ssid     = "MEI GROUP 02";
const char* password = "77namhai88";
/* create a server and listen on port 8088 */
const int port = 8088;
WiFiServer server(port);
void setup()
{
  Serial.begin(115200);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  /* connecting to WiFi */
  WiFi.begin(ssid, password);
  /*wait until ESP32 connect to WiFi*/
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected with IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Port : ");
  Serial.println(port);
  Serial.print("Subnet Mask : ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway IP : ");
  Serial.println(WiFi.gatewayIP());
  //Serial.print("DNS Server : ");
  //Serial.println(WiFi.dnsServerIP());
  /* start Server */
  server.begin();
}

String GET = "";
String SEND = "";
void loop() {
  /* listen for client */
  WiFiClient client = server.available();
  
  if (client) {
    Serial.println("new client");
    /* check client is connected */
    while (client.connected()) {
      while (client.available() > 0) {
        // read data from the connected client
        //Serial.write(client.read());
        char c = client.read();
        if (c == '\n') {
          Serial.print("C#: "); Serial.println(GET);
          GET = "";
          break;
        }
        else GET += c;
      }
      //Send Data to connected client
      while (Serial.available() > 0)
      {
        char c = Serial.read();
        if (c == '\n') {
          Serial.print("ESP: "); Serial.println(SEND);
          client.println(SEND);
          SEND = "";
          break;
        }
        else SEND += c;
      }
    }
    client.stop();
    Serial.println("Client disconnected");
  }
}
