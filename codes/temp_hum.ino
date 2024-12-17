#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"  // Inclusion de la bibliothèque pour le capteur DHT

// Définition des broches pour le capteur DHT
#define DHTPIN 4         // Broche DATA connectée au GPIO 4
#define DHTTYPE DHT11    // DHT11 ou DHT22 selon le modèle utilisé
DHT dht(DHTPIN, DHTTYPE); // Crée une instance de la classe DHT

// Informations réseau
const char* ssid = "Redmi Note 12";
const char* password = "1235679765";

// Informations du broker MQTT
const char* mqtt_server = "broker.emqx.io";  // Adresse IP de votre broker MQTT
const int mqtt_port = 1883;             // Port MQTT standard
const char* mqtt_topic_temp = "home/temperature";
const char* mqtt_topic_hum = "home/humidity";

// Objet WiFi et MQTT
WiFiClient espClient;
PubSubClient client(espClient);

// Fonction pour se connecter au réseau WiFi
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connexion au réseau WiFi : ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnecté au WiFi !");
  Serial.print("Adresse IP : ");
  Serial.println(WiFi.localIP());
}

// Fonction pour se reconnecter au broker MQTT
void reconnect() {
  while (!client.connected()) {
    Serial.print("Connexion au broker MQTT...");
    if (client.connect("ESP32_Client")) {  // Identifiant client
      Serial.println("Connecté !");
    } else {
      Serial.print("Erreur, rc=");
      Serial.print(client.state());
      Serial.println(" Nouvelle tentative dans 5 secondes...");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);     // Initialise le moniteur série
  dht.begin();              // Initialise le capteur DHT
  setup_wifi();             // Connecte au WiFi
  client.setServer(mqtt_server, mqtt_port);  // Configure le broker MQTT
}

void loop() {
  if (!client.connected()) {
    reconnect();  // Assure la connexion au broker MQTT
  }
  client.loop();

  // Lecture des données du capteur
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Vérifie si les lectures sont valides
  if (isnan(h) || isnan(t)) {
    Serial.println("Erreur de lecture du capteur DHT !");
    return;
  }

  // Affiche les données dans le moniteur série
  Serial.print("Humidité : ");
  Serial.print(h);
  Serial.print("%  Température : ");
  Serial.print(t);
  Serial.println("°C");

  // Convertit les valeurs en chaînes pour MQTT
  char tempString[8];
  char humString[8];
  dtostrf(t, 1, 2, tempString);  // Convertit température en chaîne
  dtostrf(h, 1, 2, humString);   // Convertit humidité en chaîne

  // Publie les données sur les topics MQTT
  client.publish(mqtt_topic_temp, tempString);
  client.publish(mqtt_topic_hum, humString);

  // Pause avant la prochaine lecture
  delay(2000);  // Lecture toutes les 2 secondes
}
