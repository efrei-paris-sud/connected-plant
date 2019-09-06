#include <WiFi.h>
#include <PubSubClient.h>

//on définie les informations de connection wifi et serveur
const char* ssid = "wifiPTR";
const char* password = "mdpwifi.";
const char* mqtt_server = "m23.cloudmqtt.com";
#define mqtt_port 18528
#define MQTT_USER "nodemcu"
#define MQTT_PASSWORD "test"


WiFiClient wifiClient;

PubSubClient client(wifiClient);

//connection wifi
void setup_wifi() {
  
    delay(10);
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    //Permet d'initié la connection wifi
    WiFi.begin(ssid, password);
    //Attend que la connexion s'éffectue 
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
}

void reconnect() {

  while (!client.connected()) {
    //défini notre nom sur le serveur
    String clientId = "ESP32";
    //permet d'inité la connectio au serveur MQTT
    if (client.connect(clientId.c_str(),MQTT_USER,MQTT_PASSWORD)) {
      Serial.println("connected");
      //Si on arrive à se connecté on envoi un helloword sur le topic test
      client.publish("/nodemcu/test", "hello world");
    } else {
      //On retry de ce connecté toutes les 5secondes
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(500);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  reconnect();
}

void publishSerialData(char *serialData){//cette fonction publie les données capteur sur le topic humidite_sol
  if (!client.connected()) {
    reconnect();
  }
  client.publish("/nodemcu/humidite_sol", serialData);
}
void loop() {
   client.loop();
   if (Serial.available() > 0) {
     char bfr[501];
     memset(bfr,0, 501);
     Serial.readBytesUntil( '\n',bfr,500);
     publishSerialData(bfr);
   }
 }
