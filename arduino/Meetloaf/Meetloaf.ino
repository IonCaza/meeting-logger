#include <SPI.h>
#include <Ethernet.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//include arduinojson at some point

/******* Constants *******/
String version = "0.2";
bool serialOn = true; // turns on serial for debugging, although seems like even if not turned on, serial = on lol.
bool lcdOn = true;
int Button = 0; // pin for button
int LCDTime = 250; // the value of delay time for LCD
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; // MAC address
char server[] = "www.google.com";    // name address for Google (using DNS)

/******* Variables *******/
unsigned long beginMicros, endMicros;
unsigned long byteCount = 0;
bool printWebData = true;  // set to false for better speed measurement

/******* Initializing *******/
LiquidCrystal_I2C LCD(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

EthernetClient EthClient;
IPAddress ip(192, 168, 0, 177);
IPAddress myDns(192, 168, 0, 1);

void setup() {
  pinMode(Button, INPUT_PULLUP); // Pushbutton setup
  
  if (serialOn) startSerial();
  if (lcdOn) startLCD();
  printVersion();
  // connect to ethernet here
}

void loop() {
  Serial.println("In Loop");
  while(true){
    if ( digitalRead(Button) == LOW ) { //Button is pressed?  
      Serial.println("magic prese");
    }
  }
}

void printVersion() {
  LCD.setCursor(0,0);
  LCD.print("My name is");
  LCD.setCursor(0,1);
  LCD.print("meetloaf (v" + version + ")");
  delay(5000);
}

void startLCD() {
  LCD.init(); //initialize the lcd
  LCD.backlight(); //open the backlight 
  LCD.clear();
  Serial.println("LCD On");
}

void startSerial() {
  Serial.begin(9600); // Start serial
  while (!Serial) {
    // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("");
  Serial.println("Serial On");
}

void ethernetFetch() {

  // if there are incoming bytes available
  // from the server, read them and print them:
  int len = EthClient.available();
  if (len > 0) {
    byte buffer[80];
    if (len > 80) len = 80;
    EthClient.read(buffer, len);
    if (printWebData) {
      Serial.write(buffer, len); // show in the serial monitor (slows some boards)
    }
    byteCount = byteCount + len;
  }

  // if the server's disconnected, stop the client:
  if (!EthClient.connected()) {
    endMicros = micros();
    Serial.println();
    Serial.println("disconnecting.");
    EthClient.stop();
    Serial.print("Received ");
    Serial.print(byteCount);
    Serial.print(" bytes in ");
    float seconds = (float)(endMicros - beginMicros) / 1000000.0;
    Serial.print(seconds, 4);
    float rate = (float)byteCount / seconds / 1000.0;
    Serial.print(", rate = ");
    Serial.print(rate);
    Serial.print(" kbytes/second");
    Serial.println();

    // do nothing forevermore:
  }
  while (true) {

        
    }
}

void connectEthernet() {
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
  Serial.print("connecting to ");
  Serial.print(server);
  Serial.println("...");

  // if you get a connection, report back via serial:
  if (EthClient.connect(server, 80)) {
    Serial.print("connected to ");
    Serial.println(EthClient.remoteIP());
    // Make a HTTP request:
    EthClient.println("GET /search?q=arduino HTTP/1.1");
    EthClient.println("Host: www.google.com");
    EthClient.println("Connection: close");
    EthClient.println();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
  beginMicros = micros();
}
