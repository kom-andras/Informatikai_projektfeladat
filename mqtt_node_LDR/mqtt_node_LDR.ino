#include <ArduinoJson.h>
#include <ArduinoJson.hpp>
#include <WiFi.h>
#include <PubSubClient.h>


const char* ssid = "XXX";
const char* password = "XXX";
const char* mqtt_server = "192.168.1.80";

const int ledPin = 2;
const int LDRPin = 34;
const int relayPin1 = 32;
const int relayPin2 = 33;

int ledStateOut = 0;
int relayState1 = 0;
int relayState2 = 0;

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE	(50)
char msg[MSG_BUFFER_SIZE];

void setup_wifi() {

  delay(100);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  StaticJsonDocument<256> doc;
  deserializeJson(doc, payload, length);

  int ledState = doc["led"];
  int relay1State = doc["relay1"];
  int relay2State = doc["relay2"];

  if (ledState == 1) {
    digitalWrite(ledPin, HIGH);
    ledStateOut = 1;
  } else {
    digitalWrite(ledPin, LOW);
    ledStateOut = 0;
  }

  if (relay1State == 1) {
    digitalWrite(relayPin1, LOW);
    relayState1 = 1;
  } else {
    digitalWrite(relayPin1, HIGH);
    relayState1 = 0;
  }

  if (relay2State == 1) {
    digitalWrite(relayPin2, LOW);
    relayState2 = 1;
  } else {
    digitalWrite(relayPin2, HIGH);
    relayState2 = 0;
  }

}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.publish("outTopic", "hello world");
      client.subscribe("esp32/output");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  pinMode(relayPin1, OUTPUT);
  pinMode(relayPin2, OUTPUT);
  digitalWrite(relayPin1, HIGH);
  digitalWrite(relayPin2, HIGH);

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  StaticJsonDocument<128> doc;
  char output[256];

  long now = millis();
  if (now - lastMsg > 5000) {
    lastMsg = now;
    int adat = map(analogRead(LDRPin), 0, 4095, 0, 100);

    doc["LDR"] = adat;
    doc["LedStateOut"] = ledStateOut;
    doc["relay1State"] = relayState1;
    doc["relay2State"] = relayState2;

    Serial.println("Read");

    serializeJson(doc, output);
    Serial.println(output);
    client.publish("/home/esp32", output);
    Serial.println("Sent");
  }
    
}