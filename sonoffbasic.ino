#include <Adafruit_MQTT.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const int BUTTON = 0;
const int GREEN = 13;
const int RELAY = 12;
const int SPARE = 14;

const char* ssid = "";
const char* password = "";
const char* mqtt_server = "";
const char* mqtt_user = "";
const char* mqtt_pass = "";
const char* mqtt_id = "";

unsigned long nowtime = millis();

void callback(char* topic, byte* payload, unsigned int length) {

  String strTopic = String((char*) topic);

  Serial.println(strTopic);

  if (strTopic == "lights/lounge") {
    Serial.println("lamp message");
    if ((char)payload[0] == '1') {
      Serial.println("on");
      digitalWrite (RELAY, HIGH);
      digitalWrite (GREEN, LOW);
    } else {
      Serial.println("off");
      digitalWrite (RELAY, LOW);
      digitalWrite (GREEN, HIGH);
    }
  }

}

WiFiClient espClient;
PubSubClient client(mqtt_server, 1883, callback, espClient);

void setup() 
{
  Serial.begin(115200);
  delay(10);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  pinMode(BUTTON, INPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(RELAY, OUTPUT);

  digitalWrite(RELAY, LOW);
  digitalWrite(GREEN, HIGH);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP: ");
  Serial.println(WiFi.localIP());

}

void reconnect() {
  while (!client.connected()) {
    if (client.connect(mqtt_id, mqtt_user, mqtt_pass)) {
      client.subscribe ("lights/lounge");
    } else {
      delay (5000);
    }
  }
}

void loop() 
{
  if (!client.connected()) {
    reconnect();
  }

  client.loop();
    
}
