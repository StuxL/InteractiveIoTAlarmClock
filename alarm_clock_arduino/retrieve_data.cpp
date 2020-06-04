 #include "retrieve_data.h"
#include <ArduinoJson.h>



const size_t time_capacity = 370;
char json_time[time_capacity];
char time_server[] = "worldtimeapi.org";

const size_t weather_capacity = 800;
char json_weather[600];
char weather_server[] = "api.openweathermap.org";

const size_t standing_capacity = 300;
char json_standing[standing_capacity];
char particle_server[] = "api.particle.io";

void retrieve_time(WiFiClient &client, char* Cdate, char* Ctime)
{

  Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via serial:
  if (client.connect(time_server, 80)) {
    Serial.println("connected to server");
    // Make a HTTP request:
    client.println("GET /api/timezone/Australia/Melbourne HTTP/1.1");
    client.println("Host: www.worldtimeapi.org");
    client.println("Connection: close");
    if (client.println() == 0) {
      Serial.println(F("Failed to send request"));
      return;
    }
  }

  // Check HTTP status
  char status[32] = {0};
  client.readBytesUntil('\r', status, sizeof(status));
  if (strcmp(status, "HTTP/1.1 200 OK") != 0) {
    return;
  }

  // Skip HTTP headers
  char endOfHeaders[] = "\r\n\r\n";
  if (!client.find(endOfHeaders)) {
    Serial.println(F("Invalid response"));
    return;
  }

  int i = 0;
  while (client.available()) {
    char c = client.read();
    json_time[i] = c;
    i++;
  }

  DynamicJsonDocument doc(time_capacity);
  
  DeserializationError error = deserializeJson(doc, json_time);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.c_str());
    return;
  }

  // Extract values
  for (int i = 0; i < 10; i++)
  {
    Cdate[i] = doc["datetime"].as<char*>()[i];
  }
  Cdate[10] = '\0';

  for (int i = 0; i < 5; i++)
  {
    Ctime[i] = doc["datetime"].as<char*>()[i + 11];
  }
  Ctime[5] = '\0';

  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting from server.");
    client.stop();
    return;
  }
}

void retrieve_temp(WiFiClient &client, int &temp)
{
  Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via serial:
  if (client.connect(weather_server, 80)) {
    Serial.println("connected to server");
    // Make a HTTP request:
    client.println("GET /data/2.5/weather?id=2158177&appid=9a64a34b6261532550500d5861dc8063&units=metric HTTP/1.1");
    client.println("Host: api.openweathermap.org");
    client.println("Connection: close");
    if (client.println() == 0) {
      Serial.println(F("Failed to send request"));
      return;
    }
  }

  // Check HTTP status
  char status[32] = {0};
  client.readBytesUntil('\r', status, sizeof(status));
  if (strcmp(status, "HTTP/1.1 200 OK") != 0) {
    return;
  }

  // Skip HTTP headers
  char endOfHeaders[] = "\r\n\r\n";
  if (!client.find(endOfHeaders)) {
    Serial.println(F("Invalid response"));
    return;
  }

  int i = 0;
  while (client.available()) {
    char c = client.read();
    json_weather[i] = c;
    i++;
  }

  Serial.println(json_weather);

  DynamicJsonDocument doc(weather_capacity);
  
  DeserializationError error = deserializeJson(doc, json_weather);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.c_str());
    return;
  }

  // Extract values
  temp = doc["main"]["temp"].as<int>();

  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting from server.");
    client.stop();
    return;
  }
}


void retrieve_standing(WiFiSSLClient client, bool &standing, int &standing_time)
{
  Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via serial:
  if (client.connect(particle_server, 443)) {
    Serial.println("connected to server");
    // Make a HTTP request:
    client.println("GET /v1/devices/e00fce6807deccb3d8d5d991/standingup?access_token=999b2341bd40eb2cc8c5fbd404629eb93e7cf023&format=raw HTTP/1.1");
    client.println("Host: api.particle.io");
    client.println("Connection: close");
    client.println();
  }

    

  while(true)
  {  
    // Skip HTTP headers
    char endOfHeaders[] = "\r\n\r\n";
    if (!client.find(endOfHeaders)) {
      //Serial.println(F("Invalid response"));
      continue;
    }
    int i = 0;
    while (client.available()) {
      char c = client.read();
      //Serial.write(c);
      json_standing[i] = c;
      i++;
    }

    DynamicJsonDocument doc(standing_capacity);
    
    DeserializationError error = deserializeJson(doc, json_standing);
    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      return;
    }
//  
//    // Extract values
//    //standing = doc["result"]["standing"].as<bool>();
//    //standing_time = doc["result"]["seconds"].as<int>();
//
    standing = doc["standing"].as<int>();
    standing_time = doc["seconds"].as<int>();

    Serial.println("Standing");
    Serial.println(standing);
    Serial.println("Time");
    Serial.println(standing_time);
  
    // if the server's disconnected, stop the client:
    if (!client.connected()) {
      Serial.println();
      Serial.println("disconnecting from server.");
      client.stop();
  
      // do nothing forevermore:
      return;
    }
  }
}

void time_to_hm(char* Ctime, int &hr, int &mn)
{
  hr = (((Ctime[0] - '0') * 10) + (Ctime[1] - '0'));
  mn = (((Ctime[3] - '0') * 10) + (Ctime[4] - '0'));
}

void hm_to_time(char* Ctime, int hr, int mn)
{
  //free(Ctime);
  Ctime[0] = (byte)((hr / 10) + '0');
  Ctime[1] = (byte)((hr % 10) + '0');
  Ctime[2] = ':';
  Ctime[3] = (byte)((mn / 10) + '0');
  Ctime[4] = (byte)((mn % 10) + '0');
  Ctime[5] = '\0';
}
