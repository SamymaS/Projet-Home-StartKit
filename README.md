# Projet-Home-StartKit

Ceci est un projet scolaire visant à comprendre les principes de l'Internet des Objets (IoT) en simulant le fonctionnement d'une maison intelligente. Ce projet utilise le kit **Keyestudio Smart Home (KS5009)** pour intégrer divers capteurs et actionneurs, permettant de créer des scénarios réalistes de domotique.

---

## 🚀 Objectifs
1. **Découvrir les bases de l'IoT** : Comprendre comment les capteurs et actionneurs interagissent avec une carte de contrôle.
2. **Simuler des scénarios réels** : Mettre en œuvre des fonctionnalités courantes dans une maison intelligente (éclairage, contrôle de la température, détection de mouvement, etc.).
3. **Apprentissage pratique** : Développer des compétences en électronique, programmation et assemblage de systèmes embarqués.

---

## 🛠️ Composants utilisés
- **Carte microcontrôleur** : ESP32
- **Capteurs** :
  - Capteur PIR (détection de mouvement)
  - Capteur de température et d'humidité (DHT11/DHT22)
  - Capteur de lumière
  - Capteur de gaz
  - Module RFID
  - Capteur de pluie
- **Actionneurs** :
  - LED (blanche, jaune, rouge, etc.)
  - Servo-moteur
  - Écran LCD1602 avec interface I2C
  - Ventilateur (contrôlé par PWM)
  - Buzzer (émission de sons/mélodies)
- **Modules de communication** :
  - Bluetooth (HC-05)
  - WiFi intégré à l'ESP32

---

## 📂 Structure du projet (à faire)
```
Projet-Home-StartKit/
│
├── code/           # Contient tous les fichiers .ino
│   ├──       # Contrôle de la LED
│   ├──       # Contrôle du servo-moteur
│   ├──       # Capteur température et humidité
│   └── ...   # Autres codes pour chaque module
├── libraries/      # Contient les bibliothèques nécessaires
└── README.md       # Documentation du projet
│
├── docs/
│   ├──          # Documentation utilisateur
│   └──          # Scénarios
```

---

## 🚦 Get Started
Pour commencer avec ce projet, suivez les étapes ci-dessous :

1. **Cloner le projet :**
   ```bash
   git clone https://github.com/SamymaS/Projet-Home-StartKit.git
   cd Projet-Home-StartKit

2. **Configurer l'environnement Arduino :**
   ```bash
   - Installez l'IDE Arduino si ce n'est pas déjà fait
   - Ajoutez le support ESP32 dans l'IDE : suivre les étapes dans les fichiers de documentations

3. **Installer les librairies nécessaires :**
    ```bash
    - Allez dans Croquis > Inclure une librairie > Gérer les bibliothèques.
    - Recherchez toutes les librairies nécessaire pour gérer les différents modules et capteurs (voir dossier librairies)

4. **Téléverser un code :**
    ```bash
    - Ouvrir l'un des fichiers .iso dans le répertoire codes/.
    - Sélectionnez la bonne carte ESP32 et le bon port série dans Outils > Type de carte et Outils > Port.
    - Cliquez sur Téléverser pour envoyer le code à la carte.


## 🖥️ Installation des prérequis

1. **Matériel nécessaire :**
    ```bash
    - Un kit Keyestudio Smart Home KS5009.
    - Une carte microcontrôleur ESP32.
    - Une breadboard et des câbles de connexion.
2. **Logiciel nécessaires :**
    ```bash
    - IDE Arduino
    - Git (pour cloner le projet)

3. **Bibliothèques Arduino :**
    ```bash
    - Toutes les librairies sont dans le dossier librairires (via le dropbox)

4. **Connexion des composants :**
    ```bash
    - Suivez les schémas de connexions disponibles dans le dossier documentations 
    

## 🤝 Auteurs
- **Samy Boudaoud** : Développement du code et réalisation des tests
- **Youssouf Abayazid** : Assemblage des composants et montage électronique
- **Fatim Dicko** : Câblage + montage éléctronique

---
