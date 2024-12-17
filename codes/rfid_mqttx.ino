/*
 * ESP32 - RFID Access Control with MQTT and LCD
 * Features:
 * - Detect RFID card and read UID.
 * - Send card UID via MQTT.
 * - Display access status on an LCD.
 * - Control a servo to simulate door access.
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ESP32Servo.h>
#include "MFRC522_I2C.h"

// Pin Definitions
#define SERVO_PIN 13
#define BTN_PIN 12
#define I2C_ADDRESS 0x28  // I2C address of MFRC522 (adjust if needed)

// Hardware Setup
MFRC522 mfrc522(I2C_ADDRESS);
LiquidCrystal_I2C lcd(0x27, 16, 2);  // LCD at I2C address 0x27
Servo doorServo;

// WiFi and MQTT Setup
const char* ssid = "Iphone";
const char* password = "12345678";
const char* mqttServer = "broker.emqx.io";
const int mqttPort = 1883;
const char* mqttUser = "Bonjour";
const char* mqttPassword = "123";

WiFiClient espClient;
PubSubClient client(espClient);

String passwordBuffer = "";
boolean doorOpenFlag = false;

// Predefined Authorized Card UID
String authorizedCard = "118182482";  // Change to match your card UID

// Functions
void setup_wifi();
void reconnectMQTT();
void sendMQTTMessage(const char* topic, const char* message);
void ShowReaderDetails();

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  Wire.begin();

  // Initialize MFRC522 RFID module
  mfrc522.PCD_Init();
  ShowReaderDetails();

  // Servo setup
  doorServo.attach(SERVO_PIN);
  doorServo.write(0);  // Close door initially
  pinMode(BTN_PIN, INPUT);

  // WiFi and MQTT setup
  setup_wifi();
  client.setServer(mqttServer, mqttPort);
  reconnectMQTT();

  lcd.setCursor(0, 0);
  lcd.print("Scan your Card");
}

void loop() {
  // Handle MQTT Connection
  if (!client.connected()) {
    reconnectMQTT();
  }
  client.loop();

  // Handle Button to Close Door
  if (doorOpenFlag) {
    if (digitalRead(BTN_PIN) == LOW) {
      Serial.println("Closing Door");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Door Closed");
      doorServo.write(0);
      doorOpenFlag = false;
      delay(1000);
    }
  }

  // RFID Card Detection
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    delay(50);
    return;
  }

  // Read Card UID
  Serial.print("Card UID: ");
  passwordBuffer = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i]);
    passwordBuffer += String(mfrc522.uid.uidByte[i]);
  }

  Serial.print("passwordBuffer : ");
  Serial.println(passwordBuffer);
  
  Serial.print("authorizedCard : ");
  Serial.println(authorizedCard);

  // Check Access
  if (passwordBuffer == authorizedCard) {
    Serial.println("Access Granted");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Access Granted");
    doorServo.write(180);  // Open door
    doorOpenFlag = true;
    sendMQTTMessage("smart_home/access", "Access Granted: Card Authorized");
  } else {
    Serial.println("Access Denied");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Access Denied");
    sendMQTTMessage("smart_home/access", "Access Denied: Card Unauthorized");
  }

  delay(2000);  // Avoid multiple readings
}

// WiFi Connection Function
void setup_wifi() {
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

// MQTT Reconnection Function
void reconnectMQTT() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT Broker...");
    if (client.connect("ESP32Client", mqttUser, mqttPassword)) {
      Serial.println("Connected to MQTT");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" Retrying...");
      delay(5000);
    }
  }
}

// Send Message to MQTT Broker
void sendMQTTMessage(const char* topic, const char* message) {
  if (client.publish(topic, message)) {
    Serial.print("Message sent: ");
    Serial.println(message);
  } else {
    Serial.println("Failed to send MQTT message");
  }
}

// Display RFID Reader Details
void ShowReaderDetails() {
  byte v = mfrc522.PCD_ReadRegister(mfrc522.VersionReg);
  Serial.print("MFRC522 Software Version: 0x");
  Serial.print(v, HEX);
  if (v == 0x91) Serial.println(" = v1.0");
  else if (v == 0x92) Serial.println(" = v2.0");
  else Serial.println(" (unknown)");
}
