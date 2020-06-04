#include "alarm.h"

int set_alarm(int &alarm_hr, int &alarm_mn, Adafruit_ST7735 &tft)
{
	hr_min state = HOUR;
	draw_alarm(alarm_hr, alarm_mn, tft);
  delay(1000);
	while (true)
	{
		switch(state)
		{
			case HOUR: 
				if (digitalRead(UP_BTN) == LOW)
				{
					alarm_hr++;
					if (alarm_hr == 24)
					{
						alarm_hr = 0;
					}
					draw_alarm(alarm_hr, alarm_mn, tft);
				}
				else if (digitalRead(DWN_BTN) == LOW)
				{
					alarm_hr--;
					if (alarm_hr == -1)
					{
						alarm_hr = 23;
					}
					draw_alarm(alarm_hr, alarm_mn, tft);

				}
				else if (digitalRead(ENT_BTN) == LOW)
				{
					state = MIN;
				}
        break;
			case MIN:
				if (digitalRead(UP_BTN) == LOW)
				{
					alarm_mn++;
					if (alarm_mn == 60)
					{
						alarm_mn = 0;
					}
					draw_alarm(alarm_hr, alarm_mn, tft);
				}
				else if (digitalRead(DWN_BTN) == LOW)
				{
					alarm_mn--;
					if (alarm_mn == -1)
					{
						alarm_mn = 59;
					}
					draw_alarm(alarm_hr, alarm_mn, tft);
				}
				else if (digitalRead(ENT_BTN) == LOW)
				{
          clear_alarm(tft);
					return 0;
				}
		}
		delay(500);
	}
}
