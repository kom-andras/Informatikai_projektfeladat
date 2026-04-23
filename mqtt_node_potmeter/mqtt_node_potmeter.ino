#include <ArduinoJson.h>
#include <ArduinoJson.hpp>
#include <WiFi.h>
#include <PubSubClient.h>


const char* ssid = "XXX";
const char* password = "XXX";
const char* mqtt_server = "192.168.1.80";

const int potPin = 3;
const int ledPin = 8;
int ledStateOut = 0;

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE	(50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

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
  StaticJsonDocument<32> doc;
  deserializeJson(doc, payload, length);

  int ledState = doc["led2"];

  if (ledState == 1) {
    digitalWrite(ledPin, LOW);
    ledStateOut = 1;
  } else {
   digitalWrite(ledPin, HIGH);
   ledStateOut = 0;
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.publish("outTopic", "hello world");
      client.subscribe("esp32_c3/output");
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
  digitalWrite(ledPin, HIGH);

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  StaticJsonDocument<32> doc;
  char output[55];

  long now = millis();
  if (now - lastMsg > 5000) {
    lastMsg = now;
    int adat = map(analogRead(potPin),0,4095,0,100);

    doc["a"] = adat;
    doc["ledc3"] = ledStateOut;

    Serial.println("Read");

    serializeJson(doc, output);
    Serial.println(output);
    client.publish("/home/esp32_c3", output);
    Serial.println("Sent");
  }
    
}