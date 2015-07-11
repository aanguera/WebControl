/*
  Web client
 
 This sketch connects to a website (http://www.google.com)
 using an Arduino Wiznet Ethernet shield. 
 
 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 
 created 18 Dec 2009
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe, based on work by Adrian McEwen
 
 */

#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0F, 0x73, 0x03 };
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
IPAddress server(80,32,136,98);  // numeric IP for Google (no DNS)
//char server[] = "www.google.com";    // name address for Google (using DNS)

boolean lastConnected = false;    // state of the connection last time through the main loop
// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192,168,1,177);
int led = 7;
char cLast = '<';  // The character used before
char c = '<';

// Strings for HTTP request
String requestString = "GET /cgi-bin/existeix.pl?nivell=";
String stringRead = "";
String requestStringFinal = "";

// Initialize the Ethernet client library
// with the IP address and port of the server 
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

void setup() {
  // Led configuration
  pinMode(led, OUTPUT);
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
 // httpRequest();
 digitalWrite(led, HIGH);    // turn the LED off by making the voltage LOW

}

void loop()
{
  
  // if there are incoming bytes available 
  // from the server, read them and print them:
  if (client.available()) {
    c = client.read();
    Serial.print(c);
  }
  
  if ( cLast == '>' && c == '1' )
      {
  //      Serial.println("OKOKOKKOKOKOKOKOKOKOKOKOKOKOKOKOKOKOKOKOKO.");
        digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
        delay(500);
      }
      if ( cLast == '>' && c == '0' )
      {
  //      Serial.println("OKOKOKOKOKOKOKOKOKOKOKOKOKOKOKOKOKOKOKOKOKOKOKOKO.");
        digitalWrite(led, LOW);   // turn the LED on (HIGH is the voltage level)
        delay(500);
      }
      cLast = c;    // Update the cLast variable before next comparation

  // if the server's disconnected, stop the client:
  if (!client.connected() && lastConnected) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    // do nothing forevermore:
    //while(true);
  }
  if (!client.connected()) {
    delay(500);
    httpRequest();
  }
  lastConnected = client.connected();
}

void httpRequest() {
  stringRead =  String(analogRead(A0), DEC);
  requestStringFinal = String(requestString + stringRead);
  Serial.println("connecting...");

  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    client.println(requestStringFinal);
    client.println("Host: xibo.inspeguera.cat");
    client.println("Connection: close");
    client.println();
  } 
  else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
    // If conection fail, delay and stop the connection to be ready for a new one
    delay(5000);
    client.stop();
  }
}

