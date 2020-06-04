// SPI Adafruit ST7735 compatible
// TFT_160x128_ST7735
//
// 1.8″ 160×128 TFT Color Display
const int sclk = 9;
const int mosi = 8;
const int cs = 6;
const int dc = 3;
const int rst = 2;

const int UP_BTN = 1;
const int ENT_BTN = 12;
const int DWN_BTN = 11;

#include <Adafruit_GFX.h> // core graphics library
#include <Adafruit_ST7735.h> // hardware-specific library
#include <SPI.h>
#include <WiFi101.h>

#include "melody.h"
#include "arduino_secrets.h"
#include "network_card.h"
#include "retrieve_data.h"
#include "graphics.h"
#include "alarm.h"
 
Adafruit_ST7735 tft = Adafruit_ST7735 (cs, dc, rst);
WiFiClient client;
WiFiSSLClient clientSSL;

char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int status = WL_IDLE_STATUS;     // the WiFi radio's status
char* Cdate;
char* Ctime;
int alarm_act = 0;
int hr = 0;
int mn = 0;
int sec = 0;
int temp = 0;;
int alarm_hr = 0;
int alarm_min = 0;
bool standing = false;
int standing_time = 0;


void setup() {
  Serial.begin (9600); // serial monitor stuff
  tft.initR (INITR_BLACKTAB); // initialize a ST7735S chip, black tab
  pinMode(UP_BTN, INPUT);
  pinMode(ENT_BTN, INPUT);
  pinMode(DWN_BTN, INPUT);
  
  // prepare the TFT
  tft.setTextColor (ST7735_WHITE);
  tft.fillScreen (ST7735_RED);
  
  tft.drawRect (5,35,119,30,ST7735_YELLOW); // upper rectangle
  tft.drawRect (5,70,119,84,ST7735_YELLOW); // lower reactangle

  //Allocate space for date and time
  Cdate = (char*)malloc(11);
  Ctime = (char*)malloc(6);

  //Initalise time panel
  tft.setTextSize (1); // select text size
  tft.setCursor (35, 40);
  tft.println ("2020-01-01");
  tft.setCursor (45, 50);
  tft.println ("00:00");
  tft.setTextSize(2); // set text size back to original


  //Initialise temperature text
  tft.setTextSize(2); // set text size back to original
  tft.setTextColor(ST7735_YELLOW);
  tft.setCursor (10, 75);
  tft.print ("Temp:");
  
  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
  Serial.println("Connected to wifi");
  //printWiFiStatus();

  // you're connected now, so print out the data:
  Serial.print("You're connected to the network");
  printCurrentNet();
  printWiFiData();
  retrieve_time(client, Cdate, Ctime);
  retrieve_temp(client, temp);
  time_to_hm(Ctime, hr, mn);
  draw_time(Cdate, Ctime, tft);
  draw_temp(temp, tft);

 
}

void loop() {
  
  //retrieve_standing(clientSSL, standing, standing_time);
  alarm_act = digitalRead(ENT_BTN);
  if (!alarm_act)
  {
    alarm_act = set_alarm(alarm_hr, alarm_min, tft);
  }

  if (hr == alarm_hr && mn == alarm_min)
  {
    if (!standing || standing_time < 30)
    {
      startMelody();
      retrieve_standing(clientSSL, standing, standing_time); 
    }
  }

  sec++;
  if (sec == 60)
  {
    sec = 0;
    mn++;
    hm_to_time(Ctime, hr, mn);
    draw_time(Cdate, Ctime, tft);
  }

  if (mn == 60)
  {
    mn = 0;
    hr++;
    hm_to_time(Ctime, hr, mn);
    draw_time(Cdate, Ctime, tft);
    retrieve_standing(clientSSL, standing, standing_time);
  }

  if (hr == 24)
  {
    hr = 0;
    hm_to_time(Ctime, hr, mn);
    draw_time(Cdate, Ctime, tft);
  }
  delay(1000);
}
