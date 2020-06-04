#include <Adafruit_ST7735.h>
#include "graphics.h"

#define UP_BTN 1
#define ENT_BTN 12
#define DWN_BTN 11

enum hr_min
{
  HOUR,
  MIN
};

int set_alarm(int &hr, int &mn, Adafruit_ST7735 &tft);
