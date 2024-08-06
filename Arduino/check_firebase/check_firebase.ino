#include <WiFi.h>
#include <Firebase_ESP_Client.h>

// Provide the token generation process info.
#include <addons/TokenHelper.h>

// Provide the RTDB payload printing info and other helper functions.
#include <addons/RTDBHelper.h>

// Your Wi-Fi credentials
#define WIFI_SSID "CCC"
#define WIFI_PASSWORD "987654321"

// Your Firebase project credentials
#define API_KEY "AIzaSyBOgjbAMIKzmZV3TN3xFtf1-_KBrenIgF4"
#define DATABASE_URL "https://smart-white-cane-67105-default-rtdb.asia-southeast1.firebasedatabase.app/"  // e.g. https://your-project-id.firebaseio.com/

#define USER_EMAIL "admin0@gmail.com"
#define USER_PASSWORD "12345678"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;

void setup() {
    Serial.begin(115200);
    delay(10);

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(WIFI_SSID);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        attempts++;
        if (attempts > 20) {  // Try connecting for 10 seconds
            Serial.println("Could not connect to Wi-Fi. Resetting...");
            ESP.restart();  // Reset the ESP32 if it can't connect to Wi-Fi
        }
    }

    Serial.println();
    Serial.println("Wi-Fi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    // Initialize Firebase
    config.api_key = API_KEY;
    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASSWORD;
    config.database_url = DATABASE_URL;

    // Assign the callback function for the long running token generation task
    config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h

    Firebase.reconnectNetwork(true);

    // Set buffer sizes
    fbdo.setBSSLBufferSize(4096, 1024);
    fbdo.setResponseSize(2048);

    Firebase.begin(&config, &auth);
    Firebase.setDoubleDigits(5);
    config.timeout.serverResponse = 10 * 1000;

    Serial.println("Firebase initialized");
}

void loop() {
    // Firebase.ready() should be called repeatedly to handle authentication tasks.
    if (Firebase.ready() && (millis() - sendDataPrevMillis > 2000 || sendDataPrevMillis == 0)) {
        sendDataPrevMillis = millis();
        // Perform Firebase tasks here
        if (Firebase.RTDB.setString(&fbdo, "/test", "Hello World")) {
            Serial.println("Data sent successfully");
        } else {
            Serial.print("Failed to send data: ");
            Serial.println(fbdo.errorReason());
        }
    }
}
