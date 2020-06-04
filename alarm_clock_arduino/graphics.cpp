#include "graphics.h"

void draw_time(char* Cdate, char* Ctime, Adafruit_ST7735 &tft)
{
	tft.fillRect (15,37,100,26, ST7735_RED);
	tft.setTextColor (ST7735_WHITE);
	tft.setTextSize (1); // select text size
	tft.setCursor (35, 40);
	tft.println (Cdate);
	tft.setCursor (45, 50);
	tft.println (Ctime);
}

void draw_temp(int temp, Adafruit_ST7735 &tft)
{
	//tft.fillRect (15,37,100,26, ST7735_RED);
	tft.setTextColor (ST7735_GREEN);
	tft.setTextSize (2); // select text size
	tft.setCursor (70, 75);
	tft.println (temp);
}

void draw_alarm(int &alarm_hr, int &alarm_min, Adafruit_ST7735 &tft)
{
	char alarm_str[6]; 
	hm_to_time(alarm_str, alarm_hr, alarm_min);
	tft.fillRect (17,107,90,40, ST7735_RED);
	tft.setTextColor (ST7735_GREEN);
	tft.setTextSize (3); // select text size
	tft.setCursor (20, 110);
	tft.println (alarm_str);
}

void clear_alarm(Adafruit_ST7735 &tft)
{
	tft.fillRect (17,107,90,40, ST7735_RED);
}
