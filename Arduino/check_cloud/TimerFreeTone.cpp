#include "TimerFreeTone.h"

void TimerFreeTone(uint8_t pin, unsigned long frequency, unsigned int duration, uint8_t volume) {
    if (frequency == 0 || duration == 0 || volume == 0) return; // If frequency, duration, or volume are zero, just return.

    uint32_t duty = frequency / _tft_volume[min(volume, (uint8_t)10) - 1]; // Calculate the duty cycle (volume).

    // Generate the tone for the specified duration.
    unsigned long start = millis();
    while (millis() - start < duration) {
        digitalWrite(pin, HIGH);
        delayMicroseconds(duty);
        digitalWrite(pin, LOW);
        delayMicroseconds(duty);
    }
}
