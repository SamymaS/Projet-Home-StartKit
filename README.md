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
├── codes/     # Contient tous les fichiers .ino
│   ├──       # Contrôle de la LED
│   ├──       # Contrôle du servo-moteur
│   ├──       # Contrôle du ventilateur
│   ├──       # Capteur température et humidité
│   └── ...   # Autres codes pour chaque module
├── libraries/      # Contient les bibliothèques nécessaires
└── README.md       # Documentation du projet
│
├── documentations/
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
---

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


## TEST réalisés 
Les différents tests réalisés et réussis ci-dessous :
1. **Test bouton poussoir :**
    ```bash
    - état fonctionnel.
    - appui = signal, relâche = non signal ou appui = signal, relâche = signal différent
    - Visualisation du signal avec AnalogWrite
    (Samy)

2. **Test LED :**
    ```bash
    - état fonctionnel
    - délai allumer/éteindre de 1 seconde
    (Samy)

3. **Test ventilateur :**
    ```bash
    - état fonctionnel
    - délai allumer/éteindre de 2 seconde
    (Samy)

4. **Test servo :**
    ```bash
    - état fonctionnel
    - loop + délai de variation de position du servo
    - toutes les 2 secondes la postion du servo varie entre 0 et 180 degré puis de 180 à 0
    (Youssouf)

5. **Test du WIFI :**
    ```bash
    - Configurer le nom PID + mot de passe
    - Se connecter au WIFI distant avec un appareil compatible (téléphone)
    (Fatim)

6. **Test du protocol MQTT :**
    ```bash
    - état fonctionnel
    - Installer la bibliothèque PubSubClient
    - Se connecter au WIFI (connexion à distance sur téléphone)
    - Pouvoir envoyer un message via topic (QOS) pour allumer ou éteindre une LED
    - Idem pour gérer le ventilateur (msg : low, medium, on/off)
    (Yousssouf)

7. **Test du RFID + MQTT:**
    ```bash
    - état fonctionnel
    - UID et condition pour accéder à la maison
    - SI uid est correcte -> servo rotation positive (0->180) (ouvrir porte) + envoyer topic "access granded"
    - SI uid est incorrecte -> servo rotation négative (180->0) (fermer porte) + envoyer topic "access denied"
    (fatim et Youssouf)

8. **Test température et humidité + MQTT:**
    ```bash
    - état fonctionnel
    - afficher température et humidité
    - variation des données en fonction de l'environnement
    - envoyer topic en fonction de la donnée enregistrée
    
## Scénarios réalisés 
Les différents scénarios réalisés et réussis ci-dessous :
1. **Scénario bouton poussoir + allumage LED (interrupteur) :**
    ```bash
    - Etat fonctionnel.
    - Signal ON/OFF, si signal envoyé par appui bouton poussoir -> allumer la LED. Si bouton relâcher -> eteindre LED
    - Si bouton allumer alors faire clignoter la LED pendant 3 secondes avec un delai
    (Samy)

2. **Scénario bouton poussoir + Ventilateur :**
    ```bash
    - Etat fonctionnel.
    - Signal ON/OFF, Allumer le ventilateur a chaque appui
    - bouton 2 change la vitesse du ventilateur lorsque celui-ci est allumé
    - 3 niveaux de vitesses (130, 180 et 230) valeurs PWM.
    (Samy)
3. **Scénario bouton poussoir + Servo (ouvrir la porte de la maison) :**
    ```bash
    - Etat fonctionnel.
    - le servo moteur est relié mécaniquement à une roue cranté relié elle même à une porte
    - Appuyer sur le bouton 1 pour ouvrir la porte, rotation positive (0->180)
    - Appuyer sur le bouton 2 pour fermer la porte, rotation négative (180->0)
    (Youssouf)
4. **Scénario RFID :**
    ```bash
    - Etat fonctionnel.

## 🤝 Auteurs
- **Samy Boudaoud** : Développement du code et réalisation des tests
- **Youssouf Abayazid** : Assemblage des composants et montage électronique
- **Fatim Dicko** : Câblage + montage éléctronique

---
