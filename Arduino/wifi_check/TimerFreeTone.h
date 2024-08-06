#ifndef TimerFreeTone_h
#define TimerFreeTone_h

#include "Arduino.h"

#define _TFT_MAX_VOLUME 10

static const uint8_t _tft_volume[] = {
    255, // 0 - silence (0%)
    191, // 1 - (25%)
    127, // 2 - (50%)
     63, // 3 - (75%)
     31, // 4 - (87.5%)
     15, // 5 - (93.75%)
      7, // 6 - (96.875%)
      3, // 7 - (98.4375%)
      1, // 8 - (99.21875%)
      0, // 9 - (99.609375%)
      0  // 10 - max volume (100%)
};

void TimerFreeTone(uint8_t pin, unsigned long frequency, unsigned int duration, uint8_t volume = 10);

#endif
