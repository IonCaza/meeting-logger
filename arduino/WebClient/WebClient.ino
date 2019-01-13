/*
  Client for meetloaf
 */

#include <ArduinoJson.h>
#include <ArduinoHttpClient.h>
#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)
char server[] = "hal.atex.us";    // (using DNS)
int port = 3000;

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192, 168, 0, 177);
IPAddress myDns(192, 168, 0, 1);

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient eth0;

HttpClient client = HttpClient(eth0, server, port);
int status = 0;
int statusCode = 0;
String response;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // start the Ethernet connection:
  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
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
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip, myDns);
  } else {
    Serial.print("  DHCP assigned IP ");
    Serial.println(Ethernet.localIP());
  }
  
  // give the Ethernet shield a second to initialize:
  delay(1000);
}

void loop() {

  Serial.print("making POST request to ");
  Serial.println(server);
  String contentType = "application/JSON";  
  String postData = "{ \"username\":\"1\",\"password\":\"1\" }";

  client.post("/api/signin", contentType, postData);

  // read the status code and body of the response
  delay(2000);
  statusCode = client.responseStatusCode();
  response = client.responseBody();

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);

  DynamicJsonDocument doc;
  deserializeJson(doc, response);
  JsonObject obj = doc.as<JsonObject>();

  String token = obj[String("token")];
  Serial.print("token:");
  Serial.println(token);

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println("disconnecting.");
    client.stop();
    
    // do nothing forevermore:
    while (true) {
      delay(1);
    }
  }
     while (true) {
      delay(1);
    }
}
