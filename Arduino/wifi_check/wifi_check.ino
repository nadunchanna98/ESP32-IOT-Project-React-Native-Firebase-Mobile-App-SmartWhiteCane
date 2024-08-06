#include <WiFi.h>

// Your Wi-Fi credentials
#define WIFI_SSID "CCC"
#define WIFI_PASSWORD "987654321"

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
}

void loop() {
    // Do nothing
}
