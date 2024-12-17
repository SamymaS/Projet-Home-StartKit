#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

// Informations WiFi
const char* ssid = "Redmi Note 12";
const char* password = "1235679765";

// Informations du Broker MQTT
const char* mqttServer = "broker.emqx.io";
const int mqttPort = 1883;
const char* mqttUser = "Bonjour";
const char* mqttPassword = "123";

// Pins pour la LED et le ventilateur (fan)
const int ledPin = 12;  // Pin de la LED
const int fanPin1 = 19; // Pin PWM1 pour le ventilateur
const int fanPin2 = 18; // Pin PWM2 pour le ventilateur

WiFiClient espClient;
PubSubClient client(espClient);

// Fonction pour extraire la valeur de "msg" dans le JSON , j'ai essayer le librairie ArdinoJson mais pas moyen
// donc j'ai eu recours au regex pour extraire la valeur

String extractMsg(String payload) {
  int startIdx = payload.indexOf("\"msg\": \"");
  if (startIdx != -1) {
    startIdx += 8; 
    int endIdx = payload.indexOf("\"", startIdx);
    if (endIdx != -1) {
      return payload.substring(startIdx, endIdx); 
    }
  }
  return ""; 
  
}

// Fonction de rappel pour les messages reçus
void callback(char* topic, byte* payload, unsigned int length) {
  String msg = "";
  for (int i = 0; i < length; i++) {
    msg += (char)payload[i];
  }
  Serial.print("Message reçu sur le topic : ");
  Serial.println(topic);
  Serial.print("Message: ");
  Serial.println(msg);  // on affficher le message reçu
  
  // on extraite la valeur de "msg" à partir du payload JSON
  String extractedMsg = extractMsg(msg);
  if (extractedMsg != "") {
    Serial.print("Message extrait: ");
    Serial.println(extractedMsg);
  } else {
    Serial.println("Aucune valeur de 'msg' trouvée.");
  }

  // Contrôle de la LED
  if (String(topic) == "smart_home/lights") {
    if (extractedMsg == "on") {
      digitalWrite(ledPin, HIGH);  // Allumer la LED
      Serial.println("LED allumée");
    }
    else if (extractedMsg == "off") {
      digitalWrite(ledPin, LOW);  // Éteindre la LED
      Serial.println("LED éteinte");
    }
  }

  // Contrôle du ventilateur (fan)
  if (String(topic) == "smart_home/fan") {
    if (extractedMsg == "on") {
      analogWrite(fanPin1, 255);  // on allume le ventilateur à pleine vitesse
      analogWrite(fanPin2, 200);  // on régle la vitesse à 200 (pwm)
      Serial.println("Ventilateur allumé");
    }
    else if (extractedMsg == "off") {
      analogWrite(fanPin1, 0);
      analogWrite(fanPin2, 0);
      Serial.println("Ventilateur éteint");
    }
    else if (extractedMsg == "low") {
      analogWrite(fanPin1, 128);  
      analogWrite(fanPin2, 100);
      Serial.println("Ventilateur à faible vitesse");
    }
    else if (extractedMsg == "medium") {
      analogWrite(fanPin1, 200); 
      analogWrite(fanPin2, 150);
      Serial.println("Ventilateur à vitesse moyenne");
    }
    else if (extractedMsg == "high") {
      analogWrite(fanPin1, 255);
      analogWrite(fanPin2, 210);
      Serial.println("Ventilateur à haute vitesse");
    }
  }
}

// Fonction de connexion au WiFi
void setup_wifi() {
  Serial.print("Connexion au WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connecté au WiFi !");

  // Affichage de l'adresse IP après la connexion WiFi
  Serial.print("Adresse IP de l'ESP32 : ");
  Serial.println(WiFi.localIP());
}

// Fonction de connexion au broker MQTT
void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentative de connexion au broker...");
    if (client.connect("ESP32Client", mqttUser, mqttPassword)) {
      Serial.println("Connecté au broker MQTT !");
      // S'abonner aux topics "smart_home/lights" et "smart_home/fan"
      client.subscribe("smart_home/lights");
      client.subscribe("smart_home/fan");
    } else {
      delay(5000);
      Serial.println("Connexion échouée, nouvelle tentative...");
    }
  }
}

void setup() {
  // Initialiser la communication série
  Serial.begin(115200);

  // Configurer la LED et le ventilateur
  pinMode(ledPin, OUTPUT);
  pinMode(fanPin1, OUTPUT);
  pinMode(fanPin2, OUTPUT);
  analogWrite(fanPin1, 0); 
  analogWrite(fanPin2, 0); 
  digitalWrite(ledPin, LOW);

  // Connexion au WiFi
  setup_wifi();

  // Connexion au broker MQTT
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}