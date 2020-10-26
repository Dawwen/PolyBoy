/*
    This sketch establishes a TCP connection to a "quote of the day" service.
    It sends a "hello" message, and then prints received data.
*/

#include <ESP8266WiFi.h>
#include <TM1637Display.h>

#ifndef STASSID
#define STASSID "Bayrou"
#define STAPSK  "deathnote"
#endif

#define CLK 27
#define DIO 14
#define RAND_PIN 13
#define LED 12

TM1637Display display(CLK, DIO);

const char* ssid     = STASSID;
const char* password = STAPSK;

const char* host = "192.168.43.88";
const uint16_t port = 1234;

void setup() {
  display.setBrightness(0x0f);
  randomSeed(analogRead(RAND_PIN));
  pinMode(LED, OUTPUT);

  Serial.begin(115200);
  Serial.println("TESTETST");

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  
  char rand_key = random(0,256);
  display.showNumberDec(rand_key, false); // Expect: ___0
  
  Serial.print("connecting to ");
  Serial.print(host);
  Serial.print(':');
  Serial.println(port);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    delay(5000);
    return;
  }

  // This will send a string to the server
  Serial.println("sending data to server");
  
  String s = "TEST sokoban 1 10 " + String((int)rand_key);
  if (client.connected()) {
    client.println(s);
  }

  // wait for data to be available
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      delay(60000);
      return;
    }
  }

  // Read all the lines of the reply from server and print them to Serial
  Serial.println("receiving from remote server");
  char c;
  // not testing 'client.connected()' since we do not need to send data here
  while (client.available()) {
    c = static_cast<char>(client.read());
    Serial.print(c);
  }
  Serial.println("\n");
  Serial.println((int)rand_key);
  Serial.println((int)c);
  if (c != rand_key)
  {
    Serial.println("Error on receiving data");  
    digitalWrite(LED, HIGH);
  }
  else
    digitalWrite(LED, LOW);
   
  // Close the connection
  Serial.println();
  Serial.println("closing connection");
  client.stop();

  delay(3000); // execute once every 5 minutes, don't flood remote service
}
