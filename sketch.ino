#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;
const char* topic = "sachin-flood-demo-01/sensor";

WiFiClient espClient;
PubSubClient client(espClient);

const int sensorPin = 34;
const int greenLED = 18;
const int yellowLED = 19;
const int redLED = 21;
const int buzzer = 23;

void connectWiFi() {
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");
}

void reconnectMQTT() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    String clientId = "ESP32-Flood-" + String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("MQTT Connected!");
    } else {
      Serial.print("Failed, state = ");
      Serial.println(client.state());
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(buzzer, OUTPUT);
  analogReadResolution(10);
  connectWiFi();
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) reconnectMQTT();
  client.loop();

  int rawValue = analogRead(sensorPin);
  int level = constrain(map(rawValue, 0, 1023, 0, 100), 0, 100);

  digitalWrite(greenLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(redLED, LOW);
  digitalWrite(buzzer, LOW);

  String status;
  if (level < 40) {
    status = "NORMAL";
    digitalWrite(greenLED, HIGH);
  } else if (level < 70) {
    status = "HIGH";
    digitalWrite(yellowLED, HIGH);
  } else {
    status = "FLOOD ALERT";
    digitalWrite(redLED, HIGH);
    digitalWrite(buzzer, HIGH);
  }

  String payload = "{\"raw\":" + String(rawValue) + ",\"level\":" + String(level) + "}";
  client.publish(topic, payload.c_str());

  Serial.print("Water Level: ");
  Serial.print(level);
  Serial.print("% | Status: ");
  Serial.println(status);
  delay(2000);
}
