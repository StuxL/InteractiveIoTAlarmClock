#include <Adafruit_ST7735.h> // hardware-specific library
#include "retrieve_data.h"

//Draws the current time to top time rectangle
void draw_time(char* Cdate, char* Ctime, Adafruit_ST7735 &tft);

void draw_temp(int temp, Adafruit_ST7735 &tft);

void draw_alarm(int &alarm_hr, int &alarm_min, Adafruit_ST7735 &tft);

void clear_alarm(Adafruit_ST7735 &tft);
