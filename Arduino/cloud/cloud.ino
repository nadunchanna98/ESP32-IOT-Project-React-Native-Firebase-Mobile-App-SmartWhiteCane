#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <NewPing.h>
#include "PiezoSpeaker.h"

// Provide the token generation process info.
#include <addons/TokenHelper.h>

// Provide the RTDB payload printing info and other helper functions.
#include <addons/RTDBHelper.h>

// Your Wi-Fi credentials
#define WIFI_SSID "CCC"
#define WIFI_PASSWORD "987654321"

// Your Firebase project credentials
#define API_KEY "AIzaSyBOgjbAMIKzmZV3TN3xFtf1-_KBrenIgF4"
#define DATABASE_URL "https://smart-white-cane-67105-default-rtdb.asia-southeast1.firebasedatabase.app/"  
#define USER_EMAIL "admin0@gmail.com"
#define USER_PASSWORD "12345678"

// Pins
#define HCSR04_PIN_TRIG 13
#define HCSR04_PIN_ECHO 12
#define IRFLAME_PIN_DO 14
#define IROBJAVOID_PIN_OUT 27
#define THINSPEAKER_PIN_POS 26
#define WATERLEVELSENSOR_5V_PIN_SIG 34

// Object initialization
NewPing hcsr04(HCSR04_PIN_TRIG, HCSR04_PIN_ECHO);
PiezoSpeaker thinSpeaker(THINSPEAKER_PIN_POS);
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// Define vars for testing
const int testDelay = 500;  // delay of 0.5 seconds between tests
unsigned long previousMillis = 0;
int testIndex = 1;
int waterLevelIni = 0;
const int waterLevelThreshold = 500;

void setup() {
    Serial.begin(9600);
    while (!Serial); // wait for serial port to connect. Needed for native USB
    Serial.println("start");

    pinMode(IROBJAVOID_PIN_OUT, INPUT);
    pinMode(IRFLAME_PIN_DO, INPUT);  // Set the flame detector DO pin as input
    pinMode(WATERLEVELSENSOR_5V_PIN_SIG, INPUT);  // Set the water level sensor pin as input

    // Connect to Wi-Fi
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(300);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();

    // Initialize Firebase
    config.api_key = API_KEY;
    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASSWORD;
    config.database_url = DATABASE_URL;
    config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h
    Firebase.reconnectNetwork(true);
    fbdo.setBSSLBufferSize(4096 /* Rx buffer size */, 1024 /* Tx buffer size */);
    fbdo.setResponseSize(2048);
    Firebase.begin(&config, &auth);
    Firebase.setDoubleDigits(5);
    config.timeout.serverResponse = 10 * 1000;
}

void loop() {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= testDelay) {
        previousMillis = currentMillis;

        switch (testIndex) {
            case 1:
                
                testFlameDetectionSensor();
                 testWaterLevelSensor();
                testUltrasonicSensor();
            default:
                testIndex = 0;
                break;
        }
        testIndex++;
    }
}

// Test Ultrasonic Sensor
void testUltrasonicSensor() {
    int hcsr04Dist = hcsr04.ping_cm();
    delay(10);
    Serial.print(F("Distance: ")); Serial.print(hcsr04Dist); Serial.println(F(" [cm]"));
    if (hcsr04Dist < 10) {  // Adjusted condition to play beep if distance < 10 cm
        playBeep(1);  // Play Beep 1 if distance 
    } else {
        Serial.println(F("Distance is greater than 10 cm, no beep."));
    }
    // Send data to Firebase
    if (Firebase.RTDB.setInt(&fbdo, "/ultrasonic", hcsr04Dist)) {
        Serial.println("Ultrasonic data sent successfully");
    } else {
        Serial.print("Failed to send ultrasonic data: ");
        Serial.println(fbdo.errorReason());
    }
}

// Test Infrared Flame Detection Sensor
void testFlameDetectionSensor() {
    bool flameDetected = digitalRead(IRFLAME_PIN_DO) == LOW;  // Assuming LOW means flame detected
    Serial.print(F("Flame Detected: ")); Serial.println(flameDetected);
    if (flameDetected) {
        playBeep(3);  // Play Beep 3 if flame is detected
    }
    // Send data to Firebase
    if (Firebase.RTDB.setBool(&fbdo, "/flame", flameDetected)) {
        Serial.println("Flame data sent successfully");
    } else {
        Serial.print("Failed to send flame data: ");
        Serial.println(fbdo.errorReason());
    }
}

// Test Water Level Sensor
void testWaterLevelSensor() {
    int waterLevel = analogRead(WATERLEVELSENSOR_5V_PIN_SIG);
    Serial.print(F("Water Level: ")); Serial.println(waterLevel);
    if (waterLevel > 3000) {
        playBeep(5);  // Play Beep 5 if water level is detected
    }
    // Send data to Firebase
    if (Firebase.RTDB.setInt(&fbdo, "/waterlevel", waterLevel)) {
        Serial.println("Water level data sent successfully");
    } else {
        Serial.print("Failed to send water level data: ");
        Serial.println(fbdo.errorReason());
    }
}

// Function to play the appropriate beep sound
void playBeep(int beepNumber) {
    int duration = 100; // duration of the beep in milliseconds
    int frequency = 1000; // frequency of the beep in Hertz

    if (beepNumber == 1) {
        tone(THINSPEAKER_PIN_POS, frequency, duration);
        delay(200);
    } else if (beepNumber == 2) {
        tone(THINSPEAKER_PIN_POS, frequency, duration);
        delay(100);
        tone(THINSPEAKER_PIN_POS, frequency, duration);
    } else if (beepNumber == 3) {
        for (int i = 0; i < 3; i++) {
            tone(THINSPEAKER_PIN_POS, frequency, duration);
            delay(100);
        }
    } else if (beepNumber == 4) {
        for (int i = 0; i < 4; i++) {
            tone(THINSPEAKER_PIN_POS, frequency, duration);
            delay(100);
        }
    } else if (beepNumber == 5) {
        for (int i = 0; i < 5; i++) {
            tone(THINSPEAKER_PIN_POS, frequency, duration);
            delay(100);
        }
    } else if (beepNumber == 6) {
        for (int i = 0; i < 6; i++) {
            tone(THINSPEAKER_PIN_POS, frequency, duration);
            delay(100);
        }
    }
}
