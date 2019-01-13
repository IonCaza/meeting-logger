#include <SPI.h>
#include <Ethernet.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


int Button = 0; // pin for button
/**********************************************************/
char array1[]="1234567890111213                "; //the string to print on the LCD
char array2[]="1234567890111214                "; //the string to print on the LCD
char array3[]="1234567890111215                "; //the string to print on the LCD

int LCDTime = 250; //the value of delay time

// initialize the library with the numbers of the interface pins
LiquidCrystal_I2C LCD(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)
char server[] = "www.google.com";    // name address for Google (using DNS)

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192, 168, 0, 177);
IPAddress myDns(192, 168, 0, 1);

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient EthClient;

// Variables to measure the speed
unsigned long beginMicros, endMicros;
unsigned long byteCount = 0;
bool printWebData = true;  // set to false for better speed measurement

void setup() {
  pinMode(Button, INPUT_PULLUP); // Pushbutton
  
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  
  LCD.init(); //initialize the lcd
  LCD.backlight(); //open the backlight 
  
  LCD.clear(); //Clears the LCD screen and positions the cursor in the upper-left  corner.
  LCD.setCursor(0,0); // set the cursor to column 15, line 1
        
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
  if (client.connect(server, 80)) {
    Serial.print("connected to ");
    Serial.println(client.remoteIP());
    // Make a HTTP request:
    client.println("GET /search?q=arduino HTTP/1.1");
    client.println("Host: www.google.com");
    client.println("Connection: close");
    client.println();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
  beginMicros = micros();
}

void loop() {
  // if there are incoming bytes available
  // from the server, read them and print them:
  int len = client.available();
  if (len > 0) {
    byte buffer[80];
    if (len > 80) len = 80;
    client.read(buffer, len);
    if (printWebData) {
      Serial.write(buffer, len); // show in the serial monitor (slows some boards)
    }
    byteCount = byteCount + len;
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    endMicros = micros();
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
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
    if ( digitalRead(btn) == LOW ) { //Button is pressed?
      
    Serial.println("magic prese");
    }
        lcd.setCursor(16,0); // set the cursor to column 15, line 0
        for (int positionCounter1 = 0; positionCounter1 < sizeof(array1); positionCounter1++)
        {
          lcd.scrollDisplayLeft(); //Scrolls the contents of the display one space to the left.
          lcd.print(array1[positionCounter1]); // Print a message to the LCD.
          delay(tim); //wait for 250 microseconds
        }
        lcd.clear(); //Clears the LCD screen and positions the cursor in the upper-left  corner.
        lcd.setCursor(16,1); // set the cursor to column 15, line 1
        for (int positionCounter = 0; positionCounter < sizeof(array1); positionCounter++)
        {
          lcd.scrollDisplayLeft(); //Scrolls the contents of the display one space to the left.
          lcd.print(array2[positionCounter]); // Print a message to the LCD.
          delay(tim); //wait for 250 microseconds
        }
        lcd.clear(); //Clears the LCD screen and positions the cursor in the upper-left corner.
        lcd.setCursor(16,0); // set the cursor to column 15, line 0
        for (int positionCounter1 = 0; positionCounter1 < sizeof(array3); positionCounter1++)
        {
          lcd.scrollDisplayLeft(); //Scrolls the contents of the display one space to the left.
          lcd.print(array3[positionCounter1]); // Print a message to the LCD.
          delay(tim); //wait for 250 microseconds
        }
        lcd.clear(); //Clears the LCD screen and positions the cursor in the upper-left  corner.
    }
}
