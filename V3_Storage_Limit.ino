#include <BLEDevice.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <WiFi.h>
#include <PubSubClient.h>

#define THRESHOLD 10
const char* ssid = "Sailesh_5G";
const char* password = "Saileash@03";

const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;
const char* mqtt_topic = "tag/status";

WiFiClient espClient;
PubSubClient client(espClient);
int16_t prev_x, prev_y, prev_z; // Initialized to 0 by default
int scanTime = 5;

class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    uint8_t* payload = advertisedDevice.getPayload();
    int length = advertisedDevice.getPayloadLength();
    
    if (length < 20 || payload[8] != 0x16 || payload[9] != 0xE1 || payload[10] != 0xFF) 
      {
        return;
      }
      
    int16_t raw_x = (int16_t)((payload[14] << 8) | payload[15]);
    int16_t raw_y = (int16_t)((payload[16] << 8) | payload[17]);
    int16_t raw_z = (int16_t)((payload[18] << 8) | payload[19]);

    int16_t dx = raw_x - prev_x;
    int16_t dy = raw_y - prev_y;
    int16_t dz = raw_z - prev_z;
    prev_x = raw_x;
    prev_y = raw_y;
    prev_z = raw_z;

    String status = (abs(dx) > THRESHOLD || abs(dy) > THRESHOLD || abs(dz) > THRESHOLD) ? "moving" : "stationary";
    char msg[50];
    snprintf(msg, sizeof(msg), "{\"tag_id\":\"0364\",\"status\":\"%s\"}", status.c_str());

    if (client.connected()) 
     { 
      client.publish(mqtt_topic, msg);
     }
  }
};

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
      {
        delay(500);
        Serial.println("Connecting to WiFi");
      }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  client.setServer(mqtt_server, mqtt_port);
  client.connect("ESP32Client");

  BLEDevice::init("");
  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true);
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP32Client")) {
      Serial.println("connected");
      // Subscribe
      client.subscribe("esp32/output");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void loop() {
  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->start(scanTime, false);
  if (!client.connected()) 
      {
        reconnect();
      }
  client.loop();
  delay(1000);
}
