// Libraries
#include "Arduino.h"
#include "NewPing.h"
#include "PiezoSpeaker.h"

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

// Define vars for testing
const int testDelay = 500;  // delay of 0.5 seconds between tests
unsigned long previousMillis = 0;
int testIndex = 1;
int waterLevelIni = 0;

// Threshold for water detection (this value may need to be adjusted based on your sensor and setup)
const int waterLevelThreshold = 500;

void setup() {
    Serial.begin(9600);
    while (!Serial); // wait for serial port to connect. Needed for native USB
    Serial.println("start");

    pinMode(IROBJAVOID_PIN_OUT, INPUT);
    pinMode(IRFLAME_PIN_DO, INPUT);  // Set the flame detector DO pin as input
    pinMode(WATERLEVELSENSOR_5V_PIN_SIG, INPUT);  // Set the water level sensor pin as input
}

void loop() {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= testDelay) {
        previousMillis = currentMillis;

        switch (testIndex) {
            case 1:
                testUltrasonicSensor();
                testFlameDetectionSensor();
                testWaterLevelSensor();
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
        playBeep(1);  // Play Beep 1 if distance < 10 cm
    } else {
        Serial.println(F("Distance is greater than 10 cm, no beep."));
    }
}

// Test Infrared Flame Detection Sensor
void testFlameDetectionSensor() {
    bool flameDetected = digitalRead(IRFLAME_PIN_DO) == LOW;  // Assuming LOW means flame detected
    Serial.print(F("Flame Detected: ")); Serial.println(flameDetected);
    if (flameDetected) {
        playBeep(3);  // Play Beep 3 if flame is detected
    }
}

// Test Water Level Sensor
void testWaterLevelSensor() {
    int waterLevel = analogRead(WATERLEVELSENSOR_5V_PIN_SIG);
    Serial.print(F("Water Level: ")); Serial.println(waterLevel);
    if (waterLevel > waterLevelThreshold) {
        playBeep(5);  // Play Beep 5 if water level is detected
    }
}

// Test Thin Speaker
void testThinSpeaker() {
    delay(500);
    playBeep(6);  // Play Beep 6 after melody
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
